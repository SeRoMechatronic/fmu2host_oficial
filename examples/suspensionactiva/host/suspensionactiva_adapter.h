/**
 * @file   suspensionactiva_adapter.h
 * @brief  Interfaz fmu_t HOST para SuspensionActiva.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef SUSPENSIONACTIVA_ADAPTER_H
#define SUSPENSIONACTIVA_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup suspensionactiva_meta Metadatos del modelo */
/** @{ */
#define SUSPENSIONACTIVA_MODEL_NAME          "SuspensionActiva"
#define SUSPENSIONACTIVA_GUID                "{d502a71c-9992-47e0-952e-c751a997751d}"
#define SUSPENSIONACTIVA_N_STATES            2
#define SUSPENSIONACTIVA_N_EVENT_INDICATORS  3
/** @} */

/** @defgroup suspensionactiva_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define SUSPENSIONACTIVA_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(SUSPENSIONACTIVA_N_STATES)
#define SUSPENSIONACTIVA_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(SUSPENSIONACTIVA_N_STATES)
/** @} */

/** @defgroup suspensionactiva_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define SUSPENSIONACTIVA_VR_PERFIL_BACHE                 7u   /*!< Real, input, continuous, start=0.0 */
#define SUSPENSIONACTIVA_VR_VELOCIDAD_VEHICULO           8u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define SUSPENSIONACTIVA_VR_ACTUADOR_SATURADO            0u   /*!< Boolean, output, discrete */
#define SUSPENSIONACTIVA_VR_BACHE_DETECTADO              1u   /*!< Boolean, output, discrete */
#define SUSPENSIONACTIVA_VR_MODO_CONFORT                 2u   /*!< Boolean, output, discrete */
#define SUSPENSIONACTIVA_VR_FUERZA_ACTUADOR              5u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define SUSPENSIONACTIVA_VR_KD_SUSP                      9u   /*!< Real, parameter, fixed, start=0.8 */
#define SUSPENSIONACTIVA_VR_KP_SUSP                      10u   /*!< Real, parameter, fixed, start=3.0 */
#define SUSPENSIONACTIVA_VR_SAT_ACTUADOR                 11u   /*!< Real, parameter, fixed, start=1.0 */
#define SUSPENSIONACTIVA_VR_TAU_FILTRO                   12u   /*!< Real, parameter, fixed, start=0.1 */
#define SUSPENSIONACTIVA_VR_UMBRAL_BACHE                 13u   /*!< Real, parameter, fixed, start=0.3 */
/** @} */

/** @name Locales */
/** @{ */
#define SUSPENSIONACTIVA_VR_POSICION_FILTRADA            0u   /*!< Real, local, continuous, start=0.0 */
#define SUSPENSIONACTIVA_VR_D_OUTPUTALIAS_ACTUADOR_SATURADO 0u   /*!< Boolean, local, discrete */
#define SUSPENSIONACTIVA_VR_VELOCIDAD_FILTRADA           1u   /*!< Real, local, continuous, start=0.0 */
#define SUSPENSIONACTIVA_VR_D_OUTPUTALIAS_BACHE_DETECTADO 1u   /*!< Boolean, local, discrete */
#define SUSPENSIONACTIVA_VR_DER_POSICION_FILTRADA        2u   /*!< Real, local, continuous */
#define SUSPENSIONACTIVA_VR_D_OUTPUTALIAS_MODO_CONFORT   2u   /*!< Boolean, local, discrete */
#define SUSPENSIONACTIVA_VR_DER_VELOCIDAD_FILTRADA       3u   /*!< Real, local, continuous */
#define SUSPENSIONACTIVA_VR_D_CSE1                       4u   /*!< Real, local, continuous */
#define SUSPENSIONACTIVA_VR_D_OUTPUTALIAS_FUERZA_ACTUADOR 5u   /*!< Real, local, continuous */
#define SUSPENSIONACTIVA_VR_FUERZA_RAW                   6u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para SuspensionActiva.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *suspensionactiva_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para SuspensionActiva.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *suspensionactiva_create_cs(void);

#endif /* SUSPENSIONACTIVA_ADAPTER_H */
