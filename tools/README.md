# tools/ — Generadores de codigo FMI/MCU

Este directorio contiene las herramientas de generacion de codigo que
convierten una FMU FMI 2.0 en archivos C listos para compilar en host (PC)
o en un microcontrolador (MCU) sin ningun runtime externo.

---

## Arquitectura

```
tools/
  fmu_parser.py          Modulo compartido: parsing FMU, estructuras de datos,
                         generador del loop de simulacion
  fmu_codegen_host.py    Genera el adapter HOST (PC con runtime OpenModelica)
  fmu_codegen_mcu.py     Genera el adapter MCU (puro C99, sin runtime)
  fmu_codegen.py         Version anterior monolitica (conservada por compatibilidad)
```

`fmu_parser.py` es una libreria, no se ejecuta directamente.
`fmu_codegen_host.py` y `fmu_codegen_mcu.py` son los puntos de entrada.

---

## Uso rapido

### Generar adapter HOST (PC)
```bash
python fmu_codegen_host.py <fmu_dir> examples/<modelo>/host/
```

### Generar adapter MCU (ESP32, STM32, Arduino...)
```bash
python fmu_codegen_mcu.py <fmu_dir> examples/<modelo>/mcu/
```

`<fmu_dir>` puede ser:
- Un directorio ya descomprimido (con `modelDescription.xml`)
- Un archivo `.fmu` (ZIP), que se descomprime automaticamente

### Ejemplo completo: SistemaLorenz
```bash
python fmu_codegen_host.py models/SistemaLorenz examples/sistemalorenz/host/
python fmu_codegen_mcu.py  models/SistemaLorenz examples/sistemalorenz/mcu/
```

Resultado:
```
examples/sistemalorenz/
  host/
    sistemalorenz_adapter.h   Constantes VR_*, declaracion de create()
    sistemalorenz_adapter.c   Wrapper sobre el runtime OpenModelica
    CMakeLists.txt            Target: sistemalorenz_host
    main.c                    Loop de simulacion (stdio directo)
  mcu/
    sistemalorenz_mcu.h       Struct concreto, constantes VR_*
    sistemalorenz_mcu.c       Ecuaciones ODE en C puro, sin runtime
    CMakeLists.txt            Target: sistemalorenz_mcu
    main.c                    Loop de simulacion (TODOs UART para MCU)
```

---

## Que genera cada herramienta

### fmu_codegen_host.py

| Archivo | Se sobreescribe | Descripcion |
|---------|----------------|-------------|
| `_adapter.h` | Siempre | Constantes VR_*, metadatos, declaracion create() |
| `_adapter.c` | Siempre | Wrapper fmu_t sobre runtime OpenModelica |
| `CMakeLists.txt` | Siempre | Target `<modelo>_host`, incluye fuentes FMU |
| `main.c` | Solo si no existe | Loop de simulacion HOST limpio, stdio directo |

**Estrategia**: WRAPPING. El adapter delega todas las llamadas a las
funciones `{ModelIdentifier}_fmi2GetReal`, `fmi2SetReal`, etc. del
runtime de OpenModelica. No reimplementa ecuaciones — es universal.

**Funciona con**: cualquier FMU FMI 2.0 de OpenModelica con fuentes disponibles,
independientemente de la complejidad del modelo (IF, WHEN, DAE, etc.).

### fmu_codegen_mcu.py

| Archivo | Se sobreescribe | Descripcion |
|---------|----------------|-------------|
| `_mcu.h` | Siempre | Struct con estados/parametros, constantes VR_* |
| `_mcu.c` | Siempre | Ecuaciones ODE en C puro, sin runtime |
| `CMakeLists.txt` | Siempre | Target `<modelo>_mcu`, solo 2 archivos .c |
| `main.c` | Solo si no existe | Loop de simulacion MCU limpio, TODOs UART |

**Estrategia**: REIMPLEMENTACION. Parsea los comentarios `SIMPLE_ASSIGN`
del source C de OpenModelica para extraer las ecuaciones ODE e inlinearlas
directamente en C. Requiere math.h pero ninguna otra dependencia.

**Limitaciones**:
- Solo modelos ME con al menos 1 estado continuo
- Solo ecuaciones `SIMPLE_ASSIGN` (ODE puras, sin IF/WHEN complejos)
- Solo estados de tipo `Real`

---

## El loop de simulacion (compartido)

Ambos `main.c` generados son estructuralmente identicos. La unica
diferencia esta en los includes y las macros `SIM_PRINT/SIM_DELAY/SIM_ERROR`:

**HOST `main.c`**:
```c
#include <stdio.h>
#include "sistemalorenz_adapter.h"
#define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)
// ...
fmu_t *m = sistemalorenz_create();
```

**MCU `main.c`**:
```c
#include "sistemalorenz_mcu.h"
// TODO: incluir headers de tu MCU
#ifdef MCU_STDIO_OUTPUT          // activo en CMake para test en host
#  define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#  define SIM_PRINT(fmt, ...)  /* TODO: uart_printf(...) */
#endif
// ...
fmu_t *m = sistemalorenz_mcu_create();
```

El loop del simulacion en si — `process_events()`, integracion Euler,
lectura de salidas — es generado por `generate_sim_loop()` en `fmu_parser.py`
y es identico para ambas plataformas.

---

## Verificacion numerica (MCU vs HOST)

El CMakeLists.txt MCU define `MCU_STDIO_OUTPUT` para que el ejecutable
de test en host produzca salida. Esto permite comparar directamente:

```bash
# Compilar ambos targets
cmake --build build --target sistemalorenz_host
cmake --build build --target sistemalorenz_mcu

# Ejecutar y comparar
./build/examples/sistemalorenz/host/Release/sistemalorenz_host.exe > host.txt
./build/examples/sistemalorenz/mcu/Release/sistemalorenz_mcu.exe  > mcu.txt
diff host.txt mcu.txt    # debe ser vacio: resultados bit-a-bit identicos
```

O con CTest:
```bash
ctest -C Release -R "sistemalorenz"
# sistemalorenz_host  Passed
# sistemalorenz_mcu   Passed
```

---

## Portar al MCU real

Para correr en un MCU real (ESP32, STM32, Arduino, etc.):

1. Copia estos 6 archivos a tu proyecto MCU:
   ```
   mcu/main.c
   mcu/<modelo>_mcu.h
   mcu/<modelo>_mcu.c
   include/fmu_t.h
   include/fmu_solver.h
   src/fmu_euler.c        (o fmu_rk4.c si prefieres RK4)
   ```

2. En `main.c`, reemplaza las macros TODO con las funciones de tu plataforma:
   ```c
   // Arduino/ESP32:
   #define SIM_PRINT(fmt, ...)  Serial.printf(fmt, ##__VA_ARGS__)
   #define SIM_DELAY(h)         delay((uint32_t)((h) * 1000U))
   #define SIM_ERROR(msg)       Serial.print(msg)

   // STM32 HAL:
   #define SIM_PRINT(fmt, ...)  uart_printf(fmt, ##__VA_ARGS__)
   #define SIM_DELAY(h)         HAL_Delay((uint32_t)((h) * 1000U))
   #define SIM_ERROR(msg)       uart_puts(msg)
   ```

3. Compila con tu toolchain MCU (sin OpenModelica ni ninguna DLL).

---

## fmu_parser.py — API publica

Para integracion con otras herramientas:

```python
from fmu_parser import parse_fmu, extract_fmu, FMUInfo, Variable

# Parsear una FMU
fmu_dir = extract_fmu("mi_modelo.fmu")   # descomprime si es ZIP
info = parse_fmu(fmu_dir)                # lee modelDescription.xml

print(info.model_name)    # "SistemaLorenz"
print(info.n_states)      # 3
print(info.has_me)        # True

for v in info.vars_of_causality("output"):
    print(f"  vr={v.vr}  {v.name}  ({v.type_})")
```
