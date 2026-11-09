/**
 * @file   matrizestado_adapter.h
 * @brief  Interfaz fmu_t HOST para MatrizEstado.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef MATRIZESTADO_ADAPTER_H
#define MATRIZESTADO_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup matrizestado_meta Metadatos del modelo */
/** @{ */
#define MATRIZESTADO_MODEL_NAME          "MatrizEstado"
#define MATRIZESTADO_GUID                "{3a0ae851-e11b-4c5c-82ce-70d83b41ce13}"
#define MATRIZESTADO_N_STATES            3
#define MATRIZESTADO_N_EVENT_INDICATORS  0
/** @} */

/** @defgroup matrizestado_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define MATRIZESTADO_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(MATRIZESTADO_N_STATES)
#define MATRIZESTADO_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(MATRIZESTADO_N_STATES)
/** @} */

/** @defgroup matrizestado_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Salidas */
/** @{ */
#define MATRIZESTADO_VR_TRAZA                            7u   /*!< Real, output, continuous */
#define MATRIZESTADO_VR_X_1                              9u   /*!< Real, output, continuous */
#define MATRIZESTADO_VR_X_2                              10u   /*!< Real, output, continuous */
#define MATRIZESTADO_VR_X_3                              11u   /*!< Real, output, continuous */
#define MATRIZESTADO_VR_Y_NORMA                          12u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define MATRIZESTADO_VR_A_1_1                            13u   /*!< Real, parameter, fixed, start=1.0 */
#define MATRIZESTADO_VR_A_1_2                            14u   /*!< Real, parameter, fixed, start=0.0 */
#define MATRIZESTADO_VR_A_1_3                            15u   /*!< Real, parameter, fixed, start=0.0 */
#define MATRIZESTADO_VR_A_2_1                            16u   /*!< Real, parameter, fixed, start=0.0 */
#define MATRIZESTADO_VR_A_2_2                            17u   /*!< Real, parameter, fixed, start=2.0 */
#define MATRIZESTADO_VR_A_2_3                            18u   /*!< Real, parameter, fixed, start=0.0 */
#define MATRIZESTADO_VR_A_3_1                            19u   /*!< Real, parameter, fixed, start=0.0 */
#define MATRIZESTADO_VR_A_3_2                            20u   /*!< Real, parameter, fixed, start=0.0 */
#define MATRIZESTADO_VR_A_3_3                            21u   /*!< Real, parameter, fixed, start=3.0 */
#define MATRIZESTADO_VR_B_1_1                            22u   /*!< Real, parameter, fixed, start=1.0 */
#define MATRIZESTADO_VR_B_2_1                            23u   /*!< Real, parameter, fixed, start=1.0 */
#define MATRIZESTADO_VR_B_3_1                            24u   /*!< Real, parameter, fixed, start=1.0 */
/** @} */

/** @name Locales */
/** @{ */
#define MATRIZESTADO_VR_X_STATE_1                        0u   /*!< Real, local, continuous, start=0.0 */
#define MATRIZESTADO_VR_D_OUTPUTALIAS_X_1                0u   /*!< Real, local, continuous */
#define MATRIZESTADO_VR_X_STATE_2                        1u   /*!< Real, local, continuous, start=0.0 */
#define MATRIZESTADO_VR_D_OUTPUTALIAS_X_2                1u   /*!< Real, local, continuous */
#define MATRIZESTADO_VR_X_STATE_3                        2u   /*!< Real, local, continuous, start=0.0 */
#define MATRIZESTADO_VR_D_OUTPUTALIAS_X_3                2u   /*!< Real, local, continuous */
#define MATRIZESTADO_VR_DER_X_STATE_1                    3u   /*!< Real, local, continuous */
#define MATRIZESTADO_VR_DER_X_STATE_2                    4u   /*!< Real, local, continuous */
#define MATRIZESTADO_VR_DER_X_STATE_3                    5u   /*!< Real, local, continuous */
#define MATRIZESTADO_VR_D_OUTPUTALIAS_TRAZA              6u   /*!< Real, local, continuous */
#define MATRIZESTADO_VR_U_1                              8u   /*!< Real, local, continuous, start=0.0 */
#define MATRIZESTADO_VR_D_OUTPUTALIAS_Y_NORMA            12u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para MatrizEstado.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *matrizestado_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para MatrizEstado.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *matrizestado_create_cs(void);

#endif /* MATRIZESTADO_ADAPTER_H */
