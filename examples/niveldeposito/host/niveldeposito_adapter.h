/**
 * @file   niveldeposito_adapter.h
 * @brief  Interfaz fmu_t HOST para NivelDeposito.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef NIVELDEPOSITO_ADAPTER_H
#define NIVELDEPOSITO_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup niveldeposito_meta Metadatos del modelo */
/** @{ */
#define NIVELDEPOSITO_MODEL_NAME          "NivelDeposito"
#define NIVELDEPOSITO_GUID                "{654cd5a4-778a-4ee4-be67-8cfa8b991df8}"
#define NIVELDEPOSITO_N_STATES            1
#define NIVELDEPOSITO_N_EVENT_INDICATORS  3
/** @} */

/** @defgroup niveldeposito_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define NIVELDEPOSITO_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(NIVELDEPOSITO_N_STATES)
#define NIVELDEPOSITO_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(NIVELDEPOSITO_N_STATES)
/** @} */

/** @defgroup niveldeposito_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define NIVELDEPOSITO_VR_VALVULA_MANUAL                  3u   /*!< Boolean, input, discrete, start=false */
#define NIVELDEPOSITO_VR_SENSOR_NIVEL                    6u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define NIVELDEPOSITO_VR_ALARMA_MAXIMO                   0u   /*!< Boolean, output, discrete */
#define NIVELDEPOSITO_VR_ALARMA_MINIMO                   1u   /*!< Boolean, output, discrete */
#define NIVELDEPOSITO_VR_BOMBA_ACTIVA                    2u   /*!< Boolean, output, discrete */
#define NIVELDEPOSITO_VR_BOMBA                           4u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define NIVELDEPOSITO_VR_Q_BOMBA_MAX                     7u   /*!< Real, parameter, fixed, start=0.5 */
#define NIVELDEPOSITO_VR_Q_VALVULA                       8u   /*!< Real, parameter, fixed, start=0.3 */
#define NIVELDEPOSITO_VR_AREA                            9u   /*!< Real, parameter, fixed, start=1.0 */
#define NIVELDEPOSITO_VR_NIVEL_MAX                       10u   /*!< Real, parameter, fixed, start=0.8 */
#define NIVELDEPOSITO_VR_NIVEL_MIN                       11u   /*!< Real, parameter, fixed, start=0.2 */
/** @} */

/** @name Locales */
/** @{ */
#define NIVELDEPOSITO_VR_NIVEL_FILTRADO                  0u   /*!< Real, local, continuous, start=0.5 */
#define NIVELDEPOSITO_VR_D_OUTPUTALIAS_ALARMA_MAXIMO     0u   /*!< Boolean, local, discrete */
#define NIVELDEPOSITO_VR_DER_NIVEL_FILTRADO              1u   /*!< Real, local, continuous */
#define NIVELDEPOSITO_VR_D_OUTPUTALIAS_ALARMA_MINIMO     1u   /*!< Boolean, local, discrete */
#define NIVELDEPOSITO_VR_D_CSE1                          2u   /*!< Real, local, continuous */
#define NIVELDEPOSITO_VR_D_OUTPUTALIAS_BOMBA_ACTIVA      2u   /*!< Boolean, local, discrete */
#define NIVELDEPOSITO_VR_Q_SALIDA                        3u   /*!< Real, local, continuous */
#define NIVELDEPOSITO_VR_D_OUTPUTALIAS_BOMBA             4u   /*!< Real, local, continuous */
#define NIVELDEPOSITO_VR_ERROR_NIVEL                     5u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para NivelDeposito.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *niveldeposito_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para NivelDeposito.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *niveldeposito_create_cs(void);

#endif /* NIVELDEPOSITO_ADAPTER_H */
