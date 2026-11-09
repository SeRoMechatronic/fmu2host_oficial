/**
 * @file   selectormodo_adapter.h
 * @brief  Interfaz fmu_t HOST para SelectorModo.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef SELECTORMODO_ADAPTER_H
#define SELECTORMODO_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup selectormodo_meta Metadatos del modelo */
/** @{ */
#define SELECTORMODO_MODEL_NAME          "SelectorModo"
#define SELECTORMODO_GUID                "{1a2b3f1f-16f4-4130-bc9c-3c8938410178}"
#define SELECTORMODO_N_STATES            0
#define SELECTORMODO_N_EVENT_INDICATORS  4
/** @} */

/** @defgroup selectormodo_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define SELECTORMODO_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(SELECTORMODO_N_STATES)
#define SELECTORMODO_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(SELECTORMODO_N_STATES)
/** @} */

/** @defgroup selectormodo_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define SELECTORMODO_VR_CONSIGNA_MANUAL                  0u   /*!< Real, input, continuous, start=0.0 */
#define SELECTORMODO_VR_MODO_OPERACION                   1u   /*!< Integer, input, discrete, start=0 */
/** @} */

/** @name Salidas */
/** @{ */
#define SELECTORMODO_VR_CODIGO_ESTADO                    0u   /*!< Integer, output, discrete */
#define SELECTORMODO_VR_FALLO_MODO                       0u   /*!< Boolean, output, discrete */
#define SELECTORMODO_VR_SALIDA_ACTUADOR                  1u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define SELECTORMODO_VR_MODO_AUTO                        2u   /*!< Integer, parameter, fixed, start=1 */
#define SELECTORMODO_VR_MODO_EMERGENCIA                  3u   /*!< Integer, parameter, fixed, start=2 */
#define SELECTORMODO_VR_MODO_MANUAL                      4u   /*!< Integer, parameter, fixed, start=0 */
/** @} */

/** @name Locales */
/** @{ */
#define SELECTORMODO_VR_D_OUTPUTALIAS_CODIGO_ESTADO      0u   /*!< Integer, local, discrete */
#define SELECTORMODO_VR_D_OUTPUTALIAS_FALLO_MODO         0u   /*!< Boolean, local, discrete */
#define SELECTORMODO_VR_D_OUTPUTALIAS_SALIDA_ACTUADOR    1u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para SelectorModo.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *selectormodo_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para SelectorModo.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *selectormodo_create_cs(void);

#endif /* SELECTORMODO_ADAPTER_H */
