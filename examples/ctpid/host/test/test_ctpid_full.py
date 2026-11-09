#!/usr/bin/env python3
"""Test battery completa — CTPID (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "CTPID",
    "tests": [
        {
            "id": "TC-CT-001",
            "title": "Setpoint = temperatura — ledAlcanzado activo, ventilador=0",
            "description": "temperatura=0.50, consigna=0.50: error=0, ventilador=0, ledAlcanzado=true.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.50, "consigna": 0.50},
            "checks": [
                {"col": "ventilador",   "type": "final_value", "val": 0.0, "tol": 1e-6},
                {"col": "ledAlcanzado", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "ledPorEncima", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "ledPorDebajo", "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Con consigna=temperatura=0.50, error=0. En t=0, integrador=0 y "
                "derivador=0, por lo que pid_raw=0 y ventilador=0. "
                "ledAlcanzado=TRUE porque |error|=0 <= epsilon=1.0. Ningun LED "
                "de encima o debajo activo. Verifica el punto de operacion nominal "
                "sin demanda inicial."
            ),
        },
        {
            "id": "TC-CT-002",
            "title": "Setpoint por encima — demanda de calefaccion, ledPorEncima=true",
            "description": "temperatura=0.30, consigna=0.50: error=20deg, ventilador=0.40 en t=0.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.30, "consigna": 0.50},
            "checks": [
                {"col": "ventilador",   "type": "final_value", "val": 0.40, "tol": 0.01},
                {"col": "ledPorEncima", "type": "final_value", "val": 1,    "tol": 0},
                {"col": "ledPorDebajo", "type": "final_value", "val": 0,    "tol": 0},
                {"col": "ledAlcanzado", "type": "final_value", "val": 0,    "tol": 0},
            ],
            "interpretation": (
                "error = (0.50-0.30)*100 = 20 grados. En t=0 (integrador=0, der=0): "
                "pid_raw = Kp*20 = 2.0*20 = 40. ventilador = clamp(40/100,0,1) = 0.40. "
                "ledPorEncima=TRUE (50 > 30+1). Verifica la rampa proporcional inicial "
                "y que el ventilador activa con error positivo."
            ),
        },
        {
            "id": "TC-CT-003",
            "title": "Setpoint por debajo — sobretemperatura, ventilador=0",
            "description": "temperatura=0.70, consigna=0.50: error=-20deg, ventilador=0 (clamped), ledPorDebajo=true.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.70, "consigna": 0.50},
            "checks": [
                {"col": "ventilador",   "type": "final_value", "val": 0.0, "tol": 1e-6},
                {"col": "ledPorDebajo", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "ledPorEncima", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "ledAlcanzado", "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "error = (0.50-0.70)*100 = -20 grados. pid_raw = Kp*(-20) = -40. "
                "ventilador = clamp(-40/100, 0, 1) = 0 (el ventilador no puede enfriar). "
                "ledPorDebajo=TRUE (50 < 70-1). Verifica que el ventilador se clampea "
                "a cero con error negativo (sobretemperatura)."
            ),
        },
        {
            "id": "TC-CT-004",
            "title": "Dentro de la banda muerta — ledAlcanzado activo",
            "description": "temperatura=0.51, consigna=0.50: |error|=1.0 <= epsilon → ledAlcanzado=true.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.51, "consigna": 0.50},
            "checks": [
                {"col": "ledAlcanzado", "type": "final_value", "val": 1, "tol": 0},
                {"col": "ledPorEncima", "type": "final_value", "val": 0, "tol": 0},
                {"col": "ledPorDebajo", "type": "final_value", "val": 0, "tol": 0},
            ],
            "interpretation": (
                "error = (0.50-0.51)*100 = -1.0 grado. |error|=1.0 <= epsilon=1.0: "
                "ledAlcanzado=TRUE. La condicion es abs(error)<=epsilon (no estricto). "
                "ledPorDebajo = (50 < 51-1) = (50 < 50) = FALSE (condicion estricta). "
                "Ambas condiciones de frontera se verifican simultaneamente."
            ),
        },
        {
            "id": "TC-CT-005",
            "title": "Justo fuera de la banda muerta — ledAlcanzado inactivo",
            "description": "temperatura=0.512, consigna=0.50: |error|=1.2 > epsilon=1.0 → ledAlcanzado=false.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.512, "consigna": 0.50},
            "checks": [
                {"col": "ledAlcanzado", "type": "final_value", "val": 0, "tol": 0},
                {"col": "ledPorDebajo", "type": "final_value", "val": 1, "tol": 0},
            ],
            "interpretation": (
                "error = (0.50-0.512)*100 = -1.2 grados. |error|=1.2 > epsilon=1.0: "
                "ledAlcanzado=FALSE. ledPorDebajo=TRUE (50 < 51.2-1 = 50.2). "
                "Complementario de TC-CT-004: 0.1 grado adicional saca el error de "
                "la banda muerta. Verifica que la banda muerta es exactamente +/-epsilon."
            ),
        },
        {
            "id": "TC-CT-006",
            "title": "Demanda maxima — ventilador saturado a 1.0",
            "description": "temperatura=0.0, consigna=1.0: error=100deg, pid_raw=200, ventilador=1.0.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.0, "consigna": 1.0},
            "checks": [
                {"col": "ventilador",   "type": "final_value", "val": 1.0, "tol": 1e-9},
                {"col": "ledPorEncima", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "ledAlcanzado", "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "error = (1.0-0.0)*100 = 100 grados. pid_raw = 2.0*100 = 200. "
                "ventilador = clamp(200/100, 0, 1) = clamp(2.0, 0, 1) = 1.0. "
                "El ventilador satura al maximo. ledPorEncima=TRUE (100 > 0+1). "
                "Verifica que el clamp es hacia arriba (1.0) correctamente."
            ),
        },
        {
            "id": "TC-CT-007",
            "title": "Wind-up integral — 10 segundos de error positivo, ventilador=1.0",
            "description": "temperatura=0.30, consigna=0.50 durante 10s: integrador≈200, ventilador=1.0.",
            "t_end": 10.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.30, "consigna": 0.50},
            "checks": [
                {"col": "ventilador",   "type": "final_value", "val": 1.0, "tol": 1e-6},
                {"col": "ledPorEncima", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "ledAlcanzado", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "ventilador",   "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Con error=20 grados constante durante 10s, der(integrador)=20 siempre. "
                "integrador(10) = 20*10 = 200. pid_raw = 2*20 + 0.5*200 + ... >> 100. "
                "ventilador = 1.0 (saturado). Verifica que la integracion acumulada "
                "de error satura el actuador — el wind-up del integrador es intencional "
                "en este modelo (sin anti-windup)."
            ),
        },
        {
            "id": "TC-CT-008",
            "title": "Escalon en la consigna — ledPorEncima activo despues del cambio",
            "description": "t=5: consigna 0.50→0.70 (escalon +20 grados). ledPorEncima cambia a true.",
            "t_end": 7.0, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.50, "consigna": 0.50},
            "schedule": {"consigna": [(0, 0.50), (5.0, 0.70)]},
            "checks": [
                {"col": "ledAlcanzado", "type": "at_t", "at_t": 4.9, "val": 1,   "tol": 0},
                {"col": "ledPorEncima", "type": "eventually", "op": "==", "val": 1,
                 "description": "ledPorEncima debe activarse tras el escalon de consigna"},
                {"col": "ledAlcanzado", "type": "at_t", "at_t": 7.0, "val": 0,   "tol": 0},
                {"col": "ventilador",   "type": "at_t", "at_t": 5.1, "val": 0.40, "tol": 0.05},
            ],
            "interpretation": (
                "Antes del escalon (t<5): error=0, ledAlcanzado=TRUE. "
                "Inmediatamente despues (t=5.1): consigna=0.70, temperatura=0.50, "
                "error=(0.70-0.50)*100=20 grados. ledPorEncima=TRUE, ledAlcanzado=FALSE. "
                "ventilador ≈ Kp*20/100 = 0.40 (componente proporcional dominante "
                "justo despues del escalon). Verifica la respuesta transitoria al escalon."
            ),
        },
        {
            "id": "TC-CT-009",
            "title": "Ambas entradas en cero — ledAlcanzado, sin demanda",
            "description": "temperatura=0.0, consigna=0.0: error=0, ventilador=0, ledAlcanzado=true.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 0.0, "consigna": 0.0},
            "checks": [
                {"col": "ventilador",   "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "ledAlcanzado", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "ledPorEncima", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "ledPorDebajo", "type": "final_value", "val": 0,   "tol": 0},
            ],
            "interpretation": (
                "Limite inferior: temperatura=consigna=0 → error=0. ventilador=0 "
                "(sin demanda). ledAlcanzado=TRUE. Verifica la estabilidad en el "
                "extremo inferior del rango [0,1]. No debe haber residuos de "
                "precision flotante que activen un LED equivocado con valores cero."
            ),
        },
        {
            "id": "TC-CT-010",
            "title": "Ambas entradas al maximo — ledAlcanzado, sin demanda",
            "description": "temperatura=1.0, consigna=1.0: error=0, ventilador=0, ledAlcanzado=true.",
            "t_end": 0.1, "h": 0.1, "solver": "rk4", "mode": "me",
            "inputs": {"temperatura": 1.0, "consigna": 1.0},
            "checks": [
                {"col": "ventilador",   "type": "final_value", "val": 0.0, "tol": 1e-9},
                {"col": "ledAlcanzado", "type": "final_value", "val": 1,   "tol": 0},
                {"col": "ledPorEncima", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "ledPorDebajo", "type": "final_value", "val": 0,   "tol": 0},
                {"col": "ventilador",   "type": "no_nan_inf"},
            ],
            "interpretation": (
                "Limite superior: temperatura=consigna=1.0 → error=0. Simetrico a "
                "TC-CT-009 pero en el extremo superior. ventilador=0, ledAlcanzado=TRUE. "
                "Verifica que el calculo con T_max=100 no causa desbordamiento ni "
                "precision flotante que genere un error artificial de epsilon."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
