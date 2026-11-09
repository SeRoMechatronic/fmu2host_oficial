#!/usr/bin/env python3
"""Test battery for SuspensionActiva — sistema de suspension activa con fuerza acotada"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'perfil_bache': 0.5, 'velocidad_vehiculo': 0.6},
    "model_name": "SuspensionActiva",
    "t_end_me": 10.0,
    "h_me":     0.01,
    "t_end_cs": 10.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "fuerza_actuador", "op": ">=", "val": -1.0, "name": "fuerza acotada inferior Euler"},
        {"type": "always", "col": "fuerza_actuador", "op": "<=",  "val":  1.0, "name": "fuerza acotada superior Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "fuerza_actuador", "op": ">=", "val": -1.0, "name": "fuerza acotada inferior RK4"},
        {"type": "always", "col": "fuerza_actuador", "op": "<=",  "val":  1.0, "name": "fuerza acotada [-1,1]"},
    ],
    "checks_cs": [
        {"type": "always", "col": "fuerza_actuador", "op": ">=", "val": -1.0, "name": "fuerza acotada inferior CS"},
        {"type": "always", "col": "fuerza_actuador", "op": "<=",  "val":  1.0, "name": "fuerza acotada superior CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
