#!/usr/bin/env python3
"""Test battery for CodigoErrorDiagnostico — sistema de codigos de error y diagnostico"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'temperatura': 0.90, 'tension': 0.80, 'vibracion': 0.40},
    "model_name": "CodigoErrorDiagnostico",
    "t_end_me": 1.0,
    "h_me":     0.1,
    "t_end_cs": 1.0,
    "h_cs":     0.1,
    "checks_me_euler": [
        {"type": "always", "col": "nivel_prioridad", "op": ">=", "val": 0.0, "name": "nivel_prioridad no negativo Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "nivel_prioridad", "op": ">=", "val": 3.0, "name": "nivel_prioridad=3 (sobre-temperatura) RK4"},
        {"type": "always", "col": "codigo_error",    "op": "==", "val": 101, "name": "codigo_error=101 (temperatura) RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "nivel_prioridad", "op": ">=", "val": 0.0, "name": "nivel_prioridad no negativo CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
