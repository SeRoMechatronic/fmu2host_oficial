#!/usr/bin/env python3
"""Test battery completa — SinInputs (8 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "SinInputs",
    "tests": [
        {
            "id": "TC-NI-001",
            "title": "Condiciones iniciales en t=0",
            "description": "Verifica posicion=1.0, velocidad=0.0, energia=5.0 en t=0.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion",  "type": "at_t", "at_t": 0.0, "val": 1.0, "tol": 1e-6},
                {"col": "velocidad", "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "energia",   "type": "at_t", "at_t": 0.0, "val": 5.0, "tol": 1e-3},
            ],
            "interpretation": (
                "El sistema arranca desde x0=1.0 m con velocidad nula. La energia "
                "inicial es 0.5*k*x0^2 = 0.5*10*1^2 = 5.0 J. Este test confirma que "
                "el codegen no necesita llamadas fmi2Set* para un FMU sin entradas "
                "y que las condiciones iniciales se leen correctamente de la FMU."
            ),
        },
        {
            "id": "TC-NI-002",
            "title": "Energia monotonamente decreciente",
            "description": "Con amortiguacion positiva, la energia debe decrecer estrictamente.",
            "t_end": 20.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia", "type": "monotone_dec"},
            ],
            "interpretation": (
                "El amortiguador disipa energia continuamente. Con c=0.3 N·s/m y "
                "ζ≈0.055, el sistema es subamortiguado y oscila mientras la energia "
                "decrece. Cualquier aumento de energia indicaria un error del integrador. "
                "RK4 con h=0.01 mantiene la monotonia energetica para este sistema."
            ),
        },
        {
            "id": "TC-NI-003",
            "title": "Posicion cruza el cero al menos 4 veces (oscilacion subamortiguada)",
            "description": "ζ≈0.055 implica oscilacion. La posicion debe cambiar de signo varias veces.",
            "t_end": 10.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion", "type": "sign_changes", "min_changes": 4},
            ],
            "interpretation": (
                "Con razon de amortiguacion ζ≈0.055, el sistema es claramente "
                "subamortiguado. El periodo amortiguado es T≈2.43 s, por lo que en "
                "10 s deben ocurrir al menos 4 cruces por cero. Si el sistema fuera "
                "criticamente amortiguado (por error de parametros), no oscilaria "
                "y este test fallaria."
            ),
        },
        {
            "id": "TC-NI-004",
            "title": "Comprobacion analitica en t=1.0 s",
            "description": "Solcion analitica: x(1)≈-0.728. Verifica precision del integrador RK4.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion", "type": "final_value", "val": -0.728, "tol": 0.05},
            ],
            "interpretation": (
                "La solucion analitica del oscilador subamortiguado a t=1s es "
                "x(1) ≈ e^(-0.1415) * cos(2.58) ≈ 0.868 * (-0.839) ≈ -0.728 m. "
                "RK4 con h=0.01 debe reproducir este valor con error menor a ±0.05 m. "
                "Si el resultado es muy diferente, el codegen ha generado coeficientes "
                "de ODE incorrectos para los parametros masa/amortiguacion/rigidez."
            ),
        },
        {
            "id": "TC-NI-005",
            "title": "Convergencia a cero a largo plazo",
            "description": "A t=100s el sistema amortiguado debe estar cerca del reposo.",
            "t_end": 100.0, "h": 0.05, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion",  "type": "at_t", "at_t": 100.0, "val": 0.0, "tol": 0.01},
                {"col": "velocidad", "type": "at_t", "at_t": 100.0, "val": 0.0, "tol": 0.01},
                {"col": "energia",   "type": "at_t", "at_t": 100.0, "val": 0.0, "tol": 0.001},
            ],
            "interpretation": (
                "Tras 100 segundos de amortiguamiento, el sistema converge al reposo. "
                "La constante de tiempo de decaimiento es τ=1/(ζ·ω0)≈7.07 s, por lo "
                "que a t=100s han transcurrido ~14 constantes de tiempo y la amplitud "
                "es e^(-14) ≈ 8e-7 m. La energia debe ser practicamente cero."
            ),
        },
        {
            "id": "TC-NI-006",
            "title": "Energia inicial correcta",
            "description": "Verifica E(0)=5.0 J = 0.5*k*x0^2 con k=10, x0=1.",
            "t_end": 0.001, "h": 0.0001, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia", "type": "at_t", "at_t": 0.0, "val": 5.0, "tol": 1e-6},
            ],
            "interpretation": (
                "La energia inicial E0 = 0.5*k*x0^2 + 0.5*m*v0^2 = 0.5*10*1 + 0 = 5 J. "
                "Este test de precision alta verifica que la formula de energia esta "
                "implementada correctamente en la FMU desde el primer instante."
            ),
        },
        {
            "id": "TC-NI-007",
            "title": "Sin NaN ni Inf en 20 segundos",
            "description": "Simulacion larga: ningun output debe producir valores invalidos.",
            "t_end": 20.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion",  "type": "no_nan_inf"},
                {"col": "velocidad", "type": "no_nan_inf"},
                {"col": "energia",   "type": "no_nan_inf"},
            ],
            "interpretation": (
                "20 segundos de simulacion sin entradas ni eventos. Si el codegen "
                "genera codigo de derivadas incorrecto o hay un error en la FMU, "
                "el integrador puede producir NaN/Inf. Este test verifica la "
                "estabilidad numerica basica del FMU de cero entradas."
            ),
        },
        {
            "id": "TC-NI-008",
            "title": "Posicion acotada durante oscilacion",
            "description": "La amplitud amortiguada no debe exceder el valor inicial de 1.0 m.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion", "type": "bounded", "low": -1.01, "high": 1.01},
            ],
            "interpretation": (
                "Con amortiguamiento positivo, la amplitud nunca debe superar la "
                "amplitud inicial x0=1.0 m. El sistema oscila con amplitud decreciente. "
                "Si la posicion supera 1.01 m (con tolerancia del 1%), el integrador "
                "esta ganando energia artificialmente, lo que indica un error de "
                "implementacion del ODE solver."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
