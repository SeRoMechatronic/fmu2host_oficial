#!/usr/bin/env python3
"""Test battery for EtapaSecuenciador — secuenciador de etapas con progreso acotado"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'arrancar': 1, 'parar': 0, 'sensor_confirmacion': 0.8},
    "model_name": "EtapaSecuenciador",
    "t_end_me": 50.0,
    "h_me":     0.01,
    "t_end_cs": 50.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "etapa_actual", "op": ">=", "val": 0.0, "name": "etapa_actual no negativa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "etapa_actual",    "op": ">=", "val": 0.0, "name": "etapa_actual no negativa RK4"},
        {"type": "always", "col": "progreso_etapa",  "op": ">=", "val": 0.0, "name": "progreso no negativo RK4"},
        {"type": "always", "col": "progreso_etapa",  "op": "<=", "val": 1.0, "name": "progreso no mayor que 1 RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "etapa_actual", "op": ">=", "val": 0.0, "name": "etapa_actual no negativa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
