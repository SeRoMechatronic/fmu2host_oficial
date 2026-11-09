#!/usr/bin/env python3
"""Test battery completa — Mi_Modelo_Nuevo (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "Mi_Modelo_Nuevo",
    "tests": [
        {
            "id": "TC-MN-001",
            "title": "Condiciones iniciales — filtro en reposo",
            "description": "En t=0 con entrada=1.0 y filtro activo: salida=0, flag_salida=false.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 1.0, "flag_activo": 1},
            "checks": [
                {"col": "salida_filtrada", "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "flag_salida",     "type": "at_t", "at_t": 0.0, "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "El filtro de primer orden parte del estado inicial x(0)=0. "
                "Aunque la entrada es 1.0, la salida filtrada empieza en 0 y "
                "converge gradualmente. flag_salida=false porque 0.0 < 0.5. "
                "Este test verifica que la condicion inicial se respeta antes "
                "de cualquier integracion."
            ),
        },
        {
            "id": "TC-MN-002",
            "title": "Respuesta al escalon — 63% en t=tau=1.0 s",
            "description": "Con entrada=1.0 y tau=1.0 s, la salida debe ser 0.632 en t=1 s.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 1.0, "flag_activo": 1},
            "checks": [
                {"col": "salida_filtrada", "type": "final_value", "val": 0.632, "tol": 0.02},
                {"col": "flag_salida",     "type": "final_value", "val": 1,     "tol": 0},
            ],
            "interpretation": (
                "La regla del 63% de los filtros de primer orden: a t=tau la salida "
                "alcanza 1-e^-1 ≈ 0.632 del valor final. Con tau=1.0 s y entrada=1.0, "
                "salida_filtrada(1)=0.632. flag_salida=true porque 0.632>0.5. "
                "Este es el test de referencia para verificar la constante de tiempo."
            ),
        },
        {
            "id": "TC-MN-003",
            "title": "Respuesta al escalon — 99.3% en t=5·tau=5.0 s",
            "description": "A 5 constantes de tiempo, la salida es 1-e^-5 ≈ 0.993.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 1.0, "flag_activo": 1},
            "checks": [
                {"col": "salida_filtrada", "type": "final_value", "val": 0.993, "tol": 0.01},
                {"col": "flag_salida",     "type": "final_value", "val": 1,     "tol": 0},
            ],
            "interpretation": (
                "A 5 constantes de tiempo el filtro esta virtualmente en estado "
                "estacionario (99.3% del valor final). Esta es la prueba de "
                "convergencia a largo plazo del filtro: verifica que el integrador "
                "mantiene la precision hasta el estado estacionario."
            ),
        },
        {
            "id": "TC-MN-004",
            "title": "Cruce de umbral flag_salida en t≈0.693 s",
            "description": "flag_salida cambia a true cuando salida_filtrada cruza 0.5.",
            "t_end": 1.5, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 1.0, "flag_activo": 1},
            "checks": [
                {"col": "flag_salida", "type": "at_t", "at_t": 0.6,  "val": 0, "tol": 0},
                {"col": "flag_salida", "type": "at_t", "at_t": 0.75, "val": 1, "tol": 0},
            ],
            "interpretation": (
                "El cruce de 0.5 ocurre en t=ln(2)≈0.693 s. Antes (t=0.6 s), "
                "la salida es 1-e^-0.6≈0.451<0.5, por lo que flag_salida=false. "
                "Despues (t=0.75 s), la salida es 1-e^-0.75≈0.528>0.5, flag_salida=true. "
                "Verifica que el umbral booleano de salida se calcula correctamente."
            ),
        },
        {
            "id": "TC-MN-005",
            "title": "Desactivacion — decaimiento exponencial al desactivar filtro",
            "description": "Al poner flag_activo=false en t=3 s, la salida decae.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 1.0, "flag_activo": 1},
            "schedule": {"flag_activo": [(0, 1), (3.0, 0)]},
            "checks": [
                {"col": "salida_filtrada", "type": "at_t", "at_t": 3.0, "val": 0.950, "tol": 0.02},
                {"col": "salida_filtrada", "type": "at_t", "at_t": 4.0, "val": 0.350, "tol": 0.03},
                {"col": "salida_filtrada", "type": "at_t", "at_t": 5.0, "val": 0.128, "tol": 0.03},
            ],
            "interpretation": (
                "A t=3 s (3 constantes de tiempo), la salida esta a ≈0.950 del valor "
                "final. Al desactivar el filtro, la ODE cambia a tau*dx/dt=-x (decaimiento "
                "libre). En t=4 s (1s despues): 0.950*e^-1≈0.350. En t=5 s: 0.950*e^-2≈0.128. "
                "Verifica que fmi2SetBoolean modifica la ODE correctamente en tiempo real."
            ),
        },
        {
            "id": "TC-MN-006",
            "title": "Escalon de entrada de 1.0 a 2.0 en t=5 s",
            "description": "Tras convergencia a 1.0, un nuevo escalon a 2.0 inicia nuevo transitorio.",
            "t_end": 6.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 1.0, "flag_activo": 1},
            "schedule": {"entrada_principal": [(0, 1.0), (5.0, 2.0)]},
            "checks": [
                {"col": "salida_filtrada", "type": "at_t", "at_t": 5.0, "val": 0.993, "tol": 0.01},
                {"col": "salida_filtrada", "type": "at_t", "at_t": 6.0, "val": 1.632, "tol": 0.03},
            ],
            "interpretation": (
                "Despues de 5 tau la salida ha convergido a ≈1.0. Al aplicar el nuevo "
                "escalon a 2.0, en t=6 s (1 tau despues del escalon) la salida sera "
                "1.0 + 1.0*(1-e^-1) ≈ 1.632. Verifica que fmi2SetReal actualiza "
                "la entrada en cada paso de simulacion correctamente."
            ),
        },
        {
            "id": "TC-MN-007",
            "title": "Entrada grande — sin saturacion",
            "description": "entrada=100.0 activa: salida debe converger a ≈99.3 en t=5 s.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 100.0, "flag_activo": 1},
            "checks": [
                {"col": "salida_filtrada", "type": "final_value", "val": 99.3, "tol": 1.0},
                {"col": "flag_salida",     "type": "final_value", "val": 1,    "tol": 0},
            ],
            "interpretation": (
                "El filtro es lineal: una entrada de 100.0 produce una salida de "
                "100*(1-e^-5)≈99.3 a t=5 s. No hay saturacion. flag_salida=true "
                "en cuanto salida>0.5. Verifica que el filtro escala correctamente "
                "con la magnitud de la entrada."
            ),
        },
        {
            "id": "TC-MN-008",
            "title": "Entrada negativa — filtro rastrea valores negativos",
            "description": "entrada=-1.0: salida converge a ≈-0.993, flag_salida=false.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": -1.0, "flag_activo": 1},
            "checks": [
                {"col": "salida_filtrada", "type": "final_value", "val": -0.993, "tol": 0.01},
                {"col": "flag_salida",     "type": "always", "op": "==", "val": 0},
            ],
            "interpretation": (
                "El filtro maneja correctamente entradas negativas. La salida converge "
                "a -1*(1-e^-5) ≈ -0.993, permaneciendo siempre negativa (< 0.5), "
                "por lo que flag_salida es siempre false. Verifica el manejo de "
                "signos en fmi2SetReal y en la solucion de la ODE."
            ),
        },
        {
            "id": "TC-MN-009",
            "title": "Salida siempre positiva y creciente durante activacion",
            "description": "Con entrada=1.0 y activo=true, salida es monotona creciente.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 1.0, "flag_activo": 1},
            "checks": [
                {"col": "salida_filtrada", "type": "monotone_inc"},
                {"col": "salida_filtrada", "type": "always", "op": ">=", "val": 0.0},
            ],
            "interpretation": (
                "La respuesta al escalon de un filtro de primer orden es "
                "monotonamente creciente (exponencial creciente). Cualquier "
                "oscilacion en salida_filtrada indicaria un error en la integracion "
                "de la ODE tau*dx/dt = u-x."
            ),
        },
        {
            "id": "TC-MN-010",
            "title": "Sin NaN ni Inf en simulacion completa",
            "description": "5 segundos de simulacion del filtro sin valores invalidos.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"entrada_principal": 1.0, "flag_activo": 1},
            "checks": [
                {"col": "salida_filtrada", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "El modelo Mi_Modelo_Nuevo tiene un nombre con guiones bajos que "
                "testa el codegen de nombres de identificadores C. Si el codegen "
                "genera funciones invalidas (ej. con guiones), el ejecutable no "
                "compila y este test no podra ejecutarse. La ejecucion exitosa "
                "confirma implicitamente que el naming es correcto."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
