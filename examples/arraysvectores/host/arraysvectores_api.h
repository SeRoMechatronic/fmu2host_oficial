/**
 * @file   arraysvectores_api.h
 * @brief  API de simulacion para ArraysVectores.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef ARRAYSVECTORES_API_H
#define ARRAYSVECTORES_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Salidas del modelo en cada instante t. */
typedef struct {
    double           suma_real;   /**< Real output 'suma_real' */
    int              suma_int;   /**< Integer output 'suma_int' */
    double           v_doble_1;   /**< Real output 'v_doble[1]' */
    double           v_doble_2;   /**< Real output 'v_doble[2]' */
    double           v_doble_3;   /**< Real output 'v_doble[3]' */
    double           v_doble_4;   /**< Real output 'v_doble[4]' */
    int              alguno_true;   /**< Boolean output 'alguno_true' */
} ArraysVectores_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const ArraysVectores_Outputs *out);

#endif /* ARRAYSVECTORES_API_H */
