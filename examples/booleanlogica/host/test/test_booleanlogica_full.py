#!/usr/bin/env python3
"""Test battery completa — BooleanLogica (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "BooleanLogica",
    "tests": [
        {
            "id": "TC-BL-001",
            "title": "Tabla de verdad AND/OR/XOR — caso a=F b=F",
            "description": "a=FALSE, b=FALSE: y_and=FALSE, y_or=FALSE, y_xor=FALSE.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"a": 0, "b": 0, "clk": 0, "umbral": 0.0},
            "checks": [
                {"col": "y_and", "type": "final_value", "val": 0, "tol": 0},
                {"col": "y_or",  "type": "final_value", "val": 0, "tol": 0},
                {"col": "y_xor", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Fila (F,F) de la tabla de verdad. Todos los outputs combinacionales son "
                "FALSE: AND(F,F)=F, OR(F,F)=F, XOR(F,F)=F. Si alguno devuelve TRUE con "
                "ambas entradas a FALSE, hay un error en la generacion de la expresion "
                "logica combinacional. clk=FALSE evita disparos de flanco."
            ),
        },
        {
            "id": "TC-BL-002",
            "title": "XOR: a=TRUE b=TRUE → y_xor=FALSE",
            "description": "Cuando a==b, XOR debe ser FALSE. Caso a=T, b=T.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"a": 1, "b": 1, "clk": 0, "umbral": 0.0},
            "checks": [
                {"col": "y_and", "type": "final_value", "val": 1, "tol": 0},
                {"col": "y_or",  "type": "final_value", "val": 1, "tol": 0},
                {"col": "y_xor", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Fila (T,T) de la tabla de verdad. AND(T,T)=T, OR(T,T)=T, pero "
                "XOR(T,T)=FALSE (igual a distinto: no lo son). Un error comun de "
                "codegen es generar OR en lugar de XOR, lo que daria TRUE aqui. "
                "Este test es el discriminador directo de la implementacion XOR."
            ),
        },
        {
            "id": "TC-BL-003",
            "title": "XOR: a=FALSE b=TRUE → y_xor=TRUE",
            "description": "Entradas distintas: XOR debe ser TRUE.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"a": 0, "b": 1, "clk": 0, "umbral": 0.5},
            "checks": [
                {"col": "y_and",           "type": "final_value", "val": 0, "tol": 0},
                {"col": "y_or",            "type": "final_value", "val": 1, "tol": 0},
                {"col": "y_xor",           "type": "final_value", "val": 1, "tol": 0},
                {"col": "above_threshold", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Fila (F,T): AND(F,T)=F, OR(F,T)=T, XOR(F,T)=T. Tambien verifica "
                "above_threshold con umbral=0.5 (limite exacto): 0.5 NO > 0.5 → FALSE. "
                "La condicion es estricta >. Si above_threshold devuelve TRUE con "
                "umbral=0.5 exacto, la condicion usa >= en lugar de >."
            ),
        },
        {
            "id": "TC-BL-004",
            "title": "above_threshold: umbral > 0.5 → TRUE, umbral <= 0.5 → FALSE",
            "description": "Boundary condition: umbral=0.5001 → TRUE, umbral=0.5 → FALSE.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"a": 1, "b": 0, "clk": 0, "umbral": 0.5001},
            "checks": [
                {"col": "y_xor",           "type": "final_value", "val": 1, "tol": 0},
                {"col": "above_threshold", "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "Con umbral=0.5001 > 0.5, above_threshold=TRUE. La diferencia con "
                "TC-BL-003 (umbral=0.5 → FALSE) confirma el operador estricto >. "
                "Tambien: a=T,b=F → XOR(T,F)=T. AND(T,F)=F, OR(T,F)=T. Verifica "
                "la conversion fmi2SetReal → Boolean en la misma iteracion."
            ),
        },
        {
            "id": "TC-BL-005",
            "title": "D-latch: captura a=TRUE en flanco ascendente de clk",
            "description": "a=TRUE, clk: 0→1. y_latch pasa de FALSE a TRUE en el flanco.",
            "t_end": 2.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"a": 1, "b": 0, "clk": 0, "umbral": 0.0},
            "schedule": {"clk": [(0, 0), (1.0, 1)]},
            "checks": [
                {"col": "y_latch",       "type": "at_t", "at_t": 0.5, "val": 0, "tol": 0},
                {"col": "y_latch",       "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "cuenta_flancos","type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
            ],
            "interpretation": (
                "clk permanece en FALSE hasta t=1.0 (sin flanco). y_latch=FALSE en t=0.5. "
                "En t=1.0, clk: FALSE→TRUE (flanco ascendente). La latch captura a=TRUE. "
                "En t=1.5: y_latch=TRUE, cuenta_flancos=1. Verifica que edge()/when "
                "se genera correctamente para capturar el valor de 'a' en el flanco."
            ),
        },
        {
            "id": "TC-BL-006",
            "title": "D-latch: captura a=FALSE en flanco — latch no es level-triggered",
            "description": "a=FALSE en flanco, despues a→TRUE (sin flanco): y_latch permanece FALSE.",
            "t_end": 3.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"a": 0, "b": 0, "clk": 0, "umbral": 0.0},
            "schedule": {
                "clk": [(0, 0), (1.0, 1), (2.0, 1)],
                "a":   [(0, 0), (2.0, 1)],
            },
            "checks": [
                {"col": "y_latch", "type": "at_t", "at_t": 1.5, "val": 0, "tol": 0},
                {"col": "y_latch", "type": "at_t", "at_t": 2.5, "val": 0, "tol": 0},
                {"col": "cuenta_flancos", "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "En t=1.0: flanco ascendente de clk, a=FALSE → y_latch captura FALSE. "
                "En t=2.0: a cambia a TRUE pero clk permanece TRUE (no hay flanco). "
                "La latch NO actualiza: y_latch=FALSE en t=2.5. "
                "Si y_latch fuera level-triggered, cambiaria cuando a=TRUE. "
                "cuenta_flancos=1 (solo un flanco ascendente total)."
            ),
        },
        {
            "id": "TC-BL-007",
            "title": "Contador de flancos — 3 flancos ascendentes",
            "description": "3 transiciones FALSE→TRUE en clk: cuenta_flancos=3 al final.",
            "t_end": 6.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"a": 0, "b": 0, "clk": 0, "umbral": 0.0},
            "schedule": {"clk": [(0, 0), (1.0, 1), (2.0, 0), (3.0, 1), (4.0, 0), (5.0, 1)]},
            "checks": [
                {"col": "cuenta_flancos", "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "cuenta_flancos", "type": "at_t", "at_t": 3.5, "val": 2, "tol": 0},
                {"col": "cuenta_flancos", "type": "final_value", "val": 3, "tol": 0},
            ],
            "interpretation": (
                "Tres ciclos completos: 0→1 en t=1, 3, 5. Los flancos descendentes "
                "(1→0 en t=2, 4) no deben incrementar. cuenta_flancos debe ser "
                "exactamente 1, 2, 3 respectivamente. Si el contador incrementa en "
                "flancos descendentes, edge() fue sustituido por deteccion de nivel. "
                "Si se queda en 0, el when/edge no fue generado por el codegen."
            ),
        },
        {
            "id": "TC-BL-008",
            "title": "Sin doble conteo — clk=TRUE mantenido no cuenta multiples flancos",
            "description": "clk=TRUE por 3 pasos seguidos: cuenta_flancos=1 (solo el primer flanco).",
            "t_end": 5.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"a": 0, "b": 0, "clk": 0, "umbral": 0.0},
            "schedule": {"clk": [(0, 0), (1.0, 1), (2.0, 1), (3.0, 1), (4.0, 0)]},
            "checks": [
                {"col": "cuenta_flancos", "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "cuenta_flancos", "type": "at_t", "at_t": 2.5, "val": 1, "tol": 0},
                {"col": "cuenta_flancos", "type": "at_t", "at_t": 3.5, "val": 1, "tol": 0},
                {"col": "cuenta_flancos", "type": "final_value",        "val": 1, "tol": 0},
            ],
            "interpretation": (
                "TEST CRITICO DE DOBLE CONTEO. clk permanece TRUE durante t=1,2,3 s. "
                "Solo hay UN flanco ascendente (0→1 en t=1). El contador debe "
                "mantenerse en 1 mientras clk=TRUE, no incrementar a 2, 3... "
                "Si el codegen genera 'if clk' en lugar de 'if edge(clk)', "
                "el contador incrementaria en cada paso con clk=TRUE."
            ),
        },
        {
            "id": "TC-BL-009",
            "title": "Todos los inputs activos simultaneamente — salidas combinadas",
            "description": "a=T, b=T, clk: 0→1 (flanco), umbral=1.0: todos outputs activos.",
            "t_end": 2.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"a": 1, "b": 1, "clk": 0, "umbral": 1.0},
            "schedule": {"clk": [(0, 0), (1.0, 1)]},
            "checks": [
                {"col": "y_and",           "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "y_or",            "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "y_xor",           "type": "at_t", "at_t": 1.5, "val": 0, "tol": 0},
                {"col": "y_latch",         "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "cuenta_flancos",  "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "above_threshold", "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
            ],
            "interpretation": (
                "Con a=T, b=T, clk: 0→1 y umbral=1.0, todos los outputs deben "
                "activarse (excepto y_xor=FALSE porque a==b). Verifica el orden "
                "de lectura de todos los tipos: fmi2SetBoolean(a,b,clk), "
                "fmi2SetReal(umbral) antes del paso; luego fmi2GetBoolean(y_and,...), "
                "fmi2GetInteger(cuenta_flancos). Si algun get se ejecuta fuera de orden, "
                "los outputs seran inconsistentes."
            ),
        },
        {
            "id": "TC-BL-010",
            "title": "Reset a cero — outputs combinacionales inmediatos, secuenciales retenidos",
            "description": "Tras flancos previos: a=F, b=F, clk=F → combinacional=F, latch y contador retenidos.",
            "t_end": 4.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"a": 1, "b": 1, "clk": 0, "umbral": 1.0},
            "schedule": {
                "clk":   [(0, 0), (1.0, 1), (2.0, 0)],
                "a":     [(0, 1), (3.0, 0)],
                "b":     [(0, 1), (3.0, 0)],
                "umbral": [(0, 1.0), (3.0, 0.0)],
            },
            "checks": [
                {"col": "y_and",           "type": "final_value", "val": 0, "tol": 0},
                {"col": "y_or",            "type": "final_value", "val": 0, "tol": 0},
                {"col": "y_xor",           "type": "final_value", "val": 0, "tol": 0},
                {"col": "above_threshold", "type": "final_value", "val": 0, "tol": 0},
                {"col": "y_latch",         "type": "final_value", "val": 1, "tol": 0},
                {"col": "cuenta_flancos",  "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "En t=3: a=F, b=F, clk=F, umbral=0. Los outputs combinacionales "
                "(y_and, y_or, y_xor, above_threshold) cambian a FALSE inmediatamente. "
                "Pero y_latch=TRUE (capturada en el flanco de t=1 con a=TRUE) y "
                "cuenta_flancos=1 se retienen sin nuevos flancos. Confirma que "
                "combinacional e secuencial se comportan de manera diferente."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
