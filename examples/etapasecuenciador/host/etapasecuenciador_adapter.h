/**
 * @file   etapasecuenciador_adapter.h
 * @brief  Interfaz fmu_t HOST para EtapaSecuenciador.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef ETAPASECUENCIADOR_ADAPTER_H
#define ETAPASECUENCIADOR_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup etapasecuenciador_meta Metadatos del modelo */
/** @{ */
#define ETAPASECUENCIADOR_MODEL_NAME          "EtapaSecuenciador"
#define ETAPASECUENCIADOR_GUID                "{8dd659c4-cec8-4fc5-ba83-5de4a39c0d1f}"
#define ETAPASECUENCIADOR_N_STATES            0
#define ETAPASECUENCIADOR_N_EVENT_INDICATORS  0
/** @} */

/** @defgroup etapasecuenciador_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define ETAPASECUENCIADOR_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(ETAPASECUENCIADOR_N_STATES)
#define ETAPASECUENCIADOR_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(ETAPASECUENCIADOR_N_STATES)
/** @} */

/** @defgroup etapasecuenciador_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define ETAPASECUENCIADOR_VR_SENSOR_CONFIRMACION         1u   /*!< Real, input, continuous, start=0.0 */
#define ETAPASECUENCIADOR_VR_ARRANCAR                    4u   /*!< Boolean, input, discrete, start=false */
#define ETAPASECUENCIADOR_VR_PARAR                       5u   /*!< Boolean, input, discrete, start=false */
/** @} */

/** @name Salidas */
/** @{ */
#define ETAPASECUENCIADOR_VR_PROGRESO_ETAPA              0u   /*!< Real, output, continuous */
#define ETAPASECUENCIADOR_VR_ETAPA_ACTUAL                1u   /*!< Integer, output, discrete */
#define ETAPASECUENCIADOR_VR_ETAPA_PREVIA                3u   /*!< Integer, output, discrete */
#define ETAPASECUENCIADOR_VR_SECUENCIA_COMPLETA          6u   /*!< Boolean, output, discrete */
/** @} */

/** @name Parametros */
/** @{ */
#define ETAPASECUENCIADOR_VR_N_ETAPAS                    4u   /*!< Integer, parameter, fixed, start=5 */
#define ETAPASECUENCIADOR_VR_TS                          5u   /*!< Real, parameter, fixed, start=0.1 */
#define ETAPASECUENCIADOR_VR_DURACION_ETAPA              6u   /*!< Real, parameter, fixed, start=10.0 */
/** @} */

/** @name Locales */
/** @{ */
#define ETAPASECUENCIADOR_VR_D_OUTPUTALIAS_PROGRESO_ETAPA 0u   /*!< Real, local, continuous */
#define ETAPASECUENCIADOR_VR_ETAPA                       0u   /*!< Integer, local, discrete, start=0 */
#define ETAPASECUENCIADOR_VR_D_WHENCONDITION1            0u   /*!< Boolean, local, discrete, start=true */
#define ETAPASECUENCIADOR_VR_D_OUTPUTALIAS_ETAPA_ACTUAL  1u   /*!< Integer, local, discrete */
#define ETAPASECUENCIADOR_VR_D_WHENCONDITION2            1u   /*!< Boolean, local, discrete, start=false */
#define ETAPASECUENCIADOR_VR_SENSOR_S                    2u   /*!< Real, local, discrete, start=0.0 */
#define ETAPASECUENCIADOR_VR_ETAPA_ANT                   2u   /*!< Integer, local, discrete, start=0 */
#define ETAPASECUENCIADOR_VR_D_WHENCONDITION3            2u   /*!< Boolean, local, discrete, start=false */
#define ETAPASECUENCIADOR_VR_T_INICIO                    3u   /*!< Real, local, discrete, start=0.0 */
#define ETAPASECUENCIADOR_VR_D_OUTPUTALIAS_ETAPA_PREVIA  3u   /*!< Integer, local, discrete */
#define ETAPASECUENCIADOR_VR_D_WHENCONDITION4            3u   /*!< Boolean, local, discrete, start=false */
#define ETAPASECUENCIADOR_VR_TIEMPO_EN_ETAPA             4u   /*!< Real, local, discrete, start=0.0 */
#define ETAPASECUENCIADOR_VR_D_OUTPUTALIAS_SECUENCIA_COMPLETA 6u   /*!< Boolean, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para EtapaSecuenciador.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *etapasecuenciador_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para EtapaSecuenciador.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *etapasecuenciador_create_cs(void);

#endif /* ETAPASECUENCIADOR_ADAPTER_H */
