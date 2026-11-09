#!/usr/bin/env python3
"""Test battery for CSPuro_SinME — modelo de co-simulacion pura sin Model Exchange"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'u1': 1.0, 'u2': 0.5},
    "model_name": "CSPuro_SinME",
    "t_end_me": 1.0,
    "h_me":     0.1,
    "t_end_cs": 1.0,
    "h_cs":     0.1,
    "checks_me_euler": [],
    "checks_me_rk4": [],
    "checks_cs": [
        {"type": "final_t", "t_end": 1.0, "name": "simulacion completa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
