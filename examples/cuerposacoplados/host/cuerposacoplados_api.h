/**
 * @file   cuerposacoplados_api.h
 * @brief  API de simulacion para CuerposAcoplados.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CUERPOSACOPLADOS_API_H
#define CUERPOSACOPLADOS_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           fuerza_externa;   /**< Real input 'fuerza_externa' */
} CuerposAcoplados_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              en_fase;   /**< Boolean output 'en_fase' */
    double           energia_total;   /**< Real output 'energia_total' */
    double           pos1;   /**< Real output 'pos1' */
    double           pos2;   /**< Real output 'pos2' */
    double           vel1;   /**< Real output 'vel1' */
    double           vel2;   /**< Real output 'vel2' */
} CuerposAcoplados_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, CuerposAcoplados_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const CuerposAcoplados_Outputs *out);

#endif /* CUERPOSACOPLADOS_API_H */
