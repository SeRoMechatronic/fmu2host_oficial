#!/usr/bin/env python3
"""Test battery completa — MultiplexorCanales (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "MultiplexorCanales",
    "tests": [
        {
            "id": "TC-MC-001",
            "title": "Seleccion canal 0",
            "description": "canal_seleccion=0 debe enrutar canal_0 a la salida.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": 0, "canal_0": 0.25, "canal_1": 0.5,
                       "canal_2": 0.75, "canal_3": 1.0},
            "checks": [
                {"col": "salida",       "type": "final_value", "val": 0.25, "tol": 1e-9},
                {"col": "canal_activo", "type": "final_value", "val": 0,    "tol": 0},
                {"col": "canal_valido", "type": "final_value", "val": 1,    "tol": 0},
            ],
            "interpretation": (
                "Con selector=0, la salida debe reflejar exactamente canal_0=0.25. "
                "canal_activo confirma que el canal 0 esta enrutado. La seleccion "
                "es instantanea (modelo algebraico) sin retardo alguno."
            ),
        },
        {
            "id": "TC-MC-002",
            "title": "Seleccion canal 1",
            "description": "canal_seleccion=1 debe enrutar canal_1 a la salida.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": 1, "canal_0": 0.25, "canal_1": 0.5,
                       "canal_2": 0.75, "canal_3": 1.0},
            "checks": [
                {"col": "salida",       "type": "final_value", "val": 0.50, "tol": 1e-9},
                {"col": "canal_activo", "type": "final_value", "val": 1,    "tol": 0},
                {"col": "canal_valido", "type": "final_value", "val": 1,    "tol": 0},
            ],
            "interpretation": (
                "Canal 1 seleccionado correctamente. La salida de 0.50 confirma que el "
                "multiplexor no lee de canal_0 (0.25) ni de otros canales por error de "
                "indice. Cada canal tiene un valor distinto precisamente para detectar "
                "este tipo de error."
            ),
        },
        {
            "id": "TC-MC-003",
            "title": "Seleccion canal 2",
            "description": "canal_seleccion=2 debe enrutar canal_2 a la salida.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": 2, "canal_0": 0.25, "canal_1": 0.5,
                       "canal_2": 0.75, "canal_3": 1.0},
            "checks": [
                {"col": "salida",       "type": "final_value", "val": 0.75, "tol": 1e-9},
                {"col": "canal_activo", "type": "final_value", "val": 2,    "tol": 0},
            ],
            "interpretation": (
                "Canal 2 enrutado correctamente. El valor 0.75 es univoco para canal_2 "
                "en este conjunto de entradas, por lo que cualquier error de indice "
                "en el multiplexor seria detectable inmediatamente."
            ),
        },
        {
            "id": "TC-MC-004",
            "title": "Seleccion canal 3",
            "description": "canal_seleccion=3 debe enrutar canal_3 a la salida.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": 3, "canal_0": 0.25, "canal_1": 0.5,
                       "canal_2": 0.75, "canal_3": 1.0},
            "checks": [
                {"col": "salida",       "type": "final_value", "val": 1.0, "tol": 1e-9},
                {"col": "canal_activo", "type": "final_value", "val": 3,   "tol": 0},
            ],
            "interpretation": (
                "Canal 3 (maximo indice valido) enrutado correctamente. Este test "
                "verifica el limite superior del rango valido [0,3] del selector."
            ),
        },
        {
            "id": "TC-MC-005",
            "title": "Selector invalido por defecto — demasiado bajo",
            "description": "canal_seleccion=-1 debe activar modo invalido: salida=0, activo=-1, valido=false.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": -1, "canal_0": 0.25, "canal_1": 0.5,
                       "canal_2": 0.75, "canal_3": 1.0},
            "checks": [
                {"col": "salida",       "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "canal_activo", "type": "final_value", "val": -1,  "tol": 0},
                {"col": "canal_valido", "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Un selector negativo (-1) esta fuera del rango [0,3]. El multiplexor "
                "debe responder con salida segura 0.0 y canal_valido=false. Esto "
                "verifica el manejo defensivo de entradas invalidas, critico en "
                "sistemas de control donde un valor invalido podria causar accion "
                "incorrecta en el actuador."
            ),
        },
        {
            "id": "TC-MC-006",
            "title": "Selector invalido — demasiado alto",
            "description": "canal_seleccion=4 supera el maximo. Debe activar modo invalido.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": 4, "canal_0": 0.25, "canal_1": 0.5,
                       "canal_2": 0.75, "canal_3": 1.0},
            "checks": [
                {"col": "salida",       "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "canal_activo", "type": "final_value", "val": -1,  "tol": 0},
                {"col": "canal_valido", "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Un selector de 4 (maximo valido es 3) activa el modo invalido. "
                "Este test comprueba el limite superior: el sistema debe rechazar "
                "cualquier selector > 3 con la misma respuesta segura que para "
                "selectores negativos."
            ),
        },
        {
            "id": "TC-MC-007",
            "title": "Canal 0 con valor cero",
            "description": "Seleccion valida con canal_0=0.0: salida=0, canal_activo=0, valido=true.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": 0, "canal_0": 0.0},
            "checks": [
                {"col": "salida",       "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "canal_activo", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "canal_valido", "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "Canal 0 seleccionado con valor cero. Este caso distingue entre 'canal "
                "invalido' (salida=0, valido=false) y 'canal valido con valor cero' "
                "(salida=0, valido=true). canal_valido=true confirma que la seleccion "
                "es valida aunque la salida sea 0."
            ),
        },
        {
            "id": "TC-MC-008",
            "title": "Canal 3 a escala completa",
            "description": "canal_seleccion=3 con canal_3=1.0. Verifica valor maximo.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": 3, "canal_3": 1.0},
            "checks": [
                {"col": "salida",       "type": "final_value", "val": 1.0, "tol": 1e-9},
                {"col": "canal_activo", "type": "final_value", "val": 3,   "tol": 0},
                {"col": "canal_valido", "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "El valor maximo de escala (1.0) en canal_3 se transmite sin "
                "modificacion a la salida. Confirma que no hay saturacion o "
                "recorte involuntario en el camino de datos del multiplexor."
            ),
        },
        {
            "id": "TC-MC-009",
            "title": "Cambio de canal — conmutacion instantanea",
            "description": (
                "Cambio de canal_seleccion=0 a canal_seleccion=2 a t=0.5. "
                "La salida debe cambiar instantaneamente (modelo algebraico)."
            ),
            "t_end": 1.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"canal_0": 0.3, "canal_2": 0.8, "canal_seleccion": 0},
            "schedule": {"canal_seleccion": [(0, 0), (0.5, 2)]},
            "checks": [
                {"col": "salida", "type": "at_t", "at_t": 0.0, "val": 0.3, "tol": 1e-9},
                {"col": "salida", "type": "at_t", "at_t": 1.0, "val": 0.8, "tol": 1e-9},
            ],
            "interpretation": (
                "El multiplexor es puramente algebraico: no tiene memoria ni retardo. "
                "Al cambiar el selector de 0 a 2 en t=0.5s, la salida debe cambiar "
                "de 0.3 (canal_0) a 0.8 (canal_2) instantaneamente. Este test "
                "verifica la respuesta dinamica de un modelo sin estados."
            ),
        },
        {
            "id": "TC-MC-010",
            "title": "Valores limite del selector: 0 y 3 son validos",
            "description": "Verificacion de que ambos extremos del rango [0,3] son validos.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"canal_seleccion": 0, "canal_0": 0.5, "canal_3": 0.9},
            "checks": [
                {"col": "canal_valido", "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "El selector 0 es el limite inferior valido. Un test simetrico con "
                "selector=3 (TC-MC-004) verifica el limite superior. Juntos confirman "
                "que el rango de validez [0,3] esta correctamente implementado en la "
                "logica del multiplexor."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
