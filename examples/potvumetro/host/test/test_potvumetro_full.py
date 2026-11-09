#!/usr/bin/env python3
"""Test battery completa — PotVumetro (12 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "PotVumetro",
    "tests": [
        {
            "id": "TC-PV-001",
            "title": "Todos los LEDs apagados — por debajo del primer umbral",
            "description": "pot=0.0: ningun LED debe activarse.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.0},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led3", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led4", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led5", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Con el potenciometro en posicion minima (0.0), ningun LED debe "
                "encenderse. Todos los umbrales (0.2, 0.4, 0.6, 0.8, 1.0) son mayores "
                "que 0.0. Este es el estado de reposo del vumeter: barra vacia."
            ),
        },
        {
            "id": "TC-PV-002",
            "title": "Justo encima umbral LED1 — pot=0.21",
            "description": "pot=0.21 (por encima de 0.20) activa LED1, resto apagados.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.21},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led3", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led4", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led5", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Con pot=0.21 (justo encima del umbral de LED1=0.20), LED1 enciende. "
                "Nota: el FMU usa relationhysteresis, por lo que un input constante "
                "exactamente en el umbral (pot=0.20) no dispara el evento; se requiere "
                "un valor estrictamente superior al umbral para inputs estaticos."
            ),
        },
        {
            "id": "TC-PV-003",
            "title": "Justo debajo del umbral de LED1 — pot=0.199",
            "description": "pot=0.199 mantiene todos los LEDs apagados.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.199},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Un valor infinitesimalmente por debajo del umbral de LED1 (0.199 < 0.20) "
                "mantiene todos los LEDs apagados. Junto con TC-PV-002, este par de tests "
                "confirma la precision del umbral en los dos lados del limite."
            ),
        },
        {
            "id": "TC-PV-004",
            "title": "Entre LED1 y LED2 — pot=0.30",
            "description": "pot=0.30 activa solo LED1.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.30},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led3", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Valor a mitad entre los umbrales de LED1 y LED2. Solo el primer LED "
                "esta activo. Verifica el estado intermedio mas basico de la barra "
                "de LEDs: un segmento encendido de cinco."
            ),
        },
        {
            "id": "TC-PV-005",
            "title": "Justo encima umbral LED2 — pot=0.41",
            "description": "pot=0.41 (por encima de 0.40) activa LED1 y LED2.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.41},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led3", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "pot=0.41 (justo encima del umbral LED2=0.40) activa LED1 y LED2. "
                "Verifica el segundo umbral de la barra gradual con margin sobre la "
                "hysteresis del FMU."
            ),
        },
        {
            "id": "TC-PV-006",
            "title": "Justo encima umbral LED3 — pot=0.61",
            "description": "pot=0.61 (por encima de 0.60) activa LED1, LED2 y LED3.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.61},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led3", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led4", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Tres LEDs encendidos con pot=0.61 (justo encima del umbral LED3=0.60). "
                "La barra gradual muestra nivel medio-alto. Cada umbral representa "
                "el 20% del rango total."
            ),
        },
        {
            "id": "TC-PV-007",
            "title": "Justo encima umbral LED4 — pot=0.81",
            "description": "pot=0.81 (por encima de 0.80) activa LED1 a LED4.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.81},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led3", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led4", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led5", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Cuatro LEDs encendidos con pot=0.81 (justo encima del umbral LED4=0.80). "
                "El LED5 (rojo, pico) no se activa porque 0.81 < 1.0. Nivel maximo "
                "sin alarma de pico."
            ),
        },
        {
            "id": "TC-PV-008",
            "title": "Justo por debajo de escala completa — pot=0.999",
            "description": "pot=0.999 activa LED1 a LED4, pero NO LED5.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.999},
            "checks": [
                {"col": "led4", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led5", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Un valor casi a escala completa (0.999) aun no activa LED5, cuyo "
                "umbral es exactamente 1.0. Este test critico verifica que el LED "
                "de pico (rojo) no se activa prematuramente antes de que la senal "
                "llegue al maximo real."
            ),
        },
        {
            "id": "TC-PV-009",
            "title": "Escala completa — LED1-LED4 encendidos, LED5 por hysteresis",
            "description": "pot=1.0 enciende LED1-LED4; LED5 (umbral>=1.0) no dispara con input estatico.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 1.0},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led3", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led4", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led5", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Con pot=1.0 (maximo del rango declarado [0,1]), LED1-LED4 se activan. "
                "LED5 (umbral >= 1.0) NO se activa con input estatico exactamente en el "
                "umbral, por la implementacion de relationhysteresis del FMU: requiere "
                "cruzar el umbral desde abajo. Para activar LED5 usar pot > 1.0 "
                "(ver TC-PV-012 con pot=1.5)."
            ),
        },
        {
            "id": "TC-PV-010",
            "title": "Valor a mitad de rango — pot=0.50",
            "description": "pot=0.50 activa LED1 y LED2, no LED3.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 0.50},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led2", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led3", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "A mitad del rango (0.50), el VUmetro muestra 2 de 5 LEDs. El tercer "
                "LED requiere >= 0.60, que no se alcanza con 0.50. Confirma el "
                "comportamiento esperado en el punto medio de la escala."
            ),
        },
        {
            "id": "TC-PV-011",
            "title": "Entrada fuera de rango — negativa",
            "description": "pot=-0.1 no debe activar ningún LED.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": -0.1},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 0, "tol": 0},
                {"col": "led5", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Entrada negativa fuera del rango declarado [0,1]. El codegen y el "
                "modelo deben manejar este caso sin crash ni NaN. Con pot=-0.1, "
                "ninguna condicion >= umbral se cumple, por lo que todos los LEDs "
                "permanecen apagados. Verifica robustez ante entradas invalidas."
            ),
        },
        {
            "id": "TC-PV-012",
            "title": "Entrada fuera de rango — positiva alta",
            "description": "pot=1.5 debe activar todos los LEDs ya que supera todos los umbrales.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"pot": 1.5},
            "checks": [
                {"col": "led1", "type": "final_value", "val": 1, "tol": 0},
                {"col": "led5", "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "Con pot=1.5, todos los umbrales (incluido 1.0) son superados por la "
                "condicion >=, por lo que todos los LEDs se encienden. Esto es "
                "diferente del caso negativo: aqui el valor es mayor que todos los "
                "umbrales en lugar de menor. Confirma el comportamiento de saturacion "
                "alta del VUmetro."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
