/**
 * @file   niveldeposito_api.h
 * @brief  API de simulacion para NivelDeposito.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef NIVELDEPOSITO_API_H
#define NIVELDEPOSITO_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    int              valvula_manual;   /**< Boolean input 'valvula_manual' */
    double           sensor_nivel;   /**< Real input 'sensor_nivel' */
} NivelDeposito_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              alarma_maximo;   /**< Boolean output 'alarma_maximo' */
    int              alarma_minimo;   /**< Boolean output 'alarma_minimo' */
    int              bomba_activa;   /**< Boolean output 'bomba_activa' */
    double           bomba;   /**< Real output 'bomba' */
} NivelDeposito_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, NivelDeposito_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const NivelDeposito_Outputs *out);

#endif /* NIVELDEPOSITO_API_H */
