/**
 * @file   sininputs_adapter.h
 * @brief  Interfaz fmu_t HOST para SinInputs.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef SININPUTS_ADAPTER_H
#define SININPUTS_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup sininputs_meta Metadatos del modelo */
/** @{ */
#define SININPUTS_MODEL_NAME          "SinInputs"
#define SININPUTS_GUID                "{37f63974-f08a-453d-90f1-ec44faf2fc2e}"
#define SININPUTS_N_STATES            2
#define SININPUTS_N_EVENT_INDICATORS  0
/** @} */

/** @defgroup sininputs_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define SININPUTS_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(SININPUTS_N_STATES)
#define SININPUTS_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(SININPUTS_N_STATES)
/** @} */

/** @defgroup sininputs_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Salidas */
/** @{ */
#define SININPUTS_VR_ENERGIA                             4u   /*!< Real, output, continuous */
#define SININPUTS_VR_POSICION                            5u   /*!< Real, output, continuous */
#define SININPUTS_VR_VELOCIDAD                           6u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define SININPUTS_VR_AMORTIGUACION                       7u   /*!< Real, parameter, fixed, start=0.3 */
#define SININPUTS_VR_MASA                                8u   /*!< Real, parameter, fixed, start=1.5 */
#define SININPUTS_VR_RIGIDEZ                             9u   /*!< Real, parameter, fixed, start=10.0 */
#define SININPUTS_VR_V0                                  10u   /*!< Real, parameter, fixed, start=0.0 */
#define SININPUTS_VR_X0                                  11u   /*!< Real, parameter, fixed, start=1.0 */
/** @} */

/** @name Locales */
/** @{ */
#define SININPUTS_VR_V                                   0u   /*!< Real, local, continuous, start=0.0 */
#define SININPUTS_VR_D_OUTPUTALIAS_VELOCIDAD             0u   /*!< Real, local, continuous */
#define SININPUTS_VR_X                                   1u   /*!< Real, local, continuous, start=1.0 */
#define SININPUTS_VR_D_OUTPUTALIAS_POSICION              1u   /*!< Real, local, continuous */
#define SININPUTS_VR_DER_V                               2u   /*!< Real, local, continuous */
#define SININPUTS_VR_DER_X                               3u   /*!< Real, local, continuous */
#define SININPUTS_VR_D_OUTPUTALIAS_ENERGIA               4u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para SinInputs.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *sininputs_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para SinInputs.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *sininputs_create_cs(void);

#endif /* SININPUTS_ADAPTER_H */
