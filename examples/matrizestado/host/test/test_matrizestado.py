#!/usr/bin/env python3
"""Test battery for MatrizEstado — sistema de espacio de estado con traza conservada"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "model_name": "MatrizEstado",
    "t_end_me": 2.0,
    "h_me":     0.01,
    "t_end_cs": 2.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "traza", "op": ">=", "val": 5.0, "name": "traza conservada Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "traza", "op": ">=", "val": 5.9, "name": "traza conservada (aprox 6)"},
        {"type": "at_t",   "col": "traza", "t": 1.0,   "val": 6.0, "tol": 0.01, "name": "traza exacta en t=1"},
    ],
    "checks_cs": [
        {"type": "always", "col": "traza", "op": ">=", "val": 5.0, "name": "traza conservada CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
