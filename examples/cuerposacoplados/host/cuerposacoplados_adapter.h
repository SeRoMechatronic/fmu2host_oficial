/**
 * @file   cuerposacoplados_adapter.h
 * @brief  Interfaz fmu_t HOST para CuerposAcoplados.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CUERPOSACOPLADOS_ADAPTER_H
#define CUERPOSACOPLADOS_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup cuerposacoplados_meta Metadatos del modelo */
/** @{ */
#define CUERPOSACOPLADOS_MODEL_NAME          "CuerposAcoplados"
#define CUERPOSACOPLADOS_GUID                "{524f87b0-4900-4b8c-a309-98239f39e4fa}"
#define CUERPOSACOPLADOS_N_STATES            4
#define CUERPOSACOPLADOS_N_EVENT_INDICATORS  1
/** @} */

/** @defgroup cuerposacoplados_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define CUERPOSACOPLADOS_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(CUERPOSACOPLADOS_N_STATES)
#define CUERPOSACOPLADOS_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(CUERPOSACOPLADOS_N_STATES)
/** @} */

/** @defgroup cuerposacoplados_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define CUERPOSACOPLADOS_VR_FUERZA_EXTERNA               9u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define CUERPOSACOPLADOS_VR_EN_FASE                      0u   /*!< Boolean, output, discrete */
#define CUERPOSACOPLADOS_VR_ENERGIA_TOTAL                8u   /*!< Real, output, continuous */
#define CUERPOSACOPLADOS_VR_POS1                         10u   /*!< Real, output, continuous */
#define CUERPOSACOPLADOS_VR_POS2                         11u   /*!< Real, output, continuous */
#define CUERPOSACOPLADOS_VR_VEL1                         12u   /*!< Real, output, continuous */
#define CUERPOSACOPLADOS_VR_VEL2                         13u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define CUERPOSACOPLADOS_VR_K1                           14u   /*!< Real, parameter, fixed, start=4.0 */
#define CUERPOSACOPLADOS_VR_K2                           15u   /*!< Real, parameter, fixed, start=2.0 */
#define CUERPOSACOPLADOS_VR_KC                           16u   /*!< Real, parameter, fixed, start=1.0 */
#define CUERPOSACOPLADOS_VR_M1                           17u   /*!< Real, parameter, fixed, start=1.0 */
#define CUERPOSACOPLADOS_VR_M2                           18u   /*!< Real, parameter, fixed, start=2.0 */
/** @} */

/** @name Locales */
/** @{ */
#define CUERPOSACOPLADOS_VR_V1                           0u   /*!< Real, local, continuous, start=0.0 */
#define CUERPOSACOPLADOS_VR_D_OUTPUTALIAS_VEL1           0u   /*!< Real, local, continuous */
#define CUERPOSACOPLADOS_VR_D_OUTPUTALIAS_EN_FASE        0u   /*!< Boolean, local, discrete */
#define CUERPOSACOPLADOS_VR_V2                           1u   /*!< Real, local, continuous, start=0.5 */
#define CUERPOSACOPLADOS_VR_D_OUTPUTALIAS_VEL2           1u   /*!< Real, local, continuous */
#define CUERPOSACOPLADOS_VR_X1                           2u   /*!< Real, local, continuous, start=1.0 */
#define CUERPOSACOPLADOS_VR_D_OUTPUTALIAS_POS1           2u   /*!< Real, local, continuous */
#define CUERPOSACOPLADOS_VR_X2                           3u   /*!< Real, local, continuous, start=-0.5 */
#define CUERPOSACOPLADOS_VR_D_OUTPUTALIAS_POS2           3u   /*!< Real, local, continuous */
#define CUERPOSACOPLADOS_VR_DER_V1                       4u   /*!< Real, local, continuous */
#define CUERPOSACOPLADOS_VR_DER_V2                       5u   /*!< Real, local, continuous */
#define CUERPOSACOPLADOS_VR_DER_X1                       6u   /*!< Real, local, continuous */
#define CUERPOSACOPLADOS_VR_DER_X2                       7u   /*!< Real, local, continuous */
#define CUERPOSACOPLADOS_VR_D_OUTPUTALIAS_ENERGIA_TOTAL  8u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para CuerposAcoplados.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *cuerposacoplados_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para CuerposAcoplados.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *cuerposacoplados_create_cs(void);

#endif /* CUERPOSACOPLADOS_ADAPTER_H */
