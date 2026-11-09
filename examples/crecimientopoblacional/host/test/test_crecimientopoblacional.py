#!/usr/bin/env python3
"""Test battery for CrecimientoPoblacional — modelo logistico de crecimiento poblacional"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {},
    "model_name": "CrecimientoPoblacional",
    "t_end_me": 5.0,
    "h_me":     0.1,
    "t_end_cs": 5.0,
    "h_cs":     0.1,
    "checks_me_euler": [
        {"type": "always", "col": "poblacion", "op": ">", "val": 0.0, "name": "poblacion positiva Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always",  "col": "superpoblacion", "op": "==", "val": 0,    "name": "RK4 no sobrepasa K"},
        {"type": "always",  "col": "poblacion",      "op": ">",  "val": 0.0,  "name": "poblacion siempre positiva"},
        {"type": "at_t",    "col": "poblacion",      "t": 5.0,   "val": 95.0, "tol": 5.0, "name": "poblacion cerca de K en t=5"},
    ],
    "checks_cs": [
        {"type": "always", "col": "poblacion", "op": ">",  "val": 0.0,  "name": "poblacion positiva CS"},
        {"type": "at_t",   "col": "poblacion", "t": 5.0,   "val": 95.0, "tol": 10.0, "name": "poblacion cerca de K en t=5 CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
