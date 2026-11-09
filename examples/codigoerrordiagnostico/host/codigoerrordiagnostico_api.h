/**
 * @file   codigoerrordiagnostico_api.h
 * @brief  API de simulacion para CodigoErrorDiagnostico.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CODIGOERRORDIAGNOSTICO_API_H
#define CODIGOERRORDIAGNOSTICO_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           temperatura;   /**< Real input 'temperatura' */
    double           tension;   /**< Real input 'tension' */
    double           vibracion;   /**< Real input 'vibracion' */
} CodigoErrorDiagnostico_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    double           factor_reduccion;   /**< Real output 'factor_reduccion' */
    int              codigo_error;   /**< Integer output 'codigo_error' */
    int              parada_emergencia;   /**< Boolean output 'parada_emergencia' */
    int              nivel_prioridad;   /**< Integer output 'nivel_prioridad' */
} CodigoErrorDiagnostico_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, CodigoErrorDiagnostico_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const CodigoErrorDiagnostico_Outputs *out);

#endif /* CODIGOERRORDIAGNOSTICO_API_H */
