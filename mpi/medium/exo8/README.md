# Exercice 8

Dans cet exercice, vous allez reprendre le produit scalaire parallèle de l’exercice 7 et étudier comment ses performances évoluent avec le nombre de processus. On distingue deux façons de mesurer cette évolution :

- **Strong scaling** : la taille **totale** du problème est fixe et on augmente le nombre de processus. Chaque processus a donc de moins en moins de travail. Idéalement, le temps est divisé par $p$ lorsqu’on utilise $p$ processus.
- **Weak scaling** : la taille du problème **par processus** est fixe et on augmente le nombre de processus. La taille totale augmente donc avec $p$. Idéalement, le temps reste constant.

## Programme

Modifiez votre programme de l’exercice 7 pour qu’il prenne deux arguments : le mode (`strong` ou `weak`) et une taille. En mode `strong`, la taille est la taille totale des vecteurs ; en mode `weak`, c’est la taille par processus. Exemples de lancement :

```
mpirun -np 4 ./run strong 160000000
mpirun -np 4 ./run weak 10000000
```

En mode `weak`, la taille totale des vecteurs vaut donc la taille donnée multipliée par le nombre de processus.

Pour mesurer le temps, utilisez **MPI_Wtime**, qui renvoie le temps écoulé en secondes. Le chronomètre doit inclure le calcul local et le **MPI_Reduce** final. Pour obtenir une mesure fiable :

- appelez **MPI_Barrier** juste avant de démarrer le chronomètre ;
- le temps d’une exécution parallèle est celui du processus le plus lent : récupérez le maximum des temps de tous les processus sur le processus 0 avec **MPI_Reduce** et l’opération **MPI_MAX** ;
- répétez la mesure plusieurs fois (par exemple 10) et gardez la médiane.

Performances avec array_size=1'073'741'824 (32⁶):
- baseline (1 proc): 3318ms
- strong:
    - 2: 1562ms
    - 4: 761ms
    - 8: 389ms
    - 16: 227ms


## Questions

1. Le speedup en strong scaling est-il proche de l’idéal ? À partir de combien de processus l’efficacité chute-t-elle nettement ?
2. Comparez l’efficacité en strong et en weak scaling. Laquelle se maintient le mieux lorsque $p$ augmente ? Pourquoi ?
3. D’après la loi d’Amdahl, si une fraction $f$ du programme ne peut pas être parallélisée, le speedup maximal vaut $\dfrac{1}{f}$. Quelles parties de votre programme ne sont pas parallélisées ?
