/**
 * @file   sistemalorenz_api.h
 * @brief  API de simulacion para SistemaLorenz.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef SISTEMALORENZ_API_H
#define SISTEMALORENZ_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              on_attractor;   /**< Boolean output 'on_attractor' */
    double           x_out;   /**< Real output 'x_out' */
    double           y_out;   /**< Real output 'y_out' */
    double           z_out;   /**< Real output 'z_out' */
} SistemaLorenz_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const SistemaLorenz_Outputs *out);

#endif /* SISTEMALORENZ_API_H */
