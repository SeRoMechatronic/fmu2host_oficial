/**
 * @file   mi_modelo_nuevo_api.h
 * @brief  API de simulacion para Mi_Modelo_Nuevo.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef MI_MODELO_NUEVO_API_H
#define MI_MODELO_NUEVO_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    int              flag_activo;   /**< Boolean input 'flag_activo' */
    double           entrada_principal;   /**< Real input 'entrada_principal' */
} Mi_Modelo_Nuevo_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              flag_salida;   /**< Boolean output 'flag_salida' */
    double           salida_filtrada;   /**< Real output 'salida_filtrada' */
} Mi_Modelo_Nuevo_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, Mi_Modelo_Nuevo_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const Mi_Modelo_Nuevo_Outputs *out);

#endif /* MI_MODELO_NUEVO_API_H */
