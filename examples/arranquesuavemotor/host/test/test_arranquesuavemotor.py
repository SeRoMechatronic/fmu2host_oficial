#!/usr/bin/env python3
"""Test battery for ArranqueSuaveMotor — control de arranque suave con rampa de tension"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'orden_arranque': 1, 'carga_motor': 0.5},
    "model_name": "ArranqueSuaveMotor",
    "t_end_me": 12.0,
    "h_me":     0.01,
    "t_end_cs": 12.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "tension_aplicada", "op": ">=", "val": 0.0, "name": "tension no negativa Euler"},
        {"type": "always", "col": "tension_aplicada", "op": "<=", "val": 1.0, "name": "tension no mayor que 1 Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always",     "col": "tension_aplicada", "op": ">=", "val": 0.0, "name": "tension no negativa RK4"},
        {"type": "always",     "col": "tension_aplicada", "op": "<=", "val": 1.0, "name": "tension no excede 1.0 RK4"},
        {"type": "eventually", "col": "tension_aplicada", "op": ">",  "val": 0.5, "name": "rampa supera 50% en t=12s RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "tension_aplicada", "op": ">=", "val": 0.0, "name": "tension no negativa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
