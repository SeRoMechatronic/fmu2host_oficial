/**
 * @file   tiposmixtos_adapter.h
 * @brief  Interfaz fmu_t HOST para TiposMixtos.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef TIPOSMIXTOS_ADAPTER_H
#define TIPOSMIXTOS_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup tiposmixtos_meta Metadatos del modelo */
/** @{ */
#define TIPOSMIXTOS_MODEL_NAME          "TiposMixtos"
#define TIPOSMIXTOS_GUID                "{d5c6119d-6663-45d8-a27b-93c10193be62}"
#define TIPOSMIXTOS_N_STATES            0
#define TIPOSMIXTOS_N_EVENT_INDICATORS  1
/** @} */

/** @defgroup tiposmixtos_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define TIPOSMIXTOS_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(TIPOSMIXTOS_N_STATES)
#define TIPOSMIXTOS_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(TIPOSMIXTOS_N_STATES)
/** @} */

/** @defgroup tiposmixtos_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define TIPOSMIXTOS_VR_I_IN                              0u   /*!< Integer, input, discrete, start=0 */
#define TIPOSMIXTOS_VR_B_IN                              0u   /*!< Boolean, input, discrete, start=false */
#define TIPOSMIXTOS_VR_R_IN                              1u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define TIPOSMIXTOS_VR_R_ABS                             0u   /*!< Real, output, continuous */
#define TIPOSMIXTOS_VR_I_OUT                             1u   /*!< Integer, output, discrete */
#define TIPOSMIXTOS_VR_B_OUT                             1u   /*!< Boolean, output, discrete */
#define TIPOSMIXTOS_VR_R_OUT                             2u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define TIPOSMIXTOS_VR_ETIQUETA                          0u   /*!< String, parameter, fixed, start=sensor_principal */
#define TIPOSMIXTOS_VR_UNIDAD                            1u   /*!< String, parameter, fixed, start=m/s */
/** @} */

/** @name Locales */
/** @{ */
#define TIPOSMIXTOS_VR_D_OUTPUTALIAS_R_ABS               0u   /*!< Real, local, continuous */
#define TIPOSMIXTOS_VR_D_OUTPUTALIAS_I_OUT               1u   /*!< Integer, local, discrete */
#define TIPOSMIXTOS_VR_D_OUTPUTALIAS_R_OUT               2u   /*!< Real, local, continuous */
#define TIPOSMIXTOS_VR_D_OUTPUTALIAS_B_OUT               2u   /*!< Boolean, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para TiposMixtos.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *tiposmixtos_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para TiposMixtos.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *tiposmixtos_create_cs(void);

#endif /* TIPOSMIXTOS_ADAPTER_H */
