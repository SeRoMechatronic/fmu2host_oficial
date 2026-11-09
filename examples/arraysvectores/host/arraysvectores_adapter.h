/**
 * @file   arraysvectores_adapter.h
 * @brief  Interfaz fmu_t HOST para ArraysVectores.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef ARRAYSVECTORES_ADAPTER_H
#define ARRAYSVECTORES_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup arraysvectores_meta Metadatos del modelo */
/** @{ */
#define ARRAYSVECTORES_MODEL_NAME          "ArraysVectores"
#define ARRAYSVECTORES_GUID                "{00d6ddbc-ef60-461b-ad3e-2fcdca1616a5}"
#define ARRAYSVECTORES_N_STATES            0
#define ARRAYSVECTORES_N_EVENT_INDICATORS  0
/** @} */

/** @defgroup arraysvectores_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define ARRAYSVECTORES_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(ARRAYSVECTORES_N_STATES)
#define ARRAYSVECTORES_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(ARRAYSVECTORES_N_STATES)
/** @} */

/** @defgroup arraysvectores_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Salidas */
/** @{ */
#define ARRAYSVECTORES_VR_SUMA_REAL                      0u   /*!< Real, output, continuous */
#define ARRAYSVECTORES_VR_SUMA_INT                       0u   /*!< Integer, output, discrete */
#define ARRAYSVECTORES_VR_V_DOBLE_1                      1u   /*!< Real, output, continuous */
#define ARRAYSVECTORES_VR_V_DOBLE_2                      2u   /*!< Real, output, continuous */
#define ARRAYSVECTORES_VR_V_DOBLE_3                      3u   /*!< Real, output, continuous */
#define ARRAYSVECTORES_VR_V_DOBLE_4                      4u   /*!< Real, output, continuous */
#define ARRAYSVECTORES_VR_ALGUNO_TRUE                    5u   /*!< Boolean, output, fixed */
/** @} */

/** @name Parametros calculados */
/** @{ */
#define ARRAYSVECTORES_VR_D_OUTPUTALIAS_ALGUNO_TRUE      4u   /*!< Boolean, calculatedParameter, fixed */
#define ARRAYSVECTORES_VR_N                              5u   /*!< Integer, calculatedParameter, fixed */
/** @} */

/** @name Locales */
/** @{ */
#define ARRAYSVECTORES_VR_D_OUTPUTALIAS_SUMA_REAL        0u   /*!< Real, local, continuous */
#define ARRAYSVECTORES_VR_D_OUTPUTALIAS_SUMA_INT         0u   /*!< Integer, local, discrete */
#define ARRAYSVECTORES_VR_V_BOOL_1                       0u   /*!< Boolean, local, discrete, start=false */
#define ARRAYSVECTORES_VR_D_OUTPUTALIAS_V_DOBLE_1        1u   /*!< Real, local, continuous */
#define ARRAYSVECTORES_VR_V_INT_1                        1u   /*!< Integer, local, discrete, start=0 */
#define ARRAYSVECTORES_VR_V_BOOL_2                       1u   /*!< Boolean, local, discrete, start=false */
#define ARRAYSVECTORES_VR_D_OUTPUTALIAS_V_DOBLE_2        2u   /*!< Real, local, continuous */
#define ARRAYSVECTORES_VR_V_INT_2                        2u   /*!< Integer, local, discrete, start=0 */
#define ARRAYSVECTORES_VR_V_BOOL_3                       2u   /*!< Boolean, local, discrete, start=false */
#define ARRAYSVECTORES_VR_D_OUTPUTALIAS_V_DOBLE_3        3u   /*!< Real, local, continuous */
#define ARRAYSVECTORES_VR_V_INT_3                        3u   /*!< Integer, local, discrete, start=0 */
#define ARRAYSVECTORES_VR_V_BOOL_4                       3u   /*!< Boolean, local, discrete, start=false */
#define ARRAYSVECTORES_VR_D_OUTPUTALIAS_V_DOBLE_4        4u   /*!< Real, local, continuous */
#define ARRAYSVECTORES_VR_V_INT_4                        4u   /*!< Integer, local, discrete, start=0 */
#define ARRAYSVECTORES_VR_V_REAL_1                       5u   /*!< Real, local, continuous, start=0.0 */
#define ARRAYSVECTORES_VR_V_REAL_2                       6u   /*!< Real, local, continuous, start=0.0 */
#define ARRAYSVECTORES_VR_V_REAL_3                       7u   /*!< Real, local, continuous, start=0.0 */
#define ARRAYSVECTORES_VR_V_REAL_4                       8u   /*!< Real, local, continuous, start=0.0 */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para ArraysVectores.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *arraysvectores_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para ArraysVectores.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *arraysvectores_create_cs(void);

#endif /* ARRAYSVECTORES_ADAPTER_H */
