#!/usr/bin/env python3
"""Test battery for FrenadoABS — sistema de frenado ABS con modulacion de presion"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'velocidad_rueda': 0.9, 'presion_pedal': 0.9},
    "model_name": "FrenadoABS",
    "t_end_me": 20.0,
    "h_me":     0.01,
    "t_end_cs": 20.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "presion_modulada", "op": ">=", "val": 0.0, "name": "presion no negativa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "presion_modulada", "op": ">=", "val": 0.0, "name": "presion no negativa RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "presion_modulada", "op": ">=", "val": 0.0, "name": "presion no negativa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
