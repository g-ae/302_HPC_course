# Exercice 5

Dans cet exercice, vous allez écrire un programme en C++ qui calcule le produit matriciel de deux matrices carrées de grande taille. Chaque matrice doit être remplie avec des valeurs aléatoires.

Chaque matrice doit être stockée sous la forme d’un tableau à une dimension et non d’un tableau à deux dimensions. Les lignes de la matrice sont rangées les unes à la suite des autres : pour une matrice de taille $n \times m$, l’élément situé à la ligne $i$ et à la colonne $j$ se trouve à l’indice $i \times m + j$ du tableau.

L’objectif est de tester les performances du programme en fonction de la taille des matrices. Vous devrez mesurer le temps d’exécution pour différentes tailles : $500 \times 500$, $1000 \times 1000$ et $2000 \times 2000$. Chronométrez uniquement le calcul du produit matriciel, sans inclure l’allocation et le remplissage des matrices, et affichez le temps mesuré en millisecondes.

La taille des matrices ne doit pas être écrite en dur dans le code. Vous devez la passer en argument lors du lancement du programme à l’aide de **argc** et **argv**, comme dans l’exercice 3.

Exemple de lancement :

```
./run 1000
```

Quelle est la complexité de votre algorithme ? Les temps mesurés sont-ils cohérents avec cette complexité ?

Performance:
- 500: 1.7 s
- 1000: 7.8 s
- 2000: 78 s

Complexité : O(N³) -> naïf