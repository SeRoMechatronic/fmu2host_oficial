/**
 * @file   arranquesuavemotor_api.h
 * @brief  API de simulacion para ArranqueSuaveMotor.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef ARRANQUESUAVEMOTOR_API_H
#define ARRANQUESUAVEMOTOR_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    int              orden_arranque;   /**< Boolean input 'orden_arranque' */
    double           carga_motor;   /**< Real input 'carga_motor' */
} ArranqueSuaveMotor_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              en_rampa;   /**< Boolean output 'en_rampa' */
    int              fallo_sobrecarga;   /**< Boolean output 'fallo_sobrecarga' */
    int              motor_en_marcha;   /**< Boolean output 'motor_en_marcha' */
    double           tension_aplicada;   /**< Real output 'tension_aplicada' */
} ArranqueSuaveMotor_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, ArranqueSuaveMotor_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const ArranqueSuaveMotor_Outputs *out);

#endif /* ARRANQUESUAVEMOTOR_API_H */
