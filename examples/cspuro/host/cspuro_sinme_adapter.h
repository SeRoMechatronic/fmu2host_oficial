/**
 * @file   cspuro_sinme_adapter.h
 * @brief  Interfaz fmu_t HOST para CSPuro_SinME.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CSPURO_SINME_ADAPTER_H
#define CSPURO_SINME_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup cspuro_sinme_meta Metadatos del modelo */
/** @{ */
#define CSPURO_SINME_MODEL_NAME          "CSPuro_SinME"
#define CSPURO_SINME_GUID                "{79540962-4d5c-427a-9da9-96325a54c165}"
#define CSPURO_SINME_N_STATES            0
#define CSPURO_SINME_N_EVENT_INDICATORS  1
/** @} */

/** @defgroup cspuro_sinme_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define CSPURO_SINME_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(CSPURO_SINME_N_STATES)
#define CSPURO_SINME_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(CSPURO_SINME_N_STATES)
/** @} */

/** @defgroup cspuro_sinme_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define CSPURO_SINME_VR_U1                               0u   /*!< Real, input, continuous, start=0.0 */
#define CSPURO_SINME_VR_U2                               1u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define CSPURO_SINME_VR_ACTIVE                           0u   /*!< Boolean, output, discrete */
#define CSPURO_SINME_VR_Y_PROD                           2u   /*!< Real, output, continuous */
#define CSPURO_SINME_VR_Y_SUM                            3u   /*!< Real, output, continuous */
/** @} */

/** @name Locales */
/** @{ */
#define CSPURO_SINME_VR_D_OUTPUTALIAS_ACTIVE             0u   /*!< Boolean, local, discrete */
#define CSPURO_SINME_VR_D_OUTPUTALIAS_Y_PROD             2u   /*!< Real, local, continuous */
#define CSPURO_SINME_VR_D_OUTPUTALIAS_Y_SUM              3u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para CSPuro_SinME.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *cspuro_sinme_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para CSPuro_SinME.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *cspuro_sinme_create_cs(void);

#endif /* CSPURO_SINME_ADAPTER_H */
