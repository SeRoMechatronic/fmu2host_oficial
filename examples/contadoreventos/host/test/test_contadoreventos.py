#!/usr/bin/env python3
"""Test battery for ContadorEventos — contador de eventos discretos"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'evento': 1, 'reset': 0},
    "model_name": "ContadorEventos",
    "t_end_me": 1.0,
    "h_me":     0.1,
    "t_end_cs": 1.0,
    "h_cs":     0.1,
    "checks_me_euler": [
        {"type": "always", "col": "cuenta", "op": ">=", "val": 0.0, "name": "cuenta no negativa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "cuenta", "op": ">=", "val": 0.0, "name": "cuenta no negativa RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "cuenta", "op": ">=", "val": 0.0, "name": "cuenta no negativa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
