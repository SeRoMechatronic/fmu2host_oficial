#!/usr/bin/env python3
"""Test battery for MultiplexorCanales — multiplexor de canales de senal"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'canal_seleccion': 0, 'canal_0': 0.5, 'canal_1': 0.75, 'canal_2': 0.25, 'canal_3': 1.0},
    "model_name": "MultiplexorCanales",
    "t_end_me": 1.0,
    "h_me":     0.5,
    "t_end_cs": 1.0,
    "h_cs":     0.5,
    "checks_me_euler": [
        {"type": "final_t", "t_end": 1.0, "name": "simulacion completa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "final_t", "t_end": 1.0, "name": "simulacion completa RK4"},
    ],
    "checks_cs": [
        {"type": "final_t", "t_end": 1.0, "name": "simulacion completa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
