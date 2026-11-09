/**
 * @file   etapasecuenciador_api.h
 * @brief  API de simulacion para EtapaSecuenciador.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef ETAPASECUENCIADOR_API_H
#define ETAPASECUENCIADOR_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           sensor_confirmacion;   /**< Real input 'sensor_confirmacion' */
    int              arrancar;   /**< Boolean input 'arrancar' */
    int              parar;   /**< Boolean input 'parar' */
} EtapaSecuenciador_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    double           progreso_etapa;   /**< Real output 'progreso_etapa' */
    int              etapa_actual;   /**< Integer output 'etapa_actual' */
    int              etapa_previa;   /**< Integer output 'etapa_previa' */
    int              secuencia_completa;   /**< Boolean output 'secuencia_completa' */
} EtapaSecuenciador_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, EtapaSecuenciador_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const EtapaSecuenciador_Outputs *out);

#endif /* ETAPASECUENCIADOR_API_H */
