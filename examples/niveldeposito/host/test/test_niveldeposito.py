#!/usr/bin/env python3
"""Test battery for NivelDeposito — control de nivel de deposito con bomba"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'sensor_nivel': 0.8, 'valvula_manual': 0},
    "model_name": "NivelDeposito",
    "t_end_me": 10.0,
    "h_me":     0.01,
    "t_end_cs": 10.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "bomba", "op": ">=", "val": 0.0, "name": "bomba no negativa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "bomba", "op": ">=", "val": 0.0, "name": "bomba no negativa RK4"},
        {"type": "always", "col": "bomba", "op": "<=", "val": 1.0, "name": "bomba no mayor que 1 RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "bomba", "op": ">=", "val": 0.0, "name": "bomba no negativa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
