/**
 * @file   codigoerrordiagnostico_adapter.h
 * @brief  Interfaz fmu_t HOST para CodigoErrorDiagnostico.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CODIGOERRORDIAGNOSTICO_ADAPTER_H
#define CODIGOERRORDIAGNOSTICO_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup codigoerrordiagnostico_meta Metadatos del modelo */
/** @{ */
#define CODIGOERRORDIAGNOSTICO_MODEL_NAME          "CodigoErrorDiagnostico"
#define CODIGOERRORDIAGNOSTICO_GUID                "{5d9a5441-4697-4945-99cb-289a15bd1126}"
#define CODIGOERRORDIAGNOSTICO_N_STATES            0
#define CODIGOERRORDIAGNOSTICO_N_EVENT_INDICATORS  3
/** @} */

/** @defgroup codigoerrordiagnostico_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define CODIGOERRORDIAGNOSTICO_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(CODIGOERRORDIAGNOSTICO_N_STATES)
#define CODIGOERRORDIAGNOSTICO_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(CODIGOERRORDIAGNOSTICO_N_STATES)
/** @} */

/** @defgroup codigoerrordiagnostico_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define CODIGOERRORDIAGNOSTICO_VR_TEMPERATURA            1u   /*!< Real, input, continuous, start=0.0 */
#define CODIGOERRORDIAGNOSTICO_VR_TENSION                2u   /*!< Real, input, continuous, start=0.0 */
#define CODIGOERRORDIAGNOSTICO_VR_VIBRACION              3u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define CODIGOERRORDIAGNOSTICO_VR_FACTOR_REDUCCION       0u   /*!< Real, output, continuous */
#define CODIGOERRORDIAGNOSTICO_VR_CODIGO_ERROR           0u   /*!< Integer, output, discrete */
#define CODIGOERRORDIAGNOSTICO_VR_PARADA_EMERGENCIA      0u   /*!< Boolean, output, discrete */
#define CODIGOERRORDIAGNOSTICO_VR_NIVEL_PRIORIDAD        1u   /*!< Integer, output, discrete */
/** @} */

/** @name Parametros */
/** @{ */
#define CODIGOERRORDIAGNOSTICO_VR_UMBRAL_TEMPERATURA     4u   /*!< Real, parameter, fixed, start=0.85 */
#define CODIGOERRORDIAGNOSTICO_VR_UMBRAL_TENSION         5u   /*!< Real, parameter, fixed, start=0.1 */
#define CODIGOERRORDIAGNOSTICO_VR_UMBRAL_VIBRACION       6u   /*!< Real, parameter, fixed, start=0.75 */
/** @} */

/** @name Locales */
/** @{ */
#define CODIGOERRORDIAGNOSTICO_VR_D_OUTPUTALIAS_FACTOR_REDUCCION 0u   /*!< Real, local, continuous */
#define CODIGOERRORDIAGNOSTICO_VR_D_OUTPUTALIAS_CODIGO_ERROR 0u   /*!< Integer, local, discrete */
#define CODIGOERRORDIAGNOSTICO_VR_D_OUTPUTALIAS_PARADA_EMERGENCIA 0u   /*!< Boolean, local, discrete */
#define CODIGOERRORDIAGNOSTICO_VR_D_OUTPUTALIAS_NIVEL_PRIORIDAD 1u   /*!< Integer, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para CodigoErrorDiagnostico.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *codigoerrordiagnostico_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para CodigoErrorDiagnostico.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *codigoerrordiagnostico_create_cs(void);

#endif /* CODIGOERRORDIAGNOSTICO_ADAPTER_H */
