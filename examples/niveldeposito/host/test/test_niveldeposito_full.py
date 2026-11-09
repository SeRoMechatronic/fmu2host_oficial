#!/usr/bin/env python3
"""Test battery completa — NivelDeposito (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "NivelDeposito",
    "tests": [
        {
            "id": "TC-ND-001",
            "title": "Estado estacionario en setpoint — valvula cerrada",
            "description": "nivel_filtrado=0.5 en setpoint: bomba=0.5, sin alarmas.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.50, "valvula_manual": 0},
            "checks": [
                {"col": "bomba",          "type": "final_value", "val": 0.50, "tol": 0.02},
                {"col": "alarma_minimo",  "type": "final_value", "val": 0,    "tol": 0},
                {"col": "alarma_maximo",  "type": "final_value", "val": 0,    "tol": 0},
                {"col": "bomba_activa",   "type": "final_value", "val": 1,    "tol": 0},
            ],
            "interpretation": (
                "Con nivel en el setpoint (0.5=50%), el error es cero y la bomba "
                "opera al 50% de su capacidad (bomba=0.5). Ninguna alarma activa. "
                "bomba_activa=true porque 0.5>0.05. Este es el punto de operacion "
                "nominal del controlador proporcional del deposito."
            ),
        },
        {
            "id": "TC-ND-002",
            "title": "Nivel exactamente en umbral minimo — sin alarma",
            "description": "nivel_filtrado converge a 0.20: alarma_minimo=false (limite exclusivo).",
            "t_end": 20.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.20, "valvula_manual": 0},
            "checks": [
                {"col": "alarma_minimo", "type": "final_value", "val": 0, "tol": 0},
                {"col": "bomba",         "type": "final_value", "val": 1.0,"tol": 0.05},
            ],
            "interpretation": (
                "El umbral minimo usa operador estricto <. Con nivel=0.20 exacto, "
                "la condicion 0.20 < 0.20 es falsa: no hay alarma. La bomba opera "
                "al maximo (error=0.3, bomba=0.5+2*0.3=1.1 → clamped a 1.0). "
                "Boundary condition critica para el sistema de alarmas."
            ),
        },
        {
            "id": "TC-ND-003",
            "title": "Nivel por debajo del umbral minimo — alarma activa",
            "description": "nivel_filtrado converge a 0.199 (cruzando 0.20 desde 0.5): alarma_minimo=true, bomba=1.0.",
            "t_end": 20.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.199, "valvula_manual": 0},
            "checks": [
                {"col": "alarma_minimo", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "bomba",         "type": "final_value", "val": 1.0, "tol": 0.05},
            ],
            "interpretation": (
                "Con nivel=0.199 (justo debajo del umbral 0.20), la alarma minima "
                "se activa. La bomba trabaja al maximo para recuperar el nivel. "
                "Este test verifica el comportamiento del sistema ante un nivel "
                "de liquido peligrosamente bajo."
            ),
        },
        {
            "id": "TC-ND-004",
            "title": "Nivel exactamente en umbral maximo — sin alarma",
            "description": "nivel_filtrado converge a 0.80 (desde 0.5): alarma_maximo=false, bomba=0.",
            "t_end": 20.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.80, "valvula_manual": 0},
            "checks": [
                {"col": "alarma_maximo", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "bomba",         "type": "final_value", "val": 0.0, "tol": 0.05},
            ],
            "interpretation": (
                "El umbral maximo usa operador estricto >. Con nivel=0.80 exacto, "
                "no hay alarma. La bomba se desactiva (error negativo: 0.5-0.8=-0.3, "
                "bomba=0.5+2*(-0.3)=-0.1 → clamped a 0.0). "
                "Simetrico al TC-ND-002 para el limite superior."
            ),
        },
        {
            "id": "TC-ND-005",
            "title": "Nivel por encima del umbral maximo — alarma alta",
            "description": "nivel_filtrado converge a 0.801 (cruzando 0.80 desde 0.5): alarma_maximo=true, bomba=0.",
            "t_end": 20.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.801, "valvula_manual": 0},
            "checks": [
                {"col": "alarma_maximo", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "bomba",         "type": "final_value", "val": 0.0, "tol": 0.05},
            ],
            "interpretation": (
                "Nivel de 0.801 activa la alarma de nivel alto y corta la bomba. "
                "El controlador proporcional reduce la bomba para evitar desbordamiento. "
                "Esta situacion requiere intervencion manual (abrir valvula) o "
                "esperar a que el nivel baje por debrito propio del deposito."
            ),
        },
        {
            "id": "TC-ND-006",
            "title": "Valvula manual abierta — compensacion feedforward",
            "description": "Con valvula=true en setpoint: feedforward reduce la bomba.",
            "t_end": 0.5, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.50, "valvula_manual": 1},
            "checks": [
                {"col": "bomba", "type": "final_value", "val": 0.0, "tol": 0.05},
            ],
            "interpretation": (
                "Al abrir la valvula manual, se activa el termino feedforward "
                "Q_salida/Q_bomba_max=0.3/0.5=0.6. En el setpoint: "
                "bomba=0.5+0-0.6=-0.1 → clamped a 0.0. El feedforward compensa "
                "el caudal de salida, pero en este caso domina y apaga la bomba. "
                "Verifica que fmi2SetBoolean afecta la logica de control."
            ),
        },
        {
            "id": "TC-ND-007",
            "title": "Nivel bajo con valvula abierta — demanda combinada",
            "description": "nivel converge a 0.30, valvula=true: bomba=0.30 (P-control + feedforward) en estado estacionario.",
            "t_end": 20.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.30, "valvula_manual": 1},
            "checks": [
                {"col": "bomba",          "type": "final_value", "val": 0.30, "tol": 0.05},
                {"col": "alarma_minimo",  "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "Con nivel=0.30 (por encima del umbral 0.20) y valvula abierta: "
                "error=0.5-0.3=0.2, bomba=0.5+2*0.2-0.6=0.3. La combinacion de "
                "control proporcional y compensacion feedforward da 0.30. "
                "Este caso ejercita ambos terminos de la ecuacion de control."
            ),
        },
        {
            "id": "TC-ND-008",
            "title": "Deposito vacio — bomba al maximo",
            "description": "nivel converge a 0.0 (cruzando 0.20 desde 0.5): alarma_minimo=true, bomba=1.0.",
            "t_end": 20.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.0, "valvula_manual": 0},
            "checks": [
                {"col": "alarma_minimo", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "bomba",         "type": "final_value", "val": 1.0, "tol": 0.05},
            ],
            "interpretation": (
                "Deposito completamente vacio: nivel=0 (muy por debajo de 0.20). "
                "La alarma minima se activa y la bomba trabaja al maximo para "
                "rellenar el deposito. Este es el escenario de maximo error "
                "del controlador proporcional."
            ),
        },
        {
            "id": "TC-ND-009",
            "title": "Deposito lleno — bomba apagada",
            "description": "nivel converge a 1.0 (cruzando 0.80 desde 0.5): alarma_maximo=true, bomba=0.",
            "t_end": 20.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 1.0, "valvula_manual": 0},
            "checks": [
                {"col": "alarma_maximo", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "bomba",         "type": "final_value", "val": 0.0, "tol": 0.05},
                {"col": "bomba_activa",  "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Deposito completamente lleno: nivel=1.0 (muy por encima de 0.80). "
                "La alarma maxima se activa y la bomba se apaga completamente. "
                "bomba_activa=false porque bomba=0.0<=0.05. Escenario de desbordamiento "
                "potencial que requiere abrir la valvula manual para drenar."
            ),
        },
        {
            "id": "TC-ND-010",
            "title": "Transitorio del filtro — sensor baja de 0.5 a 0.2 en t=2 s",
            "description": "Despues de un escalon del sensor, el nivel filtrado responde con tau=2 s.",
            "t_end": 6.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"sensor_nivel": 0.50, "valvula_manual": 0},
            "schedule": {"sensor_nivel": [(0, 0.50), (2.0, 0.20)]},
            "checks": [
                {"col": "bomba", "type": "at_t", "at_t": 4.0, "val": 0.8, "tol": 0.15},
                {"col": "bomba", "type": "at_t", "at_t": 2.0, "val": 0.5, "tol": 0.05},
            ],
            "interpretation": (
                "Antes del escalon (t=2 s): nivel_filtrado≈0.5, bomba≈0.5. "
                "Despues del escalon, el sensor baja a 0.2 pero el filtro (tau=2 s) "
                "responde gradualmente: a t=4 s (1 tau despues del escalon), "
                "nivel_filtrado ≈ 0.5+(0.2-0.5)*(1-e^-1)≈0.31. bomba aumenta. "
                "Verifica la dinamica del filtro del sensor de nivel."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
