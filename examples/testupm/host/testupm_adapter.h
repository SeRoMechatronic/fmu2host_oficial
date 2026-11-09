/**
 * @file   testupm_adapter.h
 * @brief  Interfaz fmu_t HOST para testUPM.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef TESTUPM_ADAPTER_H
#define TESTUPM_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup testupm_meta Metadatos del modelo */
/** @{ */
#define TESTUPM_MODEL_NAME          "testUPM"
#define TESTUPM_GUID                "{f9aef13a-d816-4d5b-a585-267f68f52835}"
#define TESTUPM_N_STATES            0
#define TESTUPM_N_EVENT_INDICATORS  5
/** @} */

/** @defgroup testupm_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define TESTUPM_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(TESTUPM_N_STATES)
#define TESTUPM_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(TESTUPM_N_STATES)
/** @} */

/** @defgroup testupm_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define TESTUPM_VR_POT                                   0u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define TESTUPM_VR_LED1                                  0u   /*!< Boolean, output, discrete */
#define TESTUPM_VR_LED2                                  1u   /*!< Boolean, output, discrete */
#define TESTUPM_VR_LED3                                  2u   /*!< Boolean, output, discrete */
#define TESTUPM_VR_LED4                                  3u   /*!< Boolean, output, discrete */
#define TESTUPM_VR_LED5                                  4u   /*!< Boolean, output, discrete */
/** @} */

/** @name Locales */
/** @{ */
#define TESTUPM_VR_D_OUTPUTALIAS_LED1                    0u   /*!< Boolean, local, discrete */
#define TESTUPM_VR_D_OUTPUTALIAS_LED2                    1u   /*!< Boolean, local, discrete */
#define TESTUPM_VR_D_OUTPUTALIAS_LED3                    2u   /*!< Boolean, local, discrete */
#define TESTUPM_VR_D_OUTPUTALIAS_LED4                    3u   /*!< Boolean, local, discrete */
#define TESTUPM_VR_D_OUTPUTALIAS_LED5                    4u   /*!< Boolean, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para testUPM.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *testupm_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para testUPM.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *testupm_create_cs(void);

#endif /* TESTUPM_ADAPTER_H */
