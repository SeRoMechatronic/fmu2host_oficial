/**
 * @file   valoresextremos_adapter.h
 * @brief  Interfaz fmu_t HOST para ValoresExtremos.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef VALORESEXTREMOS_ADAPTER_H
#define VALORESEXTREMOS_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup valoresextremos_meta Metadatos del modelo */
/** @{ */
#define VALORESEXTREMOS_MODEL_NAME          "ValoresExtremos"
#define VALORESEXTREMOS_GUID                "{4c9968b8-d207-48b0-8a5a-5fb81577d374}"
#define VALORESEXTREMOS_N_STATES            0
#define VALORESEXTREMOS_N_EVENT_INDICATORS  4
/** @} */

/** @defgroup valoresextremos_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define VALORESEXTREMOS_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(VALORESEXTREMOS_N_STATES)
#define VALORESEXTREMOS_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(VALORESEXTREMOS_N_STATES)
/** @} */

/** @defgroup valoresextremos_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define VALORESEXTREMOS_VR_U                             1u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define VALORESEXTREMOS_VR_ES_FINITO                     0u   /*!< Boolean, output, discrete */
#define VALORESEXTREMOS_VR_Y_INV                         2u   /*!< Real, output, continuous */
#define VALORESEXTREMOS_VR_Y_LOG                         3u   /*!< Real, output, continuous */
#define VALORESEXTREMOS_VR_Y_SAT                         4u   /*!< Real, output, continuous */
#define VALORESEXTREMOS_VR_Y_SQRT                        5u   /*!< Real, output, continuous */
/** @} */

/** @name Locales */
/** @{ */
#define VALORESEXTREMOS_VR_D_CSE1                        0u   /*!< Real, local, continuous */
#define VALORESEXTREMOS_VR_D_OUTPUTALIAS_ES_FINITO       0u   /*!< Boolean, local, discrete */
#define VALORESEXTREMOS_VR_D_OUTPUTALIAS_Y_INV           2u   /*!< Real, local, continuous */
#define VALORESEXTREMOS_VR_D_OUTPUTALIAS_Y_LOG           3u   /*!< Real, local, continuous */
#define VALORESEXTREMOS_VR_D_OUTPUTALIAS_Y_SAT           4u   /*!< Real, local, continuous */
#define VALORESEXTREMOS_VR_D_OUTPUTALIAS_Y_SQRT          5u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para ValoresExtremos.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *valoresextremos_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para ValoresExtremos.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *valoresextremos_create_cs(void);

#endif /* VALORESEXTREMOS_ADAPTER_H */
