/**
 * fmi2_api.h — Tipos y typedefs de función FMI 2.0 (autocontenido)
 *
 * Consolida fmi2TypesPlatform.h + fmi2FunctionTypes.h del SDK oficial en un
 * único header limpio: sin DllExport, sin #pragma pack, sin macros de prefijo.
 *
 * Compatibilidad: FMI 2.0 Co-Simulation y Model Exchange.
 */

#ifndef FMI2_API_H
#define FMI2_API_H

#include <stddef.h>  /* size_t */

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * Tipos base (fmi2TypesPlatform.h "default")
 * ========================================================================= */

typedef void*           fmi2Component;             /* instancia opaca del modelo    */
typedef void*           fmi2ComponentEnvironment;  /* entorno del simulador         */
typedef void*           fmi2FMUstate;              /* snapshot del estado interno   */
typedef unsigned int    fmi2ValueReference;        /* índice de variable            */
typedef double          fmi2Real;                  /* flotante 64-bit               */
typedef int             fmi2Integer;               /* entero con signo              */
typedef int             fmi2Boolean;               /* booleano (0 / 1)              */
typedef char            fmi2Char;
typedef const fmi2Char* fmi2String;
typedef char            fmi2Byte;

#define fmi2True  1
#define fmi2False 0

/* =========================================================================
 * Status de retorno
 * ========================================================================= */

typedef enum {
    fmi2OK      = 0,  /* éxito                                        */
    fmi2Warning = 1,  /* advertencia — la simulación puede continuar  */
    fmi2Discard = 2,  /* el paso fue descartado (reducir h)           */
    fmi2Error   = 3,  /* error — la instancia ya no es usable         */
    fmi2Fatal   = 4,  /* error fatal — todas las instancias afectadas */
    fmi2Pending = 5,  /* operación asíncrona en progreso              */
} fmi2Status;

/* =========================================================================
 * Tipo de FMU
 * ========================================================================= */

typedef enum {
    fmi2ModelExchange = 0,
    fmi2CoSimulation  = 1,
} fmi2Type;

/* =========================================================================
 * Callbacks — se pasan en fmi2Instantiate
 * ========================================================================= */

typedef void  (*fmi2CallbackLogger)        (fmi2ComponentEnvironment env,
                                            fmi2String instanceName,
                                            fmi2Status status,
                                            fmi2String category,
                                            fmi2String message, ...);
typedef void* (*fmi2CallbackAllocateMemory)(size_t nobj, size_t size);
typedef void  (*fmi2CallbackFreeMemory)    (void *obj);
typedef void  (*fmi2StepFinished)          (fmi2ComponentEnvironment env,
                                            fmi2Status status);

typedef struct {
    fmi2CallbackLogger         logger;
    fmi2CallbackAllocateMemory allocateMemory;
    fmi2CallbackFreeMemory     freeMemory;
    fmi2StepFinished           stepFinished;       /* NULL si síncrono        */
    fmi2ComponentEnvironment   componentEnvironment;
} fmi2CallbackFunctions;

/* =========================================================================
 * EventInfo — resultado de fmi2NewDiscreteStates (Model Exchange)
 * ========================================================================= */

typedef struct {
    fmi2Boolean newDiscreteStatesNeeded;           /* iterar de nuevo         */
    fmi2Boolean terminateSimulation;               /* pedir fin               */
    fmi2Boolean nominalsOfContinuousStatesChanged;
    fmi2Boolean valuesOfContinuousStatesChanged;
    fmi2Boolean nextEventTimeDefined;
    fmi2Real    nextEventTime;
} fmi2EventInfo;

/* =========================================================================
 * Typedefs de función — se usan con dlsym() en host
 *
 * Cada typedef corresponde a una función FMI 2.0. El wrapper carga el
 * puntero con dlsym(handle, "ModelName_fmi2DoStep") etc.
 * ========================================================================= */

/* --- Ciclo de vida -------------------------------------------------------- */
typedef fmi2Component (*fmi2InstantiateTYPE)(
    fmi2String instanceName, fmi2Type fmuType,
    fmi2String fmuGUID, fmi2String fmuResourceLocation,
    const fmi2CallbackFunctions *functions,
    fmi2Boolean visible, fmi2Boolean loggingOn);

typedef fmi2Status (*fmi2SetupExperimentTYPE)(
    fmi2Component c,
    fmi2Boolean toleranceDefined, fmi2Real tolerance,
    fmi2Real startTime,
    fmi2Boolean stopTimeDefined, fmi2Real stopTime);

typedef fmi2Status (*fmi2EnterInitializationModeTYPE)(fmi2Component c);
typedef fmi2Status (*fmi2ExitInitializationModeTYPE) (fmi2Component c);
typedef fmi2Status (*fmi2TerminateTYPE)              (fmi2Component c);
typedef void       (*fmi2FreeInstanceTYPE)           (fmi2Component c);
typedef fmi2Status (*fmi2ResetTYPE)                  (fmi2Component c);

/* --- Co-Simulation -------------------------------------------------------- */
typedef fmi2Status (*fmi2DoStepTYPE)(
    fmi2Component c,
    fmi2Real currentCommunicationPoint,
    fmi2Real communicationStepSize,
    fmi2Boolean noSetFMUStatePriorToCurrentPoint);

typedef fmi2Status (*fmi2CancelStepTYPE)(fmi2Component c);

/* --- Model Exchange ------------------------------------------------------- */
typedef fmi2Status (*fmi2SetTimeTYPE)                (fmi2Component c, fmi2Real time);
typedef fmi2Status (*fmi2SetContinuousStatesTYPE)    (fmi2Component c, const fmi2Real x[], size_t nx);
typedef fmi2Status (*fmi2GetDerivativesTYPE)         (fmi2Component c, fmi2Real dx[], size_t nx);
typedef fmi2Status (*fmi2GetContinuousStatesTYPE)    (fmi2Component c, fmi2Real x[], size_t nx);
typedef fmi2Status (*fmi2GetEventIndicatorsTYPE)     (fmi2Component c, fmi2Real z[], size_t ni);
typedef fmi2Status (*fmi2EnterEventModeTYPE)         (fmi2Component c);
typedef fmi2Status (*fmi2EnterContinuousTimeModeTYPE)(fmi2Component c);
typedef fmi2Status (*fmi2NewDiscreteStatesTYPE)      (fmi2Component c, fmi2EventInfo *eventInfo);
typedef fmi2Status (*fmi2CompletedIntegratorStepTYPE)(
    fmi2Component c,
    fmi2Boolean noSetFMUStatePriorToCurrentPoint,
    fmi2Boolean *enterEventMode,
    fmi2Boolean *terminateSimulation);

/* --- Get/Set variables ---------------------------------------------------- */
typedef fmi2Status (*fmi2GetRealTYPE)   (fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Real    v[]);
typedef fmi2Status (*fmi2SetRealTYPE)   (fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Real    v[]);
typedef fmi2Status (*fmi2GetIntegerTYPE)(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Integer v[]);
typedef fmi2Status (*fmi2SetIntegerTYPE)(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer v[]);
typedef fmi2Status (*fmi2GetBooleanTYPE)(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Boolean v[]);
typedef fmi2Status (*fmi2SetBooleanTYPE)(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Boolean v[]);
typedef fmi2Status (*fmi2GetStringTYPE) (fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2String  v[]);
typedef fmi2Status (*fmi2SetStringTYPE) (fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2String  v[]);

/* --- Estado serializable (checkpointing) ---------------------------------- */
typedef fmi2Status (*fmi2GetFMUstateTYPE)            (fmi2Component c, fmi2FMUstate *state);
typedef fmi2Status (*fmi2SetFMUstateTYPE)            (fmi2Component c, fmi2FMUstate  state);
typedef fmi2Status (*fmi2FreeFMUstateTYPE)           (fmi2Component c, fmi2FMUstate *state);

#ifdef __cplusplus
}
#endif

#endif /* FMI2_API_H */
