/**
 * @file   stringinputoutput_api.h
 * @brief  API de simulacion para StringInputOutput.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef STRINGINPUTOUTPUT_API_H
#define STRINGINPUTOUTPUT_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           value;   /**< Real input 'value' */
    const char *     mode_operation;   /**< String input 'mode_operation' */
    const char *     tag_sensor;   /**< String input 'tag_sensor' */
} StringInputOutput_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    double           scaled_value;   /**< Real output 'scaled_value' */
    int              alarm;   /**< Boolean output 'alarm' */
    const char *     alert_msg;   /**< String output 'alert_msg' */
    const char *     status;   /**< String output 'status' */
} StringInputOutput_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, StringInputOutput_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const StringInputOutput_Outputs *out);

#endif /* STRINGINPUTOUTPUT_API_H */
