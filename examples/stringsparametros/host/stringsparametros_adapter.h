/**
 * @file   stringsparametros_adapter.h
 * @brief  Interfaz fmu_t HOST para StringsParametros.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef STRINGSPARAMETROS_ADAPTER_H
#define STRINGSPARAMETROS_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup stringsparametros_meta Metadatos del modelo */
/** @{ */
#define STRINGSPARAMETROS_MODEL_NAME          "StringsParametros"
#define STRINGSPARAMETROS_GUID                "{77af6522-3e13-4790-bfe6-bb3bab410d3e}"
#define STRINGSPARAMETROS_N_STATES            0
#define STRINGSPARAMETROS_N_EVENT_INDICATORS  0
/** @} */

/** @defgroup stringsparametros_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define STRINGSPARAMETROS_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(STRINGSPARAMETROS_N_STATES)
#define STRINGSPARAMETROS_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(STRINGSPARAMETROS_N_STATES)
/** @} */

/** @defgroup stringsparametros_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define STRINGSPARAMETROS_VR_U                           0u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define STRINGSPARAMETROS_VR_Y                           1u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define STRINGSPARAMETROS_VR_LEN_NOMBRE                  0u   /*!< Integer, parameter, fixed, start=34 */
#define STRINGSPARAMETROS_VR_ESPECIAL                    0u   /*!< String, parameter, fixed, start=val=3.14;tag=alpha_beta;unit=m2/s */
#define STRINGSPARAMETROS_VR_LARGO                       1u   /*!< String, parameter, fixed, start=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa */
#define STRINGSPARAMETROS_VR_NOMBRE                      2u   /*!< String, parameter, fixed, start=Sensor de Presión #1 (Alta Temp.) */
#define STRINGSPARAMETROS_VR_RUTA                        3u   /*!< String, parameter, fixed, start=/datos/planta/linea_A/modulo_02 */
#define STRINGSPARAMETROS_VR_UNICODE_STR                 4u   /*!< String, parameter, fixed, start=Angstrom [A] delta+-epsilon */
#define STRINGSPARAMETROS_VR_VACIO                       5u   /*!< String, parameter, fixed, start= */
/** @} */

/** @name Locales */
/** @{ */
#define STRINGSPARAMETROS_VR_D_OUTPUTALIAS_Y             1u   /*!< Real, local, continuous */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para StringsParametros.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *stringsparametros_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para StringsParametros.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *stringsparametros_create_cs(void);

#endif /* STRINGSPARAMETROS_ADAPTER_H */
