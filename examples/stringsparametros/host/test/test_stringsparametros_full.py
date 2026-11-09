#!/usr/bin/env python3
"""Test battery completa — StringsParametros (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "StringsParametros",
    "tests": [
        {
            "id": "TC-SP-001",
            "title": "Salida numerica basica — u=1.0",
            "description": "y = u * len_nombre = 1.0 * 34 = 34.0.",
            "t_end": 1.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y", "type": "final_value", "val": 34.0, "tol": 1e-9},
            ],
            "interpretation": (
                "El modelo tiene un path numerico simple: y = u * len_nombre = u * 34. "
                "Con u=1.0, y=34.0. Este test verifica que la parte numerica del "
                "modelo funciona aunque los parametros String sean complejos. "
                "La lectura de parametros String no debe interferir con el calculo numerico."
            ),
        },
        {
            "id": "TC-SP-002",
            "title": "Salida numerica con entrada negativa",
            "description": "u=-2.5: y = -2.5 * 34 = -85.0.",
            "t_end": 1.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": -2.5},
            "checks": [
                {"col": "y", "type": "final_value", "val": -85.0, "tol": 1e-9},
            ],
            "interpretation": (
                "La multiplicacion u*34 funciona con valores negativos. Verifica que "
                "fmi2SetReal maneja correctamente entradas negativas incluso en "
                "presencia de parametros String complejos en la FMU."
            ),
        },
        {
            "id": "TC-SP-003",
            "title": "Salida numerica con entrada cero",
            "description": "u=0.0: y = 0.0 * 34 = 0.0.",
            "t_end": 1.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 0.0},
            "checks": [
                {"col": "y", "type": "final_value", "val": 0.0, "tol": 1e-9},
            ],
            "interpretation": (
                "Entrada cero produce salida cero. El modelo no tiene estados ni "
                "integracion, es puramente algebraico (y=u*34). Con u=0, y=0 "
                "exactamente, sin residuos de los parametros String."
            ),
        },
        {
            "id": "TC-SP-004",
            "title": "Parametro String 'nombre' — sin truncamiento",
            "description": "El modelo debe inicializarse sin crash con nombre de 34 caracteres.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y", "type": "final_value", "val": 34.0, "tol": 1e-9},
                {"col": "y", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "El parametro 'nombre' tiene 34 caracteres incluyendo acento (ó), "
                "hash (#) y parentesis. Si el buffer del codegen es menor de 35 bytes, "
                "hay desbordamiento en la inicializacion. El modelo produce y=34 "
                "si y solo si la inicializacion se completo sin corrupcion de memoria."
            ),
        },
        {
            "id": "TC-SP-005",
            "title": "Parametro String 'ruta' con barras — sin truncamiento",
            "description": "El modelo se inicializa con ruta='/datos/planta/linea_A/modulo_02' (31 chars).",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 2.0},
            "checks": [
                {"col": "y", "type": "final_value", "val": 68.0, "tol": 1e-9},
            ],
            "interpretation": (
                "Las barras '/' en el parametro ruta no deben interpretarse como "
                "separadores de path en el codegen. Con u=2, y=68 confirma que "
                "la inicializacion fue exitosa y que las barras se tratan como "
                "caracteres literales en el String de FMI 2.0."
            ),
        },
        {
            "id": "TC-SP-006",
            "title": "Parametro String 'especial' con delimitadores '=;/' — sin truncamiento",
            "description": "especial='val=3.14;tag=alpha_beta;unit=m2/s': sin interpretacion erronea.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 3.0},
            "checks": [
                {"col": "y", "type": "final_value", "val": 102.0, "tol": 1e-9},
            ],
            "interpretation": (
                "El parametro 'especial' contiene = ; y / que podrian ser malinterpretados. "
                "Si el codegen usa = como delimitador de asignacion CLI, podria truncar "
                "el String en el primer '='. Con u=3, y=102 confirma que todos los "
                "caracteres especiales se trataron como parte del String."
            ),
        },
        {
            "id": "TC-SP-007",
            "title": "Parametro String 'vacio' — string vacio sin null pointer",
            "description": "vacio='': el modelo no debe crashear con String de longitud 0.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y", "type": "final_value", "val": 34.0, "tol": 1e-9},
                {"col": "y", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "TEST CRITICO. El String vacio es el caso mas comun de crash en "
                "codegen de FMU: fmi2GetString devuelve '' y el codegen llama "
                "strlen(NULL) o strcpy desde NULL. Si el modelo produce y=34 sin "
                "crash, el String vacio se maneja correctamente. Un crash aqui "
                "indica un null pointer dereference en la inicializacion."
            ),
        },
        {
            "id": "TC-SP-008",
            "title": "Parametro String 'unicode_str' — 27 caracteres ASCII",
            "description": "unicode_str='Angstrom [A] delta+-epsilon': inicializacion exitosa.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 4.0},
            "checks": [
                {"col": "y", "type": "final_value", "val": 136.0, "tol": 1e-9},
            ],
            "interpretation": (
                "El String con simbolos ASCII ([], +-) se almacena sin truncamiento. "
                "Aunque se llama 'unicode', son caracteres ASCII puros que el codegen "
                "debe manejar en un buffer de char sin conversion de encoding. "
                "Con u=4, y=136 confirma la inicializacion exitosa."
            ),
        },
        {
            "id": "TC-SP-009",
            "title": "Parametro String 'largo' — 98 caracteres sin truncamiento",
            "description": "largo='aaa...' (98 'a'): buffer debe ser >=99 bytes.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 5.0},
            "checks": [
                {"col": "y", "type": "final_value", "val": 170.0, "tol": 1e-9},
                {"col": "y", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "TEST DE DESBORDAMIENTO DE BUFFER. El String de 98 'a' requiere "
                "un buffer de al menos 99 bytes (98 chars + terminador nulo). "
                "Si el codegen usa char[32] o char[64], hay buffer overflow. "
                "Con u=5, y=170 indica que la inicializacion se completo sin "
                "corrupcion. Ejecutar con AddressSanitizer para mayor certeza."
            ),
        },
        {
            "id": "TC-SP-010",
            "title": "Estabilidad numerica a pesar de la complejidad de Strings",
            "description": "Simulacion larga: la complejidad de Strings no afecta el calculo numerico.",
            "t_end": 10.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y", "type": "always", "op": "==", "val": 34.0},
            ],
            "interpretation": (
                "El modelo algebraico puro y=u*34 debe producir exactamente 34.0 "
                "en todos los pasos de simulacion con u=1.0. La inicializacion "
                "de los 6 parametros String no debe dejar efectos residuales que "
                "modifiquen el calculo numerico en pasos posteriores. "
                "Confirmacion de la separacion entre parametros de inicializacion "
                "y el calculo de estado estacionario."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
