#!/usr/bin/env python3
"""Test battery completa — TiposMixtos (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "TiposMixtos",
    "tests": [
        {
            "id": "TC-TM-001",
            "title": "Valores nominales — todos los tipos activos",
            "description": "r_in=3.0, i_in=5, b_in=true: r_out=6, i_out=6, b_out=false, r_abs=3.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 3.0, "i_in": 5, "b_in": 1},
            "checks": [
                {"col": "r_out", "type": "final_value", "val": 6.0, "tol": 1e-9},
                {"col": "i_out", "type": "final_value", "val": 6,   "tol": 0},
                {"col": "b_out", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "r_abs", "type": "final_value", "val": 3.0, "tol": 1e-9},
            ],
            "interpretation": (
                "Caso nominal con los cuatro tipos de FMI 2.0 activos simultaneamente. "
                "r_out=r_in*2=6, i_out=i_in+1=6, b_out=NOT(TRUE)=FALSE, r_abs=|3|=3. "
                "Este test ejercita los cuatro caminos de fmi2Set*/fmi2Get* en un "
                "solo paso de simulacion."
            ),
        },
        {
            "id": "TC-TM-002",
            "title": "Real negativo, entero cero, booleano false",
            "description": "r_in=-4.5, i_in=0, b_in=false: r_out=-9, i_out=1, b_out=true, r_abs=4.5.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": -4.5, "i_in": 0, "b_in": 0},
            "checks": [
                {"col": "r_out", "type": "final_value", "val": -9.0, "tol": 1e-9},
                {"col": "i_out", "type": "final_value", "val": 1,    "tol": 0},
                {"col": "b_out", "type": "final_value", "val": 1,    "tol": 0},
                {"col": "r_abs", "type": "final_value", "val": 4.5,  "tol": 1e-9},
            ],
            "interpretation": (
                "Real negativo: r_out=-9 (negativo) pero r_abs=4.5 (positivo). "
                "Entero cero: i_out=0+1=1. Booleano false negado: b_out=TRUE. "
                "Verifica que r_abs no confunde el signo con el resultado de r_out "
                "y que el tipo Boolean se niega correctamente para FALSE."
            ),
        },
        {
            "id": "TC-TM-003",
            "title": "Real cero",
            "description": "r_in=0.0: r_out=0, r_abs=0 (cero como valor absoluto).",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 0.0, "i_in": 10, "b_in": 1},
            "checks": [
                {"col": "r_out", "type": "final_value", "val": 0.0,  "tol": 1e-9},
                {"col": "i_out", "type": "final_value", "val": 11,   "tol": 0},
                {"col": "b_out", "type": "final_value", "val": 0,    "tol": 0},
                {"col": "r_abs", "type": "final_value", "val": 0.0,  "tol": 1e-9},
            ],
            "interpretation": (
                "El valor absoluto del cero es cero. r_out=0*2=0 y r_abs=|0|=0. "
                "i_out=10+1=11. b_out=NOT(TRUE)=FALSE. El cero como entrada real "
                "no debe causar comportamientos especiales en ninguno de los tipos."
            ),
        },
        {
            "id": "TC-TM-004",
            "title": "Entero negativo",
            "description": "i_in=-7: i_out=-7+1=-6. Incremento correcto para negativos.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 1.0, "i_in": -7, "b_in": 0},
            "checks": [
                {"col": "r_out", "type": "final_value", "val": 2.0,  "tol": 1e-9},
                {"col": "i_out", "type": "final_value", "val": -6,   "tol": 0},
                {"col": "b_out", "type": "final_value", "val": 1,    "tol": 0},
            ],
            "interpretation": (
                "El incremento i_in+1 funciona correctamente para enteros negativos: "
                "-7+1=-6. Un error de implementacion comun es usar abs() antes de "
                "incrementar, lo que daria 7+1=8 en lugar de -6. b_out=NOT(FALSE)=TRUE."
            ),
        },
        {
            "id": "TC-TM-005",
            "title": "Real grande",
            "description": "r_in=1e8: r_out=2e8, sin desbordamiento de double.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 1.0e8, "i_in": 999, "b_in": 1},
            "checks": [
                {"col": "r_out", "type": "final_value", "val": 2.0e8, "tol": 1.0},
                {"col": "i_out", "type": "final_value", "val": 1000,  "tol": 0},
                {"col": "r_abs", "type": "final_value", "val": 1.0e8, "tol": 1.0},
            ],
            "interpretation": (
                "Magnitud grande (1e8): el double puede representar exactamente "
                "2e8 sin perdida de precision. i_out=999+1=1000. Verifica que "
                "no hay truncamiento accidental de los tipos cuando los valores "
                "son grandes pero dentro del rango de double."
            ),
        },
        {
            "id": "TC-TM-006",
            "title": "Real muy pequeño",
            "description": "r_in=1e-15: r_out≈2e-15, sin truncamiento a cero.",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 1.0e-15, "i_in": 0, "b_in": 0},
            "checks": [
                {"col": "r_out", "type": "final_value", "val": 2.0e-15, "tol": 1e-25},
                {"col": "r_abs", "type": "final_value", "val": 1.0e-15, "tol": 1e-25},
                {"col": "r_out", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Valor real cerca del epsilon de maquina (1e-15 >> DBL_EPSILON≈2.2e-16). "
                "r_out=2e-15 no debe ser truncado a cero. Verifica que fmi2SetReal "
                "transmite valores muy pequenos sin perdida de precision."
            ),
        },
        {
            "id": "TC-TM-007",
            "title": "Entero cerca del maximo de int32",
            "description": "i_in=2147483646: i_out=2147483647 (INT32_MAX).",
            "t_end": 0.2, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 0.0, "i_in": 2147483646, "b_in": 0},
            "checks": [
                {"col": "i_out", "type": "final_value", "val": 2147483647, "tol": 0},
            ],
            "interpretation": (
                "INT32_MAX - 1 + 1 = INT32_MAX. Un error de tipo (almacenar el "
                "entero en float) perderia precision: (float)2147483646 ≠ 2147483646. "
                "El resultado exacto 2147483647 solo es posible si el tipo es "
                "int32_t en todo el camino de datos."
            ),
        },
        {
            "id": "TC-TM-008",
            "title": "Bascule booleano — tres pasos",
            "description": "Tres pasos alternando b_in=true/false: b_out siempre niega.",
            "t_end": 3.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 0.0, "i_in": 0, "b_in": 1},
            "schedule": {"b_in": [(0, 1), (1.0, 0), (2.0, 1)]},
            "checks": [
                {"col": "b_out", "type": "at_t", "at_t": 0.5, "val": 0, "tol": 0},
                {"col": "b_out", "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
                {"col": "b_out", "type": "at_t", "at_t": 2.5, "val": 0, "tol": 0},
            ],
            "interpretation": (
                "La negacion booleana es combinacional: b_out=NOT(b_in) en todo momento. "
                "Al cambiar b_in con el scheduler, b_out debe invertirse inmediatamente. "
                "Verifica que b_out no es latched ni tiene memoria: responde "
                "instantaneamente a cada cambio de b_in."
            ),
        },
        {
            "id": "TC-TM-009",
            "title": "Cambios simultaneos de todos los tipos",
            "description": "Cambios de r_in, i_in y b_in al mismo tiempo en cada paso.",
            "t_end": 3.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 1.0, "i_in": 0, "b_in": 1},
            "schedule": {
                "r_in": [(0, 1.0), (1.0, -2.0), (2.0, 0.0)],
                "i_in": [(0, 0),   (1.0, 5),    (2.0, -1)],
                "b_in": [(0, 1),   (1.0, 0),    (2.0, 1)],
            },
            "checks": [
                {"col": "r_out", "type": "at_t", "at_t": 0.5, "val": 2.0, "tol": 1e-9},
                {"col": "r_out", "type": "at_t", "at_t": 1.5, "val": -4.0,"tol": 1e-9},
                {"col": "i_out", "type": "at_t", "at_t": 1.5, "val": 6,   "tol": 0},
                {"col": "b_out", "type": "at_t", "at_t": 1.5, "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "Los tres tipos cambian en el mismo paso de simulacion. Verifica que "
                "fmi2SetReal, fmi2SetInteger y fmi2SetBoolean se llaman todos antes "
                "de la evaluacion de los outputs. Un codegen que solo actualiza un "
                "tipo antes de cada paso produciria valores mezclados incorrectos."
            ),
        },
        {
            "id": "TC-TM-010",
            "title": "Sin NaN ni Inf en todos los tipos",
            "description": "Simulacion con valores extremos: ningun output invalido.",
            "t_end": 2.0, "h": 1.0, "solver": "rk4", "mode": "me",
            "inputs": {"r_in": 1.0e8, "i_in": 1000000, "b_in": 1},
            "checks": [
                {"col": "r_out", "type": "no_nan_inf"},
                {"col": "r_abs", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Con valores grandes pero finitos de todos los tipos, ninguna salida "
                "debe producir NaN o Inf. r_out=2e8 y r_abs=1e8 son finitos. "
                "i_out=1000001 es un entero valido. b_out es 0 o 1. "
                "Verifica la integridad numerica del modelo algebraico completo."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
