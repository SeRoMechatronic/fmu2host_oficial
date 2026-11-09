#!/usr/bin/env python3
"""Test battery completa — ValoresExtremos (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "ValoresExtremos",
    "tests": [
        {
            "id": "TC-VE-001",
            "title": "u=0.0 — division por cero y log de cero protegidos",
            "description": "y_inv=1e30, y_sqrt=0, y_log=-1e30, y_sat=0, es_finito=true.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 0.0},
            "checks": [
                {"col": "y_inv",     "type": "final_value", "val": 1.0e30,  "tol": 1e20},
                {"col": "y_sqrt",    "type": "final_value", "val": 0.0,     "tol": 1e-9},
                {"col": "y_log",     "type": "final_value", "val": -1.0e30, "tol": 1e20},
                {"col": "y_sat",     "type": "final_value", "val": 0.0,     "tol": 1e-9},
                {"col": "es_finito", "type": "final_value", "val": 1,       "tol": 0},
                {"col": "y_inv",     "type": "no_nan_inf"},
            ],
            "interpretation": (
                "TEST CRITICO. Con u=0, sin guardas: 1/0 y log(0) producen NaN/Inf. "
                "El codegen debe preservar los if/else protectores. y_inv=1e30 "
                "(centinela para division protegida), y_log=-1e30 (centinela para "
                "log protegido), y_sqrt=0 (√0=0 es matematicamente correcto). "
                "Si aparece NaN, el codegen ha eliminado las guardas."
            ),
        },
        {
            "id": "TC-VE-002",
            "title": "u=-5.0 — negativo: sqrt y log protegidos",
            "description": "y_inv=-0.2, y_sqrt=0, y_log=-1e30, y_sat=-1.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": -5.0},
            "checks": [
                {"col": "y_inv",  "type": "final_value", "val": -0.2,     "tol": 1e-9},
                {"col": "y_sqrt", "type": "final_value", "val": 0.0,      "tol": 1e-9},
                {"col": "y_log",  "type": "final_value", "val": -1.0e30,  "tol": 1e20},
                {"col": "y_sat",  "type": "final_value", "val": -1.0,     "tol": 1e-9},
                {"col": "y_inv",  "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Entrada negativa: 1/(-5)=-0.2 (valido), sqrt(-5) indefinido → guarda "
                "devuelve 0, log(-5) indefinido → guarda devuelve -1e30. "
                "y_sat=clamp(-5,-1,1)=-1 (saturacion maxima negativa). "
                "Verifica las tres guardas protectoras simultaneamente."
            ),
        },
        {
            "id": "TC-VE-003",
            "title": "u=1.0 — valor nominal: todas las operaciones validas",
            "description": "y_inv=1, y_sqrt=1, y_log=0, y_sat=1.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y_inv",     "type": "final_value", "val": 1.0,  "tol": 1e-9},
                {"col": "y_sqrt",    "type": "final_value", "val": 1.0,  "tol": 1e-9},
                {"col": "y_log",     "type": "final_value", "val": 0.0,  "tol": 1e-6},
                {"col": "y_sat",     "type": "final_value", "val": 1.0,  "tol": 1e-9},
                {"col": "es_finito", "type": "final_value", "val": 1,    "tol": 0},
            ],
            "interpretation": (
                "Con u=1.0, todas las operaciones son bien definidas: 1/1=1, sqrt(1)=1, "
                "ln(1)=0. y_sat=1.0 (exactamente en el limite superior de saturacion). "
                "Este caso nominal verifica que las guardas no disparan falsamente "
                "para valores normales."
            ),
        },
        {
            "id": "TC-VE-004",
            "title": "u=-1.0 — simetrico al nominal positivo",
            "description": "y_inv=-1, y_sqrt=0 (guarda), y_log=-1e30 (guarda), y_sat=-1.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": -1.0},
            "checks": [
                {"col": "y_inv",  "type": "final_value", "val": -1.0,    "tol": 1e-9},
                {"col": "y_sqrt", "type": "final_value", "val": 0.0,     "tol": 1e-9},
                {"col": "y_log",  "type": "final_value", "val": -1.0e30, "tol": 1e20},
                {"col": "y_sat",  "type": "final_value", "val": -1.0,    "tol": 1e-9},
            ],
            "interpretation": (
                "Simetrico al caso u=1.0 pero con signo negativo. La inversa sigue "
                "siendo valida (-1/-1 no hay division por cero). Las guardas de "
                "sqrt y log se activan para u<0. y_sat queda en -1 (limite inferior)."
            ),
        },
        {
            "id": "TC-VE-005",
            "title": "u=2.0 — por encima de saturacion",
            "description": "y_sat=1.0 (saturado), y_sqrt≈1.414, y_log≈0.693.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 2.0},
            "checks": [
                {"col": "y_sat",  "type": "final_value", "val": 1.0,   "tol": 1e-9},
                {"col": "y_sqrt", "type": "final_value", "val": 1.4142,"tol": 0.001},
                {"col": "y_log",  "type": "final_value", "val": 0.6931,"tol": 0.001},
            ],
            "interpretation": (
                "u=2.0 supera el limite superior de saturacion. y_sat=1.0 (recortado). "
                "y_sqrt=sqrt(2)≈1.414, y_log=ln(2)≈0.693 son valores estandar "
                "reconocibles. Verifica que la saturacion opera correctamente y que "
                "las operaciones no-saturadas dan resultados esperados."
            ),
        },
        {
            "id": "TC-VE-006",
            "title": "u=-10.0 — saturacion profunda negativa",
            "description": "y_sat=-1 (saturado abajo), y_inv=-0.1.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": -10.0},
            "checks": [
                {"col": "y_inv",  "type": "final_value", "val": -0.1,    "tol": 1e-9},
                {"col": "y_sqrt", "type": "final_value", "val": 0.0,     "tol": 1e-9},
                {"col": "y_sat",  "type": "final_value", "val": -1.0,    "tol": 1e-9},
            ],
            "interpretation": (
                "Entrada muy negativa: saturacion al limite inferior. 1/(-10)=-0.1 "
                "sigue siendo valido (lejos de cero). sqrt y log protegidos. "
                "Verifica el comportamiento consistente para valores grandes negativos."
            ),
        },
        {
            "id": "TC-VE-007",
            "title": "u=1e-11 — por debajo del umbral de guarda",
            "description": "y_inv=1e30 y y_log=-1e30 (guardas activas), y_sqrt≈3.16e-6.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0e-11},
            "checks": [
                {"col": "y_inv",  "type": "final_value", "val": 1.0e30,  "tol": 1e20},
                {"col": "y_log",  "type": "final_value", "val": -1.0e30, "tol": 1e20},
                {"col": "y_sat",  "type": "final_value", "val": 1.0e-11, "tol": 1e-20},
                {"col": "es_finito","type": "final_value","val": 1,      "tol": 0},
            ],
            "interpretation": (
                "1e-11 esta por debajo del umbral de guarda 1e-10. Aunque u>0, "
                "las guardas de y_inv y y_log se activan (|u|<1e-10 y u<1e-10). "
                "y_sqrt=sqrt(1e-11)≈3.16e-6 es valido (u>=0). Verifica que las "
                "guardas tienen umbrales en 1e-10 y no en otros valores."
            ),
        },
        {
            "id": "TC-VE-008",
            "title": "u=1e30 — cerca de Inf, es_finito=false",
            "description": "y_sat=1.0, es_finito=false (|u|>=1e29).",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0e30},
            "checks": [
                {"col": "y_sat",     "type": "final_value", "val": 1.0, "tol": 1e-9},
                {"col": "es_finito", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "y_inv",     "type": "no_nan_inf"},
                {"col": "y_log",     "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Con u=1e30 (maximo double practico), es_finito=false porque |1e30|>=1e29. "
                "y_sat=1.0 (saturado). Las operaciones son validas: 1/1e30≈1e-30, "
                "sqrt(1e30)≈1e15, log(1e30)≈69.08. Ninguna debe producir NaN/Inf."
            ),
        },
        {
            "id": "TC-VE-009",
            "title": "u=100 — valor tipico positivo con resultados conocidos",
            "description": "y_inv=0.01, y_sqrt=10, y_log≈4.605, y_sat=1.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"u": 100.0},
            "checks": [
                {"col": "y_inv",  "type": "final_value", "val": 0.01,  "tol": 1e-9},
                {"col": "y_sqrt", "type": "final_value", "val": 10.0,  "tol": 1e-6},
                {"col": "y_log",  "type": "final_value", "val": 4.6052,"tol": 0.001},
                {"col": "y_sat",  "type": "final_value", "val": 1.0,   "tol": 1e-9},
            ],
            "interpretation": (
                "Valores reconocibles con u=100: 1/100=0.01, sqrt(100)=10, "
                "ln(100)=2*ln(10)≈4.6052. y_sat=1.0 (saturado, 100>>1). "
                "Este test con valores exactos reconocibles detecta errores de "
                "implementacion (ej. log base 10 en lugar de natural, o sqrt(u^2) "
                "en lugar de sqrt(u))."
            ),
        },
        {
            "id": "TC-VE-010",
            "title": "Sin NaN ni Inf en todos los casos — barrido completo",
            "description": "Simulacion con varios cambios de u: ningun output debe ser invalido.",
            "t_end": 5.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "schedule": {"u": [(0, 0.0), (0.5, -5.0), (1.0, 1.0), (1.5, -1.0), (2.0, 2.0),
                               (2.5, 1.0e-11), (3.0, 100.0), (3.5, -10.0), (4.0, 0.5)]},
            "checks": [
                {"col": "y_inv",  "type": "no_nan_inf"},
                {"col": "y_sqrt", "type": "no_nan_inf"},
                {"col": "y_log",  "type": "no_nan_inf"},
                {"col": "y_sat",  "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Barrido de valores que cubren todos los casos: 0 (guarda inv/log), "
                "negativo (guarda sqrt/log), positivo nominal, limite saturacion, "
                "por encima de saturacion, muy pequeno (guarda inv/log), grande, etc. "
                "En ningun instante debe aparecer NaN o Inf. Este es el test de "
                "integridad de guardas mas completo de la bateria."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
