#!/usr/bin/env python3
"""Test battery completa — ReguladorBateria (7 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "ReguladorBateria",
    "tests": [
        {
            "id": "TC-RB-001",
            "title": "Cargador desconectado — sin corriente",
            "description": "Con carga_conectada=false: corriente=0, cargando=false.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tension_bateria": 0.50, "carga_conectada": 0},
            "checks": [
                {"col": "corriente_carga",     "type": "always", "op": "==", "val": 0.0},
                {"col": "cargando",            "type": "always", "op": "==", "val": 0},
                {"col": "carga_completa",      "type": "final_value", "val": 0, "tol": 0},
                {"col": "fallo_sobretension",  "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Sin conexion del cargador, no debe fluir corriente de carga. "
                "La tension de la bateria es monitoreada pero el regulador no actua. "
                "Este estado representa la bateria en uso (sin carga conectada)."
            ),
        },
        {
            "id": "TC-RB-002",
            "title": "Cargador conectado — bateria baja, demanda inicial",
            "description": "Con tension=0.30 y carga=true: cargando=true, corriente crece.",
            "t_end": 2.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tension_bateria": 0.30, "carga_conectada": 1},
            "checks": [
                {"col": "cargando",       "type": "final_value", "val": 1, "tol": 0},
                {"col": "corriente_carga","type": "eventually", "op": ">", "val": 0.1,
                 "description": "La corriente debe crecer por encima de 0.1"},
                {"col": "fallo_sobretension", "type": "always", "op": "==", "val": 0},
            ],
            "interpretation": (
                "Con bateria al 30% (muy por debajo de V_nominal=0.75), el regulador "
                "activa la carga. La corriente crece desde 0 (estados iniciales nulos) "
                "segun la dinamica del controlador de segundo orden. cargando=true "
                "y no hay fallo de sobretension."
            ),
        },
        {
            "id": "TC-RB-003",
            "title": "Tension alta — fallo sobretension prevalece sobre carga_completa",
            "description": "tension=0.98 > V_max=0.95: fallo_sobretension=true, cargando=false. carga_completa no alcanza (V_carga_completa=0.98 > V_max=0.95 por diseno del modelo).",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"tension_bateria": 0.98, "carga_conectada": 1},
            "checks": [
                {"col": "fallo_sobretension", "type": "final_value", "val": 1, "tol": 0,
                 "description": "0.98 > V_max=0.95 activa la proteccion de sobretension"},
                {"col": "cargando",           "type": "final_value", "val": 0, "tol": 0,
                 "description": "La carga se detiene ante el fallo de sobretension"},
            ],
            "interpretation": (
                "El modelo tiene V_max=0.95 < V_carga_completa=0.98, por lo que "
                "cualquier tension >= V_carga_completa tambien supera V_max y "
                "activa fallo_sobretension. Con tension=0.98: la proteccion de "
                "sobretension se activa (0.98 > 0.95) y cargando=false. "
                "En este diseno, la 'bateria llena' siempre co-ocurre con el fallo "
                "de sobretension por los parametros del modelo."
            ),
        },
        {
            "id": "TC-RB-004",
            "title": "Fallo de sobretension",
            "description": "Con tension=0.96 (>V_max=0.95): fallo_sobretension=true.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"tension_bateria": 0.96, "carga_conectada": 1},
            "checks": [
                {"col": "fallo_sobretension", "type": "final_value", "val": 1, "tol": 0},
                {"col": "cargando",           "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Con tension=0.96 > V_max=0.95, se activa la proteccion de sobretension. "
                "El cargador se desconecta (cargando=false) para evitar dano. "
                "Este mecanismo protege la bateria de sobrecargas que podrian "
                "reducir su vida util o provocar fallos termicos."
            ),
        },
        {
            "id": "TC-RB-005",
            "title": "Limite exacto de sobretension — sin fallo",
            "description": "tension=0.95 (exactamente V_max): fallo_sobretension=false.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"tension_bateria": 0.95, "carga_conectada": 1},
            "checks": [
                {"col": "fallo_sobretension", "type": "final_value", "val": 0, "tol": 0},
                {"col": "cargando",           "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "El umbral de sobretension usa operador estricto >. Con tension=0.95 "
                "exacto, 0.95 NO > 0.95, por lo que no hay fallo. cargando=true porque "
                "la tension esta por debajo del umbral de carga completa (0.98). "
                "Verifica la boundary condition critica del sistema de proteccion."
            ),
        },
        {
            "id": "TC-RB-006",
            "title": "Punto de operacion nominal — tension=V_nominal",
            "description": "Con tension=0.75 (V_nominal): error=0, sin demanda inicial.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"tension_bateria": 0.75, "carga_conectada": 1},
            "checks": [
                {"col": "corriente_carga",    "type": "final_value", "val": 0.0, "tol": 0.05},
                {"col": "cargando",           "type": "final_value", "val": 1,   "tol": 0},
                {"col": "fallo_sobretension", "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Con tension exactamente en V_nominal=0.75, el error de voltaje es "
                "cero. Con estados x1=x2=0 inicialmente, la corriente de carga es 0. "
                "El sistema esta en su punto de operacion nominal: listo para cargar "
                "pero sin demanda activa."
            ),
        },
        {
            "id": "TC-RB-007",
            "title": "Anti-windup — desconexion y reconexion sin pico de corriente",
            "description": "Tras carga prolongada, desconexion y reconexion: corriente acotada.",
            "t_end": 8.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"tension_bateria": 0.30, "carga_conectada": 1},
            "schedule": {"carga_conectada": [(0, 1), (5.0, 0), (5.1, 1)]},
            "checks": [
                {"col": "corriente_carga", "type": "bounded", "low": 0.0, "high": 1.1},
                {"col": "corriente_carga", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Tras 5 s de carga con bateria baja, los estados internos del "
                "regulador han acumulado energia. Al desconectar (t=5 s) y reconectar "
                "inmediatamente (t=5.1 s), el anti-windup debe evitar un pico de "
                "corriente superior a I_max=1.0. La corriente debe mantenerse en [0,1.1]."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
