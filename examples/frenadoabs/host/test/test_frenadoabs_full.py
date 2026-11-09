#!/usr/bin/env python3
"""Test battery completa — FrenadoABS (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "FrenadoABS",
    "tests": [
        {
            "id": "TC-FABS-001",
            "title": "Sin frenado — estado estacionario, lambda=0, ABS inactivo",
            "description": "velocidad=0.8 constante, pedal=0: lambda→0, abs_activo=false siempre.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.80, "presion_pedal": 0.0},
            "checks": [
                {"col": "abs_activo",      "type": "final_value", "val": 0,   "tol": 0},
                {"col": "rueda_bloqueada", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "frenado_normal",  "type": "final_value", "val": 0,   "tol": 0},
                {"col": "presion_modulada","type": "final_value", "val": 0.0, "tol": 0.01},
            ],
            "interpretation": (
                "Con velocidad constante y presion=0, tras convergencia de filtros "
                "(5*tau_v=0.25s, 5*tau_p=0.4s): v_filtrada→0.8, p_filtrada→0, "
                "dv_filtrada→0 (velocidad constante). lambda=clamp(0/(0.8*20),0,1)=0. "
                "abs_activo=FALSE (0 <= 0.15). frenado_normal=FALSE (pedal < 0.05). "
                "presion_modulada=0 (sin presion de pedal)."
            ),
        },
        {
            "id": "TC-FABS-002",
            "title": "Frenado suave — ABS no activado, frenado_normal=true",
            "description": "velocidad=0.6, pedal=0.3 en estado estacionario: frenado_normal=true, abs=false.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.60, "presion_pedal": 0.30},
            "checks": [
                {"col": "abs_activo",     "type": "final_value", "val": 0, "tol": 0},
                {"col": "rueda_bloqueada","type": "final_value", "val": 0, "tol": 0},
                {"col": "frenado_normal", "type": "final_value", "val": 1, "tol": 0},
                {"col": "presion_modulada","type": "no_nan_inf"},
            ],
            "interpretation": (
                "Con velocidad constante y pedal=0.3, en estado estacionario: "
                "dv_filtrada→0, lambda→0. abs_activo=FALSE (lambda=0 < 0.15). "
                "frenado_normal=TRUE (lambda<=0.15 AND pedal=0.3 > 0.05). "
                "presion_modulada=p_filtrada (sin modulacion ABS). Verifica el "
                "modo de frenado normal sin intervencion del ABS."
            ),
        },
        {
            "id": "TC-FABS-003",
            "title": "Frenado de emergencia — ABS activa tras escalon de velocidad",
            "description": "velocidad_rueda: 0.8→0.0 (escalon). abs_activo eventually=true.",
            "t_end": 0.5, "h": 0.005, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.8, "presion_pedal": 0.9},
            "schedule": {"velocidad_rueda": [(0, 0.8), (0.1, 0.0)]},
            "checks": [
                {"col": "abs_activo", "type": "eventually", "op": "==", "val": 1,
                 "description": "ABS debe activarse tras el escalon de velocidad cero"},
                {"col": "presion_modulada", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "La velocidad cae abruptamente de 0.8 a 0.0 en t=0.1 s. El filtro de "
                "velocidad (tau=0.05 s) produce dv_filtrada fuertemente negativo, "
                "lo que genera lambda > 0.15. abs_activo=TRUE. Si el codegen no "
                "propaga correctamente los 5 estados del ABS, lambda no se calcula "
                "correctamente y abs_activo permanece FALSE."
            ),
        },
        {
            "id": "TC-FABS-004",
            "title": "Bloqueo de rueda — rueda_bloqueada=true con desaceleracion extrema",
            "description": "velocidad_rueda: 0.8→0.0 con pedal maximo. rueda_bloqueada eventually=true.",
            "t_end": 0.5, "h": 0.005, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.8, "presion_pedal": 1.0},
            "schedule": {"velocidad_rueda": [(0, 0.8), (0.05, 0.0)]},
            "checks": [
                {"col": "rueda_bloqueada", "type": "eventually", "op": "==", "val": 1,
                 "description": "rueda_bloqueada debe activarse con desaceleracion muy rapida"},
                {"col": "abs_activo",      "type": "eventually", "op": "==", "val": 1,
                 "description": "abs_activo tambien debe estar activo"},
            ],
            "interpretation": (
                "Desaceleracion extrema: velocidad cae en 0.05 s. El filtro produce "
                "dv_filtrada muy negativo. lambda = clamp(-dv_filt/(v_filt*20),0,1) "
                "puede alcanzar 1.0 (rueda totalmente bloqueada). rueda_bloqueada=TRUE "
                "(lambda > 0.90). Verifica que el buffer de 5 estados integra "
                "correctamente sin desbordamiento."
            ),
        },
        {
            "id": "TC-FABS-005",
            "title": "Vehiculo detenido — guarda de division por cero en lambda",
            "description": "velocidad_rueda=0: v_filtrada → 0 → guarda activa, lambda=0, abs=false.",
            "t_end": 0.5, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.0, "presion_pedal": 1.0},
            "checks": [
                {"col": "abs_activo",      "type": "always", "op": "==", "val": 0},
                {"col": "rueda_bloqueada", "type": "always", "op": "==", "val": 0},
                {"col": "presion_modulada","type": "no_nan_inf"},
            ],
            "interpretation": (
                "Con velocidad=0, v_filtrada → 0 (rapidamente, tau=0.05s). La guarda "
                "activa: if v_filtrada > 0.01 then lambda = ... else lambda = 0. "
                "Esto previene division por cero: 1/(v_filtrada*20). "
                "abs_activo=FALSE (lambda=0 < 0.15) en todo momento. "
                "Si aparece NaN en presion_modulada, la guarda no fue generada."
            ),
        },
        {
            "id": "TC-FABS-006",
            "title": "presion_modulada acotada en [0,1] siempre",
            "description": "Con pedal=1.0 y ABS activo: presion_modulada en [0,1] sin excederse.",
            "t_end": 1.0, "h": 0.005, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.8, "presion_pedal": 1.0},
            "schedule": {"velocidad_rueda": [(0, 0.8), (0.1, 0.0)]},
            "checks": [
                {"col": "presion_modulada", "type": "bounded",    "low": 0.0, "high": 1.0},
                {"col": "presion_modulada", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "La presion modulada ABS es presion_pedal * factor de modulacion, donde "
                "el factor oscila entre 0 y 1 (segun el oscilador interno). "
                "presion_modulada = p_filtrada * (0.5 + 0.5*oscilador) ∈ [0, p_filtrada]. "
                "Con p_filtrada → 1.0, presion_modulada ∈ [0, 1.0]. Nunca debe "
                "exceder 1.0 ni ser negativa."
            ),
        },
        {
            "id": "TC-FABS-007",
            "title": "Oscilador interno — no produce NaN ni Inf durante 10 Hz",
            "description": "Oscilador en 10 Hz: presion_modulada estable, sin valores invalidos.",
            "t_end": 1.0, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.5, "presion_pedal": 0.8},
            "schedule": {"velocidad_rueda": [(0, 0.5), (0.1, 0.0)]},
            "checks": [
                {"col": "presion_modulada", "type": "no_nan_inf"},
                {"col": "abs_activo",       "type": "no_nan_inf"},
            ],
            "interpretation": (
                "El oscilador armonico interno (f=10 Hz, oscilador=sin, d_oscilador=cos) "
                "modula la presion. Los estados del oscilador tienen condiciones iniciales "
                "oscilador=0, d_oscilador=1. La integracion RK4 debe mantener la "
                "amplitud del oscilador acotada. Si los k-vectores del RK4 tienen "
                "tamanyo < 5, la integracion del oscilador puede corromperse."
            ),
        },
        {
            "id": "TC-FABS-008",
            "title": "frenado_normal requiere pedal > 0.05 — frontera exacta",
            "description": "pedal=0.03 (<= 0.05): frenado_normal=false aunque sin ABS.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.6, "presion_pedal": 0.03},
            "checks": [
                {"col": "frenado_normal", "type": "final_value", "val": 0, "tol": 0},
                {"col": "abs_activo",     "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Con velocidad constante (lambda→0, abs_activo=FALSE) y pedal=0.03 < 0.05, "
                "frenado_normal=FALSE. La condicion es: lambda<=0.15 AND presion_pedal > 0.05. "
                "El pedal de 3% no supera el umbral activo de 5%. Verifica que la "
                "condicion de pedal activo tiene umbral en 0.05 (estricto >)."
            ),
        },
        {
            "id": "TC-FABS-009",
            "title": "Buffer de 5 estados — no NaN en 2 segundos",
            "description": "2 s de simulacion con ABS activo: los 5 estados no producen NaN.",
            "t_end": 2.0, "h": 0.005, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.8, "presion_pedal": 0.9},
            "schedule": {"velocidad_rueda": [(0, 0.8), (0.1, 0.1)]},
            "checks": [
                {"col": "presion_modulada",  "type": "no_nan_inf"},
                {"col": "abs_activo",        "type": "no_nan_inf"},
                {"col": "rueda_bloqueada",   "type": "no_nan_inf"},
                {"col": "frenado_normal",    "type": "no_nan_inf"},
                {"col": "presion_modulada",  "type": "bounded", "low": 0.0, "high": 1.0},
            ],
            "interpretation": (
                "TEST CRITICO DE BUFFER. FrenadoABS tiene 5 estados (mas que cualquier "
                "otro modelo de la suite excepto MuchosEstados). Si el codegen usa "
                "EULER_BUF_SIZE o RK4_BUF_SIZE < 5, hay desbordamiento de buffer. "
                "Los estados del oscilador (posicion/velocidad) son los que mas "
                "probablemente quedan fuera del buffer en un codegen con tamano fijo."
            ),
        },
        {
            "id": "TC-FABS-010",
            "title": "Transitorio del filtro de velocidad tras escalon",
            "description": "velocidad: 0.8 → 0.0 en t=0.3. A t=0.35 (1 tau): v_filtrada ≈ 0.8*e^-1 ≈ 0.29.",
            "t_end": 0.7, "h": 0.005, "solver": "rk4", "mode": "me",
            "inputs": {"velocidad_rueda": 0.8, "presion_pedal": 0.0},
            "schedule": {"velocidad_rueda": [(0, 0.8), (0.3, 0.0)]},
            "checks": [
                {"col": "presion_modulada", "type": "no_nan_inf"},
                {"col": "abs_activo",       "type": "eventually", "op": "==", "val": 1,
                 "description": "ABS debe activarse despues del escalon de velocidad"},
            ],
            "interpretation": (
                "Con velocidad constante 0.8 durante [0, 0.3s], v_filtrada converge a 0.8. "
                "En t=0.3, velocidad cae a 0.0. El filtro con tau=0.05s produce "
                "v_filtrada(0.35) ≈ 0.8*e^(-1) ≈ 0.29 y dv_filtrada fortemente negativo. "
                "lambda = -dv_filt/(v_filt*20) >> 0.15, abs_activo=TRUE. "
                "Verifica la dinamica transitoria del filtro de primer orden."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
