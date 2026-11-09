/**
 * @file   frenadoabs_adapter.h
 * @brief  Interfaz fmu_t HOST para FrenadoABS.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef FRENADOABS_ADAPTER_H
#define FRENADOABS_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup frenadoabs_meta Metadatos del modelo */
/** @{ */
#define FRENADOABS_MODEL_NAME          "FrenadoABS"
#define FRENADOABS_GUID                "{46fc3434-2fca-47d6-8ce3-46700e75280c}"
#define FRENADOABS_N_STATES            5
#define FRENADOABS_N_EVENT_INDICATORS  4
/** @} */

/** @defgroup frenadoabs_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define FRENADOABS_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(FRENADOABS_N_STATES)
#define FRENADOABS_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(FRENADOABS_N_STATES)
/** @} */

/** @defgroup frenadoabs_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define FRENADOABS_VR_PRESION_PEDAL                      13u   /*!< Real, input, continuous, start=0.0 */
#define FRENADOABS_VR_VELOCIDAD_RUEDA                    14u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define FRENADOABS_VR_ABS_ACTIVO                         0u   /*!< Boolean, output, discrete */
#define FRENADOABS_VR_FRENADO_NORMAL                     1u   /*!< Boolean, output, discrete */
#define FRENADOABS_VR_RUEDA_BLOQUEADA                    2u   /*!< Boolean, output, discrete */
#define FRENADOABS_VR_PRESION_MODULADA                   12u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define FRENADOABS_VR_P_MAX                              15u   /*!< Real, parameter, fixed, start=1.0 */
#define FRENADOABS_VR_F_MODULACION                       16u   /*!< Real, parameter, fixed, start=10.0 */
#define FRENADOABS_VR_LAMBDA_UMBRAL                      17u   /*!< Real, parameter, fixed, start=0.15 */
#define FRENADOABS_VR_TAU_FILTRO_P                       18u   /*!< Real, parameter, fixed, start=0.08 */
#define FRENADOABS_VR_TAU_FILTRO_V                       19u   /*!< Real, parameter, fixed, start=0.05 */
/** @} */

/** @name Locales */
/** @{ */
#define FRENADOABS_VR_D_OSCILADOR                        0u   /*!< Real, local, continuous, start=1.0 */
#define FRENADOABS_VR_D_OUTPUTALIAS_ABS_ACTIVO           0u   /*!< Boolean, local, discrete */
#define FRENADOABS_VR_DV_FILTRADA                        1u   /*!< Real, local, continuous, start=0.0 */
#define FRENADOABS_VR_D_OUTPUTALIAS_FRENADO_NORMAL       1u   /*!< Boolean, local, discrete */
#define FRENADOABS_VR_OSCILADOR                          2u   /*!< Real, local, continuous, start=0.0 */
#define FRENADOABS_VR_D_OUTPUTALIAS_RUEDA_BLOQUEADA      2u   /*!< Boolean, local, discrete */
#define FRENADOABS_VR_P_FILTRADA                         3u   /*!< Real, local, continuous, start=0.0 */
#define FRENADOABS_VR_V_FILTRADA                         4u   /*!< Real, local, continuous, start=0.0 */
#define FRENADOABS_VR_DER_D_OSCILADOR                    5u   /*!< Real, local, continuous */
#define FRENADOABS_VR_DER_DV_FILTRADA                    6u   /*!< Real, local, continuous */
#define FRENADOABS_VR_DER_OSCILADOR                      7u   /*!< Real, local, continuous */
#define FRENADOABS_VR_DER_P_FILTRADA                     8u   /*!< Real, local, continuous */
#define FRENADOABS_VR_DER_V_FILTRADA                     9u   /*!< Real, local, continuous */
#define FRENADOABS_VR_DV_DT                              10u   /*!< Real, local, continuous */
#define FRENADOABS_VR_LAMBDA                             11u   /*!< Real, local, continuous */
#define FRENADOABS_VR_D_OUTPUTALIAS_PRESION_MODULADA     12u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para FrenadoABS.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *frenadoabs_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para FrenadoABS.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *frenadoabs_create_cs(void);

#endif /* FRENADOABS_ADAPTER_H */
