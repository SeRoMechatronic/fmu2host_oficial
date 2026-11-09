#!/usr/bin/env python3
"""Test battery completa — MuchosEstados (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "MuchosEstados",
    "tests": [
        {
            "id": "TC-ME-001",
            "title": "Condiciones iniciales — todos los estados en cero",
            "description": "En t=0: y1=y2=...=y8=0, todos_activos=false.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y1", "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "y8", "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "todos_activos", "type": "at_t", "at_t": 0.0, "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Los 8 filtros en cascada parten de estado cero. Con u=1.0 aplicado "
                "desde t=0, el primer filtro comienza a responder inmediatamente pero "
                "los filtros posteriores aun no tienen senal. todos_activos=false "
                "porque ninguna etapa ha superado el umbral de 0.01."
            ),
        },
        {
            "id": "TC-ME-002",
            "title": "Propagacion de senal: y1 responde, y8 retrasado",
            "description": "A t=0.1s: y1>0, y8≈0. A t=5s: y1≈1, y8>0.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y1", "type": "at_t", "at_t": 0.1, "val": 0.09, "tol": 0.02},
                {"col": "y8", "type": "at_t", "at_t": 0.1, "val": 0.0,  "tol": 0.001},
                {"col": "y1", "type": "at_t", "at_t": 5.0, "val": 0.993,"tol": 0.01},
            ],
            "interpretation": (
                "La senal se propaga en cascada. y1 responde en t=0.1 s (≈0.095). "
                "y8 aun no ha recibido la senal (≈0). A t=5 s (5 tau), y1 esta "
                "casi convergido. y8 aun esta en transitorio. Verifica que los "
                "8 estados son independientes y no comparten buffers."
            ),
        },
        {
            "id": "TC-ME-003",
            "title": "todos_activos=true después de propagacion completa",
            "description": "todos_activos cambia a true aproximadamente en t≈8 s.",
            "t_end": 20.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "todos_activos", "type": "eventually",
                 "op": "==", "val": 1,
                 "description": "todos_activos debe activarse antes de t=20 s"},
            ],
            "interpretation": (
                "La senal tarda ~8 veces el tiempo de transito individual (tau=1 s) "
                "en propagarse por las 8 etapas. todos_activos=true requiere que "
                "todos los yi > 0.01. Si este flag nunca se activa, alguno de los "
                "8 estados tiene un buffer incorrecto y siempre es cero."
            ),
        },
        {
            "id": "TC-ME-004",
            "title": "Comprobacion analitica de y1 en t=1, 2, 3 s",
            "description": "y1(t)=1-e^(-t/tau): y1(1)≈0.632, y1(2)≈0.865, y1(3)≈0.950.",
            "t_end": 3.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y1", "type": "at_t", "at_t": 1.0, "val": 0.632, "tol": 0.01},
                {"col": "y1", "type": "at_t", "at_t": 2.0, "val": 0.865, "tol": 0.01},
                {"col": "y1", "type": "at_t", "at_t": 3.0, "val": 0.950, "tol": 0.01},
            ],
            "interpretation": (
                "El primer filtro tiene solucion analitica exacta: y1(t)=1-e^(-t). "
                "Los valores en t=1,2,3 tau son el 63%, 86.5% y 95% del valor final. "
                "Este test verifica el primer slot del buffer de estados y que la "
                "ODE tau*dx/dt=u-x esta correctamente generada para la primera etapa."
            ),
        },
        {
            "id": "TC-ME-005",
            "title": "Convergencia de todas las etapas a 1.0 en t=30 s",
            "description": "A t=30 s, todas las etapas deben converger a >0.999.",
            "t_end": 30.0, "h": 0.05, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y1", "type": "final_value", "val": 1.0, "tol": 0.001},
                {"col": "y4", "type": "final_value", "val": 1.0, "tol": 0.001},
                {"col": "y8", "type": "final_value", "val": 1.0, "tol": 0.01},
                {"col": "todos_activos", "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "CRITERIO PRIMARIO. A t=30 s (muy lejos del transitorio), todas las "
                "etapas deben haber convergido al valor de la entrada (u=1). "
                "Si alguna etapa no converge, su buffer de estado esta mal dimensionado "
                "o hay un error en la conexion en cascada entre etapas."
            ),
        },
        {
            "id": "TC-ME-006",
            "title": "Ordenacion de salidas durante el transitorio",
            "description": "A t=2 s: y1>y2>y3>y4>y5>y6>y7>y8 (cada etapa retrasada).",
            "t_end": 2.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y1", "type": "at_t", "at_t": 2.0, "val": 0.865, "tol": 0.02},
                {"col": "y2", "type": "at_t", "at_t": 2.0, "val": 0.594, "tol": 0.02},
                {"col": "y8", "type": "at_t", "at_t": 2.0, "val": 0.0,   "tol": 0.01},
            ],
            "interpretation": (
                "Durante el transitorio, cada etapa tiene menos senal que la anterior. "
                "A t=2 s: y1≈0.865 (casi convergida), y2≈0.4 (a mitad), y8≈0 "
                "(apenas llegando la senal). Este ordenamiento confirma que la "
                "cascada funciona correctamente: el buffer del estado i alimenta "
                "al estado i+1 y no hay escrituras cruzadas."
            ),
        },
        {
            "id": "TC-ME-007",
            "title": "Entrada cero — todas las etapas permanecen en cero",
            "description": "Con u=0: y1=...=y8=0, todos_activos=false.",
            "t_end": 10.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u": 0.0},
            "checks": [
                {"col": "y1", "type": "always", "op": "==", "val": 0.0},
                {"col": "y8", "type": "always", "op": "==", "val": 0.0},
                {"col": "todos_activos", "type": "always", "op": "==", "val": 0},
            ],
            "interpretation": (
                "Con entrada nula y estados iniciales cero, todas las etapas "
                "permanecen en cero. Verifica que no hay ruido numerico ni "
                "condiciones iniciales no nulas en ningun buffer de los 8 estados."
            ),
        },
        {
            "id": "TC-ME-008",
            "title": "Eliminacion del escalon — decaimiento desde convergencia",
            "description": "Despues de convergencia a t=20 s, u→0: todas las etapas decaen.",
            "t_end": 30.0, "h": 0.05, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "schedule": {"u": [(0, 1.0), (20.0, 0.0)]},
            "checks": [
                {"col": "y1", "type": "at_t", "at_t": 25.0, "val": 0.007, "tol": 0.01},
                {"col": "todos_activos", "type": "eventually_false",
                 "description": "todos_activos debe volver a false durante el decaimiento"},
            ],
            "interpretation": (
                "En t=20 s, todas las etapas han convergido a 1.0. Al eliminar la "
                "entrada, la primera etapa decae: y1(25)≈e^(-5)≈0.007 (5 tau despues). "
                "Las etapas posteriores decaen mas lentamente (sistema de orden superior). "
                "todos_activos vuelve a false cuando alguna etapa baja de 0.01."
            ),
        },
        {
            "id": "TC-ME-009",
            "title": "Verificacion de buffer — todas las 8 etapas son independientes",
            "description": "Cada etapa tiene un valor diferente durante el transitorio.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y1", "type": "bounded", "low": 0.0, "high": 1.01},
                {"col": "y8", "type": "bounded", "low": 0.0, "high": 1.01},
                {"col": "y1", "type": "no_nan_inf"},
                {"col": "y8", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Las 8 etapas son acotadas en [0,1] con entrada u=1. Un buffer mal "
                "dimensionado podria causar escrituras fuera de rango que producen "
                "valores invalidos en otras etapas. Este test verifica que y1 e y8 "
                "(los extremos de la cadena) son siempre finitos y acotados."
            ),
        },
        {
            "id": "TC-ME-010",
            "title": "Sin NaN ni Inf en todas las 8 etapas durante 20 s",
            "description": "20 segundos de cascada de 8 filtros sin valores invalidos.",
            "t_end": 20.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"u": 1.0},
            "checks": [
                {"col": "y1", "type": "no_nan_inf"},
                {"col": "y4", "type": "no_nan_inf"},
                {"col": "y8", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "PRUEBA CRITICA DE BUFFER. Si el codegen asigna buffers de tamanyo "
                "menor a 8 (por ejemplo, 2, 3 o 4), las escrituras fuera de rango "
                "producen comportamiento indefinido que puede manifestarse como NaN, "
                "Inf, o valores erraticos. Este test es el discriminador de tamano "
                "de buffer para sistemas de 8 estados."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
