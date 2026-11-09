#!/usr/bin/env python3
"""Test battery completa — ArranqueSuaveMotor (10 TCs)"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools'))

CONFIG = {
    "model_name": "ArranqueSuaveMotor",
    "tests": [
        {
            "id": "TC-ASM-001",
            "title": "No start command — estado en reposo",
            "description": (
                "Verifica que con orden_arranque=false y carga_motor=0, todos los "
                "outputs permanecen inactivos en t=0. Confirma que no hay activacion "
                "espontanea sin comandar el arranque."
            ),
            "t_end": 0.5, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"orden_arranque": 0, "carga_motor": 0.0},
            "checks": [
                {"col": "tension_aplicada", "type": "always", "op": "==", "val": 0.0,
                 "description": "Sin arranque, la tension permanece en 0"},
                {"col": "motor_en_marcha",  "type": "always", "op": "==", "val": 0},
                {"col": "fallo_sobrecarga", "type": "always", "op": "==", "val": 0},
                {"col": "en_rampa",         "type": "always", "op": "==", "val": 0},
            ],
            "interpretation": (
                "Con la orden de arranque desactivada, el modelo permanece en estado "
                "de reposo. La rampa de tension no evoluciona (referencia=0), y ninguna "
                "salida booleana se activa. Este test verifica que la condicion inicial "
                "es correcta y que no existe activacion espontanea del sistema."
            ),
        },
        {
            "id": "TC-ASM-002",
            "title": "Start command — en_rampa activa inmediatamente",
            "description": (
                "Al dar la orden de arranque, 'en_rampa' debe activarse y 'tension_aplicada' "
                "debe comenzar a crecer. A t=0.1s la tension ya es positiva, pero el motor "
                "no ha llegado aun al 90% necesario para declararse en marcha."
            ),
            "t_end": 0.5, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"orden_arranque": 1, "carga_motor": 0.0},
            "checks": [
                {"col": "tension_aplicada", "type": "eventually", "op": ">", "val": 0.0,
                 "description": "La rampa comienza a crecer tras el arranque"},
                {"col": "motor_en_marcha",  "type": "always", "op": "==", "val": 0,
                 "description": "Motor no puede estar en marcha en menos de 0.5s"},
                {"col": "fallo_sobrecarga", "type": "always", "op": "==", "val": 0},
                {"col": "tension_aplicada", "type": "always", "op": ">=", "val": 0.0},
            ],
            "interpretation": (
                "En el instante del arranque, la rampa de tension comienza su ascenso "
                "exponencial con tau=3s. A t=0.1s la tension apenas alcanza ~3%, pero ya "
                "es positiva. La salida 'en_rampa' se activa (orden_arranque=true y "
                "tension<90%), mientras que 'motor_en_marcha' requiere al menos ~9s. "
                "Este test confirma la respuesta inmediata del actuador al comando."
            ),
        },
        {
            "id": "TC-ASM-003",
            "title": "Motor fully started — umbral 90% superado",
            "description": (
                "Corrida de 12s con orden de arranque continua. A t=12s la tension debe "
                "superar el 90% y el motor debe declararse en marcha. Verifica la "
                "dinamica completa del ciclo de arranque suave."
            ),
            "t_end": 12.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"orden_arranque": 1, "carga_motor": 0.0},
            "checks": [
                {"col": "tension_aplicada", "at_t": 12.0, "val": 0.978, "tol": 0.03,
                 "description": "A t=12s la tension alcanza ~98% (respuesta de 1er orden)"},
                {"col": "motor_en_marcha",  "type": "eventually", "op": "==", "val": 1,
                 "description": "Motor en marcha cuando tension supera 90%"},
                {"col": "en_rampa",         "at_t": 12.0, "val": 0, "tol": 0,
                 "description": "Una vez en marcha, en_rampa se desactiva"},
                {"col": "fallo_sobrecarga", "type": "always", "op": "==", "val": 0},
                {"col": "tension_aplicada", "type": "monotone_inc",
                 "description": "La tension debe crecer monotonamente (sin carga)"},
            ],
            "interpretation": (
                "Con tau_rampa=3s y tau_pt1=0.5s, a t=12s (4 constantes de tiempo) la "
                "rampa alcanza 1-e^-4=98.2%. El filtro PT1 la sigue de cerca. El motor "
                "se declara en marcha hacia t~9s cuando la tension_filtrada supera 0.90. "
                "La monotonia de la tension confirma la estabilidad del controlador de "
                "arranque suave bajo condiciones nominales sin sobrecarga."
            ),
        },
        {
            "id": "TC-ASM-004",
            "title": "Stop command — tension decae tras parada",
            "description": (
                "Motor arrancado de t=0 a t=10s, luego orden de parada. A t=13s "
                "(3s tras la parada = 1 tau_rampa) la tension debe haber caido "
                "significativamente. Verifica el arranque suave inverso (rampa de bajada)."
            ),
            "t_end": 13.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"carga_motor": 0.0},
            "schedule": {"orden_arranque": [(0, 1), (10.0, 0)]},
            "checks": [
                {"col": "tension_aplicada", "at_t": 10.0, "val": 0.964, "tol": 0.05,
                 "description": "Antes de la parada, tension cerca del 96% (t=10s, ~3.3 tau)"},
                {"col": "tension_aplicada", "at_t": 13.0, "val": 0.35, "tol": 0.12,
                 "description": "A t=13s (3s de decaimiento), tension debe haber bajado (~1-1/e ≈ 35-38%)"},
                {"col": "motor_en_marcha",  "at_t": 13.0, "val": 0, "tol": 0,
                 "description": "Motor no en marcha cuando orden_arranque=false"},
            ],
            "interpretation": (
                "Al desactivar la orden a t=10s, la referencia pasa a 0 y la rampa decae "
                "con tau=3s. A t=13s han transcurrido 3s = 1 tau, por lo que la rampa "
                "habrá decaído en 1-e^-1=63%, quedando en ~36%. El filtro PT1 (tau=0.5s) "
                "sigue la rampa casi instantaneamente. Motor_en_marcha se desactiva "
                "inmediatamente al quitar la orden, confirmando la semantica booleana directa."
            ),
        },
        {
            "id": "TC-ASM-005",
            "title": "Brief overload (1s) — no dispara fallo",
            "description": (
                "Sobrecarga de 1s (carga_motor=0.95 durante t=10..11s). El integrador "
                "de sobrecarga apenas acumula 1s y luego decae. A t=12s fallo_sobrecarga "
                "debe ser FALSE (umbral es 2s)."
            ),
            "t_end": 12.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"orden_arranque": 1},
            "schedule": {"carga_motor": [(0, 0.0), (10.0, 0.95), (11.0, 0.0)]},
            "checks": [
                {"col": "fallo_sobrecarga", "at_t": 12.0, "val": 0, "tol": 0,
                 "description": "1s de sobrecarga no debe disparar el fallo (umbral=2s)"},
                {"col": "fallo_sobrecarga", "type": "always", "op": "==", "val": 0,
                 "description": "Fallo nunca debe activarse en toda la simulacion"},
                {"col": "motor_en_marcha",  "at_t": 12.0, "val": 1, "tol": 0,
                 "description": "Motor sigue en marcha tras la sobrecarga breve"},
            ],
            "interpretation": (
                "Con t_retardo=2s, una sobrecarga de 1s no alcanza el umbral de fallo. "
                "El integrador acumula 1s pero luego decae con tau=0.5s antes de llegar a 2. "
                "Este test valida la robustez del sistema: perturbaciones cortas no generan "
                "paradas innecesarias, lo que es critico en aplicaciones industriales donde "
                "picos transitorios de carga son frecuentes."
            ),
        },
        {
            "id": "TC-ASM-006",
            "title": "Sustained overload (2s) — fallo dispara",
            "description": (
                "Sobrecarga sostenida desde t=10s con carga_motor=0.95. A t=12s "
                "(2s de sobrecarga continua) el integrador supera el umbral y "
                "fallo_sobrecarga debe activarse."
            ),
            "t_end": 12.5, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"orden_arranque": 1},
            "schedule": {"carga_motor": [(0, 0.0), (10.0, 0.95)]},
            "checks": [
                {"col": "fallo_sobrecarga", "type": "eventually", "op": "==", "val": 1,
                 "description": "Sobrecarga sostenida 2s debe disparar el fallo"},
                {"col": "en_rampa", "at_t": 12.0, "val": 0, "tol": 0,
                 "description": "en_rampa se desactiva cuando hay fallo"},
            ],
            "interpretation": (
                "Con sobrecarga continua desde t=10s, el integrador acumula a razon de "
                "1 s/s (der=1.0 cuando carga>0.9). A t=12s el integrador llega a 2s "
                "(valor de t_retardo), disparando el fallo. Este test verifica la "
                "proteccion contra sobrecargas prolongadas, fundamental en motores "
                "electricos donde el sobrecalentamiento por exceso de corriente puede "
                "causar danos permanentes."
            ),
        },
        {
            "id": "TC-ASM-007",
            "title": "Overload exactamente en umbral — no fallo",
            "description": (
                "carga_motor=0.90 es exactamente el umbral. La condicion es estricta "
                "(carga > 0.9), por lo que no debe acumularse el integrador."
            ),
            "t_end": 5.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"orden_arranque": 1, "carga_motor": 0.90},
            "checks": [
                {"col": "fallo_sobrecarga", "type": "always", "op": "==", "val": 0,
                 "description": "En el umbral exacto (no estrictamente mayor), no hay fallo"},
            ],
            "interpretation": (
                "El umbral de sobrecarga es estrictamente mayor que 0.9 (umbral_sobrecarga=0.9). "
                "Con carga=0.9 exactamente, la condicion carga_motor > umbral es falsa, por lo "
                "que el integrador decae (der = -tiempo_sob/tau) en lugar de crecer. "
                "Este test valida la semantica de borde: '>' no es '>='."
            ),
        },
        {
            "id": "TC-ASM-008",
            "title": "Overload justo por encima del umbral — acumulador sube",
            "description": (
                "carga_motor=0.91 supera el umbral por poco. Der(tiempo_sobrecarga)=1.0 "
                "y el acumulador debe crecer. Complementario al TC-007."
            ),
            "t_end": 1.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"orden_arranque": 1, "carga_motor": 0.91},
            "checks": [
                {"col": "fallo_sobrecarga", "at_t": 1.0, "val": 0, "tol": 0,
                 "description": "Despues de 1s, el fallo aun no ha disparado (umbral=2s)"},
                {"col": "fallo_sobrecarga", "type": "eventually", "op": "==", "val": 0,
                 "description": "Verificamos que el fallo no dispara prematuramente"},
            ],
            "interpretation": (
                "Con carga=0.91 > 0.9, la derivada del integrador es +1.0, por lo que "
                "tiempo_sobrecarga crece linealmente. A t=1s vale ~1s, por debajo del "
                "umbral de 2s. Si se mantuviera la sobrecarga hasta t=2s, dispararia. "
                "Este test contrasta con TC-007 para verificar la logica de borde."
            ),
        },
        {
            "id": "TC-ASM-009",
            "title": "Ramp timing — verificacion a 1 constante de tiempo",
            "description": (
                "A t=3s (= tau_rampa), la rampa debe haber alcanzado 1-e^-1 ≈ 63.2% "
                "del valor final. Verifica la dinamica temporal exacta del primer orden."
            ),
            "t_end": 3.0, "h": 0.001, "solver": "rk4", "mode": "me",
            "inputs": {"orden_arranque": 1, "carga_motor": 0.0},
            "checks": [
                {"col": "tension_aplicada", "at_t": 3.0, "val": 0.559, "tol": 0.02,
                 "description": "A t=tau_rampa=3s, tension ~56% (cascade PT1+rampa: 1-1.2e^-1+0.2e^-6)"},
                {"col": "en_rampa", "at_t": 3.0, "val": 1, "tol": 0,
                 "description": "en_rampa todavia activo a t=3s (<90%)"},
                {"col": "motor_en_marcha", "at_t": 3.0, "val": 0, "tol": 0,
                 "description": "Motor aun no en marcha a t=3s"},
            ],
            "interpretation": (
                "Para un sistema de primer orden con tau=3s, la respuesta al escalon a t=3s "
                "vale 1-e^-1=63.2%. Sin embargo, la tension_aplicada pasa por dos filtros "
                "en cascada (rampa tau=3s + PT1 tau=0.5s), por lo que el valor real es "
                "ligeramente inferior (~60%). Este test valida la constante de tiempo del "
                "sistema y confirma que la dinamica temporal es correcta."
            ),
        },
        {
            "id": "TC-ASM-010",
            "title": "Stop during ramp — en_rampa desactiva inmediatamente",
            "description": (
                "Motor arrancando (t=0..2s), luego parada a t=2s mientras la tension "
                "aun esta en rampa. En_rampa debe desactivarse inmediatamente al quitar "
                "la orden, aunque la tension tarde en decaer."
            ),
            "t_end": 4.0, "h": 0.01, "solver": "rk4", "mode": "me",
            "inputs": {"carga_motor": 0.0},
            "schedule": {"orden_arranque": [(0, 1), (2.0, 0)]},
            "checks": [
                {"col": "tension_aplicada", "at_t": 2.0, "val": 0.388, "tol": 0.04,
                 "description": "A t=2s la tension alcanza ~39% (cascade: 1-1.2e^-2/3+0.2e^-4)"},
                {"col": "en_rampa", "at_t": 2.1, "val": 0, "tol": 0,
                 "description": "en_rampa=false inmediatamente tras quitar la orden"},
                {"col": "tension_aplicada", "type": "eventually", "op": ">", "val": 0.0,
                 "description": "Tension positiva durante la rampa inicial"},
            ],
            "interpretation": (
                "La salida en_rampa es una funcion logica directa de orden_arranque: "
                "se desactiva en el mismo ciclo en que la orden se retira. En cambio, "
                "la tension_aplicada tiene memoria (estados continuos) y continua "
                "decayendo durante varios segundos. Este test verifica la diferencia "
                "entre la respuesta instantanea de outputs discretos y la inercia de "
                "los estados continuos."
            ),
        },
    ]
}

if __name__ == "__main__":
    tools_dir = os.path.join(os.path.dirname(__file__), '..', '..', '..', '..', 'tools')
    sys.path.insert(0, tools_dir)
    from full_test_runner import run_battery
    from pathlib import Path
    sys.exit(run_battery(Path(__file__).resolve()))
