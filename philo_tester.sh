#!/bin/bash

set -o pipefail

if [ $# -lt 4 ]; then
    echo "Uso:"
    echo "  $0 ./philo arg1 arg2 arg3 [arg4 [arg5 ...]]"
    exit 1
fi

EXEC="$1"
shift
ARGS=("$@")
NUM_ARGS=$#

SUCCESS=0
FAILURE=1

RESULT=$SUCCESS
GENERAL_RESULT=$SUCCESS

# Chiedi quante volte ripetere
read -r -p "Quante volte vuoi ripetere il test? " LOOPS
if ! [[ "$LOOPS" =~ ^[0-9]+$ ]] || [ "$LOOPS" -lt 1 ]; then
    echo "Errore: LOOPS deve essere un intero >= 1"
    exit 1
fi

# Timeout per il caso 4 argomenti
if [ "$NUM_ARGS" -eq 4 ]; then
    read -r -p "Tempo massimo di riferimento (secondi)? " MAX_TIME
    if ! [[ "$MAX_TIME" =~ ^[0-9]+$ ]] || [ "$MAX_TIME" -lt 1 ]; then
        echo "Errore: MAX_TIME deve essere un intero >= 1"
        exit 1
    fi
fi

echo "==============================="
echo "Eseguibile: $EXEC"
echo "Argomenti: ${ARGS[*]}"
echo "Ripetizioni: $LOOPS"
echo "==============================="

if [ $NUM_ARGS -eq 4 ]; then
    # --- Modalità “morte predittiva” ---
    ALWAYS_DIED=1
    NEVER_DIED=1

    counter_pid=""
    cleanup_counter() {
        if [ -n "$counter_pid" ] && kill -0 "$counter_pid" 2>/dev/null; then
            kill "$counter_pid" 2>/dev/null
            wait "$counter_pid" 2>/dev/null
        fi
        counter_pid=""
    }
    trap cleanup_counter EXIT INT TERM

    for ((run=1; run<=LOOPS; run++)); do
        printf "Run %d: " "$run"

        # loop in background per stampare i secondi trascorsi
        (
            seconds_passed=0
            while :; do
                printf "\rRun %d: Tempo trascorso: %ss   " "$run" "$seconds_passed"
                sleep 1
                seconds_passed=$((seconds_passed+1))
            done
        ) &
        counter_pid=$!

        # lancio con timeout
        OUTPUT=$(timeout "$MAX_TIME"s "$EXEC" "${ARGS[@]}" 2>&1)
        EXIT_STATUS=$?

        cleanup_counter

        printf "\r\033[KRun %d: " "$run"
        # controlla se philo è terminato correttamente o è stato ucciso
        if [ "$EXIT_STATUS" -eq 124 ]; then
            echo "✅ Nessuno è morto"
            NEVER_DIED=0
        elif [ "$EXIT_STATUS" -eq 125 ]; then
            echo "❌ ERRORE - timeout ha fallito (argomenti invalidi o errore interno)"
            NEVER_DIED=0
        elif [ "$EXIT_STATUS" -eq 126 ] || [ "$EXIT_STATUS" -eq 127 ]; then
            echo "❌ ERRORE - eseguibile non trovato/non eseguibile"
            NEVER_DIED=0
        elif printf "%s" "$OUTPUT" | grep -q "died"; then
            echo "⚠️ Un filosofo è morto"
            NEVER_DIED=0
        else
            echo "✅ Nessuno è morto"
            ALWAYS_DIED=0
        fi
    done

    echo "-----------------------------"
    if [ $ALWAYS_DIED -eq 1 ]; then
        echo "🎉 In tutti i run, almeno un filosofo è sempre morto"
    elif [ $NEVER_DIED -eq 1 ]; then
        echo "🎉 In tutti i run, nessuno è mai morto"
    else
        echo "⚠️ Alcuni run hanno visto morti, altri no"
    fi

else
    # --- Modalità standard (5 o più argomenti) ---
    NUM_PHILO="${ARGS[0]}"
    REQUIRED_MEALS="${ARGS[4]}"

    for ((run=1; run<=LOOPS; run++)); do
        echo -n "Run $run: "

        OUTPUT=$("$EXEC" "${ARGS[@]}")

        RESULT=$SUCCESS

        # Controllo morti
        if echo "$OUTPUT" | grep -q "died"; then
            echo "❌ FAIL - Un filosofo è morto"
            RESULT=$FAILURE
#            exit 1
        fi

        # Controllo numero pasti
        for ((i=1; i<=NUM_PHILO; i++)); do
            COUNT=$(echo "$OUTPUT" | awk -v id="$i" '$2 == id && $3 == "is" && $4 == "eating"' | wc -l)
            if [ "$COUNT" -lt "$REQUIRED_MEALS" ]; then
                echo "❌ FAIL - Filosofo $i ha mangiato $COUNT volte"
                RESULT=$FAILURE
#                exit 1
            fi
        done

        if [ "$RESULT" -ne $FAILURE ]; then
          echo "✅ SUCCESS"
        else
          GENERAL_RESULT=$FAILURE
        fi
    done

    echo "==============================="
    if [ "$GENERAL_RESULT" -ne $FAILURE ]; then
      echo "🎉 Tutti i test sono passati!"
    else
      echo "❌ Qualche test non e\` passato!"
    fi
fi