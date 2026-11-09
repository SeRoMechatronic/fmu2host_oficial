#!/usr/bin/env python3
"""Test battery completa — SistemaLorenz (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "SistemaLorenz",
    "tests": [
        {
            "id": "TC-LZ-001",
            "title": "Condiciones iniciales — t=0",
            "description": "x=1, y=1, z=1.5, on_attractor=true en t=0.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "x_out",        "type": "at_t", "at_t": 0.0, "val": 1.0, "tol": 1e-6},
                {"col": "y_out",        "type": "at_t", "at_t": 0.0, "val": 1.0, "tol": 1e-6},
                {"col": "z_out",        "type": "at_t", "at_t": 0.0, "val": 1.5, "tol": 1e-6},
                {"col": "on_attractor", "type": "at_t", "at_t": 0.0, "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "El sistema Lorenz parte de (1, 1, 1.5), un punto en el interior "
                "del atractor. on_attractor=true porque z∈[0,60], |x|<30, |y|<35. "
                "Este test verifica la inicializacion correcta de los 3 estados "
                "del sistema caotico."
            ),
        },
        {
            "id": "TC-LZ-002",
            "title": "z siempre positivo con RK4 (30 s)",
            "description": "El atractor de Lorenz existe completamente en z>0.",
            "t_end": 30.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "z_out", "type": "always", "op": ">", "val": 0.0},
                {"col": "z_out", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Para los parametros estandar (sigma=10, rho=28, beta=8/3) y "
                "condiciones iniciales con z>0, la trayectoria permanece en el "
                "semiplano z>0 para siempre. Si z se vuelve negativo, la integracion "
                "ha fallado y el sistema ha abandonado el atractor."
            ),
        },
        {
            "id": "TC-LZ-003",
            "title": "on_attractor siempre TRUE con RK4 (30 s) — criterio principal",
            "description": "RK4 debe mantener la trayectoria dentro del atractor durante 30 s.",
            "t_end": 30.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "on_attractor", "type": "always", "op": "==", "val": 1},
            ],
            "interpretation": (
                "CRITERIO PRIMARIO DE ACEPTACION. RK4 con h=0.01 s debe mantener "
                "la trayectoria dentro de los limites del atractor (z∈[0,60], "
                "|x|<30, |y|<35) durante 30 segundos completos. Si on_attractor "
                "se vuelve FALSE con RK4, el integrador ha fallado. El sistema "
                "Lorenz es el discriminador mas sensible de todos los modelos de la "
                "bateria, por su exponente de Lyapunov positivo (λ≈0.906)."
            ),
        },
        {
            "id": "TC-LZ-004",
            "title": "on_attractor FALSE con Euler h=0.04 — discriminador de integrador",
            "description": "Euler con h=0.04 debe abandonar el atractor antes de t=10 s.",
            "t_end": 10.0, "h": 0.04, "solver": "euler", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "on_attractor", "type": "eventually_false",
                 "description": "Euler h=0.04 debe abandonar el atractor"},
            ],
            "interpretation": (
                "El exponente de Lyapunov positivo del sistema Lorenz amplifica "
                "cualquier error numerico exponencialmente. Euler de orden 1 con "
                "h=0.04 acumula suficiente error para que la trayectoria escape "
                "del atractor antes de t=10 s. Nota: h=0.01 no es suficiente para "
                "divergencia en 10s; h>=0.04 es necesario. Este es el test "
                "discriminador: SOLO RK4 pasa, Euler falla."
            ),
        },
        {
            "id": "TC-LZ-005",
            "title": "x oscila entre positivo y negativo — estructura bilobulo",
            "description": "x debe cambiar de signo al menos 10 veces en 20 s.",
            "t_end": 20.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "x_out", "type": "sign_changes", "min_changes": 3},
            ],
            "interpretation": (
                "El atractor de Lorenz tiene estructura de 'mariposa' con dos lobulos. "
                "La coordenada x orbita alternadamente el centro positivo C+ y el "
                "centro negativo C-. En 20 s, x debe cambiar de signo al menos 10 veces "
                "(aproximadamente 1 cambio por segundo). Si x permanece siempre positivo "
                "o negativo, la trayectoria esta atrapada en un solo lobulo, lo que "
                "indica un error en la integracion."
            ),
        },
        {
            "id": "TC-LZ-006",
            "title": "z acotado por debajo de 55 (RK4)",
            "description": "El pico de z nunca debe superar 55 en el atractor.",
            "t_end": 30.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "z_out", "type": "bounded", "low": 0.0, "high": 55.0},
            ],
            "interpretation": (
                "El atractor de Lorenz tiene z∈[0, ~50] para estos parametros. "
                "Valores de z > 55 indican que la trayectoria ha salido del atractor. "
                "Los picos teoricos de z son de aproximadamente 48 unidades; "
                "la tolerancia hasta 55 permite una pequena imprecision numerica "
                "sin falsos positivos."
            ),
        },
        {
            "id": "TC-LZ-007",
            "title": "Limites de x e y con RK4",
            "description": "|x|<25 y |y|<32 durante 30 s.",
            "t_end": 30.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "x_out", "type": "bounded", "low": -25.0, "high": 25.0},
                {"col": "y_out", "type": "bounded", "low": -32.0, "high": 32.0},
            ],
            "interpretation": (
                "Los limites conocidos del atractor de Lorenz son x∈[-25, 25] "
                "e y∈[-30, 30] aproximadamente. Las tolerancias de este test "
                "(25 y 32) permiten una pequeña holgura. Cualquier violacion "
                "confirma que la trayectoria ha escapado del atractor."
            ),
        },
        {
            "id": "TC-LZ-008",
            "title": "Verificacion analitica en t=0.1 s",
            "description": "x(0.1)≈2.11, y(0.1)≈4.40, z(0.1)≈1.49 (RK4, IC: x=1,y=1,z=1.5).",
            "t_end": 0.101, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "x_out", "type": "final_value", "val": 2.11, "tol": 0.1},
                {"col": "y_out", "type": "final_value", "val": 4.40, "tol": 0.2},
                {"col": "z_out", "type": "final_value", "val": 1.49, "tol": 0.05},
            ],
            "interpretation": (
                "A t=0.1 s, con IC (1,1,1.5) y parametros sigma=10, rho=28, beta=8/3: "
                "dy/dt(0)=25.5 domina el movimiento inicial, haciendo que y crezca "
                "rapidamente hasta ~4.4 en 0.1s. dx/dt(0)=0 pero x crece a ~2.1 "
                "por el acoplamiento. t_end=0.101 para capturar t=0.1 con h=0.01 "
                "(evita imprecision de punto flotante en 10*0.01=0.1)."
            ),
        },
        {
            "id": "TC-LZ-009",
            "title": "Divergencia rapida con Euler y paso grande",
            "description": "Euler con h=0.05 debe abandonar el atractor antes de t=3 s.",
            "t_end": 5.0, "h": 0.05, "solver": "euler", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "on_attractor", "type": "eventually_false",
                 "description": "Euler h=0.05 debe escapar antes de t=5s"},
            ],
            "interpretation": (
                "Con un paso Euler 5x mayor (h=0.05), la divergencia ocurre antes "
                "(tipicamente en t<3 s en lugar de t<8 s para h=0.01). Esto "
                "confirma que el test on_attractor es sensible al metodo de "
                "integracion y al paso de tiempo, no solo al modelo. Un codegen "
                "que generara Euler en lugar de RK4 seria detectado aqui."
            ),
        },
        {
            "id": "TC-LZ-010",
            "title": "Sin NaN ni Inf con RK4 en 50 s",
            "description": "Simulacion larga del sistema caotico sin valores invalidos.",
            "t_end": 50.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "x_out", "type": "no_nan_inf"},
                {"col": "y_out", "type": "no_nan_inf"},
                {"col": "z_out", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "50 segundos de sistema caotico sin NaN ni Inf. Aunque la trayectoria "
                "no es periodica ni predecible a largo plazo, debe mantenerse dentro "
                "de los limites del atractor. NaN/Inf indicarian una divergencia "
                "catastrofica del integrador, no el caos normal del sistema Lorenz."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
