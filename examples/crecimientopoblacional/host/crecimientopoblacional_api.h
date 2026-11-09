/**
 * @file   crecimientopoblacional_api.h
 * @brief  API de simulacion para CrecimientoPoblacional.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CRECIMIENTOPOBLACIONAL_API_H
#define CRECIMIENTOPOBLACIONAL_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           tasa_entrada;   /**< Real input 'tasa_entrada' */
} CrecimientoPoblacional_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              superpoblacion;   /**< Boolean output 'superpoblacion' */
    double           poblacion;   /**< Real output 'poblacion' */
    double           saturacion;   /**< Real output 'saturacion' */
    double           tasa_crecimiento;   /**< Real output 'tasa_crecimiento' */
} CrecimientoPoblacional_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, CrecimientoPoblacional_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const CrecimientoPoblacional_Outputs *out);

#endif /* CRECIMIENTOPOBLACIONAL_API_H */
