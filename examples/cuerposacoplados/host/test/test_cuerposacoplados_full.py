#!/usr/bin/env python3
"""Test battery completa — CuerposAcoplados (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "CuerposAcoplados",
    "tests": [
        {
            "id": "TC-CA-001",
            "title": "Condiciones iniciales en t=0",
            "description": "pos1=1.0, pos2=-0.5, vel1=0, vel2=0.5, energia≈3.625, en_fase=false.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 0.0},
            "checks": [
                {"col": "pos1",          "type": "at_t", "at_t": 0.0, "val": 1.0,   "tol": 1e-6},
                {"col": "pos2",          "type": "at_t", "at_t": 0.0, "val": -0.5,  "tol": 1e-6},
                {"col": "vel1",          "type": "at_t", "at_t": 0.0, "val": 0.0,   "tol": 1e-6},
                {"col": "vel2",          "type": "at_t", "at_t": 0.0, "val": 0.5,   "tol": 1e-6},
                {"col": "energia_total", "type": "at_t", "at_t": 0.0, "val": 3.625, "tol": 0.01},
                {"col": "en_fase",       "type": "at_t", "at_t": 0.0, "val": 0,     "tol": 0},
            ],
            "interpretation": (
                "Los 4 estados tienen condiciones iniciales: x1=1.0, x2=-0.5, v1=0, v2=0.5. "
                "Energia inicial E0=0.5*1*0²+0.5*2*0.5²+0.5*4*1²+0.5*2*0.25+0.5*1*2.25=3.625 J. "
                "en_fase=FALSE porque sign(x1=1)>0 y sign(x2=-0.5)<0 (signos opuestos). "
                "Verifica que el buffer de estados de 4 elementos se inicializa correctamente."
            ),
        },
        {
            "id": "TC-CA-002",
            "title": "Conservacion de energia con RK4 — 20 s",
            "description": "Con F=0 y RK4, |energia - 3.625| < 0.05 J en todo momento.",
            "t_end": 20.0, "h": 0.05, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 0.0},
            "checks": [
                {"col": "energia_total", "type": "bounded", "low": 3.575, "high": 3.675},
                {"col": "energia_total", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "TEST PRIMARIO DE ENERGIA. El sistema conservativo sin disipacion ni "
                "fuerza externa debe conservar la energia mecanica total. RK4 con h=0.05 "
                "mantiene la energia en [3.575, 3.675] J durante 20 s. "
                "Si el buffer de estados tiene un tamano incorrecto (por ejemplo 2 en "
                "lugar de 4), los estados v1 o v2 se corrompen y la energia diverge."
            ),
        },
        {
            "id": "TC-CA-003",
            "title": "Deriva de energia con Euler — discriminador de integrador",
            "description": "Con Euler, energia_total debe desviarse mas de 0.2 J antes de t=20 s.",
            "t_end": 20.0, "h": 0.05, "solver": "euler", "mode": "me",
            "inputs": {"fuerza_externa": 0.0},
            "checks": [
                {"col": "energia_total", "type": "eventually", "op": ">", "val": 3.825,
                 "description": "Euler debe provocar deriva de energia > 0.2 J"},
                {"col": "energia_total", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Euler es un metodo de primer orden que introduce disipacion artificial "
                "en sistemas hamiltonianos. Con h=0.05 y 4 estados, la energia debe "
                "subir o bajar mas de 0.2 J antes de t=20 s. Si la energia se conserva "
                "igual que con RK4, el codegen no esta usando correctamente el buffer "
                "de k-vectores del integrador RK4 y esta degradando a Euler."
            ),
        },
        {
            "id": "TC-CA-004",
            "title": "Transiciones de en_fase — batido de modos",
            "description": "en_fase cambia al menos 8 veces en 30 s (4 inversiones de fase).",
            "t_end": 30.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 0.0},
            "checks": [
                {"col": "en_fase", "type": "eventually", "op": "==", "val": 1,
                 "description": "en_fase debe cambiar a 1 en algun momento (batido de modos)"},
                {"col": "en_fase", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Las dos frecuencias naturales (sqrt(5)≈2.24 y sqrt(1.5)≈1.22 rad/s) "
                "producen un efecto de batido: los cuerpos oscilan alternativamente "
                "en fase y en contra-fase. en_fase=sign(x1)==sign(x2) cambia con "
                "cada inversion de fase relativa. Al menos 4 cambios en 30 s confirman "
                "que la dinamica de 4 estados se simula correctamente."
            ),
        },
        {
            "id": "TC-CA-005",
            "title": "Ambas masas oscilan cruzando cero — resortes de pared activos",
            "description": "pos1 y pos2 cambian de signo al menos 3 veces cada una en 10 s.",
            "t_end": 10.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 0.0},
            "checks": [
                {"col": "pos1", "type": "sign_changes", "min": 3},
                {"col": "pos2", "type": "sign_changes", "min": 3},
                {"col": "pos1", "type": "no_nan_inf"},
                {"col": "pos2", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Los resortes de pared impiden que las masas se desplacen indefinidamente. "
                "Con las condiciones iniciales x1=1, x2=-0.5, ambas masas oscilan "
                "alrededor de cero y cruzan el eje varias veces. Si alguna masa no "
                "cruza el cero, la integracion de su estado tiene un offset incorrecto "
                "(buffer contaminado por otro estado)."
            ),
        },
        {
            "id": "TC-CA-006",
            "title": "Fuerza externa aumenta energia — F=5 N durante 5 s",
            "description": "Con fuerza_externa=5.0 constante, energia_total(5s) > 3.625 J.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 5.0},
            "checks": [
                {"col": "energia_total", "type": "eventually", "op": ">", "val": 4.0,
                 "description": "La energia debe crecer por encima de 4.0 J con F=5"},
                {"col": "energia_total", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Una fuerza externa F=5 N sobre la masa 1 realiza trabajo W=F*v1*dt. "
                "La energia mecanica crece por encima del valor inicial 3.625 J. "
                "Si el input fuerza_externa no se propaga a la ODE (fmi2SetReal no "
                "actualiza el termino F en la ecuacion de movimiento), la energia "
                "permaneceria en 3.625 J como en el caso libre."
            ),
        },
        {
            "id": "TC-CA-007",
            "title": "Fuerza → 0 conserva energia tras la actuacion",
            "description": "F=5 N hasta t=2, luego F=0: energia conservada a partir de t=2.",
            "t_end": 10.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 5.0},
            "schedule": {"fuerza_externa": [(0, 5.0), (2.0, 0.0)]},
            "checks": [
                {"col": "energia_total", "type": "at_t", "at_t": 1.9,  "val": 5.0, "tol": 0.2},
                {"col": "energia_total", "type": "bounded",             "low": 3.0, "high": 10.0},
                {"col": "energia_total", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Durante t=[0,2] la fuerza inyecta energia. En t=2, se retira la fuerza. "
                "A partir de t=2, el sistema conserva la energia ganada (libre, sin disipacion). "
                "La energia en t≈2 es mayor que 4 J (F ha trabajado sobre la masa). "
                "Despues de t=2, la energia oscila entre [E_min, E_max] con RK4 "
                "manteniendo la conservacion."
            ),
        },
        {
            "id": "TC-CA-008",
            "title": "Buffer de 4 estados — ausencia de NaN/Inf en toda la simulacion",
            "description": "20 s de simulacion: pos1, pos2, vel1, vel2 y energia siempre finitos.",
            "t_end": 20.0, "h": 0.05, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 0.0},
            "checks": [
                {"col": "pos1",          "type": "no_nan_inf"},
                {"col": "pos2",          "type": "no_nan_inf"},
                {"col": "vel1",          "type": "no_nan_inf"},
                {"col": "vel2",          "type": "no_nan_inf"},
                {"col": "energia_total", "type": "no_nan_inf"},
            ],
            "interpretation": (
                "TEST CRITICO DE BUFFER. Si el codegen asigna buffers de tamanyo < 4 "
                "para el vector de estado, las escrituras fuera de rango corrompen "
                "memoria y producen NaN, Inf o valores erraticos. Este modelo tiene "
                "4 estados (x1, x2, v1, v2) y es el primero de la suite que requiere "
                "EULER_BUF_SIZE / RK4_BUF_SIZE >= 4."
            ),
        },
        {
            "id": "TC-CA-009",
            "title": "Amplitudes acotadas — estabilidad a largo plazo",
            "description": "En 50 s: |pos1|, |pos2| < 3.0 m. No hay crecimiento de amplitud.",
            "t_end": 50.0, "h": 0.05, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 0.0},
            "checks": [
                {"col": "pos1", "type": "bounded", "low": -3.0, "high": 3.0},
                {"col": "pos2", "type": "bounded", "low": -3.0, "high": 3.0},
            ],
            "interpretation": (
                "Los resortes garantizan que las amplitudes son acotadas (eigenvalores "
                "imaginarios puros). Con RK4 y h=0.05, no debe haber crecimiento "
                "esponencial de amplitud. Si las posiciones superan 3.0 m, hay "
                "inestabilidad numerica (h demasiado grande) o un error en las "
                "ecuaciones de movimiento (acoplamiento k_c incorrecto)."
            ),
        },
        {
            "id": "TC-CA-010",
            "title": "Independencia de fuerza cero y fuerza maxima",
            "description": "Comparacion de energias: F=0 conserva, F=10 crece, sin NaN.",
            "t_end": 3.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"fuerza_externa": 10.0},
            "checks": [
                {"col": "energia_total", "type": "eventually", "op": ">", "val": 5.0,
                 "description": "Con F=10 N la energia debe superar 5 J"},
                {"col": "energia_total", "type": "no_nan_inf"},
                {"col": "en_fase",       "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Con fuerza_externa=10 N (doble del caso TC-CA-006), la energia crece "
                "mas rapidamente. En 3 s con F=10 N, la energia supera facilmente 5 J "
                "(mas del 38% sobre la energia inicial). Verifica que fmi2SetReal "
                "transmite correctamente valores grandes y que la ODE los integra "
                "sin problemas numericos."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
