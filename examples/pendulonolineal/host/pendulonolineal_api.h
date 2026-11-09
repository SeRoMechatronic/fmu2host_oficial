/**
 * @file   pendulonolineal_api.h
 * @brief  API de simulacion para PenduloNoLineal.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef PENDULONOLINEAL_API_H
#define PENDULONOLINEAL_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              en_reposo;   /**< Boolean output 'en_reposo' */
    double           angulo;   /**< Real output 'angulo' */
    double           energia_total;   /**< Real output 'energia_total' */
    double           velocidad_angular;   /**< Real output 'velocidad_angular' */
} PenduloNoLineal_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const PenduloNoLineal_Outputs *out);

#endif /* PENDULONOLINEAL_API_H */
