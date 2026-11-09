#!/usr/bin/env python3
"""Test battery for OsciladorArmonico — oscilador armonico con conservacion de energia"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "model_name": "OsciladorArmonico",
    "t_end_me": 20.0,
    "h_me":     0.01,
    "t_end_cs": 20.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always",       "col": "energia",  "op": ">",  "val": 0.0, "name": "energia positiva Euler"},
        {"type": "sign_changes", "col": "posicion",  "min_changes": 5,        "name": "oscilacion detectada Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always",       "col": "energia",  "op": ">",   "val": 0.0,    "name": "energia positiva RK4"},
        {"type": "sign_changes", "col": "posicion",  "min_changes": 10,           "name": "oscilacion detectada (RK4)"},
        {"type": "at_t",         "col": "energia",  "t": 20.0,   "val": 19.739, "tol": 0.2, "name": "energia conservada RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "energia", "op": ">", "val": 0.0, "name": "energia positiva CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
