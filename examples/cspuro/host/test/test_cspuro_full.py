#!/usr/bin/env python3
"""Test battery completa — CSPuro_SinME (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "CSPuro_SinME",
    "tests": [
        {
            "id": "TC-CS-001",
            "title": "Valores positivos basicos — u1 > u2",
            "description": "u1=3.0, u2=2.0: suma=5, producto=6, active=true.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": 3.0, "u2": 2.0},
            "checks": [
                {"col": "y_sum",  "type": "final_value", "val": 5.0,  "tol": 1e-9},
                {"col": "y_prod", "type": "final_value", "val": 6.0,  "tol": 1e-9},
                {"col": "active", "type": "final_value", "val": 1,    "tol": 0},
            ],
            "interpretation": (
                "Caso nominal con u1 > u2. El modelo CoSimulation evalua suma y "
                "producto algebraicamente en cada paso de comunicacion. active=true "
                "porque u1=3.0 es estrictamente mayor que u2=2.0. Este test "
                "confirma que el doStep() del FMU CS funciona correctamente para "
                "el caso basico mas sencillo."
            ),
        },
        {
            "id": "TC-CS-002",
            "title": "Valores iguales — limite estricto de active",
            "description": "u1=5.0, u2=5.0: active=false (> es estricto).",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": 5.0, "u2": 5.0},
            "checks": [
                {"col": "y_sum",  "type": "final_value", "val": 10.0, "tol": 1e-9},
                {"col": "y_prod", "type": "final_value", "val": 25.0, "tol": 1e-9},
                {"col": "active", "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "Con entradas iguales, la condicion u1 > u2 es falsa (0 > 0), por "
                "lo que active=false. La suma y el producto son correctos (10 y 25). "
                "Este caso limite verifica que el operador de comparacion es "
                "estrictamente mayor (>) y no mayor o igual (>=)."
            ),
        },
        {
            "id": "TC-CS-003",
            "title": "u1 menor que u2",
            "description": "u1=1.0, u2=4.0: active=false.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": 1.0, "u2": 4.0},
            "checks": [
                {"col": "y_sum",  "type": "final_value", "val": 5.0, "tol": 1e-9},
                {"col": "y_prod", "type": "final_value", "val": 4.0, "tol": 1e-9},
                {"col": "active", "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Cuando u2 domina (4.0 > 1.0), active permanece false. La suma da 5.0 "
                "y el producto 4.0. Verifica que la comparacion es correcta cuando "
                "los roles se invierten respecto al caso TC-CS-001."
            ),
        },
        {
            "id": "TC-CS-004",
            "title": "Entradas negativas — producto positivo",
            "description": "u1=-3.0, u2=-1.0: producto positivo, active=false.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": -3.0, "u2": -1.0},
            "checks": [
                {"col": "y_sum",  "type": "final_value", "val": -4.0, "tol": 1e-9},
                {"col": "y_prod", "type": "final_value", "val": 3.0,  "tol": 1e-9},
                {"col": "active", "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "Entradas negativas: -3 + (-1) = -4 (suma negativa), (-3)*(-1) = 3 "
                "(producto positivo por regla de signos). active=false porque -3 < -1. "
                "Este test verifica el manejo correcto de signos en ambas operaciones."
            ),
        },
        {
            "id": "TC-CS-005",
            "title": "Entradas cero — sin division ni NaN",
            "description": "u1=0.0, u2=0.0: suma=0, producto=0, active=false.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": 0.0, "u2": 0.0},
            "checks": [
                {"col": "y_sum",  "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "y_prod", "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "active", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "y_sum",  "type": "no_nan_inf"},
            ],
            "interpretation": (
                "El caso de ceros verifica que no hay division por cero ni NaN. "
                "El modelo solo realiza suma y multiplicacion, operaciones seguras "
                "con cero. active=false porque 0 no es > 0."
            ),
        },
        {
            "id": "TC-CS-006",
            "title": "Valores grandes — precision numerica",
            "description": "u1=1e6, u2=1e6: suma=2e6, producto=1e12.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": 1.0e6, "u2": 1.0e6},
            "checks": [
                {"col": "y_sum",  "type": "final_value", "val": 2.0e6,  "tol": 1.0},
                {"col": "y_prod", "type": "final_value", "val": 1.0e12, "tol": 1e6},
            ],
            "interpretation": (
                "Magnitudes grandes (1e6) verifican que no hay perdida de precision "
                "significativa en suma y multiplicacion de doubles. La tolerancia "
                "absoluta se escala al rango del resultado esperado."
            ),
        },
        {
            "id": "TC-CS-007",
            "title": "Signo mixto — u1 negativo, u2 positivo",
            "description": "u1=-2.0, u2=3.0: producto=-6, active=false.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": -2.0, "u2": 3.0},
            "checks": [
                {"col": "y_sum",  "type": "final_value", "val": 1.0,  "tol": 1e-9},
                {"col": "y_prod", "type": "final_value", "val": -6.0, "tol": 1e-9},
                {"col": "active", "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "Operandos de signo opuesto. El producto es negativo (-2 * 3 = -6), "
                "la suma es positiva (-2 + 3 = 1). active=false porque -2 < 3. "
                "Verifica el camino de datos con producto negativo en fmi2GetReal."
            ),
        },
        {
            "id": "TC-CS-008",
            "title": "Cambio de entrada a mitad — respuesta inmediata",
            "description": "u1 cambia de 1 a 5 en t=0.5s. Respuesta algebraica inmediata.",
            "t_end": 1.0, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": 1.0, "u2": 2.0},
            "schedule": {"u1": [(0, 1.0), (0.5, 5.0)]},
            "checks": [
                {"col": "y_sum",  "type": "at_t", "at_t": 0.4, "val": 3.0, "tol": 1e-9},
                {"col": "y_sum",  "type": "at_t", "at_t": 1.0, "val": 7.0, "tol": 1e-9},
                {"col": "active", "type": "at_t", "at_t": 1.0, "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "El modelo CS algebraico responde instantaneamente al cambio de entrada. "
                "Antes del cambio (t=0.4s): u1=1+u2=2, suma=3. Despues (t=1s): "
                "u1=5+u2=2, suma=7. Ademas active cambia de false a true. Esto "
                "confirma que fmi2SetReal es llamado en cada paso de comunicacion "
                "y no solo en la inicializacion."
            ),
        },
        {
            "id": "TC-CS-009",
            "title": "Valores muy pequeños — cerca de epsilon maquina",
            "description": "u1=u2=1e-15: suma=2e-15, producto=1e-30.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": 1.0e-15, "u2": 1.0e-15},
            "checks": [
                {"col": "y_sum",  "type": "final_value", "val": 2.0e-15, "tol": 1e-25},
                {"col": "y_prod", "type": "no_nan_inf"},
                {"col": "active", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Valores cerca del epsilon de maquina (1e-15). El producto (1e-30) "
                "esta cerca del subdesbordamiento de double. Se verifica que no "
                "hay NaN ni Inf y que la comparacion active da correctamente false "
                "para valores iguales muy pequenos."
            ),
        },
        {
            "id": "TC-CS-010",
            "title": "Verificacion estructural — sin solver ODE en CS",
            "description": "Simulacion CS larga sin divergencia: modelo algebraico puro.",
            "t_end": 10.0, "h": 1.0, "solver": "rk4", "mode": "cs",
            "inputs": {"u1": 2.0, "u2": 1.0},
            "checks": [
                {"col": "y_sum",  "type": "always", "op": "==", "val": 3.0},
                {"col": "y_prod", "type": "always", "op": "==", "val": 2.0},
                {"col": "active", "type": "eventually", "op": "==", "val": 1},
            ],
            "interpretation": (
                "En 10 segundos de simulacion con paso de 1s, las salidas algebraicas "
                "permanecen constantes en todos los pasos (suma=3, producto=2, active=1). "
                "Al ser el modelo puramente algebraico, no hay integracion ni acumulacion "
                "de error. Esto confirma que la ruta CS del codegen no introduce ODE "
                "solver ni modifica los outputs entre pasos de comunicacion."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
