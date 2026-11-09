#!/usr/bin/env python3
"""Test battery for PenduloNoLineal — pendulo no lineal con angulo acotado"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "model_name": "PenduloNoLineal",
    "t_end_me": 10.0,
    "h_me":     0.05,
    "t_end_cs": 10.0,
    "h_cs":     0.05,
    "checks_me_euler": [
        {"type": "always", "col": "energia_total", "op": ">", "val": 0.0, "name": "energia total positiva Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "energia_total", "op": ">",    "val": 0.0, "name": "energia total positiva RK4"},
        {"type": "always", "col": "angulo",         "op": "abs<", "val": 3.2, "name": "angulo acotado"},
    ],
    "checks_cs": [
        {"type": "always", "col": "energia_total", "op": ">", "val": 0.0, "name": "energia total positiva CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
