# inf3135-automne2021-tp3

## Description

Ceci est un programme qui a pour but de créer un menu de restaurant à partir d'un fichier texte
fournit par l'utilisateur. Le fichier texte sera analyser ligne par ligne. L'utilisateur doit entrer 
le nom de la recette ainsi que toutes ses catégories entre crochets. Il sera aussi possible pour l'utilisateur de faire une recherche de recette
de deux façons: Une recherche par catégorie et une recherche par catégorie avec un mot clé pour la recette

## Auteur

Jonathan Labelle (LABJ28039006)

## Fonctionnement

Ce programme doit être lancé lors par la ligne de commande.

Pour être utilisable, il doit d'abord être compilé avec une de ces deux comamndes:

```sh
make
make build
```
Pour exécuter le programme, il sera nécessaire de fournir un fichier d'entrer pour les recettes d'une de ces
deux façons:
```sh
./main exemple.txt
make run ARGS="exemple.txt"
```
Il est aussi possible de générer disverses statiques lors que l'éxécution du programme. À noter que le fichier de
statistiques sera écraser s'il existe dejà. Pour exécuter les statistiques à la fin normale du programme, il faut utiliser
une de ces deux commandes 

```sh
./main exemple.txt -S fichiersorti.txt
make run ARGS="exemple.txt -S fichiersorti.txt"
```

## Format fichier d'entrée

Le fichier d'entrée doit être de format .txt et doit contenir une recette par ligne ainsi qu'un nombre illimité de catégories à laquelle elle peut appartenir.
Une ligne mal formée ne sera pas ajouté au programme, mais les autres lignes du fichier le seront si elles sont bien formées.

```sh
PokeBol vege [vegetarien][asiatique]
Omelette au saumon fume [dejeuner][poisson]
Plateau de legumes [vegetarien]
Fondue au fromage [vegetarien -- ligne ignoree
```

