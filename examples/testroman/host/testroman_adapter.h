/**
 * @file   testroman_adapter.h
 * @brief  Interfaz fmu_t HOST para testROMAN.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef TESTROMAN_ADAPTER_H
#define TESTROMAN_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup testroman_meta Metadatos del modelo */
/** @{ */
#define TESTROMAN_MODEL_NAME          "testROMAN"
#define TESTROMAN_GUID                "{671fe98f-565f-4384-a7a9-879683f50f40}"
#define TESTROMAN_N_STATES            0
#define TESTROMAN_N_EVENT_INDICATORS  5
/** @} */

/** @defgroup testroman_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define TESTROMAN_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(TESTROMAN_N_STATES)
#define TESTROMAN_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(TESTROMAN_N_STATES)
/** @} */

/** @defgroup testroman_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define TESTROMAN_VR_POT                                 0u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define TESTROMAN_VR_LED1                                0u   /*!< Boolean, output, discrete */
#define TESTROMAN_VR_LED2                                1u   /*!< Boolean, output, discrete */
#define TESTROMAN_VR_LED3                                2u   /*!< Boolean, output, discrete */
#define TESTROMAN_VR_LED4                                3u   /*!< Boolean, output, discrete */
#define TESTROMAN_VR_LED5                                4u   /*!< Boolean, output, discrete */
/** @} */

/** @name Locales */
/** @{ */
#define TESTROMAN_VR_D_OUTPUTALIAS_LED1                  0u   /*!< Boolean, local, discrete */
#define TESTROMAN_VR_D_OUTPUTALIAS_LED2                  1u   /*!< Boolean, local, discrete */
#define TESTROMAN_VR_D_OUTPUTALIAS_LED3                  2u   /*!< Boolean, local, discrete */
#define TESTROMAN_VR_D_OUTPUTALIAS_LED4                  3u   /*!< Boolean, local, discrete */
#define TESTROMAN_VR_D_OUTPUTALIAS_LED5                  4u   /*!< Boolean, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para testROMAN.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *testroman_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para testROMAN.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *testroman_create_cs(void);

#endif /* TESTROMAN_ADAPTER_H */
