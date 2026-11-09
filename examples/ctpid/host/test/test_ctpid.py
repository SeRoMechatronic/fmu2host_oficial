#!/usr/bin/env python3
"""Test battery for CTPID — controlador PID en tiempo continuo"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'temperatura': 0.2, 'consigna': 0.8},
    "model_name": "CTPID",
    "t_end_me": 10.0,
    "h_me":     0.01,
    "t_end_cs": 10.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "ventilador", "op": ">=", "val": 0.0, "name": "ventilador no negativo Euler"},
        {"type": "always", "col": "ventilador", "op": "<=", "val": 1.0, "name": "ventilador no mayor que 1 Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "ventilador", "op": ">=", "val": 0.0, "name": "ventilador no negativo RK4"},
        {"type": "always", "col": "ventilador", "op": "<=", "val": 1.0, "name": "ventilador no mayor que 1 RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "ventilador", "op": ">=", "val": 0.0, "name": "ventilador no negativo CS"},
        {"type": "always", "col": "ventilador", "op": "<=", "val": 1.0, "name": "ventilador no mayor que 1 CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
