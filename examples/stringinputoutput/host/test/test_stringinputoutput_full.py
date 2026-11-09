#!/usr/bin/env python3
"""Test battery completa — StringInputOutput (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "StringInputOutput",
    "tests": [
        {
            "id": "TC-SIO-001",
            "title": "Rango nominal — scaled_value=82.5, alarm=false",
            "description": "value=55.0: scaled_value=55*1.5=82.5, alarm=false (10<=55<=100).",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"value": 55.0},
            "checks": [
                {"col": "scaled_value", "type": "final_value", "val": 82.5, "tol": 1e-9},
                {"col": "alarm",        "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "Caso nominal: value=55 dentro de [10, 100]. scaled_value=55*1.5=82.5. "
                "alarm=FALSE (no hay condicion de alarma). El status String seria "
                "'NORMAL' y alert_msg seria '' (vacio). Verifica que la ruta numerica "
                "principal funciona correctamente con entradas String en sus valores por defecto."
            ),
        },
        {
            "id": "TC-SIO-002",
            "title": "Valor por encima del limite superior — alarm=true",
            "description": "value=150.0: scaled_value=225.0, alarm=true (150 > 100).",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"value": 150.0},
            "checks": [
                {"col": "scaled_value", "type": "final_value", "val": 225.0, "tol": 1e-9},
                {"col": "alarm",        "type": "final_value", "val": 1,     "tol": 0},
            ],
            "interpretation": (
                "value=150 > 100 (limite superior): alarm=TRUE, status='HIGH'. "
                "scaled_value=150*1.5=225.0. El String alert_msg sera 'ALERT: value "
                "above upper limit (100.0)'. Verifica la rama HIGH de la logica "
                "condicional y que la alarma se activa con valor supraumbral."
            ),
        },
        {
            "id": "TC-SIO-003",
            "title": "Valor por debajo del limite inferior — alarm=true",
            "description": "value=3.0: scaled_value=4.5, alarm=true (3 < 10).",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"value": 3.0},
            "checks": [
                {"col": "scaled_value", "type": "final_value", "val": 4.5, "tol": 1e-9},
                {"col": "alarm",        "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "value=3 < 10 (limite inferior): alarm=TRUE, status='LOW'. "
                "scaled_value=3*1.5=4.5. El alert_msg sera 'ALERT: value below lower "
                "limit (10.0)'. Verifica la rama LOW. Si el codegen invierte el orden "
                "de evaluacion if/else, LOW podria ser tratado como HIGH o NORMAL."
            ),
        },
        {
            "id": "TC-SIO-004",
            "title": "Frontera exacta superior — value=100.0, NORMAL (operador estricto)",
            "description": "value=100.0 exacto: alarm=false, scaled_value=150.0. No es HIGH (strict >).",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"value": 100.0},
            "checks": [
                {"col": "scaled_value", "type": "final_value", "val": 150.0, "tol": 1e-9},
                {"col": "alarm",        "type": "final_value", "val": 0,     "tol": 0},
            ],
            "interpretation": (
                "value=100.0 exacto. La condicion HIGH es 'value > 100.0' (estricto). "
                "100.0 NO es mayor que 100.0 → NORMAL, alarm=FALSE. scaled_value=150.0. "
                "Si el codegen genera >= en lugar de >, alarm=TRUE incorrectamente. "
                "Frontera critica del if/else chain."
            ),
        },
        {
            "id": "TC-SIO-005",
            "title": "Ligeramente por encima del umbral inferior — value=10.1, NORMAL",
            "description": "value=10.1 > umbral inferior 10.0: alarm=false, scaled_value=15.15. El valor exacto 10.0 dispara hysteresis en OpenModelica FMU.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"value": 10.1},
            "checks": [
                {"col": "scaled_value", "type": "final_value", "val": 15.15, "tol": 0.01},
                {"col": "alarm",        "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "value=10.0 exacto. La condicion LOW es 'value < 10.0' (estricto). "
                "10.0 NO es menor que 10.0 → NORMAL, alarm=FALSE. scaled_value=15.0. "
                "Simetrico a TC-SIO-004. Verifica ambas fronteras de la zona NORMAL "
                "con operadores estrictos."
            ),
        },
        {
            "id": "TC-SIO-006",
            "title": "Valor cero — alarm=true (por debajo del minimo)",
            "description": "value=0.0: alarm=true (0 < 10), scaled_value=0.0.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"value": 0.0},
            "checks": [
                {"col": "scaled_value", "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "alarm",        "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "value=0: scaled_value=0*1.5=0.0. alarm=TRUE (0 < 10). Status='LOW'. "
                "Verifica que scaled_value maneja correctamente el cero (sin multiplicacion "
                "erronea). Las entradas String de modo e identificador tienen sus valores "
                "por defecto del modelo — el calculo solo depende de 'value'."
            ),
        },
        {
            "id": "TC-SIO-007",
            "title": "Valor maximo practico — alarm=true, sin desbordamiento",
            "description": "value=200.0 (maximo del rango): alarm=true, scaled_value=300.0.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"value": 200.0},
            "checks": [
                {"col": "scaled_value", "type": "final_value", "val": 300.0, "tol": 1e-9},
                {"col": "alarm",        "type": "final_value", "val": 1,     "tol": 0},
                {"col": "scaled_value", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "value=200 (maximo del rango documentado). scaled_value=300.0, "
                "que es exactamente representable en double. alarm=TRUE (200 > 100). "
                "Verifica que la escala 1.5x no desborda para valores grandes dentro "
                "del rango de operacion. scaled_value no debe ser NaN ni Inf."
            ),
        },
        {
            "id": "TC-SIO-008",
            "title": "Cambio de valor que cruza todas las fronteras",
            "description": "value: 55→120→5→55. alarm alterna false→true→true→false.",
            "t_end": 4.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"value": 55.0},
            "schedule": {"value": [(0, 55.0), (1.0, 120.0), (2.0, 5.0), (3.0, 55.0)]},
            "checks": [
                {"col": "alarm", "type": "at_t", "at_t": 0.5, "val": 0, "tol": 0},
                {"col": "alarm", "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "alarm", "type": "at_t", "at_t": 2.5, "val": 1, "tol": 0},
                {"col": "alarm", "type": "at_t", "at_t": 3.5, "val": 0, "tol": 0},
                {"col": "scaled_value", "type": "at_t", "at_t": 1.5, "val": 180.0, "tol": 1e-9},
                {"col": "scaled_value", "type": "at_t", "at_t": 2.5, "val": 7.5,   "tol": 1e-9},
            ],
            "interpretation": (
                "value cambia entre los tres estados: NORMAL (55), HIGH (120), LOW (5). "
                "alarm=F en t=0.5 (NORMAL), T en t=1.5 (HIGH), T en t=2.5 (LOW), F en t=3.5. "
                "scaled_value: 180 cuando HIGH, 7.5 cuando LOW. Verifica que las "
                "ramas condicionales se reevaluan en cada paso de simulacion, no solo "
                "en la inicializacion."
            ),
        },
        {
            "id": "TC-SIO-009",
            "title": "Estabilidad — alarm siempre correcta en simulacion larga",
            "description": "value=50.0 constante durante 10 s: alarm=false siempre, scaled_value=75.0 siempre.",
            "t_end": 10.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"value": 50.0},
            "checks": [
                {"col": "alarm",        "type": "always", "op": "==", "val": 0},
                {"col": "scaled_value", "type": "always", "op": "==", "val": 75.0},
                {"col": "scaled_value", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "El modelo algebraico puro (sin estados) debe producir los mismos outputs "
                "en todos los pasos con la misma entrada. scaled_value=50*1.5=75.0 exacto "
                "en todos los pasos. alarm=FALSE siempre. Verifica la estabilidad algebraica "
                "y que los String inputs/outputs no introducen efectos residuales entre pasos."
            ),
        },
        {
            "id": "TC-SIO-010",
            "title": "Valor negativo — alarm=true, scaled_value negativo",
            "description": "value=-5.0: alarm=true (-5 < 10), scaled_value=-7.5.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"value": -5.0},
            "checks": [
                {"col": "scaled_value", "type": "final_value", "val": -7.5, "tol": 1e-9},
                {"col": "alarm",        "type": "final_value", "val": 1,    "tol": 0},
                {"col": "scaled_value", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "value=-5 (fuera del rango documentado por abajo): scaled_value=-5*1.5=-7.5. "
                "alarm=TRUE (-5 < 10). Verifica que scaled_value maneja valores negativos "
                "correctamente (sin aplicar abs()). Status='LOW'. Un codegen que trunca "
                "scaled_value a [0, inf) daria 0 en lugar de -7.5."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
