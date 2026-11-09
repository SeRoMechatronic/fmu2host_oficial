/**
 * @file   mi_modelo_nuevo_adapter.h
 * @brief  Interfaz fmu_t HOST para Mi_Modelo_Nuevo.
 *
 *  Header compartido por _adapter_me.c y _adapter_cs.c.
 *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef MI_MODELO_NUEVO_ADAPTER_H
#define MI_MODELO_NUEVO_ADAPTER_H

#include "fmu_t.h"
#include "fmu_solver.h"

/** @defgroup mi_modelo_nuevo_meta Metadatos del modelo */
/** @{ */
#define MI_MODELO_NUEVO_MODEL_NAME          "Mi_Modelo_Nuevo"
#define MI_MODELO_NUEVO_GUID                "{849bd289-0db4-442e-8921-9fad06a5254d}"
#define MI_MODELO_NUEVO_N_STATES            1
#define MI_MODELO_NUEVO_N_EVENT_INDICATORS  1
/** @} */

/** @defgroup mi_modelo_nuevo_solver Tamanios de buffer para solvers Euler y RK4 (ME) */
/** @{ */
#define MI_MODELO_NUEVO_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE(MI_MODELO_NUEVO_N_STATES)
#define MI_MODELO_NUEVO_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE(MI_MODELO_NUEVO_N_STATES)
/** @} */

/** @defgroup mi_modelo_nuevo_vr ValueReferences (de modelDescription.xml) */
/** @{ */
/** @name Entradas */
/** @{ */
#define MI_MODELO_NUEVO_VR_FLAG_ACTIVO                   0u   /*!< Boolean, input, discrete, start=false */
#define MI_MODELO_NUEVO_VR_ENTRADA_PRINCIPAL             2u   /*!< Real, input, continuous, start=0.0 */
/** @} */

/** @name Salidas */
/** @{ */
#define MI_MODELO_NUEVO_VR_FLAG_SALIDA                   1u   /*!< Boolean, output, discrete */
#define MI_MODELO_NUEVO_VR_SALIDA_FILTRADA               3u   /*!< Real, output, continuous */
/** @} */

/** @name Parametros */
/** @{ */
#define MI_MODELO_NUEVO_VR_NOMBRE_FMU                    0u   /*!< String, parameter, fixed, start=Mi-Modelo-Nuevo */
#define MI_MODELO_NUEVO_VR_TAU                           4u   /*!< Real, parameter, fixed, start=1.0 */
/** @} */

/** @name Locales */
/** @{ */
#define MI_MODELO_NUEVO_VR_X                             0u   /*!< Real, local, continuous, start=0.0 */
#define MI_MODELO_NUEVO_VR_D_OUTPUTALIAS_SALIDA_FILTRADA 0u   /*!< Real, local, continuous */
#define MI_MODELO_NUEVO_VR_DER_X                         1u   /*!< Real, local, continuous */
#define MI_MODELO_NUEVO_VR_D_OUTPUTALIAS_FLAG_SALIDA     1u   /*!< Boolean, local, discrete */
/** @} */

/** @} */

/** @brief Devuelve el adapter Model Exchange para Mi_Modelo_Nuevo.
 *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */
fmu_t *mi_modelo_nuevo_create_me(void);

/** @brief Devuelve el adapter Co-Simulation para Mi_Modelo_Nuevo.
 *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */
fmu_t *mi_modelo_nuevo_create_cs(void);

#endif /* MI_MODELO_NUEVO_ADAPTER_H */
