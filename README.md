<p align="left">
  <a href="#--------pipex--">🇬🇧 English</a> |
  <a href="#--------pipex---1">🇫🇷 Français</a>
</p>

<h1 align="center">
  <br>
  <img src="https://i.ibb.co/gZRkSfSJ/pipex.png" alt="pipex logo" width="150">
  <br>
  pipex
  <br>
</h1>

<h4 align="center"><em>The pipex program reproduces the behavior of the pipe (|) in the Unix shell.</em></h4>

<p align="center">
  <img src="https://img.shields.io/badge/languages-1-orange">
  <img src="https://img.shields.io/badge/C-100%25-blue">
  <img src="https://img.shields.io/badge/Grade-125%2F100-brightgreen">
</p>

<p align="center">
  <a href="https://drive.google.com/file/d/1Rrs0QEOL5afB_ZfqLnsBhxkWwYKMlMsa/view?usp=sharing">Subject</a> |
  <a href="#-project-overview">Overview</a> •
  <a href="#-code-architecture-and-organization">Architecture</a> •
  <a href="#-sorting-algorithm">Operating</a> •
  <a href="#%EF%B8%8F-compilation-and-testing">Compilation</a>
</p>

---

## 📌 **Project overview**
Pipex is a C program that reproduces the behavior of pipes (`|`) in the Unix shell. It redirects the input and output of several commands using `pipes`, `forks` and `execve`. The project also includes a bonus part with `here_doc` and management of an arbitrary number of commands.

---

## 📂 **Code architecture and organization**

---

<h1 align="center">
  <br>
  <img src="https://i.ibb.co/gZRkSfSJ/pipex.png" alt="pipex logo" width="150">
  <br>
  pipex
  <br>
</h1>

<h4 align="center"><em>Le programme pipex reproduit le comportement du pipe (|) en shell Unix</em></h4>

<p align="center">
  <img src="https://img.shields.io/badge/langages-1-orange">
  <img src="https://img.shields.io/badge/C-100%25-blue">
  <img src="https://img.shields.io/badge/Note-125%2F100-brightgreen">
</p>

<p align="center">
  <a href="https://drive.google.com/file/d/1n6tau0JgNefliLCaBLxRrFNodVj-uq56/view?usp=sharing">Sujet</a> |
  <a href="#-aperçu-du-projet">Aperçu</a> •
  <a href="#-architecture-et-organisation-du-code">Architecture</a> •
  <a href="#-sorting-algorithm">Fonctionnement</a> •
  <a href="#%EF%B8%8F-compilation-and-testing">Compilation</a>
</p>

---

## 📌 **Aperçu du projet**
Pipex est un programme en C qui reproduit le comportement des pipes (`|`) du shell Unix. Il redirige l'entrée et la sortie de plusieurs commandes grâce à l'utilisation de `pipes`, `forks`, et `execve`. Le projet comprend aussi une partie bonus avec le `here_doc` et la gestion d'un nombre arbitraire de commandes.

---

## 📂 **Architecture et organisation du code**

---

## 🏛 **Fonctionnement**

### 🔸 **Pipes**
Un pipe est un mécanisme de communication entre processus:
* Une extrémité pour écrire (sortie)
* Une extrémité pour lire (entrée)
* Les données circulent dans un seul sens

Dans le code :
```c
int pipe(int fds[2]);
```
* `fds[0]` : descripteur de lecture (read end)
* `fds[1]` : descripteur d'écriture (write end)

Exemple concret :
```bash
ls | grep test
```
* `ls` écrit dans le pipe
* `grep` lit depuis le pipe
* Les données passent directement de `ls` à `grep`


### 🔸 **Processus**
Un processus est un programme en cours d'exécution.

Chaque processus a :
* Son propre espace mémoire
* Son propre identifiant (PID)
* Ses propres ressources (fichiers ouverts, etc.)

La commande `ps aux` affiche tous les processus en cours d'exécution sur le système.

### 🔸 **Fork (Division de processus)**
`fork()` est comme une division cellulaire pour les processus:
* Crée une copie exacte du processus actuel
* Le processus original est appelé "parent"
* La copie est appelée "enfant"
* Les deux continuent à s'exécuter

Dans le code :
```c
pid_t pid = fork();
  if (pid == 0)
  {
    // Code exécuté par l'enfant
  }
  else
  {
    // Code exécuté par le parent
  }
```

Exemple concret:
```bash
./pipex file1 cmd1 cmd2 file2
```
* Le programme principal (parent) crée deux enfants
* Le premier enfant exécute `cmd1`
* Le deuxième enfant exécute `cmd2`


### 🔸 **PID (Process ID)**
Chaque processus a un identifiant unique (PID):
* Le PID du parent reste le même
* L'enfant reçoit un nouveau PID

`fork()` retourne :
* `0` dans le processus enfant
* Le PID de l'enfant dans le processus parent
* `-1` en cas d'erreur

### 🔸 **Relation parent/enfant**
* Le parent crée les enfants
* Le parent peut attendre la fin des enfants
* Les enfants héritent des ressources du parent
* Les enfants peuvent communiquer avec le parent

Dans `pipex`:
* Le parent crée les pipes
* Les enfants utilisent les pipes pour communiquer
* Le parent attend que les enfants terminent

### 🔸 **Descripteurs de fichiers (File descriptors)**
Un descripteur de fichier est un numéro qui représente un fichier ouvert :
* `0` : `stdin` (entrée standard)
* `1` : `stdout` (sortie standard)
* `2` : `stderr` (erreur standard)
* `3` et plus : fichiers ouverts par le programme

Exemple dans `pipex`:
```c
dup2(fd, STDOUT_FILENO);  // Redirige stdout vers fd
```
* Permet de rediriger l'entrée/sortie d'un programme
* Utilisé pour connecter les pipes aux commandes

### 🔸 **Redirection des entrées/sorties**
C'est comme changer la direction d'un tuyau :
* `>` : Redirection de sortie, écrase le fichier de destination
* `>>` : Redirection de sortie, ajoute à la fin du fichier de destination (append)
* `<` : Redirection d'entrée, lit depuis un fichier au lieu du clavier
* `<<` : `here_doc`, permet de saisir du texte jusqu'à un mot-clé
* `|` : Connecte la sortie d'une commande à l'entrée d'une autre

Dans `pipex`:
```bash
./pipex file1 cmd1 cmd2 file2
< file1 cmd1 | cmd2 > file2
```

### 🔸 **Here Document (`here_doc`)**

Un here document est une façon de fournir une entrée à un programme directement dans la ligne de commande, au lieu de lire depuis un fichier. C'est comme taper directement dans le terminal.
```bash
./pipex here_doc LIMITER cmd1 cmd2 file
./pipex here_doc STOP ls wc outfile
```
* Le programme lit l'entrée jusqu'à trouver `LIMITER`
* Utilise cette entrée comme `stdin` pour `cmd1`
* Écrit la sortie dans `file`

Sans `here_doc`:
```bash
echo "ligne 1
ligne 2
ligne 3" > input.txt
cat input.txt | wc -l
```
Avec `here_doc`:
```bash
cat << EOF | wc -l
ligne 1
ligne 2
ligne 3
EOF
```
Dans les deux cas, le résultat sera le même : le nombre de lignes (`3`).

Quand on exécute cette commande:
1. Le programme attend que l'on tape du texte
2. On peut taper autant de lignes que l'on veut
3. Quand on tape `LIMITER`, le programme arrête de lire
4. Le texte que l'on a tapé est utilisé comme entrée pour la première commande
5. La sortie est écrite dans `outfile`

Exemple:
```bash
./pipex here_doc END grep a wc outfile
```
Puis on tape:
```bash
apple
banana
cherry
date
END
```

Le programme va :
1. Lire tout ce qu'on a tapé jusqu'à `END`
2. Utiliser ce texte comme entrée pour `grep a`
3. `grep a` va trouver les lignes contenant 'a' (apple, banana, date)
4. `wc` va compter ces lignes
5. Le résultat (`3`) sera écrit dans `outfile `

#### Pourquoi utiliser here_doc ?
1. **Flexibilité**: On peut fournir l'entrée directement sans créer de fichier
2. **Interactivité**: Utile pour les programmes qui ont besoin d'une entrée interactive
3. **Scripting**: Permet d'inclure des données directement dans les scripts
4. **Test**: Facile pour tester des commandes avec différentes entrées

### 🔸 **Exemple complet de fonctionnement**
```bash
./pipex file1 "ls -l" "wc -l" file2
```

1. Le programme principal (parent):
* Ouvre `file1` en lecture
* Ouvre `file2` en écriture
* Crée un pipe
2. Premier enfant:
* Redirige `stdin` vers `file1`
* Redirige `stdout` vers le pipe
* Exécute `ls -l`
3. Deuxième enfant:
* Redirige `stdin` vers le pipe
* Redirige `stdout` vers `file2`
* Exécute `wc -l`
4. Le parent:
* Attend que les deux enfants terminent
* Ferme les pipes
* Termine proprement

### 🔸 **Arbre des processus**
Dans pipex, nous créé un arbre de processus :
```
pipex (PID: 1000)
├── cmd1 (PID: 1001)
└── cmd2 (PID: 1002)
```
Exemple avec plusieurs commandes (bonus) :
```
pipex (PID: 1000)
├── cmd1 (PID: 1001)
├── cmd2 (PID: 1002)
└── cmd3 (PID: 1003)
```

#### Communication entre processus
Les processus communiquent via les pipes:
```
pipex (1000)
├── cmd1 (1001) -> écrit dans pipe1
└── cmd2 (1002) <- lit depuis pipe1
```

1. Partie Obligatoire - Fonctionnement Global
Le programme pipex simule le comportement du pipe (|) en shell Unix. Voici le flux d'exécution détaillé :
1. Initialisation :
* Le programme vérifie qu'il a exactement 4 arguments
* Initialise la structure t_main qui contient toutes les informations nécessaires
* Récupère les chemins d'exécution depuis la variable d'environnement PATH
