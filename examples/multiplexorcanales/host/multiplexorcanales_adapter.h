/**
 * @file   multiplexorcanales_adapter.h
 * @brief  Interfaz fmu_t HOST para MultiplexorCanales.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef MULTIPLEXORCANALES_ADAPTER_H
#define MULTIPLEXORCANALES_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup multiplexorcanales_meta Metadatos del modelo */
/** @{ */
#define MULTIPLEXORCANALES_MODEL_NAME          "MultiplexorCanales"
#define MULTIPLEXORCANALES_GUID                "{dcf0a32f-6203-4553-8a23-9c7afeb44655}"
#define MULTIPLEXORCANALES_N_STATES            0
#define MULTIPLEXORCANALES_N_EVENT_INDICATORS  7
/** @} */

/** @defgroup multiplexorcanales_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define MULTIPLEXORCANALES_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(MULTIPLEXORCANALES_N_STATES)
#define MULTIPLEXORCANALES_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(MULTIPLEXORCANALES_N_STATES)
/** @} */

/** @defgroup multiplexorcanales_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define MULTIPLEXORCANALES_VR_CANAL_0                    0u   /*!< Real, input, continuous, start=0.0 */
#define MULTIPLEXORCANALES_VR_CANAL_1                    1u   /*!< Real, input, continuous, start=0.0 */
#define MULTIPLEXORCANALES_VR_CANAL_SELECCION            1u   /*!< Integer, input, discrete, start=0 */
#define MULTIPLEXORCANALES_VR_CANAL_2                    2u   /*!< Real, input, continuous, start=0.0 */
#define MULTIPLEXORCANALES_VR_CANAL_3                    3u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define MULTIPLEXORCANALES_VR_CANAL_ACTIVO               0u   /*!< Integer, output, discrete */
#define MULTIPLEXORCANALES_VR_CANAL_VALIDO               0u   /*!< Boolean, output, discrete */
#define MULTIPLEXORCANALES_VR_SALIDA                     4u   /*!< Real, output, continuous */
/** @} */

/** @name Locales */
/** @{ */
#define MULTIPLEXORCANALES_VR_D_OUTPUTALIAS_CANAL_ACTIVO 0u   /*!< Integer, local, discrete */
#define MULTIPLEXORCANALES_VR_D_OUTPUTALIAS_CANAL_VALIDO 0u   /*!< Boolean, local, discrete */
#define MULTIPLEXORCANALES_VR_D_OUTPUTALIAS_SALIDA       4u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para MultiplexorCanales.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *multiplexorcanales_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para MultiplexorCanales.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *multiplexorcanales_create_cs(void);

#endif /* MULTIPLEXORCANALES_ADAPTER_H */
