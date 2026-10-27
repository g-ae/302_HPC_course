# Exercice 3

Dans cet exercice, vous allez modifier votre premier programme parallèle afin que les processus affichent leur message dans l’ordre croissant de leur rang. Au lieu de **MPI_Barrier**, vous allez utiliser **MPI_Send** et **MPI_Recv**.

**MPI_Recv** est bloquant : un processus qui l’appelle attend jusqu’à ce qu’il ait reçu le message attendu. Utilisez cette propriété pour qu’un processus n’affiche son message qu’après avoir reçu l’autorisation du processus précédent, puis transmette à son tour l’autorisation au processus suivant.

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

Lancez votre programme plusieurs fois. L’ordre d’affichage est-il maintenant garanti ? Comparez avec l’exercice 2.

- Je pense qu'on est dans le même état que l'exercice 2, où le problème c'est la synchronisation des `stdout`. Mais pour le peu de tests effectués, aucun problème n'a été aperçu.