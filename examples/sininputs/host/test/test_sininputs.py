#!/usr/bin/env python3
"""Test battery for SinInputs — oscilador subamortiguado sin entradas externas"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "model_name": "SinInputs",
    "t_end_me": 20.0,
    "h_me":     0.01,
    "t_end_cs": 20.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "posicion", "op": ">=", "val": -5.0, "name": "posicion acotada inferior Euler"},
        {"type": "always", "col": "posicion", "op": "<=",  "val":  5.0, "name": "posicion acotada superior Euler"},
    ],
    "checks_me_rk4": [
        {"type": "monotone",     "col": "energia",  "direction": "dec", "name": "energia decreciente (amortiguamiento)"},
        {"type": "sign_changes", "col": "posicion",  "min_changes": 4,   "name": "oscilacion subamortiguada"},
    ],
    "checks_cs": [
        {"type": "always", "col": "energia", "op": ">", "val": 0.0, "name": "energia positiva CS"},
        {"type": "sign_changes", "col": "posicion", "min_changes": 2, "name": "oscilacion detectada en CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
