#!/usr/bin/env python3
"""Test battery completa — EtapaSecuenciador (12 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "EtapaSecuenciador",
    "tests": [
        {
            "id": "TC-ES-001",
            "title": "Estado idle inicial",
            "description": "Sin arrancar: etapa_actual=0, progreso=0, secuencia_completa=false.",
            "t_end": 1.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "checks": [
                {"col": "etapa_actual",      "type": "at_t", "at_t": 0.0, "val": 0,   "tol": 0},
                {"col": "progreso_etapa",    "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "secuencia_completa","type": "always", "op": "==", "val": 0},
            ],
            "interpretation": (
                "Estado inicial: etapa=0 (idle), temporizador=0. Sin flanco ascendente "
                "en arrancar, el secuenciador no entra en ninguna etapa. "
                "progreso=temporizador/duracion=0/10=0. secuencia_completa=FALSE "
                "siempre. Verifica que el estado discreto se inicializa en idle."
            ),
        },
        {
            "id": "TC-ES-002",
            "title": "Comando de arranque — entra en etapa 1",
            "description": "Flanco ascendente en arrancar: etapa_actual pasa a 1.",
            "t_end": 3.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "schedule": {"arrancar": [(0, 0), (0.5, 1), (1.0, 0)]},
            "checks": [
                {"col": "etapa_actual", "type": "at_t", "at_t": 0.3,  "val": 0, "tol": 0},
                {"col": "etapa_actual", "type": "eventually", "op": "==", "val": 1,
                 "description": "etapa_actual debe llegar a 1 tras el flanco de arrancar"},
            ],
            "interpretation": (
                "En t=0: etapa=0 (idle). Flanco ascendente de arrancar en t=0.5. "
                "La secuencia entra en etapa=1 (primera etapa activa). El temporizador "
                "comienza en 0. Verifica que edge(arrancar) with etapa==0 es la "
                "condicion correcta para iniciar la secuencia."
            ),
        },
        {
            "id": "TC-ES-003",
            "title": "Progreso dentro de la etapa 1 en t=5 s",
            "description": "Tras arrancar, a t=5s: etapa_actual=1, progreso≈0.50.",
            "t_end": 7.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "schedule": {"arrancar": [(0, 0), (0.1, 1), (0.2, 0)]},
            "checks": [
                {"col": "etapa_actual",   "type": "at_t", "at_t": 5.1, "val": 1,   "tol": 0},
                {"col": "progreso_etapa", "type": "at_t", "at_t": 5.1, "val": 0.50, "tol": 0.05},
                {"col": "secuencia_completa", "type": "at_t", "at_t": 5.1, "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Tras el flanco de arrancar (t≈0.1), la secuencia entra en etapa=1. "
                "El temporizador crece a razon de 1 s/s. En t≈5.1 s (5 s despues): "
                "temporizador≈5.0, progreso=min(1.0, 5/10)=0.50. La etapa no avanza "
                "hasta que temporizador>=10 Y sensor>0.5."
            ),
        },
        {
            "id": "TC-ES-004",
            "title": "Avance de etapa — etapa 1→2 tras 10 s con sensor confirmado",
            "description": "Despues de 10 s en etapa 1 con sensor=0.8: etapa pasa a 2.",
            "t_end": 13.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "schedule": {"arrancar": [(0, 0), (0.1, 1), (0.2, 0)]},
            "checks": [
                {"col": "etapa_actual", "type": "at_t", "at_t": 12.0, "val": 2, "tol": 0},
                {"col": "etapa_previa", "type": "at_t", "at_t": 12.0, "val": 1, "tol": 0},
            ],
            "interpretation": (
                "Tras ~10 s en etapa=1 con sensor_confirmacion=0.8>0.5, la condicion "
                "de avance se cumple: temporizador>=10 AND sensor>0.5. El secuenciador "
                "pasa a etapa=2 y resetea el temporizador. etapa_previa=1 registra "
                "la etapa anterior. Verifica la logica de avance de estado."
            ),
        },
        {
            "id": "TC-ES-005",
            "title": "Sin avance sin confirmacion del sensor",
            "description": "Con sensor=0.4 (< 0.5): la etapa no avanza aunque hayan pasado 10 s.",
            "t_end": 15.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.4},
            "schedule": {"arrancar": [(0, 0), (0.1, 1), (0.2, 0)]},
            "checks": [
                {"col": "etapa_actual",   "type": "at_t", "at_t": 12.0, "val": 1,   "tol": 0},
                {"col": "progreso_etapa", "type": "at_t", "at_t": 12.0, "val": 1.0, "tol": 0.01},
            ],
            "interpretation": (
                "Con sensor=0.4 <= 0.5, la condicion de avance requiere sensor>0.5 "
                "(estricto) que no se cumple. Aunque han transcurrido >10 s (mas de "
                "duracion_etapa), la etapa permanece en 1. progreso=min(1.0,>1.0)=1.0 "
                "(clamped). Verifica que el sensor es una condicion AND necesaria "
                "para el avance, no opcional."
            ),
        },
        {
            "id": "TC-ES-006",
            "title": "Sensor exactamente en el umbral — sin avance (operador estricto)",
            "description": "sensor=0.5 exacto: NO avanza (> es estricto, 0.5 no > 0.5).",
            "t_end": 15.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.5},
            "schedule": {"arrancar": [(0, 0), (0.1, 1), (0.2, 0)]},
            "checks": [
                {"col": "etapa_actual", "type": "at_t", "at_t": 13.0, "val": 1, "tol": 0},
            ],
            "interpretation": (
                "sensor_confirmacion=0.5 exacto. La condicion de avance es 'sensor > 0.5' "
                "con operador estricto. 0.5 NO es mayor que 0.5, por lo que el "
                "secuenciador NO avanza aunque hayan pasado mas de 10 s. "
                "Si la condicion fuera >=, habria avance. Verifica la frontera critica "
                "del umbral de confirmacion."
            ),
        },
        {
            "id": "TC-ES-007",
            "title": "Parada durante secuencia — vuelta inmediata a idle",
            "description": "Flanco en parar durante etapa 3: etapa_actual=0 inmediatamente.",
            "t_end": 35.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "schedule": {
                "arrancar": [(0, 0), (0.1, 1), (0.2, 0)],
                "parar":    [(0, 0), (25.0, 1), (25.5, 0)],
            },
            "checks": [
                {"col": "etapa_actual", "type": "at_t", "at_t": 24.0, "val": 3, "tol": 0},
                {"col": "etapa_actual", "type": "at_t", "at_t": 25.5, "val": 0, "tol": 0},
            ],
            "interpretation": (
                "En t≈24s la secuencia esta en etapa=3 (0→1→2→3, cada una 10s). "
                "Flanco ascendente en parar a t=25: el secuenciador vuelve a etapa=0 "
                "inmediatamente, reseteando temporizador. Verifica que el reset "
                "de parada tiene prioridad y que edge(parar) funciona desde cualquier "
                "etapa activa (no solo desde idle)."
            ),
        },
        {
            "id": "TC-ES-008",
            "title": "Arrancar ignorado si ya en ejecucion",
            "description": "Flanco de arrancar mientras en etapa 2: etapa_actual permanece en 2.",
            "t_end": 25.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "schedule": {
                "arrancar": [(0, 0), (0.1, 1), (0.2, 0), (13.0, 1), (13.5, 0)],
            },
            "checks": [
                {"col": "etapa_actual", "type": "at_t", "at_t": 12.5, "val": 2, "tol": 0},
                {"col": "etapa_actual", "type": "at_t", "at_t": 14.0, "val": 2, "tol": 0},
            ],
            "interpretation": (
                "En t≈12.5 la secuencia esta en etapa=2. Segundo flanco de arrancar "
                "en t=13: como la condicion es 'when edge(arrancar) and etapa==0', "
                "el flanco se ignora porque etapa!=0. La secuencia permanece en etapa=2 "
                "sin reiniciarse. Verifica la condicion de guarda del arranque."
            ),
        },
        {
            "id": "TC-ES-009",
            "title": "Secuencia completa — secuencia_completa=true al finalizar",
            "description": "5 etapas x 10 s = ~50 s: secuencia_completa=true, etapa vuelve a 0.",
            "t_end": 55.0, "h": 0.2, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "schedule": {"arrancar": [(0, 0), (0.2, 1), (0.4, 0)]},
            "checks": [
                {"col": "secuencia_completa", "type": "eventually", "op": "==", "val": 1,
                 "description": "secuencia_completa debe activarse antes de t=55 s"},
                {"col": "etapa_actual",       "type": "final_value", "val": 0, "tol": 0},
                {"col": "etapa_previa",       "type": "eventually", "op": "==", "val": 5,
                 "description": "etapa_previa debe llegar a 5 al completar la ultima etapa"},
            ],
            "interpretation": (
                "La secuencia completa pasa por 5 etapas de 10 s cada una (con sensor=0.8). "
                "Duracion total ≈50 s + tiempo de transicion. Al completar la etapa 5, "
                "secuencia_completa=TRUE (pulso de 1 paso) y etapa_actual vuelve a 0. "
                "etapa_previa=5 registra que la ultima etapa completada fue la 5."
            ),
        },
        {
            "id": "TC-ES-010",
            "title": "Reinicio tras completion — nueva secuencia arranca correctamente",
            "description": "Tras completion (etapa=0), nuevo flanco de arrancar: etapa=1 de nuevo.",
            "t_end": 65.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "schedule": {
                "arrancar": [(0, 0), (0.5, 1), (1.0, 0), (54.0, 1), (54.5, 0)],
            },
            "checks": [
                {"col": "etapa_actual", "type": "eventually", "op": "==", "val": 1,
                 "description": "etapa_actual debe llegar a 1 tras primer arrancar"},
                {"col": "etapa_actual", "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "Tras completar la primera secuencia (≈51 s), el secuenciador vuelve "
                "a etapa=0. Segundo flanco de arrancar en t=54 s: la condicion "
                "'edge(arrancar) and etapa==0' se cumple de nuevo y la secuencia "
                "reinicia en etapa=1. Verifica que el secuenciador es reutilizable "
                "sin necesidad de reiniciar la FMU."
            ),
        },
        {
            "id": "TC-ES-011",
            "title": "Progreso clamped a 1.0 cuando sensor bloquea el avance",
            "description": "Con sensor < 0.5 y temporizador > duracion: progreso = 1.0 (clamped).",
            "t_end": 20.0, "h": 0.2, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.3},
            "schedule": {"arrancar": [(0, 0), (0.2, 1), (0.4, 0)]},
            "checks": [
                {"col": "etapa_actual",   "type": "at_t", "at_t": 15.0, "val": 1,   "tol": 0},
                {"col": "progreso_etapa", "type": "at_t", "at_t": 15.0, "val": 1.0, "tol": 0.01},
            ],
            "interpretation": (
                "Con sensor=0.3 < 0.5, el secuenciador no puede avanzar. El temporizador "
                "crece mas alla de duracion_etapa=10. progreso=min(1.0, timer/10): "
                "cuando timer>10, progreso se clampea a 1.0. Verifica que el clamp "
                "de progreso funciona correctamente y que la variable no supera 1.0."
            ),
        },
        {
            "id": "TC-ES-012",
            "title": "Ciclo de parada y reinicio",
            "description": "Arrancar→etapa1, luego parar→idle, luego arrancar→etapa1 fresco.",
            "t_end": 10.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"arrancar": 0, "parar": 0, "sensor_confirmacion": 0.8},
            "schedule": {
                "arrancar": [(0, 0), (0.1, 1), (0.2, 0), (6.1, 1), (6.2, 0)],
                "parar":    [(0, 0), (5.0, 1), (5.5, 0)],
            },
            "checks": [
                {"col": "etapa_actual",   "type": "at_t", "at_t": 3.0,  "val": 1,   "tol": 0},
                {"col": "etapa_actual",   "type": "at_t", "at_t": 5.5,  "val": 0,   "tol": 0},
                {"col": "etapa_actual",   "type": "at_t", "at_t": 7.0,  "val": 1,   "tol": 0},
                {"col": "progreso_etapa", "type": "at_t", "at_t": 6.5,  "val": 0.0, "tol": 0.15},
            ],
            "interpretation": (
                "Ciclo completo: arrancar en t=0.1 → etapa=1 en t=3. Parar en t=5 → "
                "idle (etapa=0) en t=5.5. Segundo arrancar en t=6.1 → etapa=1 fresca "
                "con temporizador≈0 en t=6.5 (progreso≈0). Verifica que tras parar "
                "el temporizador se resetea y el reinicio parte de cero."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
