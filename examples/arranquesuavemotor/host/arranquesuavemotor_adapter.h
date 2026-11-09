/**
 * @file   arranquesuavemotor_adapter.h
 * @brief  Interfaz fmu_t HOST para ArranqueSuaveMotor.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef ARRANQUESUAVEMOTOR_ADAPTER_H
#define ARRANQUESUAVEMOTOR_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup arranquesuavemotor_meta Metadatos del modelo */
/** @{ */
#define ARRANQUESUAVEMOTOR_MODEL_NAME          "ArranqueSuaveMotor"
#define ARRANQUESUAVEMOTOR_GUID                "{9b76140e-9465-4bfc-ae96-7c5a06fa5352}"
#define ARRANQUESUAVEMOTOR_N_STATES            3
#define ARRANQUESUAVEMOTOR_N_EVENT_INDICATORS  4
/** @} */

/** @defgroup arranquesuavemotor_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define ARRANQUESUAVEMOTOR_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(ARRANQUESUAVEMOTOR_N_STATES)
#define ARRANQUESUAVEMOTOR_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(ARRANQUESUAVEMOTOR_N_STATES)
/** @} */

/** @defgroup arranquesuavemotor_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define ARRANQUESUAVEMOTOR_VR_ORDEN_ARRANQUE             3u   /*!< Boolean, input, discrete, start=false */
#define ARRANQUESUAVEMOTOR_VR_CARGA_MOTOR                7u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define ARRANQUESUAVEMOTOR_VR_EN_RAMPA                   0u   /*!< Boolean, output, discrete */
#define ARRANQUESUAVEMOTOR_VR_FALLO_SOBRECARGA           1u   /*!< Boolean, output, discrete */
#define ARRANQUESUAVEMOTOR_VR_MOTOR_EN_MARCHA            2u   /*!< Boolean, output, discrete */
#define ARRANQUESUAVEMOTOR_VR_TENSION_APLICADA           9u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define ARRANQUESUAVEMOTOR_VR_T_RETARDO                  10u   /*!< Real, parameter, fixed, start=2.0 */
#define ARRANQUESUAVEMOTOR_VR_TAU_PT1                    11u   /*!< Real, parameter, fixed, start=0.5 */
#define ARRANQUESUAVEMOTOR_VR_TAU_RAMPA                  12u   /*!< Real, parameter, fixed, start=3.0 */
#define ARRANQUESUAVEMOTOR_VR_UMBRAL_SOBRECARGA          13u   /*!< Real, parameter, fixed, start=0.9 */
/** @} */

/** @name Locales */
/** @{ */
#define ARRANQUESUAVEMOTOR_VR_RAMPA                      0u   /*!< Real, local, continuous, start=0.0 */
#define ARRANQUESUAVEMOTOR_VR_D_OUTPUTALIAS_EN_RAMPA     0u   /*!< Boolean, local, discrete */
#define ARRANQUESUAVEMOTOR_VR_TENSION_FILTRADA           1u   /*!< Real, local, continuous, start=0.0 */
#define ARRANQUESUAVEMOTOR_VR_D_OUTPUTALIAS_FALLO_SOBRECARGA 1u   /*!< Boolean, local, discrete */
#define ARRANQUESUAVEMOTOR_VR_TIEMPO_SOBRECARGA          2u   /*!< Real, local, continuous, start=0.0 */
#define ARRANQUESUAVEMOTOR_VR_D_OUTPUTALIAS_MOTOR_EN_MARCHA 2u   /*!< Boolean, local, discrete */
#define ARRANQUESUAVEMOTOR_VR_DER_RAMPA                  3u   /*!< Real, local, continuous */
#define ARRANQUESUAVEMOTOR_VR_DER_TENSION_FILTRADA       4u   /*!< Real, local, continuous */
#define ARRANQUESUAVEMOTOR_VR_DER_TIEMPO_SOBRECARGA      5u   /*!< Real, local, continuous */
#define ARRANQUESUAVEMOTOR_VR_D_CSE1                     6u   /*!< Real, local, continuous */
#define ARRANQUESUAVEMOTOR_VR_REFERENCIA_RAMPA           8u   /*!< Real, local, continuous */
#define ARRANQUESUAVEMOTOR_VR_D_OUTPUTALIAS_TENSION_APLICADA 9u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para ArranqueSuaveMotor.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *arranquesuavemotor_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para ArranqueSuaveMotor.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *arranquesuavemotor_create_cs(void);

#endif /* ARRANQUESUAVEMOTOR_ADAPTER_H */
