# Exercice 6

Dans cet exercice, vous disposez de 17 fichiers texte contenant les données RGB de 17 images de taille $1024 \times 1024$. Ces fichiers se trouvent dans le dossier **Pictures** et se terminent par **_RGB.txt**. Chaque ligne d’un fichier représente les valeurs r, g et b d’un pixel de l’image correspondante, séparées par des virgules et comprises entre 0 et 255. Par exemple :

```
16,0,10
11,0,7
15,2,12
```

Votre objectif est d’écrire un programme en C++ qui lit ces fichiers et calcule la valeur moyenne de r, g et b pour chaque image. Le programme doit afficher, pour chaque image, le nom du fichier et les trois valeurs moyennes.

Avant de traiter les données, le programme doit vérifier que chaque fichier s’ouvre correctement. Si un fichier ne peut pas être ouvert, le programme doit afficher un message d’erreur avec **cerr**, ignorer ce fichier et continuer avec les suivants.

Enfin, mesurez le temps total d’exécution du programme avec la bibliothèque **chrono** et affichez-le en millisecondes.

- Exécution du programme total en 5 ms.