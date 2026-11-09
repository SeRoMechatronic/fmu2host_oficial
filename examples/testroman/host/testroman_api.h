/**
 * @file   testroman_api.h
 * @brief  API de simulacion para testROMAN.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef TESTROMAN_API_H
#define TESTROMAN_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           pot;   /**< Real input 'pot' */
} testROMAN_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              led1;   /**< Boolean output 'led1' */
    int              led2;   /**< Boolean output 'led2' */
    int              led3;   /**< Boolean output 'led3' */
    int              led4;   /**< Boolean output 'led4' */
    int              led5;   /**< Boolean output 'led5' */
} testROMAN_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, testROMAN_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const testROMAN_Outputs *out);

#endif /* TESTROMAN_API_H */
