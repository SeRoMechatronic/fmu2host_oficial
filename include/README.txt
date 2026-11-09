================================================================================
  include/ — Headers universales de la librería fmu_t
================================================================================

PROPÓSITO
---------
Estos tres headers son la base de toda la librería. Son autocontenidos,
no dependen de nada externo y funcionan igual en host (x86) y en MCU (ARM, AVR,
RISC-V). Cópialos al proyecto destino o apunta el compilador a esta carpeta.

ARCHIVOS
--------
  fmi2_api.h
    Todos los tipos y typedefs de función del estándar FMI 2.0.
    Consolida fmi2TypesPlatform.h + fmi2FunctionTypes.h del SDK oficial en un
    único header limpio: sin DllExport, sin #pragma pack, sin macros de prefijo.

    Tipos principales:
      fmi2Real            → double (64-bit)
      fmi2Integer         → int (32-bit)
      fmi2Boolean         → int (32-bit, 0=false 1=true)
      fmi2ValueReference  → unsigned int (índice de variable)
      fmi2Component       → void* (handle opaco de la instancia FMU)
      fmi2Status          → enum {fmi2OK, fmi2Warning, fmi2Discard, fmi2Error, fmi2Fatal}
      fmi2CallbackFunctions → struct con logger + allocator (se pasa en Instantiate)
      fmi2EventInfo       → struct de eventos para Model Exchange

    Typedefs de función (para dlsym o extern):
      fmi2InstantiateTYPE, fmi2DoStepTYPE, fmi2GetRealTYPE, etc.

  fmu_t.h
    Interfaz abstracta unificada. Define el struct fmu_t con punteros a función
    que encapsulan cualquier FMU FMI 2.0 con una interfaz polimórfica.

    Tipos propios (independientes del SDK FMI):
      fmu_real_t    → double   (igual que fmi2Real en host)
      fmu_bool_t    → int      (igual que fmi2Boolean)
      fmu_int_t     → int      (igual que fmi2Integer)
      fmu_vref_t    → unsigned int (igual que fmi2ValueReference)
      fmu_tick_t    → uint64_t (ticks de reloj de plataforma)
      fmu_status_t  → enum {FMU_OK, FMU_WARNING, FMU_ERROR, FMU_FATAL}
      fmu_mode_t    → enum {FMU_MODE_CS, FMU_MODE_ME}

    Punteros a función del struct fmu_t:
      initialize        → fmi2EnterInitializationMode + fmi2ExitInitializationMode
      terminate         → fmi2Terminate + fmi2FreeInstance
      reset             → fmi2Reset
      do_step           → fmi2DoStep                  [solo CS]
      set_time          → fmi2SetTime                 [solo ME]
      get_derivatives   → fmi2GetDerivatives          [solo ME]
      get_cont_states   → fmi2GetContinuousStates     [solo ME]
      set_cont_states   → fmi2SetContinuousStates     [solo ME]
      completed_step    → fmi2CompletedIntegratorStep [solo ME]
      get_real/set_real → fmi2GetReal / fmi2SetReal
      get_boolean/set_boolean
      get_integer/set_integer
      get_clock         → función de reloj de plataforma (HAL)

    Macro de conveniencia:
      FMU_CALL(m, fn, ...)  Llama m->fn(m, ...) solo si fn != NULL

  fmu_solver.h
    Solvers numéricos de paso fijo para FMUs en modo Model Exchange.
    Sin malloc: el caller declara el buffer de trabajo como variable estática.

    Macros de tamaño de buffer:
      FMU_EULER_WORK_SIZE(nx)   = nx          (1 array de derivadas)
      FMU_RK4_WORK_SIZE(nx)     = 5 * nx     (k1 k2 k3 k4 x_tmp)

    Funciones:
      fmu_solver_init(s, work, size)           Inicializa el solver con buffer externo
      fmu_euler_step(m, s, x, nx, t, h)       Paso Euler explícito
      fmu_rk4_step  (m, s, x, nx, t, h)       Paso Runge-Kutta orden 4

    Uso típico:
      static fmu_real_t buf[FMU_RK4_WORK_SIZE(2)];  // modelo con 2 estados
      fmu_solver_t solver;
      fmu_solver_init(&solver, buf, FMU_RK4_WORK_SIZE(2));
      fmu_rk4_step(m, &solver, x, 2, t, h);

CÓMO USAR
---------
  En CMakeLists.txt del proyecto destino:
    target_link_libraries(mi_ejecutable PRIVATE fmi)
    (el target fmi ya expone este directorio como include público)

  En código C:
    #include "fmu_t.h"      // siempre
    #include "fmu_solver.h" // si usas ME con solver propio
    #include "fmi2_api.h"   // si accedes a tipos FMI directamente
================================================================================
