/**
 * @file   stringsparametros_api.h
 * @brief  API de simulacion para StringsParametros.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef STRINGSPARAMETROS_API_H
#define STRINGSPARAMETROS_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           u;   /**< Real input 'u' */
} StringsParametros_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    double           y;   /**< Real output 'y' */
} StringsParametros_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, StringsParametros_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const StringsParametros_Outputs *out);

#endif /* STRINGSPARAMETROS_API_H */
