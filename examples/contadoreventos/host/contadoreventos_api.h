/**
 * @file   contadoreventos_api.h
 * @brief  API de simulacion para ContadorEventos.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CONTADOREVENTOS_API_H
#define CONTADOREVENTOS_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    int              evento;   /**< Boolean input 'evento' */
    int              reset;   /**< Boolean input 'reset' */
} ContadorEventos_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              cuenta;   /**< Integer output 'cuenta' */
    int              decenas;   /**< Integer output 'decenas' */
    int              desbordamiento;   /**< Boolean output 'desbordamiento' */
    int              unidades;   /**< Integer output 'unidades' */
} ContadorEventos_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, ContadorEventos_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const ContadorEventos_Outputs *out);

#endif /* CONTADOREVENTOS_API_H */
