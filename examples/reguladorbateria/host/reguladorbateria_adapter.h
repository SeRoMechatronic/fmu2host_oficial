/**
 * @file   reguladorbateria_adapter.h
 * @brief  Interfaz fmu_t HOST para ReguladorBateria.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef REGULADORBATERIA_ADAPTER_H
#define REGULADORBATERIA_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup reguladorbateria_meta Metadatos del modelo */
/** @{ */
#define REGULADORBATERIA_MODEL_NAME          "ReguladorBateria"
#define REGULADORBATERIA_GUID                "{69132570-939a-43d4-814a-e9b7801e344c}"
#define REGULADORBATERIA_N_STATES            2
#define REGULADORBATERIA_N_EVENT_INDICATORS  3
/** @} */

/** @defgroup reguladorbateria_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define REGULADORBATERIA_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(REGULADORBATERIA_N_STATES)
#define REGULADORBATERIA_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(REGULADORBATERIA_N_STATES)
/** @} */

/** @defgroup reguladorbateria_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define REGULADORBATERIA_VR_CARGA_CONECTADA              1u   /*!< Boolean, input, discrete, start=false */
#define REGULADORBATERIA_VR_TENSION_BATERIA              9u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define REGULADORBATERIA_VR_CARGA_COMPLETA               0u   /*!< Boolean, output, discrete */
#define REGULADORBATERIA_VR_CARGANDO                     2u   /*!< Boolean, output, discrete */
#define REGULADORBATERIA_VR_FALLO_SOBRETENSION           3u   /*!< Boolean, output, discrete */
#define REGULADORBATERIA_VR_CORRIENTE_CARGA              6u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define REGULADORBATERIA_VR_I_MAX                        10u   /*!< Real, parameter, fixed, start=1.0 */
#define REGULADORBATERIA_VR_KI_AW                        11u   /*!< Real, parameter, fixed, start=0.5 */
#define REGULADORBATERIA_VR_V_CARGA_COMPLETA             12u   /*!< Real, parameter, fixed, start=0.98 */
#define REGULADORBATERIA_VR_V_MAX                        13u   /*!< Real, parameter, fixed, start=0.95 */
#define REGULADORBATERIA_VR_V_NOMINAL                    14u   /*!< Real, parameter, fixed, start=0.75 */
#define REGULADORBATERIA_VR_WN                           15u   /*!< Real, parameter, fixed, start=10.0 */
#define REGULADORBATERIA_VR_ZETA                         16u   /*!< Real, parameter, fixed, start=0.7 */
/** @} */

/** @name Locales */
/** @{ */
#define REGULADORBATERIA_VR_X1                           0u   /*!< Real, local, continuous, start=0.0 */
#define REGULADORBATERIA_VR_D_OUTPUTALIAS_CARGA_COMPLETA 0u   /*!< Boolean, local, discrete */
#define REGULADORBATERIA_VR_X2                           1u   /*!< Real, local, continuous, start=0.0 */
#define REGULADORBATERIA_VR_DER_X1                       2u   /*!< Real, local, continuous */
#define REGULADORBATERIA_VR_D_OUTPUTALIAS_CARGANDO       2u   /*!< Boolean, local, discrete */
#define REGULADORBATERIA_VR_DER_X2                       3u   /*!< Real, local, continuous */
#define REGULADORBATERIA_VR_D_OUTPUTALIAS_FALLO_SOBRETENSION 3u   /*!< Boolean, local, discrete */
#define REGULADORBATERIA_VR_D_CSE1                       4u   /*!< Real, local, continuous */
#define REGULADORBATERIA_VR_AW_ERROR                     5u   /*!< Real, local, continuous */
#define REGULADORBATERIA_VR_D_OUTPUTALIAS_CORRIENTE_CARGA 6u   /*!< Real, local, continuous */
#define REGULADORBATERIA_VR_CORRIENTE_SAT                6u   /*!< Real, local, continuous */
#define REGULADORBATERIA_VR_CORRIENTE_RAW                7u   /*!< Real, local, continuous */
#define REGULADORBATERIA_VR_ERROR_V                      8u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para ReguladorBateria.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *reguladorbateria_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para ReguladorBateria.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *reguladorbateria_create_cs(void);

#endif /* REGULADORBATERIA_ADAPTER_H */
