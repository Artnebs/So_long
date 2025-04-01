#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

BIN="./so_long"
MAPS_DIR="./maps_test_so_long"
LOGS_DIR="./logs"

MAPS=("valid.ber" "no_exit.ber" "no_player.ber" "no_collectible.ber" "open_map.ber" "invalid_char.ber")

mkdir -p "$LOGS_DIR"

if [ ! -x "$BIN" ]; then
    echo -e "${RED}❌ Erreur : $BIN introuvable ou non exécutable${NC}"
    exit 1
fi

echo "🚀 Lancement des tests avec Valgrind (1 log filtré par map)..."
echo

for map in "${MAPS[@]}"; do
    MAP_PATH="$MAPS_DIR/$map"
    VALGRIND_LOG="${LOGS_DIR}/${map}.log"
    FILTERED_LOG="${LOGS_DIR}/${map}.filtered.log"

    if [ ! -f "$MAP_PATH" ]; then
        echo -e "${RED}❌ Map manquante : $map${NC}"
        continue
    fi

    echo -e "🧪 Test de ${map}..."

    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        --log-file="$VALGRIND_LOG" "$BIN" "$MAP_PATH" > /dev/null 2>&1

    grep -v -E "libX11|libxcb|XWindow|XOpenDisplay|XReadEvents|XSend|writev|vgpreload|libc|_X" "$VALGRIND_LOG" > "$FILTERED_LOG"

    # Vérifie si fuite mémoire réellement présente
    DEF_LOST=$(grep "definitely lost: [^0]" "$FILTERED_LOG")

    if [ -z "$DEF_LOST" ]; then
        echo -e "${GREEN}✅ ${map} : aucune fuite mémoire dans ton code${NC}"
    else
        echo -e "${RED}🚨 ${map} : fuite mémoire détectée dans ton code ! Voir : ${FILTERED_LOG}${NC}"
        grep "definitely lost" "$FILTERED_LOG"
    fi

    echo
done

echo "📁 Tous les logs sont dans le dossier : ${LOGS_DIR}/"
