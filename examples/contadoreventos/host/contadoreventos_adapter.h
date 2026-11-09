/**
 * @file   contadoreventos_adapter.h
 * @brief  Interfaz fmu_t HOST para ContadorEventos.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CONTADOREVENTOS_ADAPTER_H
#define CONTADOREVENTOS_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup contadoreventos_meta Metadatos del modelo */
/** @{ */
#define CONTADOREVENTOS_MODEL_NAME          "ContadorEventos"
#define CONTADOREVENTOS_GUID                "{74a5f633-cf1b-4cc7-a4bb-0e6d63cf1bac}"
#define CONTADOREVENTOS_N_STATES            0
#define CONTADOREVENTOS_N_EVENT_INDICATORS  2
/** @} */

/** @defgroup contadoreventos_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define CONTADOREVENTOS_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(CONTADOREVENTOS_N_STATES)
#define CONTADOREVENTOS_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(CONTADOREVENTOS_N_STATES)
/** @} */

/** @defgroup contadoreventos_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define CONTADOREVENTOS_VR_EVENTO                        3u   /*!< Boolean, input, discrete, start=false */
#define CONTADOREVENTOS_VR_RESET                         4u   /*!< Boolean, input, discrete, start=false */
/** @} */

/** @name Salidas */
/** @{ */
#define CONTADOREVENTOS_VR_CUENTA                        1u   /*!< Integer, output, discrete */
#define CONTADOREVENTOS_VR_DECENAS                       2u   /*!< Integer, output, discrete */
#define CONTADOREVENTOS_VR_DESBORDAMIENTO                2u   /*!< Boolean, output, discrete */
#define CONTADOREVENTOS_VR_UNIDADES                      3u   /*!< Integer, output, discrete */
/** @} */

/** @name Locales */
/** @{ */
#define CONTADOREVENTOS_VR_CONTADOR                      0u   /*!< Integer, local, discrete, start=0 */
#define CONTADOREVENTOS_VR_D_WHENCONDITION1              0u   /*!< Boolean, local, discrete, start=false */
#define CONTADOREVENTOS_VR_D_OUTPUTALIAS_CUENTA          1u   /*!< Integer, local, discrete */
#define CONTADOREVENTOS_VR_D_WHENCONDITION2              1u   /*!< Boolean, local, discrete, start=false */
#define CONTADOREVENTOS_VR_D_OUTPUTALIAS_DECENAS         2u   /*!< Integer, local, discrete */
#define CONTADOREVENTOS_VR_D_OUTPUTALIAS_DESBORDAMIENTO  2u   /*!< Boolean, local, discrete */
#define CONTADOREVENTOS_VR_D_OUTPUTALIAS_UNIDADES        3u   /*!< Integer, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para ContadorEventos.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *contadoreventos_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para ContadorEventos.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *contadoreventos_create_cs(void);

#endif /* CONTADOREVENTOS_ADAPTER_H */
