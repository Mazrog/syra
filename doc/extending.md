# Création de modules réseaux
---
*Maxime Cabanal et Simon Chaize*

### Notion de module
Dans l'architecture telle que nous l'avons imaginé, un noeud du réseau assure sa compatibilité avec un protocole en intégrant le module qui lui est associé.

![Traitement des données](img/cheminement.png)

Ainsi, créer un module pour un protocole PLOP revient à créer :
```
src
    network
        adapters
            plop_adapter.hpp

        subifs
            plop_subif.hpp

    requests
        plop_request.hpp
        plop_request.cpp
```

Viennent ensuite quelques détails concernant le comportement des noeuds vis-à-vis des requêtes :

### Comportement

Grandement influencé par le module `express` de l'univers `NodeJS`, nous avons développé ceci pour être le plus simple d'accès.

Un comportement est défini par une fonction ne retournant rien et prenant deux arguments : la requête d'entrée et la requête réponse :

```cpp
using Behaviour = std::function<void(const Request *, Request *)>;
```

Tous ces comportements sont rangés dans un dictionnaire, indexés par un point d'entrée sous la forme d'une chaîne de caractères :
```cpp
using ApiTree = std::map<std::string, Behaviour>;
```

#### Mis en place des comportements

Dans le fichier `router.hpp`, ajouter une spécialisation de la fonction `operator()` (ici pour une classe nommée `Plop_Request`):
```cpp
template <>
inline void Router::operator()<Plop_Request>(Plop_Request const& request, Plop_Request & response) {
    // faire quelque chose en fonction des requêtes entrée et sortie
    // Objet apiTree disponible pour appeler les comportements stockés
}
```

Une fois cette fonction définie, nous pouvons définir quoi faire de ces requêtes dans notre programme principal :

```cpp
int main() {
    Node<Plop> server;
    
    Router * myRouter = new Router();
    
    /* On enregistre les comportements dans le routeur */
    myRouter->on("entryPoint", [&server] (const Request * req, Request * res) {
        // définir comment remplir res en fonction de req
        // static_cast possible ici car nous savons que les requêtes seront des Plop_Request *
    });
    
    /* Ne pas oublier de lier le router à l'adapteur */
    server.plop_use(myRouter);
    
    [...]

    return 0;
}
```












