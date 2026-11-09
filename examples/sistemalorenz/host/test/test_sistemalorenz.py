#!/usr/bin/env python3
"""Test battery for SistemaLorenz — sistema caotico de Lorenz con deteccion de atractor"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "model_name": "SistemaLorenz",
    "t_end_me": 30.0,
    "h_me":     0.01,
    "t_end_cs": 30.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "z_out", "op": ">",    "val": 0.0,  "name": "z positivo Euler"},
        {"type": "always", "col": "x_out", "op": "abs<", "val": 35.0, "name": "x acotado Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always",       "col": "on_attractor", "op": "==", "val": 1,   "name": "siempre en el atractor"},
        {"type": "always",       "col": "z_out",        "op": ">",  "val": 0.0, "name": "z siempre positivo"},
        {"type": "always",       "col": "x_out",        "op": "abs<", "val": 25.0, "name": "x acotado abs<25"},
        {"type": "sign_changes", "col": "x_out",        "min_changes": 8,          "name": "oscilacion caotica en x"},
    ],
    "checks_cs": [
        {"type": "always", "col": "on_attractor", "op": "==", "val": 1,   "name": "siempre en el atractor CS"},
        {"type": "always", "col": "z_out",        "op": ">",  "val": 0.0, "name": "z positivo CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
