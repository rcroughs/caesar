#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

print_banner() {
  echo -e "${BLUE}╔════════════════════════════════════════════╗${NC}"
  echo -e "${BLUE}║${YELLOW} $1 ${BLUE}     ║${NC}"
  echo -e "${BLUE}╚════════════════════════════════════════════╝${NC}"
}

print_step() {
  echo -e "\n${CYAN}[ÉTAPE $1]${NC} $2"
}

if ! command -v bc &>/dev/null; then
  echo -e "${RED}[ERROR]${NC} La commande 'bc' n'est pas installée."
  echo -e "Pour l'installer:"
  echo -e "Sur Debian/Ubuntu: ${GREEN}sudo apt-get install bc${NC}"
  echo -e "Sur Fedora: ${GREEN}sudo dnf install bc${NC}"
  echo -e "Sur macOS avec Homebrew: ${GREEN}brew install bc${NC}"
  exit 1
fi

if [ ! -f "./encode" ] || [ ! -f "./decode" ]; then
  echo -e "${YELLOW}[WARNING]${NC} Les fichiers ne sont pas compilés. Tentative d'exécution du Makefile"
  if [ -f "./Makefile" ]; then
    make
  else
    echo -e "${RED}[ERROR]${NC} Le Makefile est introuvable. Veuillez compiler les fichiers manuellement."
    exit 1
  fi
fi

clear
print_banner "Démonstration du Chiffrement de César"

print_step "1" "Entrez le texte à chiffrer"
printf "${YELLOW}→${NC} "
read -r texte_original

offset=$((1 + RANDOM % 25))

print_step "2" "Chiffrement du texte avec un offset aléatoire"
echo -e "Offset choisi aléatoirement: ${GREEN}$offset${NC}"
texte_chiffre=$(./encode "$texte_original" "$offset")
echo -e "Texte chiffré: ${GREEN}$texte_chiffre${NC}"

printf "\nAppuyez sur Entrée pour lancer le déchiffrement..."
read -r

print_step "3" "Tentative de déchiffrement (test de tous les offsets)"
echo -e "Analyse de tous les offsets possibles:\n"

DEBUT=$(date +%s.%N)

./decode "$texte_chiffre" | while IFS= read -r line; do
  if [[ $line == *"$texte_original"* ]]; then
    echo -e "${GREEN}$line ← TROUVÉ !${NC}"
  else
    echo "$line"
  fi
done

FIN=$(date +%s.%N)
TEMPS=$(echo "$FIN - $DEBUT" | bc)
TEMPS_MS=$(echo "$TEMPS * 1000" | bc)

print_step "4" "Conclusion"
echo -e "L'offset original était: ${GREEN}$offset${NC}"
echo -e "Temps nécessaire pour tester tous les offsets: ${GREEN}${TEMPS_MS%.*} ms${NC}"
echo -e "\n${YELLOW}Ce qui démontre que même si l'offset est inconnu,${NC}"
echo -e "${YELLOW}il est facile de retrouver le message original en testant${NC}"
echo -e "${YELLOW}les 25 possibilités de déchiffrement.${NC}"

echo -e "\n${BLUE}Fin de la démonstration${NC}"
