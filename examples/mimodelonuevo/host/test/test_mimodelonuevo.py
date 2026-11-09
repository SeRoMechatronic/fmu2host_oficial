#!/usr/bin/env python3
"""Test battery for Mi_Modelo_Nuevo — modelo generico con salida filtrada"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))
from test_utils import run_test_battery

CONFIG = {
    "test_inputs": {'entrada_principal': 1.0, 'flag_activo': 1},
    "model_name": "Mi_Modelo_Nuevo",
    "t_end_me": 5.0,
    "h_me":     0.01,
    "t_end_cs": 5.0,
    "h_cs":     0.01,
    "checks_me_euler": [
        {"type": "always", "col": "salida_filtrada", "op": ">=", "val": 0.0, "name": "salida_filtrada no negativa Euler"},
    ],
    "checks_me_rk4": [
        {"type": "always", "col": "salida_filtrada", "op": ">=", "val": 0.0, "name": "salida_filtrada no negativa RK4"},
    ],
    "checks_cs": [
        {"type": "always", "col": "salida_filtrada", "op": ">=", "val": 0.0, "name": "salida_filtrada no negativa CS"},
    ],
}

if __name__ == "__main__":
    sys.exit(run_test_battery(__file__, CONFIG))
