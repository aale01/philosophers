#!/bin/bash

# Uso:
# ./check_meals.sh output.txt NUM_PHILO REQUIRED_MEALS

OUTPUT_FILE="$1"
NUM_PHILO="$2"
REQUIRED_MEALS="$3"

if [ $# -ne 3 ]; then
    echo "Uso: $0 output.txt NUM_PHILO REQUIRED_MEALS"
    exit 1
fi

if [ ! -f "$OUTPUT_FILE" ]; then
    echo "Errore: file $OUTPUT_FILE non trovato"
    exit 1
fi

echo "Controllo pasti..."
echo "Filosofi: $NUM_PHILO"
echo "Pasti richiesti: $REQUIRED_MEALS"
echo "-----------------------------"

for ((i=1; i<=NUM_PHILO; i++)); do
    # Conta quante volte il filosofo i ha mangiato
    COUNT=$(grep -E " $i is eating" "$OUTPUT_FILE" | wc -l)

    if [ "$COUNT" -ge "$REQUIRED_MEALS" ]; then
        echo "Filosofo $i ✅ OK ($COUNT pasti)"
    else
        echo "Filosofo $i ❌ ERRORE ($COUNT pasti)"
    fi
done