#!/usr/bin/env python3
"""Test battery for MuchosEstados — sistema con multiples estados que convergen"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'u': 1.0},
    "model_name": "MuchosEstados",
    "t_end_me": 30.0,
    "h_me":     0.01,
    "t_end_cs": 30.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "y1", "op": ">=", "val": 0.0, "name": "y1 no negativo Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "y1", "op": ">=", "val": 0.0,  "name": "y1 no negativo RK4"},
        {"type": "always", "col": "y8", "op": ">=", "val": 0.0,  "name": "y8 no negativo RK4"},
        {"type": "always", "col": "y8", "op": ">=", "val": 0.0, "name": "y8 no negativo RK4 (convergencia)"},
    ],
    "checks_cs": [
        {"type": "always", "col": "y1", "op": ">=", "val": 0.0, "name": "y1 no negativo CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
