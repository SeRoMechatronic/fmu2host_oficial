#!/usr/bin/env python3
"""Test battery for CuerposAcoplados — sistema mecanico de cuerpos acoplados con conservacion de energia"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'fuerza_externa': 1.0},
    "model_name": "CuerposAcoplados",
    "t_end_me": 20.0,
    "h_me":     0.05,
    "t_end_cs": 20.0,
    "h_cs":     0.05,
    "checks_me_euler": [
        {"type": "always", "col": "energia_total", "op": ">", "val": 0.0, "name": "energia total positiva Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "energia_total", "op": ">",   "val": 0.0,   "name": "energia total positiva RK4"},
        {"type": "at_t",   "col": "energia_total", "t": 0.0,    "val": 3.625, "tol": 0.1, "name": "energia inicial correcta"},
    ],
    "checks_cs": [
        {"type": "always", "col": "energia_total", "op": ">", "val": 0.0, "name": "energia total positiva CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
