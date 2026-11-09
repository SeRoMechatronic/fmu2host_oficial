/**
 * @file   crecimientopoblacional_adapter.h
 * @brief  Interfaz fmu_t HOST para CrecimientoPoblacional.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CRECIMIENTOPOBLACIONAL_ADAPTER_H
#define CRECIMIENTOPOBLACIONAL_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup crecimientopoblacional_meta Metadatos del modelo */
/** @{ */
#define CRECIMIENTOPOBLACIONAL_MODEL_NAME          "CrecimientoPoblacional"
#define CRECIMIENTOPOBLACIONAL_GUID                "{6f1a99bb-380b-404d-acf5-24f241c917f3}"
#define CRECIMIENTOPOBLACIONAL_N_STATES            1
#define CRECIMIENTOPOBLACIONAL_N_EVENT_INDICATORS  1
/** @} */

/** @defgroup crecimientopoblacional_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define CRECIMIENTOPOBLACIONAL_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(CRECIMIENTOPOBLACIONAL_N_STATES)
#define CRECIMIENTOPOBLACIONAL_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(CRECIMIENTOPOBLACIONAL_N_STATES)
/** @} */

/** @defgroup crecimientopoblacional_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define CRECIMIENTOPOBLACIONAL_VR_TASA_ENTRADA           5u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define CRECIMIENTOPOBLACIONAL_VR_SUPERPOBLACION         0u   /*!< Boolean, output, discrete */
#define CRECIMIENTOPOBLACIONAL_VR_POBLACION              2u   /*!< Real, output, continuous */
#define CRECIMIENTOPOBLACIONAL_VR_SATURACION             3u   /*!< Real, output, continuous */
#define CRECIMIENTOPOBLACIONAL_VR_TASA_CRECIMIENTO       4u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define CRECIMIENTOPOBLACIONAL_VR_K                      6u   /*!< Real, parameter, fixed, start=100.0 */
#define CRECIMIENTOPOBLACIONAL_VR_R                      7u   /*!< Real, parameter, fixed, start=3.5 */
/** @} */

/** @name Locales */
/** @{ */
#define CRECIMIENTOPOBLACIONAL_VR_N                      0u   /*!< Real, local, continuous, start=2.0 */
#define CRECIMIENTOPOBLACIONAL_VR_D_OUTPUTALIAS_POBLACION 0u   /*!< Real, local, continuous */
#define CRECIMIENTOPOBLACIONAL_VR_D_OUTPUTALIAS_SUPERPOBLACION 0u   /*!< Boolean, local, discrete */
#define CRECIMIENTOPOBLACIONAL_VR_DER_N                  1u   /*!< Real, local, continuous */
#define CRECIMIENTOPOBLACIONAL_VR_D_OUTPUTALIAS_SATURACION 3u   /*!< Real, local, continuous */
#define CRECIMIENTOPOBLACIONAL_VR_D_OUTPUTALIAS_TASA_CRECIMIENTO 4u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para CrecimientoPoblacional.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *crecimientopoblacional_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para CrecimientoPoblacional.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *crecimientopoblacional_create_cs(void);

#endif /* CRECIMIENTOPOBLACIONAL_ADAPTER_H */
