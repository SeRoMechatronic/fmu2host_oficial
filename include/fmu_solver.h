/**
 * fmu_solver.h — Solvers numéricos de paso fijo para FMUs en modo Model Exchange
 *
 * Diseño:
 *   - Sin malloc: el caller declara el buffer de trabajo como variable estática.
 *   - Genérico: funciona con cualquier fmu_t que implemente los punteros ME
 *     (set_time, set_cont_states, get_derivatives, completed_step).
 *   - Intercambiable: fmu_euler_step y fmu_rk4_step tienen la misma firma,
 *     el usuario elige el método en una sola línea.
 *
 * Uso típico (MCU):
 *
 *   // Declarar buffer estático del tamaño correcto para el modelo
 *   static fmu_real_t work[FMU_RK4_WORK_SIZE(RC_FILTER_N_STATES)];
 *
 *   fmu_solver_t solver;
 *   fmu_solver_init(&solver, work, sizeof(work) / sizeof(work[0]));
 *
 *   // En el loop de control (cada h segundos):
 *   fmu_rk4_step(m, &solver, x, nx, t, h);
 *
 * Layout del buffer de trabajo:
 *   Euler → [ dx (nx) ]                                  total = nx
 *   RK4   → [ k1 (nx) | k2 (nx) | k3 (nx) | k4 (nx) | x_tmp (nx) ]
 *                                                         total = 5*nx
 */

#ifndef FMU_SOLVER_H
#define FMU_SOLVER_H

#include "fmu_t.h"

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * Macros para calcular el tamaño del buffer de trabajo
 *
 * Uso:
 *   static fmu_real_t buf[FMU_RK4_WORK_SIZE(MY_MODEL_N_STATES)];
 * ========================================================================= */

#define FMU_EULER_WORK_SIZE(nx)   ((nx))
#define FMU_RK4_WORK_SIZE(nx)     (5 * (nx))

/* =========================================================================
 * Struct del solver — agrupa el buffer y su tamaño
 *
 * No contiene estado numérico propio: el estado del modelo vive en fmu_t
 * o en el vector x[] que gestiona el caller.
 * ========================================================================= */

typedef struct {
    fmu_real_t *work;   /* puntero al buffer de trabajo (propiedad del caller) */
    int         size;   /* número de fmu_real_t que caben en work              */
    /* Callback opcional para re-aplicar las entradas del modelo antes de cada
     * evaluación de derivadas. Necesario para modelos con InputReal cuyo valor
     * debe persistir a través de los set_cont_states/set_time internos del
     * solver (algunos runtimes ME no conservan los inputs entre evaluaciones).
     * Si es NULL, el solver no re-aplica entradas (modelos autónomos). */
    void      (*apply_inputs)(fmu_t *m, void *ctx);
    void       *inputs_ctx;
} fmu_solver_t;

/* =========================================================================
 * Inicialización
 * ========================================================================= */

/**
 * Inicializa el solver con un buffer de trabajo externo.
 *
 * @param s     Puntero al solver a inicializar.
 * @param work  Buffer estático propiedad del caller (no se libera aquí).
 * @param size  Número de fmu_real_t en work (usar FMU_xxx_WORK_SIZE).
 * @return FMU_OK, o FMU_ERROR si work es NULL o size <= 0.
 */
fmu_status_t fmu_solver_init(fmu_solver_t *s, fmu_real_t *work, int size);

/* =========================================================================
 * Euler explícito (RK1)
 *
 *   x(t+h) = x(t) + h · f(x(t), t)
 *
 *   Coste:   1 evaluación de derivada por paso.
 *   Buffer:  FMU_EULER_WORK_SIZE(nx).
 *   Uso:     Sistemas lentos o muy simples; cuando h << tau del sistema.
 * ========================================================================= */

/**
 * Avanza el estado x[] un paso h con el método de Euler explícito.
 *
 * @param m   FMU en modo Model Exchange (mode == FMU_MODE_ME).
 * @param s   Solver inicializado con buffer >= FMU_EULER_WORK_SIZE(nx).
 * @param x   Vector de estado (nx elementos). Modificado en lugar.
 * @param nx  Número de estados continuos.
 * @param t   Tiempo actual (antes del paso).
 * @param h   Tamaño del paso en segundos.
 * @return FMU_OK si el paso se completó correctamente.
 */
fmu_status_t fmu_euler_step(fmu_t *m, fmu_solver_t *s,
                             fmu_real_t *x, int nx,
                             fmu_real_t t, fmu_real_t h);

/* =========================================================================
 * Runge-Kutta de orden 4 (RK4)
 *
 *   k1 = f(x,            t      )
 *   k2 = f(x + h/2·k1,  t + h/2)
 *   k3 = f(x + h/2·k2,  t + h/2)
 *   k4 = f(x + h·k3,    t + h  )
 *   x(t+h) = x(t) + h/6·(k1 + 2·k2 + 2·k3 + k4)
 *
 *   Coste:   4 evaluaciones de derivada por paso.
 *   Buffer:  FMU_RK4_WORK_SIZE(nx).
 *   Uso:     Sistemas con dinámica moderada o rápida; mejor precisión que
 *            Euler sin llegar a la complejidad de métodos adaptativos.
 * ========================================================================= */

/**
 * Avanza el estado x[] un paso h con el método Runge-Kutta de orden 4.
 *
 * @param m   FMU en modo Model Exchange (mode == FMU_MODE_ME).
 * @param s   Solver inicializado con buffer >= FMU_RK4_WORK_SIZE(nx).
 * @param x   Vector de estado (nx elementos). Modificado en lugar.
 * @param nx  Número de estados continuos.
 * @param t   Tiempo actual (antes del paso).
 * @param h   Tamaño del paso en segundos.
 * @return FMU_OK si el paso se completó correctamente.
 */
fmu_status_t fmu_rk4_step(fmu_t *m, fmu_solver_t *s,
                           fmu_real_t *x, int nx,
                           fmu_real_t t, fmu_real_t h);

#ifdef __cplusplus
}
#endif

#endif /* FMU_SOLVER_H */
