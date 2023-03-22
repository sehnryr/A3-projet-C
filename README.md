# Projet A3 - C

Ce projet concerne la partie C du projet de 3ème année de l'ISEN Ouest.
Il a pour but de simuler la supervision et la regulation de la temperature
d'une habitation.

## Table des matières

- [Projet A3 - C](#projet-a3---c)
  - [Table des matières](#table-des-matières)
  - [Prérequis](#prérequis)
  - [Utilisation](#utilisation)
  - [Problèmes connus](#problèmes-connus)

## Prérequis

Pour pouvoir utiliser ce projet, il est nécessaire d'avoir les outils suivants:
- `make`
- `gcc`
- `python3`
- `tkinter`

De plus, l'interface graphique python `gestiontemp.py` nécessite les dependances
indiquées dans le fichier `Pipfile`. Il est possible de les installer avec la
commande:
```bash
pipenv install
pipenv shell # Pour activer l'environnement virtuel
```

Il est également possible d'installer les dependances python manuellement avec
`pip` en lisant la section `[packages]` du fichier `Pipfile`.

## Utilisation

Le projet est composé de 3 modes:
- Simples autotests
- Simulation de l'habitation
- Communication avec une STM32

Les parties simulation et communication nécessitent l'utilisation de
l'interface graphique python `gestiontemp.py`.

La partie autotests permet de tester les fonctions de bases du projet.
```bash
make autotests
./build/test_autotests
```

La partie simulation permet de simuler l'habitation et de tester les fonctions
de supervision et de regulation.
```bash
make simulation
./build/test_sim
```

La partie communication permet de communiquer avec une STM32 pour tester les
fonctions de supervision et de regulation.
```bash
make usb
./build/test_usb
```

Il est également possible de supprimer les fichiers temporaires et les fichiers
objets générés par la compilation avec la commande:
```bash
make clean
```

## Problèmes connus

Sous Linux, il est possible que la communication USB ne fonctionne pas 
(erreur 3 lors de l'ouverture du port). Le problème est lié au fait que lors de
la connexion d'un périphérique FTDI, la plupart du temps, le driver `ftdi_sio`
est chargé. Mais ce driver ne permet pas à la librairie `D2XX` de communiquer
avec le périphérique.

Une solution est d'ajouter les règles udev suivantes:
```bash
# /etc/udev/rules.d/98-ftdi.rules
ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6015", ATTRS{product}=="PRODUCT_NAME", \
RUN+="/bin/sh -c 'echo $kernel > /sys/bus/usb/drivers/ftdi_sio/unbind'"
```
```bash
# /etc/udev/rules.d/99-ftdi.rules
ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6015", MODE="0666"
```

En modifiant les valeurs `idVendor`, `idProduct` et `product` en fonction du
périphérique utilisé. Il est possible de trouver ces valeurs avec la commande:
```bash
lsusb -v 2> /dev/null | grep -a "Bus ... Device ...:\|idVendor\|idProduct\|iProduct"
```

Pour recharger les règles udev, il faut exécuter la commande:
```bash
sudo udevadm trigger
```

Sources:
- https://stackoverflow.com/a/43514662/12619942
- https://www.elektormagazine.de/news/ftdi-d2xx-and-linux-overcoming-the-big-problem-
