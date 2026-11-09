/**
 * @file   ctpid_api.h
 * @brief  API de simulacion para CTPID.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CTPID_API_H
#define CTPID_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           consigna;   /**< Real input 'consigna' */
    double           temperatura;   /**< Real input 'temperatura' */
} CTPID_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              ledalcanzado;   /**< Boolean output 'ledAlcanzado' */
    int              ledpordebajo;   /**< Boolean output 'ledPorDebajo' */
    int              ledporencima;   /**< Boolean output 'ledPorEncima' */
    double           ventilador;   /**< Real output 'ventilador' */
} CTPID_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, CTPID_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const CTPID_Outputs *out);

#endif /* CTPID_API_H */
