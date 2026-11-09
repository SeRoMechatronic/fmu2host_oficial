/**
 * @file   potvumetro_adapter.h
 * @brief  Interfaz fmu_t HOST para PotVumetro.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef POTVUMETRO_ADAPTER_H
#define POTVUMETRO_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup potvumetro_meta Metadatos del modelo */
/** @{ */
#define POTVUMETRO_MODEL_NAME          "PotVumetro"
#define POTVUMETRO_GUID                "{ab7bb8fe-cb29-4aff-b8cc-95d1c27f2d3b}"
#define POTVUMETRO_N_STATES            0
#define POTVUMETRO_N_EVENT_INDICATORS  5
/** @} */

/** @defgroup potvumetro_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define POTVUMETRO_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(POTVUMETRO_N_STATES)
#define POTVUMETRO_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(POTVUMETRO_N_STATES)
/** @} */

/** @defgroup potvumetro_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define POTVUMETRO_VR_POT                                0u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define POTVUMETRO_VR_LED1                               0u   /*!< Boolean, output, discrete */
#define POTVUMETRO_VR_LED2                               1u   /*!< Boolean, output, discrete */
#define POTVUMETRO_VR_LED3                               2u   /*!< Boolean, output, discrete */
#define POTVUMETRO_VR_LED4                               3u   /*!< Boolean, output, discrete */
#define POTVUMETRO_VR_LED5                               4u   /*!< Boolean, output, discrete */
/** @} */

/** @name Locales */
/** @{ */
#define POTVUMETRO_VR_D_OUTPUTALIAS_LED1                 0u   /*!< Boolean, local, discrete */
#define POTVUMETRO_VR_D_OUTPUTALIAS_LED2                 1u   /*!< Boolean, local, discrete */
#define POTVUMETRO_VR_D_OUTPUTALIAS_LED3                 2u   /*!< Boolean, local, discrete */
#define POTVUMETRO_VR_D_OUTPUTALIAS_LED4                 3u   /*!< Boolean, local, discrete */
#define POTVUMETRO_VR_D_OUTPUTALIAS_LED5                 4u   /*!< Boolean, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para PotVumetro.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *potvumetro_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para PotVumetro.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *potvumetro_create_cs(void);

#endif /* POTVUMETRO_ADAPTER_H */
