# Exercice 2

Dans cet exercice, vous allez écrire un programme en C++ qui demande à l’utilisateur d’entrer un nombre à l’aide de **cin**. Une fois le nombre saisi, le programme devra calculer et écrire les 100 000 premiers multiples de ce nombre dans un fichier texte. Pour cela, vous utiliserez **ofstream** pour écrire dans le fichier, et vous testerez deux façons de terminer chaque ligne : avec **"\n"** et avec **endl**.

Comme dans l’exercice 1, vous mesurerez le temps d’exécution avec la bibliothèque **chrono**. Chronométrez uniquement l’écriture du fichier (de son ouverture à sa fermeture), sans inclure la saisie de l’utilisateur, et affichez le résultat en millisecondes à l’aide de **duration_cast\<milliseconds\>**.

Une fois le fichier généré, vous devrez observer et comparer les performances du programme selon la méthode utilisée pour terminer les lignes. Est-ce que le temps d’exécution change ? Le contenu du fichier est-il différent ? Que fait **endl** de plus que **"\n"** ? À vous de tester et d’analyser les résultats.

Performance :
- \n   : 38  ms
- endl : 579 ms

Les données qu'on veut envoyer dans le fichier ne sont pas envoyées directement quand on fait un `out << "data"`. Ces modifications restent dans un buffer et les données sont uniquement envoyées quand c'est demandé ou quand le buffer est plein. Ce qui fait la différence est que `endl` force toutes les données qui sont buffered à s'envoyer, donc le programme va aller réellement écrire dans le fichier à chaque fois passage dans la boucle, alors qu'avec `\n`, on écrit moins de fois dans le dossier mais plus d'infos à la fois, ce qui le rend plus rapide.

Le contenu du fichier reste le même dans les deux cas par contre.