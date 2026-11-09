#!/usr/bin/env python3
"""Test battery for StringInputOutput — modelo con entradas y salidas de tipo string"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'value': 1.0},
    "model_name": "StringInputOutput",
    "t_end_me": 4.0,
    "h_me":     1.0,
    "t_end_cs": 4.0,
    "h_cs":     1.0,
    "checks_me_euler": [
        {"type": "final_t", "t_end": 4.0, "name": "simulacion completa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "final_t", "t_end": 4.0, "name": "simulacion completa RK4"},
    ],
    "checks_cs": [
        {"type": "final_t", "t_end": 4.0, "name": "simulacion completa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
