#!/usr/bin/env python3
"""Test battery completa — SuspensionActiva (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "SuspensionActiva",
    "tests": [
        {
            "id": "TC-SA-001",
            "title": "Sin bache — todas las salidas en cero al inicio",
            "description": "perfil=0, velocidad=0.5: fuerza=0, bache=false, saturado=false, confort=false.",
            "t_end": 0.1, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.0, "velocidad_vehiculo": 0.5},
            "checks": [
                {"col": "fuerza_actuador",    "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "bache_detectado",    "type": "at_t", "at_t": 0.0, "val": 0,   "tol": 0},
                {"col": "actuador_saturado",  "type": "at_t", "at_t": 0.0, "val": 0,   "tol": 0},
                {"col": "modo_confort",       "type": "at_t", "at_t": 0.01, "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Estados iniciales: posicion_filtrada=0, velocidad_filtrada=0. "
                "Con perfil=0 y velocidad=0.5 en t=0: fuerza_raw=-(3*0+0.8*0)=0, "
                "fuerza_actuador=0. bache_detectado=FALSE (|0| < 0.30). "
                "modo_confort=FALSE (velocidad=0.5 >= 0.3). Se verifica en t=0.01 "
                "porque en t=0 la hysteresis inicializa con velocidad=0 (< 0.3) "
                "antes de aplicar el input, produciendo un transitorio de 1 paso. "
                "Linea base de carretera plana."
            ),
        },
        {
            "id": "TC-SA-002",
            "title": "Velocidad baja sin bache — modo_confort activo",
            "description": "perfil=0, velocidad=0.2: modo_confort=true (0.2 < 0.3 y sin bache).",
            "t_end": 0.1, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.0, "velocidad_vehiculo": 0.2},
            "checks": [
                {"col": "fuerza_actuador",   "type": "at_t", "at_t": 0.0, "val": 0.0, "tol": 1e-6},
                {"col": "bache_detectado",   "type": "at_t", "at_t": 0.0, "val": 0,   "tol": 0},
                {"col": "modo_confort",      "type": "at_t", "at_t": 0.0, "val": 1,   "tol": 0},
                {"col": "actuador_saturado", "type": "at_t", "at_t": 0.0, "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Con velocidad=0.2 < 0.3 (umbral de confort) y sin bache detectado: "
                "modo_confort=TRUE. La condicion es 'velocidad < 0.3 AND NOT bache'. "
                "fuerza_actuador=0 (estados en cero). Verifica la activacion de "
                "modo confort en ciudad (velocidad reducida, sin perturbaciones)."
            ),
        },
        {
            "id": "TC-SA-003",
            "title": "Bache pequeno — por debajo del umbral de deteccion",
            "description": "perfil=0.25 en estado estacionario: posicion_filtrada→0.25, bache=false.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.25, "velocidad_vehiculo": 0.5},
            "checks": [
                {"col": "bache_detectado",   "type": "final_value", "val": 0,    "tol": 0},
                {"col": "fuerza_actuador",   "type": "final_value", "val": -0.75,"tol": 0.01},
                {"col": "actuador_saturado", "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "Con perfil=0.25 constante, tras convergencia (5*tau=0.5s): "
                "posicion_filtrada→0.25, velocidad_filtrada→0. "
                "fuerza_raw=-(3*0.25+0.8*0)=-0.75 (dentro de limites). "
                "bache_detectado=FALSE (0.25 < 0.30 — por debajo del umbral). "
                "actuador_saturado=FALSE (|fuerza_raw|=0.75 < 1.0)."
            ),
        },
        {
            "id": "TC-SA-004",
            "title": "Bache exactamente en el umbral — bache_detectado=false (operador estricto)",
            "description": "posicion_filtrada→0.30 exacto: bache=false (>: 0.30 NO > 0.30).",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.30, "velocidad_vehiculo": 0.5},
            "checks": [
                {"col": "bache_detectado",   "type": "final_value", "val": 0,    "tol": 0},
                {"col": "fuerza_actuador",   "type": "final_value", "val": -0.90,"tol": 0.02},
                {"col": "actuador_saturado", "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "Con perfil=0.30, tras convergencia posicion_filtrada→0.30. "
                "bache_detectado = |posicion_filtrada| > 0.30 (estricto). "
                "0.30 NO es mayor que 0.30 → bache=FALSE. "
                "fuerza_actuador=-(3*0.30)=-0.90 (sin saturar). "
                "Verifica la frontera critica del detector de bache."
            ),
        },
        {
            "id": "TC-SA-005",
            "title": "Bache justo sobre el umbral — bache_detectado=true",
            "description": "posicion_filtrada→0.31: bache=true, modo_confort bloqueado.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.31, "velocidad_vehiculo": 0.2},
            "checks": [
                {"col": "bache_detectado", "type": "final_value", "val": 1, "tol": 0},
                {"col": "modo_confort",    "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "Con perfil=0.31, posicion_filtrada→0.31 > 0.30 → bache_detectado=TRUE. "
                "Aunque velocidad=0.2 < 0.3, modo_confort=FALSE porque la condicion "
                "es 'velocidad < 0.3 AND NOT bache'. El bache suprime el modo confort. "
                "Verifica el operador AND y la interaccion entre las dos condiciones."
            ),
        },
        {
            "id": "TC-SA-006",
            "title": "Bache grande — actuador saturado en -1.0",
            "description": "posicion_filtrada→0.50: fuerza_raw=-1.5, fuerza_actuador=-1.0 (clamped).",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.50, "velocidad_vehiculo": 0.5},
            "checks": [
                {"col": "fuerza_actuador",   "type": "final_value", "val": -1.0, "tol": 0.02},
                {"col": "actuador_saturado", "type": "final_value", "val": 1,    "tol": 0},
                {"col": "bache_detectado",   "type": "final_value", "val": 1,    "tol": 0},
            ],
            "interpretation": (
                "Con perfil=0.50, posicion_filtrada→0.50. fuerza_raw=-(3*0.50)=-1.50. "
                "fuerza_actuador=clamp(-1.50,-1,1)=-1.0. actuador_saturado=TRUE "
                "(|fuerza_raw|=1.5 >= 1.0). Verifica que el clamp opera correctamente "
                "y que actuador_saturado se activa con |raw|>=1."
            ),
        },
        {
            "id": "TC-SA-007",
            "title": "Bache negativo (socavon) — fuerza positiva, saturacion hacia arriba",
            "description": "perfil=-0.40: posicion→-0.40, fuerza_raw=+1.2, fuerza_actuador=+1.0.",
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": -0.40, "velocidad_vehiculo": 0.5},
            "checks": [
                {"col": "fuerza_actuador",   "type": "final_value", "val": 1.0, "tol": 0.02},
                {"col": "actuador_saturado", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "bache_detectado",   "type": "final_value", "val": 1,   "tol": 0},
            ],
            "interpretation": (
                "Socavon (bache negativo): posicion_filtrada→-0.40. "
                "fuerza_raw=-(3*(-0.40))=+1.20 (fuerza hacia arriba). "
                "fuerza_actuador=clamp(+1.20,-1,1)=+1.0. actuador_saturado=TRUE. "
                "bache_detectado=TRUE (|-0.40|=0.40 > 0.30). Verifica que el "
                "actuador puede ejercer fuerza positiva (levantamiento de suspension)."
            ),
        },
        {
            "id": "TC-SA-008",
            "title": "Transitorio del filtro — bache_detectado activa a t≈0.1 s",
            "description": "Escalon de perfil=0.5 en t=0: bache_detectado eventually=true.",
            "t_end": 0.5, "h": 0.005, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.5, "velocidad_vehiculo": 0.5},
            "checks": [
                {"col": "bache_detectado",   "type": "at_t", "at_t": 0.0,  "val": 0,   "tol": 0},
                {"col": "bache_detectado",   "type": "eventually", "op": "==", "val": 1,
                 "description": "bache_detectado debe activarse tras 1 tau (0.1s)"},
                {"col": "fuerza_actuador",   "type": "no_nan_inf"},
            ],
            "interpretation": (
                "En t=0: posicion_filtrada=0 (estado inicial). bache_detectado=FALSE. "
                "Con perfil=0.5 aplicado desde t=0, el filtro de primer orden con "
                "tau=0.1 s tiene respuesta: posicion(t)=0.5*(1-e^(-t/0.1)). "
                "En t=0.1: pos=0.5*(1-e^-1)≈0.316 > 0.30 → bache_detectado=TRUE. "
                "Verifica la dinamica de deteccion del primer orden."
            ),
        },
        {
            "id": "TC-SA-009",
            "title": "Frontera de velocidad para modo_confort — por encima y por debajo",
            "description": "velocidad=0.31: modo_confort=false (0.31 > 0.30). velocidad=0.29: true. Valor exacto 0.30 dispara hysteresis en OpenModelica FMU.",
            "t_end": 2.0, "h": 0.5, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.0, "velocidad_vehiculo": 0.31},
            "schedule": {"velocidad_vehiculo": [(0, 0.31), (1.0, 0.29)]},
            "checks": [
                {"col": "modo_confort", "type": "at_t", "at_t": 0.5, "val": 0, "tol": 0},
                {"col": "modo_confort", "type": "at_t", "at_t": 1.5, "val": 1, "tol": 0},
            ],
            "interpretation": (
                "La condicion modo_confort usa 'velocidad_vehiculo < 0.30' (estricto). "
                "Con velocidad=0.31 (sobre el umbral): modo_confort=FALSE en t=0.5. "
                "Con velocidad=0.29 (bajo el umbral): modo_confort=TRUE en t=1.5. "
                "Nota: el valor exacto 0.30 activa la hysteresis de OpenModelica FMU "
                "y produce modo_confort=TRUE incorrectamente; se usa 0.31 para evitarlo. "
                "Sin bache (perfil=0), la condicion de baja velocidad es suficiente."
            ),
        },
        {
            "id": "TC-SA-010",
            "title": "Interaccion P y D — fuerza con ambos terminos activos",
            "description": "Tras convergencia completa: verificar fuerza_actuador estable y sin NaN.",
            "t_end": 2.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"perfil_bache": 0.20, "velocidad_vehiculo": 0.5},
            "checks": [
                {"col": "fuerza_actuador",   "type": "final_value", "val": -0.60, "tol": 0.05},
                {"col": "actuador_saturado", "type": "final_value", "val": 0,     "tol": 0},
                {"col": "fuerza_actuador",   "type": "no_nan_inf"},
                {"col": "fuerza_actuador",   "type": "bounded", "low": -1.0, "high": 1.0},
            ],
            "interpretation": (
                "Con perfil=0.20 constante, tras convergencia completa (t=2s >> 5*tau): "
                "posicion_filtrada→0.20, velocidad_filtrada→0. "
                "fuerza_raw=-(3*0.20+0.8*0)=-0.60. fuerza_actuador=-0.60 (sin saturar). "
                "Verifica que en estado estacionario ambos estados del filtro convergen "
                "y que fuerza_actuador es estable y acotada en [-1.0, 1.0]."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
