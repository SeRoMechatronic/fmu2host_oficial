#!/usr/bin/env python3
"""Test battery for SelectorModo — selector de modo de operacion del actuador"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'modo_operacion': 0, 'consigna_manual': 0.7},
    "model_name": "SelectorModo",
    "t_end_me": 1.0,
    "h_me":     0.5,
    "t_end_cs": 1.0,
    "h_cs":     0.5,
    "checks_me_euler": [
        {"type": "always", "col": "salida_actuador", "op": ">=", "val": 0.0, "name": "salida_actuador no negativa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "salida_actuador", "op": ">=", "val": 0.0, "name": "salida_actuador no negativa RK4"},
        {"type": "always", "col": "salida_actuador", "op": "<=", "val": 1.0, "name": "salida_actuador no mayor que 1 RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "salida_actuador", "op": ">=", "val": 0.0, "name": "salida_actuador no negativa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
