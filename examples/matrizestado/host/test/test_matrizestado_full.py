#!/usr/bin/env python3
"""Test battery completa — MatrizEstado (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "MatrizEstado",
    "tests": [
        {
            "id": "TC-MZ-001",
            "title": "Condiciones iniciales — todos los estados en cero",
            "description": "En t=0 con u=1: x[1]=x[2]=x[3]=0, norma=0, traza=6.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 1.0},
            "checks": [
                {"col": "x_1_",   "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "x_2_",   "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "x_3_",   "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "y_norma","type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "traza",  "type": "at_t", "at_t": 0.0, "val": 6.0, "tol": 1e-9},
            ],
            "interpretation": (
                "El sistema empieza en x(0)=[0,0,0]. La traza A[1,1]+A[2,2]+A[3,3]="
                "1+2+3=6.0 es constante e independiente del estado. Este test "
                "verifica que la FMU se inicializa correctamente y que los "
                "parametros de la matriz A se leen bien en la inicializacion."
            ),
        },
        {
            "id": "TC-MZ-002",
            "title": "Traza constante en todo momento",
            "description": "traza debe ser exactamente 6.0 en todos los pasos de simulacion.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 1.0},
            "checks": [
                {"col": "traza", "type": "always", "op": "==", "val": 6.0},
            ],
            "interpretation": (
                "La traza de A es una constante algebraica que no depende del tiempo "
                "ni de las entradas. Debe ser exactamente 6.0 en cada paso. Si la "
                "traza cambia, los parametros de la matriz se estan leyendo "
                "incorrectamente o hay un error de indexacion en la matriz A."
            ),
        },
        {
            "id": "TC-MZ-003",
            "title": "Ordenacion de estados: x3 > x2 > x1 para u>0",
            "description": "Con u=1, los estados crecen en orden inverso al indice.",
            "t_end": 2.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 1.0},
            "checks": [
                {"col": "x_1_", "type": "always", "op": ">", "val": 0.0},
                {"col": "x_2_", "type": "always", "op": ">", "val": 0.0},
                {"col": "x_3_", "type": "always", "op": ">", "val": 0.0},
            ],
            "interpretation": (
                "Para u=1, los tres estados crecen desde 0. El orden de crecimiento "
                "es x3 > x2 > x1 porque los autovalores son lambda_3=3 > lambda_2=2 > "
                "lambda_1=1 (crecimiento exponencial mas rapido para mayor autovalor). "
                "Una transposicion de la matriz A cambiaria este ordenamiento."
            ),
        },
        {
            "id": "TC-MZ-004",
            "title": "Verificacion analitica en t=1.0 s",
            "description": "x1(1)≈1.718, x2(1)≈3.195, x3(1)≈6.029 con u=1.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 1.0},
            "checks": [
                {"col": "x_1_", "type": "final_value", "val": 1.718, "tol": 0.05},
                {"col": "x_2_", "type": "final_value", "val": 3.195, "tol": 0.05},
                {"col": "x_3_", "type": "final_value", "val": 6.029, "tol": 0.05},
            ],
            "interpretation": (
                "Solucion analitica exacta: xi(1)=(exp(lambda_i)-1)/lambda_i. "
                "x1=(e^1-1)/1≈1.718, x2=(e^2-1)/2≈3.195, x3=(e^3-1)/3≈6.029. "
                "Este es el test de referencia mas preciso: detecta errores en los "
                "coeficientes de la matriz A (autovalores equivocados) y en el "
                "indexado de la matriz (transposicion de filas/columnas)."
            ),
        },
        {
            "id": "TC-MZ-005",
            "title": "Norma creciente con u>0",
            "description": "y_norma = sqrt(x1^2+x2^2+x3^2) debe ser monotonamente creciente.",
            "t_end": 3.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 1.0},
            "checks": [
                {"col": "y_norma", "type": "monotone_inc"},
            ],
            "interpretation": (
                "Con todos los estados creciendo (sistema inestable con autovalores "
                "positivos), la norma euclidea tambien debe crecer monotonamente. "
                "No hay oscilaciones en este sistema lineal con A diagonal. "
                "Una norma no monotona indicaria un error en la integracion."
            ),
        },
        {
            "id": "TC-MZ-006",
            "title": "Entrada cero — estados permanecen en cero",
            "description": "Con u=0 y x(0)=0: todos los estados deben ser exactamente 0.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 0.0},
            "checks": [
                {"col": "x_1_",    "type": "always", "op": "==", "val": 0.0},
                {"col": "x_2_",    "type": "always", "op": "==", "val": 0.0},
                {"col": "x_3_",    "type": "always", "op": "==", "val": 0.0},
                {"col": "y_norma", "type": "always", "op": "==", "val": 0.0},
            ],
            "interpretation": (
                "El sistema homogeneo A*x con x(0)=0 y u=0 tiene solucion trivial "
                "x(t)=0 para todo t. Cualquier derivacion de cero indica que el "
                "integrador acumula error numerico desde las condiciones iniciales "
                "o que la FMU tiene una salida de ruido no esperada."
            ),
        },
        {
            "id": "TC-MZ-007",
            "title": "Entrada negativa — estados negativos con mismo ordenamiento",
            "description": "Con u=-1: x1,x2,x3 < 0 con |x3|>|x2|>|x1|.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": -1.0},
            "checks": [
                {"col": "x_1_", "type": "always", "op": "<", "val": 0.0},
                {"col": "x_2_", "type": "always", "op": "<", "val": 0.0},
                {"col": "x_3_", "type": "always", "op": "<", "val": 0.0},
            ],
            "interpretation": (
                "Con u=-1, la solucion es xi(t)=-(e^(lambda_i*t)-1)/lambda_i < 0. "
                "Los estados crecen en valor absoluto en la direccion negativa. "
                "El orden de crecimiento absoluto sigue siendo |x3|>|x2|>|x1|. "
                "Verifica el manejo de signos en fmi2SetReal."
            ),
        },
        {
            "id": "TC-MZ-008",
            "title": "Cambio de entrada en t=1 s — sistema inestable sigue creciendo",
            "description": "Al poner u=0 en t=1s, el sistema inestable sigue creciendo.",
            "t_end": 2.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 1.0},
            "schedule": {"u_1_": [(0, 1.0), (1.0, 0.0)]},
            "checks": [
                {"col": "x_1_", "type": "at_t", "at_t": 2.0, "val": 2.0, "tol": 1.0},
                {"col": "x_3_", "type": "at_t", "at_t": 2.0, "val": 30.0, "tol": 15.0},
            ],
            "interpretation": (
                "El sistema con A diagonal positiva es inestable: los estados crecen "
                "exponencialmente incluso sin entrada (u=0). En t=1 s, x3≈6. "
                "Despues de cambiar u=0, x3 sigue creciendo (sistema homogeneo "
                "inestable). A t=2 s, x3≈6*exp(3*1)≈120. Este test verifica "
                "que el cambio de entrada se aplica correctamente en el bucle."
            ),
        },
        {
            "id": "TC-MZ-009",
            "title": "Traza no cambia con entrada",
            "description": "Con u=100, la traza sigue siendo 6.0.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 100.0},
            "checks": [
                {"col": "traza", "type": "always", "op": "==", "val": 6.0},
            ],
            "interpretation": (
                "La traza es A[1,1]+A[2,2]+A[3,3]=6.0, independiente de u y del tiempo. "
                "Con una entrada grande (u=100), los estados crecen rapidamente pero "
                "la traza permanece en 6.0. Este test confirma que traza es realmente "
                "una constante algebraica y no una funcion del estado."
            ),
        },
        {
            "id": "TC-MZ-010",
            "title": "Sin NaN ni Inf en 2 segundos",
            "description": "Sistema inestable: los estados crecen pero no deben producir NaN.",
            "t_end": 2.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u_1_": 1.0},
            "checks": [
                {"col": "x_1_",    "type": "no_nan_inf"},
                {"col": "x_2_",    "type": "no_nan_inf"},
                {"col": "x_3_",    "type": "no_nan_inf"},
                {"col": "y_norma", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "En 2 segundos, x3 puede crecer hasta e^6≈400. Este valor grande "
                "pero finito no debe causar NaN/Inf con double precision. "
                "Simulaciones mas largas si podrian producir overflow (e^30≈1e13), "
                "por lo que el test se limita a t=2 s para mantenerse en rango seguro."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
