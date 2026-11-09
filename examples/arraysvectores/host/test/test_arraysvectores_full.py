#!/usr/bin/env python3
"""Test battery completa — ArraysVectores (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "ArraysVectores",
    "tests": [
        {
            "id": "TC-AV-001",
            "title": "Todos ceros — suma e indices en cero",
            "description": "v_real=[0,0,0,0], v_int=[0,0,0,0], v_bool=[F,F,F,F]: suma=0, doble=[0,0,0,0], alguno=false.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 0.0, "v_real_2_": 0.0, "v_real_3_": 0.0, "v_real_4_": 0.0,
                "v_int_1_": 0, "v_int_2_": 0, "v_int_3_": 0, "v_int_4_": 0,
                "v_bool_1_": 0, "v_bool_2_": 0, "v_bool_3_": 0, "v_bool_4_": 0,
            },
            "checks": [
                {"col": "suma_real",   "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "suma_int",    "type": "final_value", "val": 0,   "tol": 0},
                {"col": "alguno_true", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "v_doble_1_",  "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "v_doble_4_",  "type": "final_value", "val": 0.0, "tol": 1e-9},
            ],
            "interpretation": (
                "Linea base de ceros. suma_real=0, suma_int=0, alguno_true=FALSE, todos "
                "los v_doble[i]=0. Confirma la inicializacion sin efectos laterales: "
                "ninguna variable comparte memoria con otra. Si algun doble es distinto "
                "de cero con entradas cero, hay un error de inicializacion del buffer."
            ),
        },
        {
            "id": "TC-AV-002",
            "title": "Todos unos — suma=4, doble=[2,2,2,2], alguno=true",
            "description": "v_real=[1,1,1,1], v_int=[1,1,1,1], v_bool=[T,T,T,T].",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 1.0, "v_real_2_": 1.0, "v_real_3_": 1.0, "v_real_4_": 1.0,
                "v_int_1_": 1, "v_int_2_": 1, "v_int_3_": 1, "v_int_4_": 1,
                "v_bool_1_": 1, "v_bool_2_": 1, "v_bool_3_": 1, "v_bool_4_": 1,
            },
            "checks": [
                {"col": "suma_real",   "type": "final_value", "val": 4.0, "tol": 1e-9},
                {"col": "suma_int",    "type": "final_value", "val": 4,   "tol": 0},
                {"col": "alguno_true", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "v_doble_1_",  "type": "final_value", "val": 2.0, "tol": 1e-9},
                {"col": "v_doble_4_",  "type": "final_value", "val": 2.0, "tol": 1e-9},
            ],
            "interpretation": (
                "Todos los elementos unitarios. suma_real=4 (1+1+1+1), suma_int=4, "
                "alguno_true=TRUE (cualquier TRUE activa el OR). v_doble[i]=2*1=2 para "
                "todos i. Confirma el caso nominal uniforme con todas las operaciones "
                "activas simultaneamente."
            ),
        },
        {
            "id": "TC-AV-003",
            "title": "Valores reales distintos — discriminador de indice",
            "description": "v_real=[1,2,3,4]: suma=10, v_doble=[2,4,6,8]. Si todos son iguales, hay bug de indice.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 1.0, "v_real_2_": 2.0, "v_real_3_": 3.0, "v_real_4_": 4.0,
                "v_int_1_": 0, "v_int_2_": 0, "v_int_3_": 0, "v_int_4_": 0,
                "v_bool_1_": 0, "v_bool_2_": 0, "v_bool_3_": 0, "v_bool_4_": 0,
            },
            "checks": [
                {"col": "suma_real",   "type": "final_value", "val": 10.0, "tol": 1e-9},
                {"col": "v_doble_1_",  "type": "final_value", "val": 2.0,  "tol": 1e-9},
                {"col": "v_doble_2_",  "type": "final_value", "val": 4.0,  "tol": 1e-9},
                {"col": "v_doble_3_",  "type": "final_value", "val": 6.0,  "tol": 1e-9},
                {"col": "v_doble_4_",  "type": "final_value", "val": 8.0,  "tol": 1e-9},
            ],
            "interpretation": (
                "TEST DISCRIMINADOR DE INDICE. Cada elemento tiene un valor distinto "
                "[1,2,3,4]. Si el codegen lee solo v_real[1] cuatro veces (bug de indice), "
                "todos los dobles seran 2.0 en lugar de [2,4,6,8]. suma=10 solo es "
                "correcta si los cuatro fmi2GetReal leen indices distintos. Este test "
                "es el mas critico de la bateria para detectar errores de unrolling."
            ),
        },
        {
            "id": "TC-AV-004",
            "title": "Un solo TRUE en el OR — alguno_true activado",
            "description": "v_bool=[F,F,T,F]: alguno_true=true (OR de los 4 elementos).",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 0.0, "v_real_2_": 0.0, "v_real_3_": 0.0, "v_real_4_": 0.0,
                "v_int_1_": 0, "v_int_2_": 0, "v_int_3_": 0, "v_int_4_": 0,
                "v_bool_1_": 0, "v_bool_2_": 0, "v_bool_3_": 1, "v_bool_4_": 0,
            },
            "checks": [
                {"col": "alguno_true", "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "Solo v_bool[3]=TRUE, los otros tres son FALSE. alguno_true=TRUE porque "
                "OR(F,F,T,F)=TRUE. Si el codegen solo lee v_bool[1], perderia v_bool[3] "
                "y devolveria FALSE. Este test verifica que los 4 elementos booleanos "
                "se leen y se combinan correctamente en la expresion OR."
            ),
        },
        {
            "id": "TC-AV-005",
            "title": "Todos booleanos FALSE — alguno_true=false",
            "description": "v_bool=[F,F,F,F]: alguno_true=false. OR de todos-falso es falso.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 1.0, "v_real_2_": 1.0, "v_real_3_": 1.0, "v_real_4_": 1.0,
                "v_int_1_": 5, "v_int_2_": 5, "v_int_3_": 5, "v_int_4_": 5,
                "v_bool_1_": 0, "v_bool_2_": 0, "v_bool_3_": 0, "v_bool_4_": 0,
            },
            "checks": [
                {"col": "alguno_true", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "OR de cuatro FALSE debe ser FALSE. Complementario de TC-AV-004: verifica "
                "que alguno_true no se inicializa a TRUE por defecto. Las entradas reales "
                "y enteras son no nulas para confirmar que alguno_true depende solo de "
                "los booleanos y no de los valores reales o enteros."
            ),
        },
        {
            "id": "TC-AV-006",
            "title": "Reales con signos mixtos — suma y dobles con signos",
            "description": "v_real=[-1,2,-3,4]: suma=2, v_doble=[-2,4,-6,8].",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": -1.0, "v_real_2_": 2.0, "v_real_3_": -3.0, "v_real_4_": 4.0,
                "v_int_1_": 0, "v_int_2_": 0, "v_int_3_": 0, "v_int_4_": 0,
                "v_bool_1_": 0, "v_bool_2_": 0, "v_bool_3_": 0, "v_bool_4_": 0,
            },
            "checks": [
                {"col": "suma_real",   "type": "final_value", "val": 2.0,  "tol": 1e-9},
                {"col": "v_doble_1_",  "type": "final_value", "val": -2.0, "tol": 1e-9},
                {"col": "v_doble_2_",  "type": "final_value", "val": 4.0,  "tol": 1e-9},
                {"col": "v_doble_3_",  "type": "final_value", "val": -6.0, "tol": 1e-9},
                {"col": "v_doble_4_",  "type": "final_value", "val": 8.0,  "tol": 1e-9},
            ],
            "interpretation": (
                "Entradas con signos alternos [-1,2,-3,4]. suma=-1+2-3+4=2. "
                "v_doble[i]=2*v_real[i] conserva el signo: [-2,4,-6,8]. Verifica que "
                "la multiplicacion por 2 no aplica abs() ni truncamiento de signo. "
                "Un codegen que mezcle indices produciria sumas y dobles incorrectos."
            ),
        },
        {
            "id": "TC-AV-007",
            "title": "Enteros con signos mixtos — suma_int correcto",
            "description": "v_int=[-5,10,-3,2]: suma_int=4 (-5+10-3+2).",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 0.0, "v_real_2_": 0.0, "v_real_3_": 0.0, "v_real_4_": 0.0,
                "v_int_1_": -5, "v_int_2_": 10, "v_int_3_": -3, "v_int_4_": 2,
                "v_bool_1_": 0, "v_bool_2_": 0, "v_bool_3_": 0, "v_bool_4_": 0,
            },
            "checks": [
                {"col": "suma_int", "type": "final_value", "val": 4, "tol": 0},
            ],
            "interpretation": (
                "Suma de enteros con signos mixtos: -5+10-3+2=4. El tipo fmi2Integer "
                "debe manejar negativos correctamente en el unrolling. Si el codegen "
                "convierte a unsigned o aplica abs(), la suma seria 20 en lugar de 4. "
                "Exact match required (tol=0)."
            ),
        },
        {
            "id": "TC-AV-008",
            "title": "Magnitudes grandes — sin perdida de precision en suma",
            "description": "v_real=[1e6,2e6,3e6,4e6]: suma=1e7, doble=[2e6,4e6,6e6,8e6].",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 1.0e6, "v_real_2_": 2.0e6, "v_real_3_": 3.0e6, "v_real_4_": 4.0e6,
                "v_int_1_": 1000, "v_int_2_": 2000, "v_int_3_": 3000, "v_int_4_": 4000,
                "v_bool_1_": 1, "v_bool_2_": 0, "v_bool_3_": 1, "v_bool_4_": 0,
            },
            "checks": [
                {"col": "suma_real",   "type": "final_value", "val": 1.0e7,  "tol": 1.0},
                {"col": "suma_int",    "type": "final_value", "val": 10000,  "tol": 0},
                {"col": "alguno_true", "type": "final_value", "val": 1,      "tol": 0},
                {"col": "v_doble_1_",  "type": "final_value", "val": 2.0e6,  "tol": 1.0},
                {"col": "v_doble_4_",  "type": "final_value", "val": 8.0e6,  "tol": 1.0},
            ],
            "interpretation": (
                "Magnitudes grandes: el double puede representar exactamente 1e7 y 1e4. "
                "suma_int=1000+2000+3000+4000=10000. alguno_true=TRUE (v_bool[1] y [3]). "
                "Verifica que no hay truncamiento a float ni desbordamiento de entero "
                "cuando los valores son grandes pero dentro del rango representable."
            ),
        },
        {
            "id": "TC-AV-009",
            "title": "Cambio de un elemento en mitad de simulacion",
            "description": "t=0: v_real=[1,1,1,1] → suma=4. t=1: v_real[4]→5 → suma=8, v_doble[4]=10.",
            "t_end": 2.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 1.0, "v_real_2_": 1.0, "v_real_3_": 1.0, "v_real_4_": 1.0,
                "v_int_1_": 0, "v_int_2_": 0, "v_int_3_": 0, "v_int_4_": 0,
                "v_bool_1_": 0, "v_bool_2_": 0, "v_bool_3_": 0, "v_bool_4_": 0,
            },
            "schedule": {"v_real_4_": [(0, 1.0), (1.0, 5.0)]},
            "checks": [
                {"col": "suma_real",  "type": "at_t", "at_t": 0.5, "val": 4.0,  "tol": 1e-9},
                {"col": "suma_real",  "type": "at_t", "at_t": 1.5, "val": 8.0,  "tol": 1e-9},
                {"col": "v_doble_4_", "type": "at_t", "at_t": 0.5, "val": 2.0,  "tol": 1e-9},
                {"col": "v_doble_4_", "type": "at_t", "at_t": 1.5, "val": 10.0, "tol": 1e-9},
            ],
            "interpretation": (
                "Solo v_real[4] cambia de 1.0 a 5.0 en t=1.0. Antes del cambio: suma=4, "
                "v_doble[4]=2. Despues: suma=1+1+1+5=8, v_doble[4]=10. v_doble[1,2,3] "
                "permanecen en 2. Verifica que cada elemento se lee independientemente: "
                "un codegen que lee solo [1] no detectaria el cambio en [4]."
            ),
        },
        {
            "id": "TC-AV-010",
            "title": "Independencia de los 4 elementos — sin escrituras cruzadas",
            "description": "Simulacion con distintos valores en todos los elementos: cada doble refleja su propio real.",
            "t_end": 1.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {
                "v_real_1_": 10.0, "v_real_2_": 20.0, "v_real_3_": 30.0, "v_real_4_": 40.0,
                "v_int_1_": 1, "v_int_2_": 2, "v_int_3_": 3, "v_int_4_": 4,
                "v_bool_1_": 1, "v_bool_2_": 0, "v_bool_3_": 0, "v_bool_4_": 0,
            },
            "checks": [
                {"col": "suma_real",   "type": "always", "op": "==", "val": 100.0},
                {"col": "suma_int",    "type": "final_value", "val": 10,   "tol": 0},
                {"col": "alguno_true", "type": "always", "op": "==", "val": 1},
                {"col": "v_doble_1_",  "type": "always", "op": "==", "val": 20.0},
                {"col": "v_doble_2_",  "type": "always", "op": "==", "val": 40.0},
                {"col": "v_doble_3_",  "type": "always", "op": "==", "val": 60.0},
                {"col": "v_doble_4_",  "type": "always", "op": "==", "val": 80.0},
            ],
            "interpretation": (
                "VERIFICACION DE INDEPENDENCIA COMPLETA. Entradas [10,20,30,40] producen "
                "dobles [20,40,60,80] exactamente. suma_real=100 en todos los pasos. "
                "Si cualquier v_doble difiere de su valor esperado, hay una escritura "
                "cruzada entre elementos del array. Este test cubre los 4 elementos "
                "de v_doble simultaneamente con valores que los hacen distinguibles entre si."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
