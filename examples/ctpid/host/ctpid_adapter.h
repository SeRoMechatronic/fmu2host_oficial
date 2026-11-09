/**
 * @file   ctpid_adapter.h
 * @brief  Interfaz fmu_t HOST para CTPID.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CTPID_ADAPTER_H
#define CTPID_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup ctpid_meta Metadatos del modelo */
/** @{ */
#define CTPID_MODEL_NAME          "CTPID"
#define CTPID_GUID                "{1e4ce642-3cf9-4c84-8816-d34ec05d4156}"
#define CTPID_N_STATES            1
#define CTPID_N_EVENT_INDICATORS  3
/** @} */

/** @defgroup ctpid_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define CTPID_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(CTPID_N_STATES)
#define CTPID_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(CTPID_N_STATES)
/** @} */

/** @defgroup ctpid_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define CTPID_VR_CONSIGNA                                6u   /*!< Real, input, continuous, start=0.0 */
#define CTPID_VR_TEMPERATURA                             11u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define CTPID_VR_LEDALCANZADO                            0u   /*!< Boolean, output, discrete */
#define CTPID_VR_LEDPORDEBAJO                            1u   /*!< Boolean, output, discrete */
#define CTPID_VR_LEDPORENCIMA                            2u   /*!< Boolean, output, discrete */
#define CTPID_VR_VENTILADOR                              13u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define CTPID_VR_KD                                      14u   /*!< Real, parameter, fixed, start=0.1 */
#define CTPID_VR_KI                                      15u   /*!< Real, parameter, fixed, start=0.5 */
#define CTPID_VR_KP                                      16u   /*!< Real, parameter, fixed, start=2.0 */
#define CTPID_VR_T_MAX                                   17u   /*!< Real, parameter, fixed, start=100.0 */
#define CTPID_VR_T_MIN                                   18u   /*!< Real, parameter, fixed, start=0.0 */
#define CTPID_VR_EPSILON                                 19u   /*!< Real, parameter, fixed, start=1.0 */
/** @} */

/** @name Locales */
/** @{ */
#define CTPID_VR_INTEGRADOR                              0u   /*!< Real, local, continuous, start=0.0 */
#define CTPID_VR_D_OUTPUTALIAS_LEDALCANZADO              0u   /*!< Boolean, local, discrete */
#define CTPID_VR_DER_INTEGRADOR                          1u   /*!< Real, local, continuous */
#define CTPID_VR_D_OUTPUTALIAS_LEDPORDEBAJO              1u   /*!< Boolean, local, discrete */
#define CTPID_VR_DER_CONSIGNA_REAL                       2u   /*!< Real, local, continuous */
#define CTPID_VR_D_OUTPUTALIAS_LEDPORENCIMA              2u   /*!< Boolean, local, discrete */
#define CTPID_VR_DER_ERROR                               3u   /*!< Real, local, continuous */
#define CTPID_VR_DER_TEMPERATURA_REAL                    4u   /*!< Real, local, continuous */
#define CTPID_VR_D_CSE1                                  5u   /*!< Real, local, continuous */
#define CTPID_VR_CONSIGNA_REAL                           7u   /*!< Real, local, continuous */
#define CTPID_VR_DERIVADOR                               8u   /*!< Real, local, continuous */
#define CTPID_VR_ERROR                                   9u   /*!< Real, local, continuous */
#define CTPID_VR_ERROR_PREV                              9u   /*!< Real, local, continuous */
#define CTPID_VR_PID_RAW                                 10u   /*!< Real, local, continuous */
#define CTPID_VR_TEMPERATURA_REAL                        12u   /*!< Real, local, continuous */
#define CTPID_VR_D_OUTPUTALIAS_VENTILADOR                13u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para CTPID.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *ctpid_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para CTPID.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *ctpid_create_cs(void);

#endif /* CTPID_ADAPTER_H */
