/**
 * @file   muchosestados_api.h
 * @brief  API de simulacion para MuchosEstados.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef MUCHOSESTADOS_API_H
#define MUCHOSESTADOS_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           u;   /**< Real input 'u' */
} MuchosEstados_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              todos_activos;   /**< Boolean output 'todos_activos' */
    double           y1;   /**< Real output 'y1' */
    double           y2;   /**< Real output 'y2' */
    double           y3;   /**< Real output 'y3' */
    double           y4;   /**< Real output 'y4' */
    double           y5;   /**< Real output 'y5' */
    double           y6;   /**< Real output 'y6' */
    double           y7;   /**< Real output 'y7' */
    double           y8;   /**< Real output 'y8' */
} MuchosEstados_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, MuchosEstados_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const MuchosEstados_Outputs *out);

#endif /* MUCHOSESTADOS_API_H */
