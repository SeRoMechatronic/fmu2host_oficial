#!/usr/bin/env python3
"""Test battery completa — ContadorEventos (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

# Schedule helper: N rising edges on 'evento' starting at t=0, one every 2*h
def _sched_edges(n, h=0.5):
    """Generate N rising edges on evento: 0→1→0→1..., one rising edge every 2*h."""
    s = [(0, 0)]
    for i in range(n):
        s.append((round((2*i + 1) * h, 3), 1))
        s.append((round((2*i + 2) * h, 3), 0))
    return s

# 100 rising edges for saturation test
_sched_100 = _sched_edges(100, h=0.1)   # t_end must be >= 100*2*0.1 = 20.0
_sched_10  = _sched_edges(10,  h=0.5)   # t_end >= 10.0
_sched_47  = _sched_edges(47,  h=0.1)   # t_end >= 9.5, use 10.0

CONFIG = {
    "model_name": "ContadorEventos",
    "tests": [
        {
            "id": "TC-CE-001",
            "title": "Estado inicial — contador en cero",
            "description": "Sin eventos ni reset: cuenta=0, decenas=0, unidades=0, desbordamiento=false.",
            "t_end": 0.5, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "checks": [
                {"col": "cuenta",         "type": "at_t", "at_t": 0.0, "val": 0, "tol": 0},
                {"col": "decenas",        "type": "at_t", "at_t": 0.0, "val": 0, "tol": 0},
                {"col": "unidades",       "type": "at_t", "at_t": 0.0, "val": 0, "tol": 0},
                {"col": "desbordamiento", "type": "at_t", "at_t": 0.0, "val": 0, "tol": 0},
            ],
            "interpretation": (
                "El modelo arranca con contador=0. Con evento=FALSE y reset=FALSE, "
                "no se producen flancos y el contador permanece en cero. decenas=0, "
                "unidades=0 (div y mod de 0). desbordamiento=FALSE (0 < 99). "
                "Verifica que el estado discreto se inicializa correctamente."
            ),
        },
        {
            "id": "TC-CE-002",
            "title": "Un solo evento — contador pasa a 1",
            "description": "1 flanco ascendente en evento: cuenta=1, decenas=0, unidades=1.",
            "t_end": 2.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {"evento": [(0, 0), (0.5, 1), (1.0, 0)]},
            "checks": [
                {"col": "cuenta",         "type": "final_value", "val": 1, "tol": 0},
                {"col": "decenas",        "type": "final_value", "val": 0, "tol": 0},
                {"col": "unidades",       "type": "final_value", "val": 1, "tol": 0},
                {"col": "desbordamiento", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Un unico flanco ascendente (FALSE→TRUE en t=0.5). El contador pasa "
                "de 0 a 1. decenas=div(1,10)=0, unidades=mod(1,10)=1. "
                "desbordamiento=FALSE (1 < 99). Verifica el incremento minimo "
                "y que el flanco descendente (TRUE→FALSE en t=1.0) no cuenta."
            ),
        },
        {
            "id": "TC-CE-003",
            "title": "Diez eventos — descomposicion BCD: decenas=1, unidades=0",
            "description": "10 flancos ascendentes: cuenta=10, decenas=1, unidades=0.",
            "t_end": 11.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {"evento": _sched_edges(10, h=0.5)},
            "checks": [
                {"col": "cuenta",   "type": "final_value", "val": 10, "tol": 0},
                {"col": "decenas",  "type": "final_value", "val": 1,  "tol": 0},
                {"col": "unidades", "type": "final_value", "val": 0,  "tol": 0},
            ],
            "interpretation": (
                "10 flancos ascendentes generan cuenta=10. La descomposicion BCD: "
                "decenas=div(10,10)=1, unidades=mod(10,10)=0. Verifica la transicion "
                "de digito en la decena. Un error de off-by-one daria cuenta=9 o 11, "
                "y la descomposicion BCD seria incorrecta."
            ),
        },
        {
            "id": "TC-CE-004",
            "title": "47 eventos — BCD arbitrario: decenas=4, unidades=7",
            "description": "47 flancos ascendentes: cuenta=47, decenas=4, unidades=7.",
            "t_end": 10.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {"evento": _sched_47},
            "checks": [
                {"col": "cuenta",         "type": "final_value", "val": 47, "tol": 0},
                {"col": "decenas",        "type": "final_value", "val": 4,  "tol": 0},
                {"col": "unidades",       "type": "final_value", "val": 7,  "tol": 0},
                {"col": "desbordamiento", "type": "final_value", "val": 0,  "tol": 0},
            ],
            "interpretation": (
                "47 eventos: cuenta=47, decenas=div(47,10)=4, unidades=mod(47,10)=7. "
                "Valor arbitrario que verifica la descomposicion BCD en un rango "
                "intermedio. desbordamiento=FALSE (47 < 99). Confirma que la "
                "aritmetica de division y modulo es exacta para enteros no triviales."
            ),
        },
        {
            "id": "TC-CE-005",
            "title": "Reset borra el contador — cuenta vuelve a 0",
            "description": "30 eventos, luego flanco ascendente en reset: cuenta=0.",
            "t_end": 10.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {
                "evento": _sched_edges(30, h=0.1),
                "reset":  [(0, 0), (7.0, 1), (7.5, 0)],
            },
            "checks": [
                {"col": "cuenta",         "type": "at_t", "at_t": 5.9,  "val": 30, "tol": 0},
                {"col": "cuenta",         "type": "final_value",         "val": 0,  "tol": 0},
                {"col": "desbordamiento", "type": "final_value",         "val": 0,  "tol": 0},
            ],
            "interpretation": (
                "30 eventos llevan el contador a 30 (verificado en t≈6). Luego un "
                "flanco ascendente en reset (t=7.0) borra el contador a 0. "
                "desbordamiento=FALSE tras el reset. Verifica que el flanco de "
                "reset tiene efecto inmediato y que el contador no vuelve al valor "
                "previo al siguiente pulso de evento."
            ),
        },
        {
            "id": "TC-CE-006",
            "title": "Saturacion en 99 — 100 eventos, cuenta queda en 99",
            "description": "100 flancos: cuenta=99 (saturado), desbordamiento=true.",
            "t_end": 21.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {"evento": _sched_100},
            "checks": [
                {"col": "cuenta",         "type": "final_value", "val": 99, "tol": 0},
                {"col": "desbordamiento", "type": "final_value", "val": 1,  "tol": 0},
            ],
            "interpretation": (
                "El modelo satura a 99 y no incrementa mas. 100 eventos aplicados: "
                "el contador llega a 99 en el evento 99 y permanece en 99 para el "
                "evento 100. desbordamiento=TRUE cuando cuenta>=99. Verifica la "
                "condicion de saturacion: if (contador < 99) then contador+=1."
            ),
        },
        {
            "id": "TC-CE-007",
            "title": "El contador permanece en 99 tras la saturacion",
            "description": "150 eventos: cuenta=99 (permanece), no hay incremento post-99.",
            "t_end": 31.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {"evento": _sched_edges(150, h=0.1)},
            "checks": [
                {"col": "cuenta",         "type": "final_value", "val": 99, "tol": 0},
                {"col": "desbordamiento", "type": "always", "op": ">=", "val": 0},
            ],
            "interpretation": (
                "Con 150 eventos (51 mas que el umbral de saturacion), el contador "
                "debe permanecer en 99. Un error de implementacion daria 100, 101... "
                "Si el modelo usa 'if contador < 99' (estricto), satura correctamente. "
                "Si usa '<=', saturaria en 100. desbordamiento siempre >= 0 (trivial, "
                "pero confirma que no hay NaN en el output entero)."
            ),
        },
        {
            "id": "TC-CE-008",
            "title": "Reset tras desbordamiento — contador vuelve a 0",
            "description": "100 eventos (saturado), luego reset: cuenta=0, desbordamiento=false.",
            "t_end": 23.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {
                "evento": _sched_100,
                "reset":  [(0, 0), (21.5, 1), (22.0, 0)],
            },
            "checks": [
                {"col": "cuenta",         "type": "at_t", "at_t": 21.0, "val": 99, "tol": 0},
                {"col": "cuenta",         "type": "final_value",         "val": 0,  "tol": 0},
                {"col": "desbordamiento", "type": "final_value",         "val": 0,  "tol": 0},
            ],
            "interpretation": (
                "Tras saturar a 99, un flanco de reset en t=21.5 devuelve el contador "
                "a 0. desbordamiento=FALSE (0 < 99). Verifica que el reset funciona "
                "incluso desde el estado de desbordamiento: el sistema no queda "
                "bloqueado en 99 tras el reset."
            ),
        },
        {
            "id": "TC-CE-009",
            "title": "Prioridad de reset sobre evento simultaneo",
            "description": "Flanco de reset y evento en el mismo paso: reset gana, cuenta=0.",
            "t_end": 3.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {
                "evento": [(0, 0), (1.0, 1), (1.5, 0)],
                "reset":  [(0, 0), (1.0, 1), (1.5, 0)],
            },
            "checks": [
                {"col": "cuenta", "type": "at_t", "at_t": 0.5,  "val": 0, "tol": 0},
                {"col": "cuenta", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "En t=1.0, ambos evento y reset tienen flanco ascendente simultaneamente. "
                "Segun Modelica when/elsewhen, la clausula reset (elsewhen) tiene "
                "prioridad sobre evento (when). El resultado debe ser cuenta=0, no 1. "
                "Si el codegen invierte la prioridad, cuenta=1. "
                "Despues de t=1.5 (ambos bajan), no hay mas flancos: cuenta=0 al final."
            ),
        },
        {
            "id": "TC-CE-010",
            "title": "BCD en valor limite 99 — decenas=9, unidades=9",
            "description": "Exactamente 99 eventos: cuenta=99, decenas=9, unidades=9, desbordamiento=true.",
            "t_end": 20.9, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"evento": 0, "reset": 0},
            "schedule": {"evento": _sched_edges(99, h=0.1)},
            "checks": [
                {"col": "cuenta",         "type": "final_value", "val": 99, "tol": 0},
                {"col": "decenas",        "type": "final_value", "val": 9,  "tol": 0},
                {"col": "unidades",       "type": "final_value", "val": 9,  "tol": 0},
                {"col": "desbordamiento", "type": "final_value", "val": 1,  "tol": 0},
            ],
            "interpretation": (
                "99 eventos llevan el contador exactamente a 99 (sin saturar en 98). "
                "decenas=div(99,10)=9, unidades=mod(99,10)=9. desbordamiento=TRUE "
                "(99 >= 99). Verifica el valor limite exacto: la condicion "
                "desbordamiento usa >= no >. Si usara >, no habria desbordamiento con 99."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
