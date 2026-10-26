# Exercice 4

Dans cet exercice, vous allez écrire un programme en C++ qui calcule le produit scalaire de deux vecteurs de grande taille. Chaque vecteur doit être rempli avec des valeurs aléatoires. Le produit scalaire se calcule en multipliant les éléments correspondants des deux vecteurs, puis en additionnant tous les résultats obtenus. Le programme doit afficher le résultat du produit scalaire.

L’objectif est de tester les performances du programme en fonction de la taille des vecteurs. Vous devrez mesurer le temps d’exécution pour différentes tailles : 1 million, 10 millions, 50 millions et 100 millions d’éléments. Chronométrez uniquement le calcul du produit scalaire, sans inclure le remplissage des vecteurs, et affichez le résultat en millisecondes.

La taille des vecteurs ne doit pas être écrite en dur dans le code. Vous pouvez soit la passer en argument lors du lancement du programme à l’aide de **argc** et **argv**, comme dans l’exercice 3, soit faire une boucle sur les quatre tailles dans votre programme. Si vous passez la taille en argument, pensez à convertir la chaîne de caractères en nombre (par exemple avec **stoi**).

Exemple de lancement avec un argument :

```
./run 10000000
```

Quelle est la complexité de votre algorithme ? Les temps mesurés sont-ils cohérents avec cette complexité ?
- Première version O(3N), deuxième : O(N)
- A peu près. Les 

Attention au type de la variable qui contient le résultat : quelle est la valeur maximale qu’elle peut atteindre ?
- Il faut que la variable qui contient le résultat soit un Int64 (`long int`)

Performance première version avec tableaux :
- 1M: 15 ms
- 10M: segfault // 

Performance deuxième version qui ajoute directement dans la variable :
- 1M: 914ms - 0.9 s
- 10M: 4500ms - 4.5 s
- 50M: 18'582 ms - 18.6 s
- 100M: 36'002 ms - 36 s

Pour info, la deuxième version contient aussi tout le calcul des valeurs aléatoires, ce qui peut être la cause du temps que ça prend en plus.

Refait programme en utilisant des `vector<int>`, performance :
- 1M: 42ms
- 10M: 223ms
- 50M: 796ms
- 100M: 1670 ms