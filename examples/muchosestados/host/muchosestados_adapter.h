/**
 * @file   muchosestados_adapter.h
 * @brief  Interfaz fmu_t HOST para MuchosEstados.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef MUCHOSESTADOS_ADAPTER_H
#define MUCHOSESTADOS_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup muchosestados_meta Metadatos del modelo */
/** @{ */
#define MUCHOSESTADOS_MODEL_NAME          "MuchosEstados"
#define MUCHOSESTADOS_GUID                "{c3a45dfb-0863-485d-8cc5-47ecfd93da7d}"
#define MUCHOSESTADOS_N_STATES            8
#define MUCHOSESTADOS_N_EVENT_INDICATORS  1
/** @} */

/** @defgroup muchosestados_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define MUCHOSESTADOS_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(MUCHOSESTADOS_N_STATES)
#define MUCHOSESTADOS_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(MUCHOSESTADOS_N_STATES)
/** @} */

/** @defgroup muchosestados_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define MUCHOSESTADOS_VR_U                               16u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define MUCHOSESTADOS_VR_TODOS_ACTIVOS                   0u   /*!< Boolean, output, discrete */
#define MUCHOSESTADOS_VR_Y1                              17u   /*!< Real, output, continuous */
#define MUCHOSESTADOS_VR_Y2                              18u   /*!< Real, output, continuous */
#define MUCHOSESTADOS_VR_Y3                              19u   /*!< Real, output, continuous */
#define MUCHOSESTADOS_VR_Y4                              20u   /*!< Real, output, continuous */
#define MUCHOSESTADOS_VR_Y5                              21u   /*!< Real, output, continuous */
#define MUCHOSESTADOS_VR_Y6                              22u   /*!< Real, output, continuous */
#define MUCHOSESTADOS_VR_Y7                              23u   /*!< Real, output, continuous */
#define MUCHOSESTADOS_VR_Y8                              24u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define MUCHOSESTADOS_VR_TAU                             25u   /*!< Real, parameter, fixed, start=1.0 */
/** @} */

/** @name Locales */
/** @{ */
#define MUCHOSESTADOS_VR_X1                              0u   /*!< Real, local, continuous, start=0.0 */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_Y1                0u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_TODOS_ACTIVOS     0u   /*!< Boolean, local, discrete */
#define MUCHOSESTADOS_VR_X2                              1u   /*!< Real, local, continuous, start=0.0 */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_Y2                1u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_X3                              2u   /*!< Real, local, continuous, start=0.0 */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_Y3                2u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_X4                              3u   /*!< Real, local, continuous, start=0.0 */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_Y4                3u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_X5                              4u   /*!< Real, local, continuous, start=0.0 */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_Y5                4u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_X6                              5u   /*!< Real, local, continuous, start=0.0 */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_Y6                5u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_X7                              6u   /*!< Real, local, continuous, start=0.0 */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_Y7                6u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_X8                              7u   /*!< Real, local, continuous, start=0.0 */
#define MUCHOSESTADOS_VR_D_OUTPUTALIAS_Y8                7u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_DER_X1                          8u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_DER_X2                          9u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_DER_X3                          10u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_DER_X4                          11u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_DER_X5                          12u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_DER_X6                          13u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_DER_X7                          14u   /*!< Real, local, continuous */
#define MUCHOSESTADOS_VR_DER_X8                          15u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para MuchosEstados.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *muchosestados_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para MuchosEstados.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *muchosestados_create_cs(void);

#endif /* MUCHOSESTADOS_ADAPTER_H */
