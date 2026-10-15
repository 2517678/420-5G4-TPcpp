# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de donner chemin vers le repertoire data avec l'application `bibliotheque -d <chemin verrs data>`

---
<br/>
<br/>
<br/>

# Dominic Doyon

les fonctionnalit/s que j'ai choisi sont :
- **UX :** Afficher le nom d’utilisateur plutôt que l’id dans l’affichage des livres.
- **Gestion des Donnees :** Tri des résultats par titre, auteur pour l’affichage (utilisation de la fonction de tri de la STL).

## Question 1 : C++

> Expliquez en détails une fonctionnalité / notion dans le code que ne nous avons pas ou peu vu en cours. Montrez ici l’exemple sorti du code du projet.

```cpp
void Book::fromFileFormat(const string& line) {
    vector<string> parts;

    stringstream ss(line);
    string item;
    while(getline(ss, item, '|')) {
        parts.push_back(item);
    }

    // assert(parts.size() >= 4);

    title = parts[0];
    author = parts[1];
    isbn = parts[2];
    isAvailable = stoi(parts[3]); // 1 = true, 0 = false
    if(!isAvailable) {
        // assert(parts.size() == 5);
        borrowerId = parts[4];
    } else {
        borrowerId = "";
    }
}
```

Je n'ai pas beaucoup vu en classe comment séparer une ligne de texte à partir d'un séparateur. Contrairement à Java, où on peut utiliser `split("|")` pour séparer une chaîne de caractères à chaque `|`, en C++, une façon simple de faire cela est de mettre la chaîne de caractères dans un `stringstream` et d'utiliser `getline()` avec un séparateur dans le paramètre `__delim`.

Dans cet exemple, on crée un `stringstream` à partir de la ligne de texte, puis on utilise `getline()` pour extraire chaque partie jusqu'au prochain séparateur `|`. Chaque partie extraite est ensuite ajoutée à un `vector<string>`, ce qui permet d'accéder facilement aux différentes informations du livre par leur position dans le vecteur.

Cette méthode est utile pour lire les données d'un fichier et les convertir en informations utilisables par le programme. Par exemple, après avoir séparé les différentes parties, on peut récupérer le titre, l'auteur, l'ISBN et la disponibilité du livre.

*Je ne suis pas certain de tout ce qui a été couvert en classe, puisque j'ai manqué plusieurs cours. J'ai donc choisi un concept que je ne me souviens pas avoir beaucoup vu et qui est utilisé dans le projet.*

## Question 2 : Options de développement possible

> Proposez une solution plus adaptée pour la gestion de bibliothèque et faisant appel éventuellement à une technologie autre que le C++, et expliquez comment vous interfaceriez ça avec le C++. Quelle solution technologique utiliseriez vous ? Pensez au futur de cette bibliothèque à Alexandrie qui pourrait éventuellement contenir des millions de livres.

Je pense que les vecteurs ne sont pas nécessairement la meilleure solution à long terme pour gérer une bibliothèque avec des millions de livres. Par exemple, rechercher un livre dans un vecteur peut prendre beaucoup de temps si on doit parcourir tous les livres un par un. Ajouter un livre à la fin du vecteur est généralement rapide, mais certaines opérations, comme insérer un livre à une position précise, peuvent devenir plus coûteuses.

De plus, avec notre solution actuelle, les données sont conservées dans des fichiers sur un seul ordinateur, et chaque instance du programme charge ses propres données en mémoire. Si plusieurs employés utilisaient le programme sur différents ordinateurs, ils n'auraient pas nécessairement accès aux mêmes données à jour.

Je proposerais donc d'utiliser une base de données centralisée sur un serveur. Plusieurs ordinateurs pourraient s'y connecter pour consulter et modifier les informations de la bibliothèque. Une base de données est conçue pour gérer de grandes quantités de données, effectuer des recherches efficaces grâce à des index et permettre à plusieurs utilisateurs de travailler avec les mêmes données.

Pour intégrer cette solution à notre programme C++, on pourrait utiliser une bibliothèque qui permet de communiquer avec la base de données. Par exemple, MySQL possède son propre connecteur C++ (MySQL Connector/C++), qui permet au programme d'envoyer des requêtes à la base de données et de récupérer les résultats. Cela permettrait de conserver la logique du programme en C++ tout en confiant la gestion des données à un système conçu pour cela.