#!/usr/bin/env python3
"""Test battery for ReguladorBateria — regulador de bateria con corriente de carga"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'tension_bateria': 0.5, 'carga_conectada': 1},
    "model_name": "ReguladorBateria",
    "t_end_me": 5.0,
    "h_me":     0.01,
    "t_end_cs": 5.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "corriente_carga", "op": ">=", "val": 0.0, "name": "corriente_carga no negativa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "corriente_carga", "op": ">=", "val": 0.0, "name": "corriente_carga no negativa RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "corriente_carga", "op": ">=", "val": 0.0, "name": "corriente_carga no negativa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
