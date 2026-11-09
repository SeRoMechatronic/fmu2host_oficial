================================================================================
  tools/ — Herramientas de desarrollo
================================================================================

NOTA: Este archivo documenta fmu_codegen.py, la version MONOLITICA anterior.
La arquitectura actual usa tres herramientas separadas documentadas en README.md:
  fmu_parser.py        Modulo compartido de parsing
  fmu_codegen_host.py  Adapter HOST (PC con runtime OpenModelica)
  fmu_codegen_mcu.py   Adapter MCU (C puro, sin runtime)
fmu_codegen.py se conserva por compatibilidad con proyectos existentes.
================================================================================

PROPOSITO
---------
Scripts Python que automatizan tareas de desarrollo. Solo se ejecutan en el
PC de desarrollo — no se incluyen en el firmware del MCU.

ARCHIVOS
--------
  fmu_codegen.py
    Generador automatico de adaptadores fmu_t desde FMUs FMI 2.0.

    Que hace:
      1. Acepta un archivo .fmu (ZIP) o un directorio ya descomprimido
      2. Si recibe .fmu, lo descomprime automaticamente junto al archivo
      3. Parsea modelDescription.xml con xml.etree.ElementTree (stdlib)
      4. Extrae: nombre, GUID, modo CS/ME, n_estados, n_indicadores_evento,
         herramienta de modelado, y TODAS las variables con sus tipos
      5. Genera 4 archivos en el directorio de salida (ver abajo)

    Tipos FMI soportados:  Real, Integer, Boolean, String
    Modos FMI soportados:  CoSimulation, ModelExchange, ambos
    Herramientas testadas: OpenModelica (FMI 2.0 source-code)

    Los 4 archivos generados:
    ------------------------------------------------------------------
    <modelo>_adapter.h    NO editar — se regenera en cada ejecucion
      - #define UPPER_MODEL_NAME, UPPER_GUID, UPPER_N_STATES, etc.
      - #define UPPER_N_EVENT_INDICATORS
      - #define UPPER_EULER_BUF_SIZE y UPPER_RK4_BUF_SIZE
      - #define UPPER_VR_VARNAME por cada variable (agrupadas por
        causalidad: Entradas, Salidas, Parametros, Locales)
      - declaracion de fmu_t *lower_create(void)

    <modelo>_adapter.c    NO editar — se regenera en cada ejecucion
      - extern de todas las funciones FMI del modelo
      - callbacks (logger, calloc/free para host)
      - struct concreto { fmu_t base; fmi2Component inst; }
      - implementaciones de todos los punteros de fmu_t
        (initialize, terminate, reset, set_time, get_real/set_real,
         enter_event_mode, new_discrete_states, enter_cont_mode, ...)
      - instancia estatica y funcion create()

    CMakeLists.txt        Editar si es necesario — se regenera en cada ejecucion
      - GLOB_RECURSE de los fuentes de la FMU
      - includes detectados automaticamente (fmi/, fmi-export/, etc.)
      - enlace con la libreria fmi (solvers)
      - define FMI2_FUNCTION_PREFIX con el modelIdentifier
      - test de ctest

    main_template.c       RENOMBRAR a main.c — NO se sobreescribe main.c
      - Esqueleto correcto para el tipo de modelo detectado:
          ME discreto (0 estados): set_real + process_events + get_real
          ME con estados:          euler/rk4_step + completed_step + eventos
          CS:                      set_real + do_step + get_real
      - TODO comentados donde el usuario pone su logica:
          * fuente de entradas (ADC, CAN, valor fijo, archivo, etc.)
          * uso de salidas (GPIO, UART, printf, buffer, etc.)
          * parametros de simulacion (t_end, h)

    Estrategia WRAPPING:
      El adapter generado NO reimplementa las ecuaciones del modelo.
      Declara las funciones FMI (Modelo_fmi2GetReal, etc.) como extern
      y las delega directamente. La FMU source tiene toda la logica.

    Uso:
      python tools/fmu_codegen.py <fmu_o_dir> <output_dir>

    Ejemplos:
      # Con .fmu (descomprime automaticamente en fmus_models/MiModelo/)
      python tools/fmu_codegen.py examples/fmus_models/MiModelo.fmu examples/mi_modelo/

      # Con directorio ya descomprimido
      python tools/fmu_codegen.py examples/fmus_models/MiModelo/ examples/mi_modelo/

    Salida por consola (ejemplo real con FMUprueba1):
      [codegen] Parseando .../modelDescription.xml ...
      [codegen] Modelo    : FMUprueba1
      [codegen] Identifier: FMUprueba1
      [codegen] Modo      : ME
      [codegen] Estados   : 0  |  Indicadores evento: 1
      [codegen] Variables : 10
                 vr=  0  input_pot       Real     input  start=0.0
                 vr=  1  output_led      Real     output
                 vr=  2  ...             Real     parameter  start=0.0
                 ...
      [codegen] Generado  : examples/mi_modelo/fmuprueba1_adapter.h
      [codegen] Generado  : examples/mi_modelo/fmuprueba1_adapter.c
      [codegen] Generado  : examples/mi_modelo/CMakeLists.txt
      [codegen] Generado  : examples/mi_modelo/main_template.c

      [codegen] Siguiente paso:
                1. Renombra main_template.c a main.c (si aun no tienes uno)
                2. Rellena los TODO: fuente de entradas, uso de salidas, t_end, h
                3. Compila: cmake --build <build_dir>

    Workflow completo para una FMU nueva:
      1. Exportar FMU con codigo fuente desde OpenModelica/Dymola/Simulink
      2. python tools/fmu_codegen.py MiModelo.fmu examples/mi_modelo/
      3. cd examples/mi_modelo && mv main_template.c main.c
      4. Editar main.c: rellenar los 3 TODO (entrada, salida, parametros)
      5. Anadir add_subdirectory(mi_modelo) en examples/CMakeLists.txt
      6. cmake --build ../../build

    Requisitos:
      - Python >= 3.8
      - Sin dependencias externas (solo stdlib: zipfile, xml.etree, os, sys)

NOTA SOBRE __pycache__
-----------------------
  Python genera __pycache__/ automaticamente al importar o compilar .py.
  Esta ignorado por .gitignore — no aparecera en el repositorio.
  Si aparece localmente, se puede borrar sin problema:
    Windows:  rmdir /s /q tools\__pycache__
    Linux:    rm -rf tools/__pycache__
================================================================================
