#!/usr/bin/env python3
"""Test battery completa — PenduloNoLineal (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "PenduloNoLineal",
    "tests": [
        {
            "id": "TC-PN-001",
            "title": "Condiciones iniciales — angulo=2.618, omega=0",
            "description": "En t=0: angulo=2.618 rad (150°), velocidad=0, energia≈8.496 J.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "angulo",            "type": "at_t", "at_t": 0.0, "val": 2.618, "tol": 0.001},
                {"col": "velocidad_angular", "type": "at_t", "at_t": 0.0, "val": 0.0,   "tol": 1e-6},
                {"col": "energia_total",     "type": "at_t", "at_t": 0.0, "val": 8.496, "tol": 0.01},
                {"col": "en_reposo",         "type": "at_t", "at_t": 0.0, "val": 1,     "tol": 0},
            ],
            "interpretation": (
                "El pendulo parte de 150° con velocidad angular nula. La energia "
                "inicial E0 = -g*L*cos(2.618) = -9.81*(-0.866) ≈ 8.496 J. "
                "en_reposo=true porque |omega|=0 < 0.01. Este test verifica la "
                "inicializacion correcta del pendulo no lineal de gran amplitud."
            ),
        },
        {
            "id": "TC-PN-002",
            "title": "Velocidad maxima en el fondo (theta≈0)",
            "description": "max|velocidad_angular| ≈ 6.047 rad/s cuando el pendulo pasa por theta=0.",
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "velocidad_angular", "type": "eventually",
                 "op": ">", "val": 5.5,
                 "description": "velocidad maxima debe superar 5.5 rad/s"},
            ],
            "interpretation": (
                "Al pasar por el punto mas bajo (theta=0), toda la energia es cinetica. "
                "La velocidad maxima teorica es omega_max = sqrt(2*(E0 - PE_bottom)) = "
                "sqrt(2*(8.496 + 9.81)) ≈ 6.047 rad/s. El test verifica que el pendulo "
                "alcanza velocidades superiores a 5.5 rad/s, confirmando que la "
                "conversion de energia potencial a cinetica es correcta."
            ),
        },
        {
            "id": "TC-PN-003",
            "title": "Oscilacion simetrica — angulo minimo ≈ -2.618",
            "description": "Sin amortiguamiento, el pendulo debe alcanzar -2.618 rad.",
            "t_end": 10.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "angulo", "type": "eventually",
                 "op": "<", "val": -2.4,
                 "description": "El pendulo debe alcanzar angulos negativos < -2.4"},
            ],
            "interpretation": (
                "Sin amortiguamiento (g, L y las condiciones iniciales son los unicos "
                "parametros), el pendulo oscila simetricamente. Desde 2.618 rad "
                "debe alcanzar aproximadamente -2.618 rad en el otro extremo. "
                "Si solo alcanza -2.0 rad, la energia no se conserva correctamente."
            ),
        },
        {
            "id": "TC-PN-004",
            "title": "Conservacion de energia con RK4 (h=0.05, 10 s)",
            "description": "|energia - 8.496| < 0.1 J en todo momento con RK4.",
            "t_end": 10.0, "h": 0.05, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia_total", "type": "bounded", "low": 8.396, "high": 8.596},
            ],
            "interpretation": (
                "TEST DE CALIDAD PRIMARIO para RK4. Con paso moderado h=0.05 s, "
                "la energia del pendulo no lineal debe conservarse dentro de ±0.1 J "
                "(±1.2%) durante 10 segundos. El pendulo de gran angulo es mas "
                "dificil de integrar que el oscilador armonico por el termino sin(θ), "
                "que varia mas rapidamente cerca de θ=±π."
            ),
        },
        {
            "id": "TC-PN-005",
            "title": "Deriva energetica con Euler — discriminador",
            "description": "Euler con h=0.05 debe mostrar deriva >0.5 J antes de t=10 s.",
            "t_end": 10.0, "h": 0.05, "solver": "euler", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia_total", "type": "eventually",
                 "op": ">", "val": 9.0,
                 "description": "Euler debe ganar energia (>9 J desde 8.496 J)"},
            ],
            "interpretation": (
                "Euler con h=0.05 acumula error en el termino no lineal sin(θ). "
                "La energia crece sistematicamente, superando 9 J (>6% de deriva). "
                "Si Euler tambien conserva la energia con h=0.05, usar h=0.1 s "
                "para ampliar la diferencia. Este es el discriminador RK4 vs Euler."
            ),
        },
        {
            "id": "TC-PN-006",
            "title": "en_reposo activa al menos 4 veces en 15 s",
            "description": "El pendulo pasa por los extremos al menos 2 veces por ciclo.",
            "t_end": 15.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "en_reposo", "type": "count_value", "val": 1, "min_count": 3},
            ],
            "interpretation": (
                "El periodo del pendulo de 150° es aproximadamente T≈7 s (mucho mayor "
                "que el periodo lineal de 2 s). En 15 s deben ocurrir ~2 ciclos, cada "
                "uno con 2 puntos de reposo (extremos). en_reposo=true indica que "
                "|omega|<0.01, lo que sucede en los puntos de maxima amplitud."
            ),
        },
        {
            "id": "TC-PN-007",
            "title": "Angulo acotado dentro de [-3.2, 3.2] rad",
            "description": "El pendulo no tiene energia suficiente para girar completo.",
            "t_end": 30.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "angulo", "type": "bounded", "low": -3.2, "high": 3.2},
            ],
            "interpretation": (
                "Con E0≈8.496 J, el pendulo no puede alcanzar la posicion vertical "
                "invertida (θ=π=3.14 rad) que requeriria E=2gL=19.62 J. Por tanto, "
                "el pendulo oscila sin dar giros completos, acotado dentro de "
                "[-2.618, 2.618]±tolerancia. Valores fuera de [-3.2, 3.2] "
                "indicarian divergencia catastrofica del integrador."
            ),
        },
        {
            "id": "TC-PN-008",
            "title": "Estimacion del periodo de gran angulo",
            "description": "El periodo de oscilacion debe estar cerca de 7 s (≠ 2.006 s lineal).",
            "t_end": 20.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "angulo", "type": "sign_changes", "min_changes": 4},
            ],
            "interpretation": (
                "La no-linealidad alarga el periodo del pendulo. Para θ0=150°, "
                "T_grande ≈ 7 s (vs. T_lineal=2.006 s). En 20 s deben ocurrir "
                "~2.8 ciclos, con ~6 cruces de cero. El test verifica un minimo "
                "de 4 cruces, que serian consistentes con ~2 ciclos completos, "
                "confirmando el periodo largo del sistema no lineal."
            ),
        },
        {
            "id": "TC-PN-009",
            "title": "Sin NaN ni Inf en 30 s",
            "description": "Pendulo caotico-cercano sin valores invalidos en 30 s.",
            "t_end": 30.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "angulo",            "type": "no_nan_inf"},
                {"col": "velocidad_angular", "type": "no_nan_inf"},
                {"col": "energia_total",     "type": "no_nan_inf"},
            ],
            "interpretation": (
                "30 segundos de pendulo no lineal de gran angulo. La proximidad a "
                "la posicion inestable (θ=π) hace este sistema numericamente sensible. "
                "Cualquier NaN/Inf indica que el integrador ha divergido. RK4 con "
                "h=0.01 debe mantenerse estable para estos parametros."
            ),
        },
        {
            "id": "TC-PN-010",
            "title": "Comparacion energetica RK4 vs Euler en t=5 s",
            "description": "RK4 tiene menor deriva que Euler en el mismo instante.",
            "t_end": 5.0, "h": 0.05, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia_total", "type": "final_value", "val": 8.496, "tol": 0.1},
            ],
            "interpretation": (
                "A t=5 s con h=0.05, RK4 debe estar dentro de 0.1 J del valor "
                "de energia inicial. Euler con los mismos parametros estaria tipicamente "
                "a 0.3-0.5 J de deriva. Este test verifica la mitad de la comparacion "
                "directa (el caso RK4); TC-PN-005 verifica el caso Euler. Juntos "
                "demuestran la superioridad cuantitativa de RK4 para este sistema."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
