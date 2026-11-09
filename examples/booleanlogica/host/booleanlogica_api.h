/**
 * @file   booleanlogica_api.h
 * @brief  API de simulacion para BooleanLogica.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef BOOLEANLOGICA_API_H
#define BOOLEANLOGICA_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           umbral;   /**< Real input 'umbral' */
    int              a;   /**< Boolean input 'a' */
    int              b;   /**< Boolean input 'b' */
    int              clk;   /**< Boolean input 'clk' */
} BooleanLogica_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              cuenta_flancos;   /**< Integer output 'cuenta_flancos' */
    int              above_threshold;   /**< Boolean output 'above_threshold' */
    int              y_and;   /**< Boolean output 'y_and' */
    int              y_latch;   /**< Boolean output 'y_latch' */
    int              y_or;   /**< Boolean output 'y_or' */
    int              y_xor;   /**< Boolean output 'y_xor' */
} BooleanLogica_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, BooleanLogica_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const BooleanLogica_Outputs *out);

#endif /* BOOLEANLOGICA_API_H */
