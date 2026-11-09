/**
 * @file   booleanlogica_adapter.h
 * @brief  Interfaz fmu_t HOST para BooleanLogica.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef BOOLEANLOGICA_ADAPTER_H
#define BOOLEANLOGICA_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup booleanlogica_meta Metadatos del modelo */
/** @{ */
#define BOOLEANLOGICA_MODEL_NAME          "BooleanLogica"
#define BOOLEANLOGICA_GUID                "{c2452a7d-230b-4fd7-9fca-37ef7e949ad6}"
#define BOOLEANLOGICA_N_STATES            0
#define BOOLEANLOGICA_N_EVENT_INDICATORS  2
/** @} */

/** @defgroup booleanlogica_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define BOOLEANLOGICA_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(BOOLEANLOGICA_N_STATES)
#define BOOLEANLOGICA_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(BOOLEANLOGICA_N_STATES)
/** @} */

/** @defgroup booleanlogica_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define BOOLEANLOGICA_VR_UMBRAL                          0u   /*!< Real, input, continuous, start=0.0 */
#define BOOLEANLOGICA_VR_A                               1u   /*!< Boolean, input, discrete, start=false */
#define BOOLEANLOGICA_VR_B                               3u   /*!< Boolean, input, discrete, start=false */
#define BOOLEANLOGICA_VR_CLK                             4u   /*!< Boolean, input, discrete, start=false */
/** @} */

/** @name Salidas */
/** @{ */
#define BOOLEANLOGICA_VR_CUENTA_FLANCOS                  0u   /*!< Integer, output, discrete */
#define BOOLEANLOGICA_VR_ABOVE_THRESHOLD                 2u   /*!< Boolean, output, discrete */
#define BOOLEANLOGICA_VR_Y_AND                           6u   /*!< Boolean, output, discrete */
#define BOOLEANLOGICA_VR_Y_LATCH                         7u   /*!< Boolean, output, discrete */
#define BOOLEANLOGICA_VR_Y_OR                            8u   /*!< Boolean, output, discrete */
#define BOOLEANLOGICA_VR_Y_XOR                           9u   /*!< Boolean, output, discrete */
/** @} */

/** @name Locales */
/** @{ */
#define BOOLEANLOGICA_VR_D_OUTPUTALIAS_CUENTA_FLANCOS    0u   /*!< Integer, local, discrete */
#define BOOLEANLOGICA_VR_D_WHENCONDITION1                0u   /*!< Boolean, local, discrete, start=false */
#define BOOLEANLOGICA_VR_FLANCOS                         1u   /*!< Integer, local, discrete, start=0 */
#define BOOLEANLOGICA_VR_D_OUTPUTALIAS_ABOVE_THRESHOLD   2u   /*!< Boolean, local, discrete */
#define BOOLEANLOGICA_VR_LATCH                           5u   /*!< Boolean, local, discrete, start=false */
#define BOOLEANLOGICA_VR_D_OUTPUTALIAS_Y_AND             6u   /*!< Boolean, local, discrete */
#define BOOLEANLOGICA_VR_D_OUTPUTALIAS_Y_LATCH           7u   /*!< Boolean, local, discrete */
#define BOOLEANLOGICA_VR_D_OUTPUTALIAS_Y_OR              8u   /*!< Boolean, local, discrete */
#define BOOLEANLOGICA_VR_D_OUTPUTALIAS_Y_XOR             9u   /*!< Boolean, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para BooleanLogica.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *booleanlogica_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para BooleanLogica.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *booleanlogica_create_cs(void);

#endif /* BOOLEANLOGICA_ADAPTER_H */
