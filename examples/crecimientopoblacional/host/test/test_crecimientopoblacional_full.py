#!/usr/bin/env python3
"""Test battery completa — CrecimientoPoblacional (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "CrecimientoPoblacional",
    "tests": [
        {
            "id": "TC-CP-001",
            "title": "Condiciones iniciales — N(0)=2",
            "description": "En t=0: poblacion=2.0, saturacion=0.02, superpoblacion=false.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": 0.0},
            "checks": [
                {"col": "poblacion",        "type": "at_t", "at_t": 0.0, "val": 2.0, "tol": 0.01},
                {"col": "saturacion",       "type": "at_t", "at_t": 0.0, "val": 0.02,"tol": 0.001},
                {"col": "superpoblacion",   "type": "at_t", "at_t": 0.0, "val": 0,   "tol": 0},
                {"col": "tasa_crecimiento", "type": "at_t", "at_t": 0.0, "val": 6.86,"tol": 0.1},
            ],
            "interpretation": (
                "La poblacion empieza en N=2 individuos, muy lejos del equilibrio K=100. "
                "La tasa inicial de crecimiento es r*N*(1-N/K) = 3.5*2*(1-0.02) = 6.86 "
                "individuos/tiempo. La saturacion N/K=0.02 indica que el sistema esta "
                "muy lejos de la capacidad de carga."
            ),
        },
        {
            "id": "TC-CP-002",
            "title": "Convergencia a K con RK4 (t=5 s) — sin sobredisparo",
            "description": "poblacion > 95 a t=5 s, superpoblacion=false con RK4.",
            "t_end": 5.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": 0.0},
            "checks": [
                {"col": "poblacion",      "type": "final_value", "val": 97.0, "tol": 3.0},
                {"col": "superpoblacion", "type": "always", "op": "==", "val": 0},
            ],
            "interpretation": (
                "CRITERIO PRIMARIO RK4. La ecuacion logistica con r=3.5, K=100 "
                "converge a K sin sobredisparo con RK4 y h=0.1. La poblacion debe "
                "superar 95 individuos a t=5 s y nunca exceder 100 (superpoblacion=false "
                "en todo momento). RK4 sigue la curva sigmoidal correctamente."
            ),
        },
        {
            "id": "TC-CP-003",
            "title": "Sobredisparo de Euler — discriminador de integrador",
            "description": "Euler con h=1.0 (grande) debe causar superpoblacion (N>100) antes de t=3 s.",
            "t_end": 3.0, "h": 1.0, "solver": "euler", "mode": "me",
            "inputs": {"tasa_entrada": 0.0},
            "checks": [
                {"col": "superpoblacion", "type": "eventually",
                 "op": "==", "val": 1,
                 "description": "Euler con h grande debe superar K=100"},
            ],
            "interpretation": (
                "Con h=1.0 (paso grande), Euler acumula un error significativo en la "
                "region de maximo crecimiento logistico (N≈50, dN/dt_max≈87.5). "
                "El paso de 87.5 lleva N de ~37 a ~125 en un solo paso, activando "
                "superpoblacion. Con h=0.1 el error es insuficiente para superar K. "
                "Discriminador clave: RK4 con cualquier h razonable no sobrepasa."
            ),
        },
        {
            "id": "TC-CP-004",
            "title": "Pico de tasa de crecimiento cerca de N=50",
            "description": "max(tasa_crecimiento) ≈ 87.5 ind/tiempo (r*K/4).",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": 0.0},
            "checks": [
                {"col": "tasa_crecimiento", "type": "eventually",
                 "op": ">", "val": 80.0,
                 "description": "tasa maxima debe superar 80 ind/tiempo"},
            ],
            "interpretation": (
                "El punto de inflexion de la curva logistica es N*=K/2=50, donde "
                "la tasa de crecimiento alcanza su maximo: r*K/4=3.5*100/4=87.5. "
                "El test verifica que la trayectoria pasa por esta region y que "
                "el codegen genera correctamente el termino r*N*(1-N/K)."
            ),
        },
        {
            "id": "TC-CP-005",
            "title": "RK4 converge monotonamente — sin oscilacion alrededor de K",
            "description": "Con RK4, poblacion es estrictamente creciente.",
            "t_end": 10.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": 0.0},
            "checks": [
                {"col": "poblacion", "type": "monotone_inc"},
                {"col": "poblacion", "type": "bounded", "low": 0.0, "high": 101.0},
            ],
            "interpretation": (
                "La ecuacion logistica con condiciones iniciales N(0)=2 < K=100 "
                "produce una trayectoria monotonamente creciente hacia K. RK4 debe "
                "reproducir esta propiedad sin oscilaciones. Euler puede oscilar "
                "alrededor de K, pero RK4 con h=0.1 no deberia."
            ),
        },
        {
            "id": "TC-CP-006",
            "title": "Saturacion cerca de 1.0 a largo plazo",
            "description": "A t=10 s, saturacion = N/K debe estar dentro de 0.5% de 1.0.",
            "t_end": 10.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": 0.0},
            "checks": [
                {"col": "saturacion", "type": "final_value", "val": 1.0, "tol": 0.005},
            ],
            "interpretation": (
                "A largo plazo (10 constantes de tiempo aproximadamente), la ecuacion "
                "logistica converge a N=K=100, y saturacion=N/K → 1.0. Una desviacion "
                "mayor al 0.5% indicaria que el integrador no ha convergido o que "
                "el punto de equilibrio calculado es incorrecto."
            ),
        },
        {
            "id": "TC-CP-007",
            "title": "Inmigracion positiva — equilibrio por encima de K",
            "description": "Con tasa_entrada=5.0, la poblacion de equilibrio supera K=100.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": 5.0},
            "checks": [
                {"col": "poblacion", "type": "final_value", "val": 103.0, "tol": 5.0},
            ],
            "interpretation": (
                "La inmigracion constante de 5 individuos/tiempo eleva el equilibrio "
                "por encima de K. En el equilibrio: 0 = r*N*(1-N/K)+u implica N*>100. "
                "El test verifica que la entrada u=5 se suma correctamente a la ODE "
                "y que el FMU responde al input en el bucle de simulacion."
            ),
        },
        {
            "id": "TC-CP-008",
            "title": "Emigracion negativa — equilibrio por debajo de K",
            "description": "Con tasa_entrada=-1.0, la poblacion converge a N*<100.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": -1.0},
            "checks": [
                {"col": "poblacion", "type": "final_value", "val": 97.0, "tol": 4.0},
            ],
            "interpretation": (
                "La emigracion reduce la poblacion de equilibrio por debajo de K. "
                "Con u=-1, el equilibrio se mueve a N*<100. El test verifica que "
                "fmi2SetReal maneja correctamente valores negativos del input, "
                "modificando la ODE en la direccion correcta."
            ),
        },
        {
            "id": "TC-CP-009",
            "title": "Cambio de tasa de inmigracion en t=2 s",
            "description": "tasa_entrada cambia de 0 a 20 en t=2 s. Convergencia mas rapida.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": 0.0},
            "schedule": {"tasa_entrada": [(0, 0.0), (2.0, 20.0)]},
            "checks": [
                {"col": "poblacion", "type": "at_t", "at_t": 2.0, "val": 95.0, "tol": 5.0},
                {"col": "poblacion", "type": "final_value", "val": 105.0, "tol": 10.0},
            ],
            "interpretation": (
                "A t=2 s la poblacion ya habra crecido notablemente (N≈70-80). "
                "Al aplicar inmigracion de 20 individuos/tiempo, el equilibrio se "
                "eleva por encima de K y la convergencia es mas rapida. A t=5 s, "
                "la poblacion debe superar 100 (N*>100 por la inmigracion). "
                "Verifica que fmi2SetReal se llama en el bucle de simulacion."
            ),
        },
        {
            "id": "TC-CP-010",
            "title": "Sin NaN ni Inf con RK4 en 10 s",
            "description": "Simulacion completa de la curva logistica sin valores invalidos.",
            "t_end": 10.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tasa_entrada": 0.0},
            "checks": [
                {"col": "poblacion",        "type": "no_nan_inf"},
                {"col": "tasa_crecimiento", "type": "no_nan_inf"},
                {"col": "saturacion",       "type": "no_nan_inf"},
            ],
            "interpretation": (
                "La ecuacion logistica tiene un termino N*(1-N/K) que puede producir "
                "problemas numericos si N diverge. Con RK4 y h=0.01, el sistema "
                "debe mantenerse sin valores invalidos durante la convergencia completa "
                "desde N=2 hasta N≈100."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
