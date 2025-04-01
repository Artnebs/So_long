#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

BIN="./so_long"
MAPS_DIR="./maps_test_so_long"
VALGRIND_LOG="valgrind.log"

MAPS=("valid.ber" "no_exit.ber" "no_player.ber" "no_collectible.ber" "open_map.ber" "invalid_char.ber")

if [ ! -x "$BIN" ]; then
    echo -e "${RED}Erreur : $BIN introuvable ou non exécutable${NC}"
    exit 1
fi

echo "🚀 Lancement des tests fonctionnels et mémoire avec Valgrind..."
echo

for map in "${MAPS[@]}"; do
    MAP_PATH="$MAPS_DIR/$map"
    
    if [ ! -f "$MAP_PATH" ]; then
        echo -e "${RED}❌ Map manquante : $map${NC}"
        continue
    fi

    echo -e "🧪 Test de ${map}..."

    valgrind --leak-check=full --show-leak-kinds=all \
        --log-file=$VALGRIND_LOG $BIN "$MAP_PATH" > /dev/null 2>&1

    if grep -q "definitely lost: 0 bytes" $VALGRIND_LOG; then
        echo -e "${GREEN}✅ Aucune fuite mémoire détectée${NC}"
    else
        echo -e "${RED}🚨 Fuite mémoire détectée ! Voir ${VALGRIND_LOG}${NC}"
        grep "definitely lost" $VALGRIND_LOG
    fi

    echo
done

rm -f $VALGRIND_LOG
echo "🧹 Tests terminés."
