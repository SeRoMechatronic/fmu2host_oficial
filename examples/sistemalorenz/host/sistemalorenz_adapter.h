/**
 * @file   sistemalorenz_adapter.h
 * @brief  Interfaz fmu_t HOST para SistemaLorenz.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef SISTEMALORENZ_ADAPTER_H
#define SISTEMALORENZ_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup sistemalorenz_meta Metadatos del modelo */
/** @{ */
#define SISTEMALORENZ_MODEL_NAME          "SistemaLorenz"
#define SISTEMALORENZ_GUID                "{e184239f-b020-43fc-8477-5b9da822fb88}"
#define SISTEMALORENZ_N_STATES            3
#define SISTEMALORENZ_N_EVENT_INDICATORS  1
/** @} */

/** @defgroup sistemalorenz_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define SISTEMALORENZ_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(SISTEMALORENZ_N_STATES)
#define SISTEMALORENZ_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(SISTEMALORENZ_N_STATES)
/** @} */

/** @defgroup sistemalorenz_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Salidas */
/** @{ */
#define SISTEMALORENZ_VR_ON_ATTRACTOR                    0u   /*!< Boolean, output, discrete */
#define SISTEMALORENZ_VR_X_OUT                           6u   /*!< Real, output, continuous */
#define SISTEMALORENZ_VR_Y_OUT                           7u   /*!< Real, output, continuous */
#define SISTEMALORENZ_VR_Z_OUT                           8u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define SISTEMALORENZ_VR_BETA                            9u   /*!< Real, parameter, fixed, start=2.6666666666666665 */
#define SISTEMALORENZ_VR_RHO                             10u   /*!< Real, parameter, fixed, start=28.0 */
#define SISTEMALORENZ_VR_SIGMA                           11u   /*!< Real, parameter, fixed, start=10.0 */
/** @} */

/** @name Locales */
/** @{ */
#define SISTEMALORENZ_VR_X                               0u   /*!< Real, local, continuous, start=1.0 */
#define SISTEMALORENZ_VR_D_OUTPUTALIAS_X_OUT             0u   /*!< Real, local, continuous */
#define SISTEMALORENZ_VR_D_OUTPUTALIAS_ON_ATTRACTOR      0u   /*!< Boolean, local, discrete */
#define SISTEMALORENZ_VR_Y                               1u   /*!< Real, local, continuous, start=1.0 */
#define SISTEMALORENZ_VR_D_OUTPUTALIAS_Y_OUT             1u   /*!< Real, local, continuous */
#define SISTEMALORENZ_VR_Z                               2u   /*!< Real, local, continuous, start=1.5 */
#define SISTEMALORENZ_VR_D_OUTPUTALIAS_Z_OUT             2u   /*!< Real, local, continuous */
#define SISTEMALORENZ_VR_DER_X                           3u   /*!< Real, local, continuous */
#define SISTEMALORENZ_VR_DER_Y                           4u   /*!< Real, local, continuous */
#define SISTEMALORENZ_VR_DER_Z                           5u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para SistemaLorenz.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *sistemalorenz_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para SistemaLorenz.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *sistemalorenz_create_cs(void);

#endif /* SISTEMALORENZ_ADAPTER_H */
