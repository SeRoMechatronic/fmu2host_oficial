/**
 * @file   pendulonolineal_adapter.h
 * @brief  Interfaz fmu_t HOST para PenduloNoLineal.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef PENDULONOLINEAL_ADAPTER_H
#define PENDULONOLINEAL_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup pendulonolineal_meta Metadatos del modelo */
/** @{ */
#define PENDULONOLINEAL_MODEL_NAME          "PenduloNoLineal"
#define PENDULONOLINEAL_GUID                "{7efc0b1a-c4e8-44f3-ad91-6fca093cece0}"
#define PENDULONOLINEAL_N_STATES            2
#define PENDULONOLINEAL_N_EVENT_INDICATORS  1
/** @} */

/** @defgroup pendulonolineal_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define PENDULONOLINEAL_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(PENDULONOLINEAL_N_STATES)
#define PENDULONOLINEAL_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(PENDULONOLINEAL_N_STATES)
/** @} */

/** @defgroup pendulonolineal_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Salidas */
/** @{ */
#define PENDULONOLINEAL_VR_EN_REPOSO                     0u   /*!< Boolean, output, discrete */
#define PENDULONOLINEAL_VR_ANGULO                        6u   /*!< Real, output, continuous */
#define PENDULONOLINEAL_VR_ENERGIA_TOTAL                 7u   /*!< Real, output, continuous */
#define PENDULONOLINEAL_VR_VELOCIDAD_ANGULAR             8u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define PENDULONOLINEAL_VR_L                             9u   /*!< Real, parameter, fixed, start=1.0 */
#define PENDULONOLINEAL_VR_G                             10u   /*!< Real, parameter, fixed, start=9.81 */
/** @} */

/** @name Locales */
/** @{ */
#define PENDULONOLINEAL_VR_OMEGA_P                       0u   /*!< Real, local, continuous, start=0.0 */
#define PENDULONOLINEAL_VR_D_OUTPUTALIAS_VELOCIDAD_ANGULAR 0u   /*!< Real, local, continuous */
#define PENDULONOLINEAL_VR_D_OUTPUTALIAS_EN_REPOSO       0u   /*!< Boolean, local, discrete */
#define PENDULONOLINEAL_VR_THETA                         1u   /*!< Real, local, continuous, start=2.618 */
#define PENDULONOLINEAL_VR_D_OUTPUTALIAS_ANGULO          1u   /*!< Real, local, continuous */
#define PENDULONOLINEAL_VR_DER_OMEGA_P                   2u   /*!< Real, local, continuous */
#define PENDULONOLINEAL_VR_DER_THETA                     3u   /*!< Real, local, continuous */
#define PENDULONOLINEAL_VR_D_CSE1                        4u   /*!< Real, local, continuous */
#define PENDULONOLINEAL_VR_D_CSE2                        5u   /*!< Real, local, continuous */
#define PENDULONOLINEAL_VR_D_OUTPUTALIAS_ENERGIA_TOTAL   7u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para PenduloNoLineal.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *pendulonolineal_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para PenduloNoLineal.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *pendulonolineal_create_cs(void);

#endif /* PENDULONOLINEAL_ADAPTER_H */
