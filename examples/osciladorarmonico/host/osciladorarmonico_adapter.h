/**
 * @file   osciladorarmonico_adapter.h
 * @brief  Interfaz fmu_t HOST para OsciladorArmonico.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef OSCILADORARMONICO_ADAPTER_H
#define OSCILADORARMONICO_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup osciladorarmonico_meta Metadatos del modelo */
/** @{ */
#define OSCILADORARMONICO_MODEL_NAME          "OsciladorArmonico"
#define OSCILADORARMONICO_GUID                "{2a1648f8-ea28-433f-9dc2-5ab39f559706}"
#define OSCILADORARMONICO_N_STATES            2
#define OSCILADORARMONICO_N_EVENT_INDICATORS  0
/** @} */

/** @defgroup osciladorarmonico_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define OSCILADORARMONICO_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(OSCILADORARMONICO_N_STATES)
#define OSCILADORARMONICO_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(OSCILADORARMONICO_N_STATES)
/** @} */

/** @defgroup osciladorarmonico_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Salidas */
/** @{ */
#define OSCILADORARMONICO_VR_ENERGIA                     4u   /*!< Real, output, continuous */
#define OSCILADORARMONICO_VR_POSICION                    5u   /*!< Real, output, continuous */
#define OSCILADORARMONICO_VR_VELOCIDAD                   6u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define OSCILADORARMONICO_VR_OMEGA                       7u   /*!< Real, parameter, fixed, start=6.283185307179586 */
/** @} */

/** @name Locales */
/** @{ */
#define OSCILADORARMONICO_VR_V                           0u   /*!< Real, local, continuous, start=0.0 */
#define OSCILADORARMONICO_VR_D_OUTPUTALIAS_VELOCIDAD     0u   /*!< Real, local, continuous */
#define OSCILADORARMONICO_VR_X                           1u   /*!< Real, local, continuous, start=1.0 */
#define OSCILADORARMONICO_VR_D_OUTPUTALIAS_POSICION      1u   /*!< Real, local, continuous */
#define OSCILADORARMONICO_VR_DER_V                       2u   /*!< Real, local, continuous */
#define OSCILADORARMONICO_VR_DER_X                       3u   /*!< Real, local, continuous */
#define OSCILADORARMONICO_VR_D_OUTPUTALIAS_ENERGIA       4u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para OsciladorArmonico.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *osciladorarmonico_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para OsciladorArmonico.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *osciladorarmonico_create_cs(void);

#endif /* OSCILADORARMONICO_ADAPTER_H */
