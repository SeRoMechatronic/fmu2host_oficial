/**
 * @file   multiplexorcanales_api.h
 * @brief  API de simulacion para MultiplexorCanales.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef MULTIPLEXORCANALES_API_H
#define MULTIPLEXORCANALES_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           canal_0;   /**< Real input 'canal_0' */
    double           canal_1;   /**< Real input 'canal_1' */
    int              canal_seleccion;   /**< Integer input 'canal_seleccion' */
    double           canal_2;   /**< Real input 'canal_2' */
    double           canal_3;   /**< Real input 'canal_3' */
} MultiplexorCanales_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              canal_activo;   /**< Integer output 'canal_activo' */
    int              canal_valido;   /**< Boolean output 'canal_valido' */
    double           salida;   /**< Real output 'salida' */
} MultiplexorCanales_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, MultiplexorCanales_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const MultiplexorCanales_Outputs *out);

#endif /* MULTIPLEXORCANALES_API_H */
