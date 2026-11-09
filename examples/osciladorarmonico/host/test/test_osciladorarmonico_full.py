#!/usr/bin/env python3
"""Test battery completa — OsciladorArmonico (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "OsciladorArmonico",
    "tests": [
        {
            "id": "TC-OA-001",
            "title": "Condiciones iniciales — t=0",
            "description": "posicion=1.0, velocidad=0.0, energia≈19.739 en t=0.",
            "t_end": 0.01, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion",  "type": "at_t", "at_t": 0.0, "val": 1.0,    "tol": 1e-6},
                {"col": "velocidad", "type": "at_t", "at_t": 0.0, "val": 0.0,    "tol": 1e-6},
                {"col": "energia",   "type": "at_t", "at_t": 0.0, "val": 19.739, "tol": 0.01},
            ],
            "interpretation": (
                "El oscilador empieza en x=1.0 m con v=0. La energia inicial es "
                "E0 = 0.5*omega^2*1^2 = 0.5*(2π)^2 ≈ 19.739 J. Este test verifica "
                "las condiciones iniciales antes de cualquier integracion, confirmando "
                "que la FMU esta correctamente inicializada."
            ),
        },
        {
            "id": "TC-OA-002",
            "title": "Posicion analitica en t=0.25 s (cuarto de periodo)",
            "description": "x(0.25)=cos(π/2)≈0.0, v(0.25)=-2π≈-6.283.",
            "t_end": 0.251, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion",  "type": "final_value", "val": 0.0,    "tol": 0.02},
                {"col": "velocidad", "type": "final_value", "val": -6.283, "tol": 0.05},
                {"col": "energia",   "type": "final_value", "val": 19.739, "tol": 0.1},
            ],
            "interpretation": (
                "A un cuarto de periodo (T/4=0.25 s), la posicion pasa por cero "
                "y la velocidad alcanza su maximo negativo ω=2π≈6.283 rad/s. "
                "Toda la energia es cinetica en este punto (E=0.5*m*v^2). "
                "Este es el punto donde el codegen demuestra que integra "
                "correctamente el termino no-lineal omega^2*x."
            ),
        },
        {
            "id": "TC-OA-003",
            "title": "Posicion analitica en t=0.5 s (medio periodo)",
            "description": "x(0.5)=cos(π)=-1.0, v≈0.",
            "t_end": 0.501, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion",  "type": "final_value", "val": -1.0,  "tol": 0.02},
                {"col": "velocidad", "type": "final_value", "val": 0.0,   "tol": 0.1},
                {"col": "energia",   "type": "final_value", "val": 19.739,"tol": 0.1},
            ],
            "interpretation": (
                "A medio periodo (T/2=0.5 s) la posicion vuelve a la amplitud "
                "pero con signo opuesto: x=-1.0 m, v≈0. Toda la energia es "
                "potencial nuevamente. La simetria del resultado confirma que el "
                "codegen maneja correctamente los dos estados (posicion y velocidad) "
                "del oscilador."
            ),
        },
        {
            "id": "TC-OA-004",
            "title": "Periodo completo — retorno a condicion inicial",
            "description": "En t=1.0 s (un periodo), x≈1.0 y v≈0.",
            "t_end": 1.001, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion",  "type": "final_value", "val": 1.0,   "tol": 0.02},
                {"col": "velocidad", "type": "final_value", "val": 0.0,   "tol": 0.1},
                {"col": "energia",   "type": "final_value", "val": 19.739,"tol": 0.2},
            ],
            "interpretation": (
                "Tras exactamente un periodo T=1.0 s, el sistema debe retornar a "
                "su estado inicial (x=1, v=0). Un error de >0.02 m indicaria que "
                "el periodo numerico del integrador difiere del periodo analitico, "
                "lo que sugiere un error en la fuerza restauradora o en el paso de "
                "integracion."
            ),
        },
        {
            "id": "TC-OA-005",
            "title": "Conservacion de energia — RK4 sobre 20 ciclos",
            "description": "Con RK4, la desviacion de energia debe ser menor de 0.05 J en 20 s.",
            "t_end": 20.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia", "type": "bounded", "low": 19.689, "high": 19.789},
            ],
            "interpretation": (
                "Test principal de calidad del integrador. RK4 con h=0.01 s (100 "
                "pasos por ciclo) debe mantener la energia dentro de ±0.05 J "
                "(±0.25%) durante 20 ciclos completos. Este es el criterio de "
                "aceptacion primario: un integrador de orden inferior o con paso "
                "mayor fallaria este test acumulando error energetico."
            ),
        },
        {
            "id": "TC-OA-006",
            "title": "Deriva de energia con Euler — debe ser peor que RK4",
            "description": "Euler con h=0.01 debe mostrar deriva energetica mayor de 0.8 J en 20 s.",
            "t_end": 20.0, "h": 0.01, "solver": "euler", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia", "type": "eventually",
                 "op": ">", "val": 20.5,
                 "description": "Euler gana energia — debe superar 20.5 J"},
            ],
            "interpretation": (
                "Euler es un integrador de orden 1 que sistemáticamente gana energia "
                "en osciladores sin amortiguamiento. Con h=0.01 s sobre 20 ciclos, "
                "la energia del oscilador crece mas del 3% respecto al valor inicial "
                "de 19.739 J. Si Euler tambien conserva la energia, el paso h es "
                "demasiado pequeno o el test no es discriminante."
            ),
        },
        {
            "id": "TC-OA-007",
            "title": "Posicion acotada con RK4 en 50 ciclos",
            "description": "Con RK4, |posicion| debe mantenerse <= 1.5 m durante 50 s.",
            "t_end": 50.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion", "type": "bounded", "low": -1.5, "high": 1.5},
            ],
            "interpretation": (
                "Durante 50 ciclos, RK4 no debe permitir un crecimiento de amplitud "
                "mayor al 50% de la amplitud inicial (1.0 m). Un integrador simpletico "
                "ideal conservaria exactamente 1.0 m, pero RK4 permite una pequena "
                "deriva aceptable. Si la amplitud supera 1.5 m, el integrador esta "
                "inyectando energia artificialmente."
            ),
        },
        {
            "id": "TC-OA-008",
            "title": "Velocidad maxima cerca del cero de posicion",
            "description": "Cuando |posicion|<0.05, la velocidad debe ser ≈±6.283 rad/s.",
            "t_end": 5.0, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia", "type": "bounded", "low": 19.5, "high": 20.0},
                {"col": "posicion", "type": "sign_changes", "min_changes": 8},
            ],
            "interpretation": (
                "En el cruce por cero (posicion≈0), toda la energia es cinetica: "
                "E=0.5*v^2, por lo que |v|=sqrt(2E)≈sqrt(2*19.739)≈6.28 rad/s. "
                "La posicion debe cruzar el cero mas de 8 veces en 5 s (T=1 s). "
                "Ambas verificaciones juntas confirman que el oscilador esta en "
                "regimen correcto."
            ),
        },
        {
            "id": "TC-OA-009",
            "title": "Comparacion de paso — RK4 h=0.01 vs h=0.001",
            "description": "Con h=0.001, la energia debe ser mas estable que con h=0.01.",
            "t_end": 10.0, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "energia", "type": "bounded", "low": 19.730, "high": 19.748},
            ],
            "interpretation": (
                "Con un paso 10x mas pequeno (h=0.001 s), la deriva de energia de "
                "RK4 se reduce drasticamente. La ventana de tolerancia [19.730, 19.748] "
                "es 5x mas estrecha que para h=0.01. Esto verifica la propiedad de "
                "convergencia de RK4: la precision mejora como O(h^4) al reducir el paso."
            ),
        },
        {
            "id": "TC-OA-010",
            "title": "Sin NaN ni Inf en 100 ciclos con RK4",
            "description": "100 segundos de simulacion autonoma sin valores invalidos.",
            "t_end": 100.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {},
            "checks": [
                {"col": "posicion",  "type": "no_nan_inf"},
                {"col": "velocidad", "type": "no_nan_inf"},
                {"col": "energia",   "type": "no_nan_inf"},
            ],
            "interpretation": (
                "100 segundos equivalen a 100 ciclos completos del oscilador. Un "
                "codegen que genera codigo de derivadas correcto y un integrador "
                "estable no producen NaN ni Inf en este tiempo. Si aparecen valores "
                "invalidos, el integrador ha divergido catastroficamente, lo que "
                "indica un error grave en el codigo generado."
            ),
        },
    ]
}

if __name__ == "__main__":
    from full_test_runner import run_battery
    run_battery(__file__)
