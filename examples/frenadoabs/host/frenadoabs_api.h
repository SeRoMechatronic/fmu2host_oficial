/**
 * @file   frenadoabs_api.h
 * @brief  API de simulacion para FrenadoABS.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef FRENADOABS_API_H
#define FRENADOABS_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           presion_pedal;   /**< Real input 'presion_pedal' */
    double           velocidad_rueda;   /**< Real input 'velocidad_rueda' */
} FrenadoABS_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              abs_activo;   /**< Boolean output 'abs_activo' */
    int              frenado_normal;   /**< Boolean output 'frenado_normal' */
    int              rueda_bloqueada;   /**< Boolean output 'rueda_bloqueada' */
    double           presion_modulada;   /**< Real output 'presion_modulada' */
} FrenadoABS_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, FrenadoABS_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const FrenadoABS_Outputs *out);

#endif /* FRENADOABS_API_H */
