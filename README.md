# 🐚 Minishell : Un Interpréteur de Commandes POSIX-like 

 <div align="center">

  <img src="./minishelle.png" alt="(minishell)" />

</div>


</br> 

## 🚀 Introduction

Le projet **Minishell** constitue une étape fondamentale du cursus 42, visant à l'**implémentation complète d'un interpréteur de commandes (shell) à partir de zéro**, fonctionnellement comparable à **Bash** ou à d'autres shells Unix courants.

**Le but est de recoder un shell**, en maîtrisant les mécanismes fondamentaux pour exécuter des commandes, gérer les processus et les entrées/sorties du système.

En recréant les mécanismes internes du shell, ce projet permet d'acquérir une **maîtrise approfondie** des interactions entre un programme utilisateur et le système d'exploitation, consolidant ainsi la compréhension des concepts clés de la **programmation système** et de l'architecture Unix.

-----
 🖼️ Structure du Projet


Voici un aperçu de la structure de l'interpréteur et du flux des données.


**

<div align="center">

  <img src="./screen.png" alt="(minishell)" />

</div> 

## ✨ Fonctionnalités Implémentées

Notre interpréteur supporte l'ensemble des fonctionnalités essentielles d'un shell moderne, notamment :

### 1\. Gestion des Processus et I/O (Le Cœur du Shell)

  * **Processus Enfants** : Utilisation des appels système de bas niveau (`fork()`, `execve()`, `waitpid()`) pour exécuter les commandes externes.
  * **Pipes (`|`)** : Implémentation de la communication inter-processus, permettant d'enchaîner des commandes où la sortie de l'une devient l'entrée de la suivante.
  * **Redirections I/O** :
      * Sortie simple (`>`), Redirection d'ajout (`>>`).
      * Redirection d'entrée (`<`).
      * **Here Document (`<<`)** : Gestion de l'entrée en ligne jusqu'à un délimiteur spécifié.
  * **Gestion des Signaux** : Implémentation de `sigaction()` pour gérer les signaux système (`SIGINT` / Ctrl+C, `SIGQUIT` / Ctrl+), assurant la robustesse en mode interactif.

### 2\. Analyse et Interprétation (Parsing)

  * **Tokenisation** : Découpage précis de la ligne de commande en éléments logiques (tokens : commandes, arguments, opérateurs).
  * **Gestion des Quotes** : Interprétation correcte des guillemets doubles (`"`) et simples (`'`) pour contrôler l'expansion des variables et la tokenisation.
  * **Expansion des Variables** : Remplacement des variables d'environnement (`$USER`, `$HOME`, `$?`) par leur valeur avant exécution.

### 3\. Commandes Intégrées (Built-ins) et Environnement

  * **Variables d'Environnement** : Manipulation de l'environnement (ex: `$PATH`, `$HOME`) et gestion des fonctions primitives (built-ins) :
      * `cd`, `echo`, `pwd`, `export`, `unset`, `exit`.
  * **Statut de Sortie** : Gestion et retour précis du statut de sortie (`exit status`, `$?`) de la dernière commande exécutée.
  * **Recherche d'Exécutable** : Résolution du chemin des commandes via la variable `$PATH`.

-----

## 🛠️ Compétences et Concepts Maîtrisés

| Catégorie | Compétences Clés Développées |
| :--- | :--- |
| **Programmation Système** | Maîtrise des appels système de processus (`fork`, `execve`, `waitpid`), des I/O de bas niveau (`open`, `read`, `write`, `close`), et des opérations sur descripteurs de fichiers (`dup2`, `pipe`). |
| **Architecture du Shell** | **Compréhension complète du cycle de vie d'une commande** (lecture, parsing, expansion, exécution) nécessaire pour **recoder un shell complet**. |
| **Robustesse et Mémoire** | Implémentation modulaire et conforme à la norme 42. **Gestion rigoureuse des allocations** (absence de fuites mémoire) et gestion sécurisée des chaînes de caractères. |
| **Structure de Données** | Conception de structures de données adaptées (arbres syntaxiques, listes chaînées de commandes/tokens) pour représenter la ligne de commande. |

-----

## ⚙️ Installation et Compilation

### Prérequis

  * `make`
  * `cc` (Compilateur C)
  * La librairie **`readline`** (souvent disponible via `libreadline-dev` sur Linux ou `brew install readline` sur macOS).

### ⚠️ Note Importante : Dépendance `libft`

Ce projet utilise des fonctions utilitaires issues de ma librairie personnelle, **`libft`**.

Si la compilation échoue, c'est que la librairie `libft` n'est pas présente. Vous pouvez la cloner directement depuis mon répertoire GitHub et la placer dans le dossier racine du projet `minishell` :

> `git clone https://github.com/myc42/libft`

### Instructions de Compilation

1.  Clonez le projet :
    ```bash
    git clone https://github.com/myc42/minishell
    cd minishell
    ```
2.  Lancez la compilation :
    ```bash
    make
    ```
3.  Exécutez l'interpréteur :
    ```bash
    ./minishell
    ```


