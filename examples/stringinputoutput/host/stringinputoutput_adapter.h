/**
 * @file   stringinputoutput_adapter.h
 * @brief  Interfaz fmu_t HOST para StringInputOutput.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef STRINGINPUTOUTPUT_ADAPTER_H
#define STRINGINPUTOUTPUT_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup stringinputoutput_meta Metadatos del modelo */
/** @{ */
#define STRINGINPUTOUTPUT_MODEL_NAME          "StringInputOutput"
#define STRINGINPUTOUTPUT_GUID                "{f65d9ebe-f41f-4336-bd36-24062740e954}"
#define STRINGINPUTOUTPUT_N_STATES            0
#define STRINGINPUTOUTPUT_N_EVENT_INDICATORS  2
/** @} */

/** @defgroup stringinputoutput_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define STRINGINPUTOUTPUT_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(STRINGINPUTOUTPUT_N_STATES)
#define STRINGINPUTOUTPUT_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(STRINGINPUTOUTPUT_N_STATES)
/** @} */

/** @defgroup stringinputoutput_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define STRINGINPUTOUTPUT_VR_VALUE                       1u   /*!< Real, input, continuous, start=0.0 */
#define STRINGINPUTOUTPUT_VR_MODE_OPERATION              1u   /*!< String, input, continuous, start= */
#define STRINGINPUTOUTPUT_VR_TAG_SENSOR                  3u   /*!< String, input, continuous, start= */
/** @} */

/** @name Salidas */
/** @{ */
#define STRINGINPUTOUTPUT_VR_SCALED_VALUE                0u   /*!< Real, output, continuous */
#define STRINGINPUTOUTPUT_VR_ALARM                       0u   /*!< Boolean, output, discrete */
#define STRINGINPUTOUTPUT_VR_ALERT_MSG                   0u   /*!< String, output, continuous */
#define STRINGINPUTOUTPUT_VR_STATUS                      2u   /*!< String, output, continuous */
/** @} */

/** @name Locales */
/** @{ */
#define STRINGINPUTOUTPUT_VR_D_OUTPUTALIAS_SCALED_VALUE  0u   /*!< Real, local, continuous */
#define STRINGINPUTOUTPUT_VR_D_OUTPUTALIAS_ALARM         0u   /*!< Boolean, local, discrete */
#define STRINGINPUTOUTPUT_VR_D_OUTPUTALIAS_ALERT_MSG     0u   /*!< String, local, continuous */
#define STRINGINPUTOUTPUT_VR_D_OUTPUTALIAS_STATUS        2u   /*!< String, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para StringInputOutput.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *stringinputoutput_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para StringInputOutput.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *stringinputoutput_create_cs(void);

#endif /* STRINGINPUTOUTPUT_ADAPTER_H */
