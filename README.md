# Serveur Multi protocoles
---
*Projet 3e année ISIMA*
*Maxime Cabanal et Simon Chaize*

### Prérequis

Ce projet nécessite pour sa compilation :
```
cmake
jsoncpp (libjsoncpp-dev)
```

### Installation
Serveur :
Après avoir `clone` le répertoire, se rendre dans le dossier et `build` le projet :
```sh
# Dossier node-network
$ mkdir build && cd build/
$ cmake ..
$ make
```

Ceci génère deux exécutables :
- `server`
- `client_robot`
- `ros_client`, le client de test, le mock d'un vrai robot

Les fichiers de configuration associés à ces binaires se situent dans le dossier `config` et sont respectivement `server.conf` et `client.conf`.

Lancer le serveur ensuite :
```sh
# Dossier build
$ ./server
```

#### Ajout de l'interface
Pour l'interface, elle se trouve sur un autre répertoire, une fois clônée dans à un autre endroit :
```sh
# Dossier interface
$ npm install
$ gulp
```
Ceci ira générer les ressources nécessaires à l'application, que l'on va copier dans le dossier `www` du serveur :
```sh
$ cp -R assets/ /path/to/server/www/
$ cp index.html /path/to/server/www
$ cp -R img/ /path/to/server/www
```

Maintenant que le serveur est lancé et que les ressources sont bonnes, on accède à l'application via l'url `localhost` en indiquant le port renseigné dans le fichier de configuration du server.