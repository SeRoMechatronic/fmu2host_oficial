================================================================================
  src/ — Implementaciones de los solvers numéricos
================================================================================

PROPÓSITO
---------
Código C de los solvers numéricos de paso fijo. Se compilan en la librería
estática `fmi` junto a los headers de include/. Sin malloc, sin dependencias
del sistema operativo: aptos para MCU bare-metal.

ARCHIVOS
--------
  fmu_euler.c
    Solver Euler explícito (Runge-Kutta orden 1).

    Algoritmo:
      dx = f(x, t)            ← get_derivatives de la FMU
      x(t+h) = x(t) + h·dx   ← integración explícita

    Coste por paso:   1 evaluación de derivada
    Buffer necesario: FMU_EULER_WORK_SIZE(nx) = nx elementos
    Cuándo usarlo:    Sistemas lentos, modelos puramente discretos,
                      cuando h << constante de tiempo del sistema.

    También define fmu_solver_init() (compartida con RK4).

  fmu_rk4.c
    Solver Runge-Kutta de orden 4 (el clásico).

    Algoritmo:
      k1 = f(x,          t    )
      k2 = f(x + h/2·k1, t+h/2)
      k3 = f(x + h/2·k2, t+h/2)
      k4 = f(x + h·k3,   t+h  )
      x(t+h) = x(t) + h/6·(k1 + 2·k2 + 2·k3 + k4)

    Coste por paso:   4 evaluaciones de derivada
    Buffer necesario: FMU_RK4_WORK_SIZE(nx) = 5·nx elementos
                        [ k1 | k2 | k3 | k4 | x_tmp ] cada uno de nx floats
    Cuándo usarlo:    Sistemas con dinámica moderada/rápida. Misma h que Euler
                      pero error O(h^5) vs O(h^2): mucho más preciso.

COMPARATIVA EULER vs RK4
-------------------------
  Para un modelo con 2 estados (nx=2) y h=10 ms en un MCU a 100 MHz:

  Solver   Evaluaciones   Buffer (doubles)   Tiempo típico   Error local
  ------   ------------   ----------------   -------------   -----------
  Euler         1              2               ~1 µs          O(h²)
  RK4           4             10               ~4 µs          O(h⁵)

  Conclusión: RK4 cuesta 4x más pero es órdenes de magnitud más preciso.
  Para h=10 ms ambos caben holgadamente en cualquier MCU moderno.

CÓMO SE COMPILAN
----------------
  CMakeLists.txt raíz los incluye en la librería estática `fmi`:

    add_library(fmi STATIC
        src/fmu_euler.c
        src/fmu_rk4.c
    )

  Los ejemplos y el firmware MCU enlazan contra esta librería:

    target_link_libraries(mi_ejemplo PRIVATE fmi)
================================================================================
