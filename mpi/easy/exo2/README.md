# Exercice 2

Dans cet exercice, vous allez modifier votre premier programme parallèle afin que les processus affichent leur message dans l’ordre croissant de leur rang. Pour cela, vous allez utiliser **MPI_Barrier**.

**MPI_Barrier** est une opération collective : chaque processus qui l’appelle est bloqué jusqu’à ce que tous les processus l’aient appelée à leur tour. Tous les processus doivent donc l’appeler le même nombre de fois.

Exemple de résultat avec 6 processus :

```
Number of processors: 6
Processor 0 - Hello World
Processor 1 - Hello World
Processor 2 - Hello World
Processor 3 - Hello World
Processor 4 - Hello World
Processor 5 - Hello World
```

## Question

Lancez votre programme plusieurs fois. Est-ce que **MPI_Barrier** permet dans tous les cas d’afficher les messages dans l’ordre ? Pourquoi ?
- Arrivé dans le premier exercice, le nombre de processeurs s'est affiché en plein milieu du reste des messages. MPI_Barrier ne permet pas d'afficher tout dans l'ordre dans TOUS les cas.
- Chaque noeud MPI a son propre `stdout`, ensuite MPI les synchronise tous avec celui du hôte. Vu que c'est des opérations tellement rapides, ça peut arriver qu'une fraction de seconde sépare plusieurs messages, ce qui nous sort un affichage incorrect. Ce n'est que purement visuel, le fonctionnel est là.