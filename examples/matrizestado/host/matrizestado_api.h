/**
 * @file   matrizestado_api.h
 * @brief  API de simulacion para MatrizEstado.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef MATRIZESTADO_API_H
#define MATRIZESTADO_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Salidas del modelo en cada instante t. */
typedef struct {
    double           traza;   /**< Real output 'traza' */
    double           x_1;   /**< Real output 'x[1]' */
    double           x_2;   /**< Real output 'x[2]' */
    double           x_3;   /**< Real output 'x[3]' */
    double           y_norma;   /**< Real output 'y_norma' */
} MatrizEstado_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const MatrizEstado_Outputs *out);

#endif /* MATRIZESTADO_API_H */
