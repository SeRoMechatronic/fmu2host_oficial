#!/usr/bin/env python3
"""Test battery completa — SelectorModo (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "SelectorModo",
    "tests": [
        {
            "id": "TC-SM-001",
            "title": "Modo Manual — consigna pasada directamente",
            "description": "modo_operacion=0 pasa consigna_manual=0.70 a la salida.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 0, "consigna_manual": 0.70},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 0.70, "tol": 1e-9},
                {"col": "codigo_estado",   "type": "final_value", "val": 1,    "tol": 0},
                {"col": "fallo_modo",      "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "En modo Manual (0), la consigna del operador se transfiere directamente "
                "al actuador. El codigo de estado 1 confirma que el modo es Manual, "
                "y fallo_modo=false indica seleccion valida. El valor exacto 0.70 "
                "confirma que no hay modificacion de la consigna en este modo."
            ),
        },
        {
            "id": "TC-SM-002",
            "title": "Modo Manual — consigna minima",
            "description": "modo_operacion=0 con consigna_manual=0.0: salida=0.0.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 0, "consigna_manual": 0.0},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "codigo_estado",   "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "Consigna nula en modo Manual: el actuador recibe 0.0. Verifica que "
                "el modo Manual acepta el valor minimo del rango sin activar ninguna "
                "logica de proteccion o modo de fallo."
            ),
        },
        {
            "id": "TC-SM-003",
            "title": "Modo Manual — consigna maxima",
            "description": "modo_operacion=0 con consigna_manual=1.0: salida=1.0.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 0, "consigna_manual": 1.0},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 1.0, "tol": 1e-9},
                {"col": "codigo_estado",   "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "Consigna a escala completa en modo Manual. Confirma que el rango "
                "normalizado [0,1] se transmite sin recorte cuando la consigna esta "
                "exactamente en el limite superior."
            ),
        },
        {
            "id": "TC-SM-004",
            "title": "Modo Manual — consigna recortada por encima de 1.0",
            "description": "consigna_manual=1.5 debe recortarse a 1.0.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 0, "consigna_manual": 1.5},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 1.0, "tol": 1e-9},
                {"col": "fallo_modo",      "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Una consigna fuera del rango fisico [0,1] debe recortarse al maximo "
                "permitido. La funcion clamp evita que el actuador reciba comandos "
                "superiores a la escala completa, protegiendo el hardware. fallo_modo "
                "sigue siendo false porque el modo de operacion (0) es valido."
            ),
        },
        {
            "id": "TC-SM-005",
            "title": "Modo Manual — consigna recortada por debajo de 0.0",
            "description": "consigna_manual=-0.3 debe recortarse a 0.0.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 0, "consigna_manual": -0.3},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "fallo_modo",      "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Consigna negativa recortada a cero. En muchos sistemas de control, "
                "una consigna negativa de actuador no tiene sentido fisico (ej. bomba "
                "que no puede girar al reves). El recorte inferior protege el actuador "
                "de comandos fuera de su rango fisico de operacion."
            ),
        },
        {
            "id": "TC-SM-006",
            "title": "Modo Automatico — salida fija al 50%",
            "description": "modo_operacion=1: salida fija=0.5 independientemente de consigna.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 1, "consigna_manual": 0.90},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 0.5, "tol": 1e-9},
                {"col": "codigo_estado",   "type": "final_value", "val": 10,  "tol": 0},
                {"col": "fallo_modo",      "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "En modo Automatico (1), el sistema ignora la consigna manual y aplica "
                "un setpoint interno fijo del 50%. Aunque consigna_manual=0.90, la "
                "salida es 0.5. El codigo_estado=10 identifica el modo Automatico. "
                "Este comportamiento modela un controlador autonomo que no acepta "
                "interferencia manual."
            ),
        },
        {
            "id": "TC-SM-007",
            "title": "Modo Emergencia — salida forzada a cero",
            "description": "modo_operacion=2: salida=0.0 independientemente de consigna.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 2, "consigna_manual": 0.90},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "codigo_estado",   "type": "final_value", "val": 99,  "tol": 0},
                {"col": "fallo_modo",      "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "El modo Emergencia (2) fuerza la salida a cero sin importar la "
                "consigna. codigo_estado=99 es un codigo especial que identifica "
                "inequivocamente la emergencia. Este mecanismo garantiza la parada "
                "segura del actuador en cualquier condicion de emergencia."
            ),
        },
        {
            "id": "TC-SM-008",
            "title": "Modo invalido — por debajo del rango",
            "description": "modo_operacion=-1 debe activar fallo_modo=true y salida=0.0.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": -1, "consigna_manual": 0.5},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "codigo_estado",   "type": "final_value", "val": -1,  "tol": 0},
                {"col": "fallo_modo",      "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "Un modo de operacion invalido (-1) activa fallo_modo y forza la "
                "salida a cero como medida de seguridad. codigo_estado=-1 es el "
                "codigo de fallo. Este comportamiento defensivo es esencial: ante "
                "un comando de modo no reconocido, el sistema debe fallar de forma "
                "segura en lugar de comportarse de forma impredecible."
            ),
        },
        {
            "id": "TC-SM-009",
            "title": "Modo invalido — por encima del rango",
            "description": "modo_operacion=5 debe activar fallo_modo=true y salida=0.0.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 5, "consigna_manual": 0.5},
            "checks": [
                {"col": "salida_actuador", "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "codigo_estado",   "type": "final_value", "val": -1,  "tol": 0},
                {"col": "fallo_modo",      "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "Modo invalido por exceso (5, cuando el maximo es 2). El comportamiento "
                "es identico al modo invalido por defecto: salida segura a 0, "
                "codigo -1, y fallo_modo activado. Verifica que el rango valido [0,2] "
                "esta correctamente delimitado en ambos extremos."
            ),
        },
        {
            "id": "TC-SM-010",
            "title": "Limite de modo — exactamente 2 es Emergencia valida",
            "description": "modo_operacion=2 es el maximo valido: debe ser Emergencia, no fallo.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"modo_operacion": 2, "consigna_manual": 0.0},
            "checks": [
                {"col": "fallo_modo",    "type": "final_value", "val": 0,  "tol": 0},
                {"col": "codigo_estado", "type": "final_value", "val": 99, "tol": 0},
                {"col": "salida_actuador","type": "final_value","val": 0.0,"tol": 1e-9},
            ],
            "interpretation": (
                "El modo 2 (Emergencia) es el limite superior valido del rango [0,2]. "
                "fallo_modo=false confirma que el selector no lo interpreta como "
                "invalido. Este test hace de guardia contra errores off-by-one en "
                "la condicion de validacion: si el rango se implementara como [0,1] "
                "por error, el modo 2 se clasificaria como fallo en lugar de emergencia."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
