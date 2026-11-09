/**
 * @file   reguladorbateria_api.h
 * @brief  API de simulacion para ReguladorBateria.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef REGULADORBATERIA_API_H
#define REGULADORBATERIA_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    int              carga_conectada;   /**< Boolean input 'carga_conectada' */
    double           tension_bateria;   /**< Real input 'tension_bateria' */
} ReguladorBateria_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              carga_completa;   /**< Boolean output 'carga_completa' */
    int              cargando;   /**< Boolean output 'cargando' */
    int              fallo_sobretension;   /**< Boolean output 'fallo_sobretension' */
    double           corriente_carga;   /**< Real output 'corriente_carga' */
} ReguladorBateria_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, ReguladorBateria_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const ReguladorBateria_Outputs *out);

#endif /* REGULADORBATERIA_API_H */
