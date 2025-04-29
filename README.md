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
  <a href="#-operating">Operating</a> •
  <a href="#%EF%B8%8F-compiling-and-testing">Compiling</a>
</p>

---

## 📌 **Project overview**
Pipex is a C program that reproduces the behavior of pipes (`|`) in the Unix shell. It redirects the input and output of several commands using `pipes`, `forks` and `execve`. The project also includes a bonus part with `here_doc` and management of an arbitrary number of commands.

### 1. Mandatory part ✅
The pipex program simulates the behavior of the pipe (`|`) in a Unix shell. Here's the detailed execution flow:
#### 1. Initialization:
* The program checks that it has exactly 4 arguments.
* Initializes the `t_main` structure, which contains all necessary information
* retrieves execution paths from the `PATH` environment variable

#### 2. Parsing arguments :
* `get_paths` : Extracts paths from `PATH`.
* `parse_args`: Separates commands and their arguments
* `parse_paths`: Builds complete paths for executables

#### 3. Executing commands:
* Create a pipe with `pipe`.
* Fork two child processes
  * In the first child:
    * Redirects `stdin` to the input file
    * Redirects `stdout` to the pipe
    * Executes the first command
  * In the second child :
    * Redirects `stdin` to the pipe
    * Redirects `stdout` to the output file
    * Executes the second command
* The parent waits for the end of both children

### 2. Bonus part 🚀
#### 1. Handling multiple pipes:
* The program can handle an arbitrary number of commands.
* Creates a pipe between each command
* Manages I/O redirection between commands.
#### 2. Here document (here_doc):
* Allows input to be specified directly on the command line
* Syntax: `./pipex here_doc LIMITER cmd1 cmd2 file`
* Reads the input until it finds the `LIMITER`.
* Use this entry as `stdin` for the first command.

### Error handling ⚠️
The program handles several types of error:
* Invalid arguments
* Inaccessible files
* Commands not found
* Permission errors
* Memory errors
* Pipe errors
* Fork errors

Each error is handled with an appropriate message and correct exit code.

---

## 📂 **Code architecture and organization**

#### 🔹 Fonctions principales
| Fonction | Description |
|----------|------------|
| `main` | Program entry point. Checks number of arguments. Initializes `t_main` structure. Calls `get_paths` and `parse_args`. Calls `exec` or `here_doc` depending on arguments. Handles errors with `error_exit`. |
| `exec` | Main execution function. Allocates structures with `malloc_fds` and `malloc_pids`. Executes `first_cmd()` for the first command. Executes `mid_cmd` for intermediate (bonus) commands. Executes `last_cmd` for the last command. Waits for processes to finish with `wait_childrens`. Clean pipes with `close_last_pipes` and `close_own_pipes`. |
| `first_cmd` | Handles the first command. Creates a pipe with `create_own_pipes`. Fork a child process. **In child:** 1) Opens input file with `open_infile`; 2) Redirects `stdin` to file with `dup_fd`; 3) Redirects `stdout` to pipe with `dup_fd`; 4) Executes command with `exev`. **In parent:** 1) Closes unneeded pipes; 2) Stores child's PID |
| `mid_cmd` | Handles intermediate commands (bonus). Creates a pipe with `create_own_pipes`. Fork a child process. **In child:** 1) Redirects `stdin` to previous pipe; 2) Redirects `stdout` to new pipe. 3) Executes command with `exev`. **In parent:** 1) Closes unnecessary pipes; 2) Stores child's PID. |
| `last_cmd` | Handles last command. Creates a pipe with `create_own_pipes`. Fork a child process. **In child:** 1) Redirects `stdin` to previous pipe; 2) Opens output file with `open_outfile`; 3) Redirects `stdout` to file with `dup_fd`; 4) Executes command with `exev`. **In parent:** 1) Closes unnecessary pipes; 2) Stores child's PID |

#### 🔹 Gestion des pipes
| Fonction | Description |
|----------|------------|
| `dup_fd` | Duplicates a file descriptor. Uses `dup2` for redirection. Handles `dup2` errors. Used to redirect `stdin`/`stdout`. |
| `create_own_pipes` | Creates a new pipe. Uses `pipe` to create the pipe. Stores descriptors in `pipex->fds`. Handles `pipe` errors. |
| `close_own_pipes` | Close current pipes. Closes both pipe ends. Use `close` on `fds[0]` and `fds[1]`. Prevents descriptor leaks |
| `close_last_pipes` | Closes previous pipes. Goes through all previous pipes. Closes unused ends. Cleans resources |
| `wait_childrens` | Waits for all child processes to finish. Use `waitpid` for each child. Avoids zombie processes. Retrieves exit status. |

#### 🔹 Parsing et chemins
| Fonction | Description |
|----------|------------|
| `get_paths` | Retrieves execution paths. Browses `envp` to find `PATH`. Uses `ft_split` to separate paths. Uses `ft_strtrim` to clean `“PATH=”`. Stores in `pipex->cmd_paths`. |
| `parse_args` | Parse command arguments. Calculates number of commands. Allocates necessary arrays. Uses `ft_split` to separate commands. Stores in `pipex->cmd_args`. |
| `envp_check` | Checks `PATH` environment variable. Initializes paths if `PATH` is not defined. Calls `envp_loop` to process commands. Handles configuration errors |
| `envp_loop` | Browse commands. Checks absolute paths. Handles command not found errors. Updates paths in `pipex->cmd_paths`. |
| `parse_paths` | Builds complete paths. Goes through each command. Calls `join_path` for each command. Stores complete paths in `pipex->paths`. |
| `join_path` | Joins paths to form the complete path. Uses `ft_strjoin` to concatenate. Checks existence with `access`. Returns the first valid path. |

#### 🔹 Gestion des fichiers
| Fonction | Description |
|----------|------------|
| `open_infile` | Opens the input file. Checks existence with `access`. Check permissions with `access`. Opens read-only with `open`. Handles errors |
| `open_outfile_here` | Opens the output file in append mode. Verifies existence with `access`. Creates file if necessary. Opens in write mode with `open`. Handles errors |
| `check_outfile` | Checks output file permissions. Checks existence with `access`. Checks read/write permissions. Updates `pipex->err` if necessary. |
| `open_outfile` | Opens the output file. Checks existence with `access`. Creates file if necessary. Opens for writing with `open`. Handles errors |

#### 🔹 Gestion de la mémoire
| Fonction | Description |
|----------|------------|
| `free_all_exit` | Releases memory and quits. Calls `free_all`. Uses `exit` with error code. Handles clean exit |
| `error_exit` | Handles errors. Displays error message with `ft_putendl_fd`. Calls `free_all`. Quits with error code |
| `malloc_error` | Handles allocation errors. Calls `free_all`. Displays `“Malloc Error”`. Exits with code `0`. |
| `free_all` | Free all memory. Free `cmd_paths`, `cmd_args` and `paths` with `ft_free_double_tab`. Free `fds` and `pids`. |
| `malloc_pids` | Allocate PIDs. Allocates an array to store PIDs. Initializes PIDs to 0. Handles allocation errors. |
| `malloc_fds` | Allocates file descriptors. Allocates an array of `int*` for pipes. Allocate an array of `int[2]` for each pipe. Initializes `fds` to `-1`. Handles allocation errors |

#### 🔹 Fonctions de vérification
| Fonction | Description |
|----------|------------|
| `check_access` | Verifies access to commands. Checks existence with `access`. Checks permissions with `access`. Updates `pipex->err`. |
| `exev` | Executes command. Checks existence of path. Checks permissions. Use `execve` to execute. Handles errors. |

#### 🔹 Fonctions bonus
| Fonction | Description |
|----------|------------|
| `here_doc` | Manages `here_doc`. Creates a pipe with `doc_pipe`. Reads input to limit. Executes commands with pipes. Handles output in append mode. |
| `doc_pipe` | Creates the pipe for `here_doc`. Creates a pipe. Fork a process. **In child:** 1) Reads input with `get_next_line`; 2) Writes to pipe. **In parent:** Returns read fd. |

#### 🔹 Fonctions `libft`
| Fonction | Description |
|----------|------------|
| `ft_putendl_fd` | Writes a string followed by a `linefeed`. Uses `write` to write. Handles writing errors |
| `ft_strchr` | Searches for a character in a string. Returns a pointer to the character. Returns `NULL` if not found. |
| `ft_strjoin` | Concatenates two strings. Allocates a new chain. Copies the two chains. Returns the new chain. |
| `get_next_line` | Reads a line from a descriptor. Allocates memory. Handles reading errors. Returns the line read. |
| `ft_strtrim` | Deletes specified characters. Deletes at beginning and end. Returns the new string |
| `ft_split` | Divides a string according to a delimiter. Returns an array of strings. Allocates necessary memory. Handles allocation errors. |
| `ft_strnstr` | Searches for a substring. Limits search to `n` characters. Returns a pointer to the substring. Returns `NULL` if not found. |

#### 🔹 Appels système
| Fonction | Description |
|----------|------------|
| `fork` | Creates a new process by duplicating the calling process. Returns `0` in the child process. Returns the PID of the child in the parent process. Used to create processes that will execute commands. |
| `pipe` | Creates a unidirectional communication channel. **Returns two file descriptors:** 1) `fds[0]`: read end; 2) `fds[1]`: write end. Used for inter-process communication |
| `execve` | Replaces the current process image with a new program. **Parameters:** 1) `path`: executable path; 2) `argv`: array of arguments; 3) `envp`: environment variables. Used to execute commands |
| `waitpid` | Waits for the end of a child process. Recovers its exit status. Avoids zombie processes. Used to wait for commands to finish. |
| `access` | Checks file permissions. **Flags:** 1) `F_OK`: checks existence; 2) `R_OK`: checks reading; 3) `W_OK`: checks writing; 4) `X_OK`: checks execution. Used to check files and executables |
| `open` | Opens a file. **Flags:** 1) `O_RDONLY`: read only; 2) `O_WRONLY`: write only; 3) `O_CREAT`: creates if does not exist; 4) `O_TRUNC`: truncates if exists; 5) `O_APPEND`: writes to end. Used to open input/output files |
| `close` | Closes a file descriptor. Free up resources. Prevents descriptor leaks |
| `dup2` | Duplicates a file descriptor. Automatically closes the old descriptor. Used for I/O redirection. |

---

## 🏛 **Operating**

### 🔸 **Pipes**
A pipe is a communication mechanism between processes:
* One end for writing (output)
* One end for reading (input)
* Data flows in one direction only

In code :
```c
int pipe(int fds[2]);
```
* `fds[0]` : read descriptor (read end)
* `fds[1]` : write descriptor (write end)

Concrete example :
```bash
ls | grep test
```
* `ls` writes to pipe
* `grep` reads from the pipe
* Data pass directly from `ls` to `grep`.


### 🔸 **Process**
A process is a running program.

Each process has :
* Its own memory space
* Its own identifier (PID)
* Its own resources (open files, etc.)

The `ps aux` command displays all processes running on the system.

### 🔸 **Fork (Process division)**
`fork` is like a cell division for processes:
* Creates an exact copy of the current process
* The original process is called the “parent”.
* The copy is called “child”.
* Both continue to run

In the code :
```c
pid_t pid = fork();
  if (pid == 0)
  {
    // Code executed by child
  }
  else
  {
    // Code executed by parent
  }
```

Concrete example:
```bash
./pipex file1 cmd1 cmd2 file2
```
* The main (parent) program creates two children
* The first child executes `cmd1`.
* The second child runs `cmd2`.


### 🔸 **PID (Process ID)**
Each process has a unique identifier (PID):
* The parent's PID remains the same
* The child receives a new PID

`fork` returns :
* `0` in the child process
* The child's PID in the parent process
* `-1` on error

### 🔸 **Parent/child relationship**
* Parent creates children
* Parent can wait for children to finish
* Children inherit resources from parent
* Children can communicate with parent

In `pipex`:
* Parent creates pipes
* Children use pipes to communicate
* Parent waits for children to finish

### 🔸 **File descriptors**
A file descriptor is a number representing an open file:
* `0`: `stdin` (standard input)
* `1`: `stdout` (standard output)
* `2`: `stderr` (standard error)
* `3` and more: files opened by the program

Example in `pipex`:
```c
dup2(fd, STDOUT_FILENO); // Redirects stdout to fd
```
* Used to redirect program input/output
* Used to connect pipes to commands

### 🔸 **input/output direction**
It's like changing the direction of a pipe:
* `>` : Output redirection, overwrites destination file
* `>>` : Output redirection, append to end of destination file
* `<` : Input redirection, reads from file instead of keyboard
* `<<` : `here_doc`, allows text entry up to a keyword
* `|` : Connects the output of one command to the input of another

In `pipex`:
```bash
./pipex file1 cmd1 cmd2 file2
< file1 cmd1 | cmd2 > file2
```

### 🔸 **Here Document (`here_doc`)**

A here document is a way of providing input to a program directly from the command line, instead of reading from a file. It's like typing directly into the terminal.
```bash
./pipex here_doc LIMITER cmd1 cmd2 file
./pipex here_doc STOP ls wc outfile
```
* The program reads the input until it finds `LIMITER`.
* Uses this input as `stdin` for `cmd1`.
* Writes output to `file`

Without `here_doc`:
```bash
echo "line 1
line 2
line 3" > input.txt
cat input.txt | wc -l
```
With `here_doc`:
```bash
cat << EOF | wc -l
ligne 1
ligne 2
ligne 3
EOF
```
In both cases, the result will be the same: the number of lines (`3`).

When executing this command:
1. The program waits for you to type some text
2. You can type as many lines as you like
3. When you type `LIMITER`, the program stops reading.
4. The text you've typed is used as input for the first command.
5. Output is written to `outfile`.

Example:
```bash
./pipex here_doc END grep a wc outfile
```
Then we type:
```bash
apple
banana
cherry
date
END
```

The program will :
1. Read everything we typed up to `END`.
2. Use this text as input for `grep a`.
3. `grep a` will find lines containing 'a' (apple, banana, date)
4. `wc` will count these lines
5. The result (`3`) will be written to `outfile `.

#### Why use here_doc?
1. **Flexibility**: Input can be supplied directly without creating a file.
2. **Interactivity**: Useful for programs requiring interactive input.
3. **Scripting**: Allows data to be included directly in scripts.
4. **Testing**: Easy to test commands with different inputs.

### 🔸 **Complete operating example**
```bash
./pipex file1 "ls -l" "wc -l" file2
```

1. The main (parent) program:
* Open `file1` for reading
* Open `file2` for writing
* Creates a pipe
2. First child:
* Redirects `stdin` to `file1`.
* Redirects `stdout` to the pipe
* Executes `ls -l`.
3. Second child:
* Redirects `stdin` to the pipe
* Redirects `stdout` to `file2`.
* Execute `wc -l`.
4. Parent:
* Waits for both children to finish
* Closes the pipes
* Finishes cleanly

### 🔸 **Process tree**
In pipex, we create a process tree:
```
pipex (PID: 1000)
├── cmd1 (PID: 1001)
└── cmd2 (PID: 1002)
```
Example with multiple commands (bonus) :
```
pipex (PID: 1000)
├── cmd1 (PID: 1001)
├── cmd2 (PID: 1002)
└── cmd3 (PID: 1003)
```

#### Process communication
Processes communicate via pipes:
```
pipex (1000)
├── cmd1 (1001) -> write in pipe1
└── cmd2 (1002) <- read from pipe1
```

---

## ⚙️ **Compiling and testing**

### 🔧 Compiling
- To compile **pipex**:
  ```bash
  make
  ```
- To compile **the bonus part**:
  ```bash
  make bonus
  ```
- To delete object files and compiled binaries:
  ```bash
  make fclean
  ```

---

### ▶️ Use and execution

- #### ✅ Execution of `pipex` for the mandatory part:
  The **`pipex`** executable takes 4 arguments:
  * `file1` and `file2` are file names.
  * `cmd1` and `cmd2` are shell commands with parameters.
    * If commands take arguments, enclose them in quotation marks (*Ex:* `“wc -l”`). 
  ```bash
  ./pipex file1 cmd1 cmd2 file2
  ```
  #### Tests for the mandatory part
  * Basic test 2 simple commands::
    ```bash
    ./pipex infile "ls -l" "wc -l" outfile
    < infile ls -l | wc -l > outfile
    ```

   * Test with non-existent input file:
     ```bash
     ./pipex nonexistent "ls" "wc -l" outfile
     < nonexistent ls | wc -l > outfile
     ```
  
   * Test with output file without permissions:
     ```bash
     chmod 000 outfile
     ./pipex infile "ls" "wc -l" outfile
     < infile ls | wc -l > outfile
     ```
  
   * Test for non-existent commands:
     ```bash
     ./pipex infile "nonexistentcmd" "wc -l" outfile
     < infile nonexistentcmd | wc -l > outfile
     ```
  
   * Testing commands with invalid syntax:
     ```bash
     ./pipex infile "ls -" "wc -l" outfile
     < infile ls - | wc -l > outfile
     ```
  
   * Testing commands with special arguments:
     ```bash
     ./pipex infile "echo 'hello world'" "wc -w" outfile
     < infile echo 'hello world' | wc -w > outfile
     ```
  
   * Performance test (Large input file):
     ```bash
     dd if=/dev/urandom of=largefile bs=1M count=100
     ./pipex largefile "grep a" "wc -l" outfile
     < largefile grep a | wc -l > outfile
     ```
  
   * Test with paths:
     ```bash
     ./pipex infile "/bin/cat /etc/passwd" "wc -l" outfile
     < infile /bin/cat /etc/passwd | wc -l > outfile
     ```
  
   * Test with sleep command:
     ```bash
     ./pipex infile "sleep 2" "wc -l" outfile
     < infile sleep 2 | wc -l > outfile
     ```

- #### 🚀 Executing `pipex` for the bonus part:
  * The **`pipex`** executable for the bonus part takes **at least** 4 arguments:
    * `file1` and `file2` are file names.
    * `cmd1`, `cmd2`... are shell commands with parameters.
  ```bash
  ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
  ```
  * `here_doc`
  ```bash
  ./pipex here_doc LIMITER cmd cmd1 file
  ```
  #### Tests for the bonus part
  * Test with several pipes (3 commands):
    ```bash
     ./pipex infile "cat" "grep test" "wc -l" outfile
     < infile cat | grep test | wc -l > outfile
    ```

   * Test with several pipes (4 commands):
     ```bash
     ./pipex infile "cat" "grep test" "sort" "uniq -c" outfile
     < infile cat | grep test | sort | uniq -c > outfile
     ```
  
   * Tricky test:
     ```bash
     ./pipex /dev/stdin "cat" "cat" "cat" "cat" "ls" "cat" /dev/stdout
     < /dev/stdin cat | cat | cat | cat | ls | cat > /dev/stdout
     ```
  
   * Test with several pipes (10 commands):
     ```bash
     ./pipex infile "cat" "grep test" "sort" "uniq" "wc -l" "cat" "cat" "cat" "cat" "cat" outfile
     < infile cat | grep test | sort | uniq | wc -l | cat | cat | cat | cat | cat > outfile
     ```
  
   * Testing with multiple pipes and paths:
     ```bash
     ./pipex infile "/bin/cat /etc/passwd" "grep root" "wc -l" outfile
     < infile /bin/cat /etc/passwd | grep root | wc -l > outfile
     ```
  
   * Test with `here_doc`:
     ```bash
     ./pipex here_doc LIMITER "cat" "wc -l" outfile
     cat << LIMITER | wc -l >> outfile
     ```
  
   * `here_doc` test with several pipes:
     ```bash
     ./pipex here_doc LIMITER "cat" "grep test" "wc -l" outfile
     cat << LIMITER | grep test | wc -l >> outfile
     ```
  
   * `here_doc` test with complex commands:
     ```bash
     ./pipex here_doc LIMITER "grep -i hello" "sort -r" "uniq -c" outfile
     grep -i hello << LIMITER | sort -r | uniq -c >> outfile
     ```
  
   * `here_doc` test with errors:
     ```bash
     ./pipex here_doc LIMITER "nonexistentcmd" "wc -l" outfile
     nonexistentcmd << LIMITER | wc -l >> outfile
     ```

   * `here_doc` test with sleep:
     ```bash
     ./pipex here_doc LIMITER "sleep 1" "echo 'test'" "wc -l" outfile
     sleep 1 << LIMITER | echo 'test' | wc -l >> outfile
     ```

   * `here_doc` test with paths:
     ```bash
     ./pipex here_doc LIMITER "/bin/cat /etc/passwd" "grep root" "wc -l" outfile
     /bin/cat /etc/passwd << LIMITER | grep root | wc -l >> outfile
     ```

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
  <a href="#-fonctionnement">Fonctionnement</a> •
  <a href="#%EF%B8%8F-compilation-et-tests">Compilation</a>
</p>

---

## 📌 **Aperçu du projet**
Pipex est un programme en C qui reproduit le comportement des pipes (`|`) du shell Unix. Il redirige l'entrée et la sortie de plusieurs commandes grâce à l'utilisation de `pipes`, `forks`, et `execve`. Le projet comprend aussi une partie bonus avec le `here_doc` et la gestion d'un nombre arbitraire de commandes.

### 1. Partie obligatoire ✅
Le programme pipex simule le comportement du pipe (`|`) en shell Unix. Voici le flux d'exécution détaillé :
#### 1. Initialisation :
* Le programme vérifie qu'il a exactement 4 arguments
* Initialise la structure `t_main` qui contient toutes les informations nécessaires
* Récupère les chemins d'exécution depuis la variable d'environnement `PATH`

#### 2. Parsing des arguments :
* `get_paths` : Extrait les chemins depuis `PATH`
* `parse_args` : Sépare les commandes et leurs arguments
* `parse_paths` : Construit les chemins complets des exécutables

#### 3. Exécution des commandes :
* Crée un pipe avec `pipe`
* Fork deux processus enfants
  * Dans le premier enfant :
    * Redirige `stdin` vers le fichier d'entrée
    * Redirige `stdout` vers le pipe
    * Exécute la première commande
  * Dans le deuxième enfant :
    * Redirige `stdin` vers le pipe
    * Redirige `stdout` vers le fichier de sortie
    * Exécute la deuxième commande
* Le parent attend la fin des deux enfants

### 2. Partie bonus 🚀
#### 1. Gestion de plusieurs pipes :
* Le programme peut gérer un nombre arbitraire de commandes
* Crée un pipe entre chaque commande
* Gère la redirection des entrées/sorties entre les commandes
#### 2. Here document (here_doc) :
* Permet de spécifier l'entrée directement dans la ligne de commande
* Syntaxe : `./pipex here_doc LIMITER cmd1 cmd2 file`
* Lit l'entrée jusqu'à trouver le `LIMITER`
* Utilise cette entrée comme `stdin` pour la première commande

### Gestion des erreurs ⚠️
Le programme gère plusieurs types d'erreurs :
* Arguments invalides
* Fichiers inaccessibles
* Commandes non trouvées
* Erreurs de permissions
* Erreurs de mémoire
* Erreurs de pipes
* Erreurs de fork

Chaque erreur est gérée avec un message approprié et un code de sortie correct.

---

## 📂 **Architecture et organisation du code**

#### 🔹 Fonctions principales
| Fonction | Description |
|----------|------------|
| `main` | Point d'entrée du programme. Vérifie le nombre d'arguments. Initialise la structure `t_main`. Appelle `get_paths` et `parse_args`. Lance `exec` ou `here_doc` selon les arguments. Gère les erreurs avec `error_exit` |
| `exec` | Fonction principale d'exécution. Alloue les structures avec `malloc_fds` et `malloc_pids`. Exécute `first_cmd()` pour la première commande. Exécute `mid_cmd` pour les commandes intermédiaires (bonus). Exécute `last_cmd` pour la dernière commande. Attend la fin des processus avec `wait_childrens`. Nettoie les pipes avec `close_last_pipes` et `close_own_pipes` |
| `first_cmd` | Gère la première commande. Crée un pipe avec `create_own_pipes`. Fork un processus enfant. **Dans l'enfant:** 1) Ouvre le fichier d'entrée avec `open_infile`; 2) Redirige `stdin` vers le fichier avec `dup_fd`; 3) Redirige `stdout` vers le pipe avec `dup_fd`; 4) Exécute la commande avec `exev`. **Dans le parent:** 1) Ferme les pipes inutiles; 2) Stocke le PID de l'enfant |
| `mid_cmd` | Gère les commandes intermédiaires (bonus). Crée un pipe avec `create_own_pipes`. Fork un processus enfant. **Dans l'enfant:** 1) Redirige `stdin` vers le pipe précédent; 2) Redirige `stdout` vers le nouveau pipe. 3) Exécute la commande avec `exev`. **Dans le parent:** 1) Ferme les pipes inutiles; 2) Stocke le PID de l'enfant |
| `last_cmd` | Gère la dernière commande. Crée un pipe avec `create_own_pipes`. Fork un processus enfant. **Dans l'enfant:** 1) Redirige `stdin` vers le pipe précédent; 2) Ouvre le fichier de sortie avec `open_outfile`; 3) Redirige `stdout` vers le fichier avec `dup_fd`; 4) Exécute la commande avec `exev`. **Dans le parent:** 1) Ferme les pipes inutiles; 2) Stocke le PID de l'enfant |

#### 🔹 Gestion des pipes
| Fonction | Description |
|----------|------------|
| `dup_fd` | Duplique un descripteur de fichier. Utilise `dup2` pour la redirection. Gère les erreurs de `dup2`. Utilisé pour rediriger `stdin`/`stdout` |
| `create_own_pipes` | Crée un nouveau pipe. Utilise `pipe` pour créer le canal. Stocke les descripteurs dans `pipex->fds`. Gère les erreurs de `pipe` |
| `close_own_pipes` | Ferme les pipes actuels. Ferme les deux extrémités du pipe. Utilise `close` sur `fds[0]` et `fds[1]`. Évite les fuites de descripteurs |
| `close_last_pipes` | Ferme les pipes précédents. Parcourt tous les pipes précédents. Ferme les extrémités non utilisées. Nettoie les ressources |
| `wait_childrens` | Attend la fin de tous les processus enfants. Utilise `waitpid` pour chaque enfant. Évite les processus zombies. Récupère les statuts de sortie |

#### 🔹 Parsing et chemins
| Fonction | Description |
|----------|------------|
| `get_paths` | Récupère les chemins d'exécution. Parcourt `envp` pour trouver `PATH`. Utilise `ft_split` pour séparer les chemins. Utilise `ft_strtrim` pour nettoyer `"PATH="`. Stocke dans `pipex->cmd_paths` |
| `parse_args` | Parse les arguments des commandes. Calcule le nombre de commandes. Alloue les tableaux nécessaires. Utilise `ft_split` pour séparer les commandes. Stocke dans `pipex->cmd_args` |
| `envp_check` | Vérifie la variable d'environnement `PATH`. Initialise les chemins si `PATH` n'est pas défini. Appelle `envp_loop` pour traiter les commandes. Gère les erreurs de configuration |
| `envp_loop` | Parcourt les commandes. Vérifie les chemins absolus. Gère les erreurs de commandes non trouvée. Met à jour les chemins dans `pipex->cmd_paths` |
| `parse_paths` | Construit les chemins complets. Parcourt chaque commande. Appelle `join_path` pour chaque commande. Stocke les chemins complets dans `pipex->paths` |
| `join_path` | Joint les chemins pour former le chemin complet. Utilise `ft_strjoin` pour concaténer. Vérifie l'existence avec `access`. Retourne le premier chemin valide |

#### 🔹 Gestion des fichiers
| Fonction | Description |
|----------|------------|
| `open_infile` | Ouvre le fichier d'entrée. Vérifie l'existence avec `access`. Vérifie les permissions avec `access`. Ouvre en lecture seule avec `open`. Gère les erreurs |
| `open_outfile_here` | Ouvre le fichier de sortie en mode append. Vérifie l'existence avec `access`. Crée le fichier si nécessaire. Ouvre en écriture avec `open`. Gère les erreurs |
| `check_outfile` | Vérifie les permissions du fichier de sortie. Vérifie l'existence avec `access`. Vérifie les permissions en lecture/écriture. Met à jour `pipex->err` si nécessaire |
| `open_outfile` | Ouvre le fichier de sortie. Vérifie l'existence avec `access`. Crée le fichier si nécessaire. Ouvre en écriture avec `open`. Gère les erreurs |

#### 🔹 Gestion de la mémoire
| Fonction | Description |
|----------|------------|
| `free_all_exit` | Libère la mémoire et quitte. Appelle `free_all`. Utilise `exit` avec le code d'erreur. Gère la sortie propre |
| `error_exit` | Gère les erreurs. Affiche le message d'erreur avec `ft_putendl_fd`. Appelle `free_all`. Quitte avec le code d'erreur |
| `malloc_error` | Gère les erreurs d'allocation. Appelle `free_all`. Affiche `"Malloc Error"`. Quitte avec le code `0` |
| `free_all` | Libère toute la mémoire. Libère `cmd_paths`, `cmd_args` et `paths` avec `ft_free_double_tab`. Libère `fds` et `pids` |
| `malloc_pids` | Alloue les PIDs. Alloue un tableau pour stocker les PIDs. Initialise les PIDs à 0. Gère les erreurs d'allocation |
| `malloc_fds` | Alloue les descripteurs de fichiers. Alloue un tableau de `int*` pour les pipes. Alloue un tableau de `int[2]` pour chaque pipe. Initialise les `fds` à `-1`. Gère les erreurs d'allocation |

#### 🔹 Fonctions de vérification
| Fonction | Description |
|----------|------------|
| `check_access` | Vérifie l'accès aux commandes. Vérifie l'existence avec `access`. Vérifie les permissions avec `access`. Met à jour `pipex->err` |
| `exev` | Exécute la commande. Vérifie l'existence du chemin. Vérifie les permissions. Utilise `execve` pour exécuter. Gère les erreurs |

#### 🔹 Fonctions bonus
| Fonction | Description |
|----------|------------|
| `here_doc` | Gère le `here_doc`. Crée un pipe avec `doc_pipe`. Lit l'entrée jusqu'au limiter. Exécute les commandes avec les pipes. Gère la sortie en mode append |
| `doc_pipe` | Crée le pipe pour `here_doc`. Crée un pipe. Fork un processus. **Dans l'enfant:** 1) Lit l'entrée avec `get_next_line`; 2) Écrit dans le pipe. **Dans le parent:** Retourne le fd de lecture |

#### 🔹 Fonctions `libft`
| Fonction | Description |
|----------|------------|
| `ft_putendl_fd` | Écrit une chaîne suivie d'un retour à la ligne `\n`. Utilise `write` pour écrire. Gère les erreurs d'écriture |
| `ft_strchr` | Recherche un caractère dans une chaîne. Retourne un pointeur vers le caractère. Retourne `NULL` si non trouvé |
| `ft_strjoin` | Concatène deux chaînes. Alloue une nouvelle chaîne. Copie les deux chaînes. Retourne la nouvelle chaîne |
| `get_next_line` | Lit une ligne depuis un descripteur. Alloue la mémoire nécessaire. Gère les erreurs de lecture. Retourne la ligne lue |
| `ft_strtrim` | Supprime les caractères spécifiés. Enlève au début et à la fin. Retourne la nouvelle chaîne |
| `ft_split` | Divise une chaîne selon un délimiteur. Retourne un tableau de chaînes. Alloue la mémoire nécessaire. Gère les erreurs d'allocation |
| `ft_strnstr` | Recherche une sous-chaîne. Limite la recherche à `n` caractères. Retourne un pointeur vers la sous-chaîne. Retourne `NULL` si non trouvé |

#### 🔹 Appels système
| Fonction | Description |
|----------|------------|
| `fork` | Crée un nouveau processus en dupliquant le processus appelant. Retourne `0` dans le processus enfant. Retourne le PID de l'enfant dans le processus parent. Utilisé pour créer les processus qui exécuteront les commandes |
| `pipe` | Crée un canal de communication unidirectionnel. **Retourne deux descripteurs de fichiers:** 1) `fds[0]`: extrémité de lecture; 2) `fds[1]`: extrémité d'écriture. Utilisé pour la communication entre processus |
| `execve` | Remplace l'image du processus actuel par un nouveau programme. **Paramètres:** 1) `path`: chemin de l'exécutable; 2) `argv`: tableau d'arguments; 3) `envp`: variables d'environnement. Utilisé pour exécuter les commandes |
| `waitpid` | Attend la fin d'un processus enfant. Récupère son statut de sortie. Évite les processus zombies. Utilisé pour attendre la fin des commandes |
| `access` | Vérifie les permissions d'un fichier. **Flags:** 1) `F_OK` : vérifie l'existence; 2) `R_OK`: vérifie la lecture; 3) `W_OK`: vérifie l'écriture; 4) `X_OK`: vérifie l'exécution. Utilisé pour vérifier les fichiers et les exécutables |
| `open` | Ouvre un fichier. **Flags:** 1) `O_RDONLY`: lecture seule; 2) `O_WRONLY`: écriture seule; 3) `O_CREAT`: crée si n'existe pas; 4) `O_TRUNC`: tronque si existe; 5) `O_APPEND`: écrit à la fin. Utilisé pour ouvrir les fichiers d'entrée/sortie |
| `close` | Ferme un descripteur de fichier. Libère les ressources. Évite les fuites de descripteurs |
| `dup2` | Duplique un descripteur de fichier. Ferme automatiquement l'ancien descripteur. Utilisé pour la redirection des entrées/sorties |

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

---

## ⚙️ **Compilation et tests**

### 🔧 Compilation
- Pour compiler **pipex**:
  ```bash
  make
  ```
- Pour compiler **la partie bonus**:
  ```bash
  make bonus
  ```
- Pour supprimer les fichiers objets et les binaires compilés :
  ```bash
  make fclean
  ```

---

### ▶️ Utilisation et exécution

- #### ✅ Exécution de `pipex` pour la partie obligatoire:
  L’exécutable **`pipex`** prend 4 arguments:
  * `file1` et `file2` sont des noms de fichier.
  * `cmd1` et `cmd2` sont des commandes shell avec leurs paramètres.
    * Si les commandes prennent des arguments il faut les mettre entre guillemets (*Ex:* `"wc -l"`) 
  ```bash
  ./pipex file1 cmd1 cmd2 file2
  ```
  #### Tests partie obligatoire
  * Test de base 2 commande simples:
    ```bash
    ./pipex infile "ls -l" "wc -l" outfile
    < infile ls -l | wc -l > outfile
    ```

   * Test avec fichier d'entrée inexistant:
     ```bash
     ./pipex nonexistent "ls" "wc -l" outfile
     < nonexistent ls | wc -l > outfile
     ```
  
   * Test avec fichier de sortie sans permissions:
     ```bash
     chmod 000 outfile
     ./pipex infile "ls" "wc -l" outfile
     < infile ls | wc -l > outfile
     ```
  
   * Test de commandes inexistantes:
     ```bash
     ./pipex infile "nonexistentcmd" "wc -l" outfile
     < infile nonexistentcmd | wc -l > outfile
     ```
  
   * Test de commandes avec syntaxe invalide:
     ```bash
     ./pipex infile "ls -" "wc -l" outfile
     < infile ls - | wc -l > outfile
     ```
  
   * Test de commandes avec arguments spéciaux:
     ```bash
     ./pipex infile "echo 'hello world'" "wc -w" outfile
     < infile echo 'hello world' | wc -w > outfile
     ```
  
   * Test de performance (Gros fichier d'entrée):
     ```bash
     dd if=/dev/urandom of=largefile bs=1M count=100
     ./pipex largefile "grep a" "wc -l" outfile
     < largefile grep a | wc -l > outfile
     ```
  
   * Test avec chemin:
     ```bash
     ./pipex infile "/bin/cat /etc/passwd" "wc -l" outfile
     < infile /bin/cat /etc/passwd | wc -l > outfile
     ```
  
   * Test avec commande sleep:
     ```bash
     ./pipex infile "sleep 2" "wc -l" outfile
     < infile sleep 2 | wc -l > outfile
     ```

- #### 🚀 Exécution de `pipex` pour la partie bonus:
  * L’exécutable **`pipex`** pour la partie bonus prend **au moins** 4 arguments:
    * `file1` et `file2` sont des noms de fichier.
    * `cmd1`, `cmd2`... sont des commandes shell avec leurs paramètres.
  ```bash
  ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
  ```
  * `here_doc`
  ```bash
  ./pipex here_doc LIMITER cmd cmd1 file
  ```
  #### Tests partie bonus
  * Test avec plusieurs pipes (3 commandes):
    ```bash
     ./pipex infile "cat" "grep test" "wc -l" outfile
     < infile cat | grep test | wc -l > outfile
    ```

   * Test avec plusieurs pipes (4 commandes):
     ```bash
     ./pipex infile "cat" "grep test" "sort" "uniq -c" outfile
     < infile cat | grep test | sort | uniq -c > outfile
     ```
  
   * Test tricky:
     ```bash
     ./pipex /dev/stdin "cat" "cat" "cat" "cat" "ls" "cat" /dev/stdout
     < /dev/stdin cat | cat | cat | cat | ls | cat > /dev/stdout
     ```
  
   * Test avec plusieurs pipes (10 commandes):
     ```bash
     ./pipex infile "cat" "grep test" "sort" "uniq" "wc -l" "cat" "cat" "cat" "cat" "cat" outfile
     < infile cat | grep test | sort | uniq | wc -l | cat | cat | cat | cat | cat > outfile
     ```
  
   * Test avec plusieurs pipes et chemins:
     ```bash
     ./pipex infile "/bin/cat /etc/passwd" "grep root" "wc -l" outfile
     < infile /bin/cat /etc/passwd | grep root | wc -l > outfile
     ```
  
   * Test avec `here_doc`:
     ```bash
     ./pipex here_doc LIMITER "cat" "wc -l" outfile
     cat << LIMITER | wc -l >> outfile
     ```
  
   * Test `here_doc` avec plusieurs pipes:
     ```bash
     ./pipex here_doc LIMITER "cat" "grep test" "wc -l" outfile
     cat << LIMITER | grep test | wc -l >> outfile
     ```
  
   * Test `here_doc` avec commandes complexes:
     ```bash
     ./pipex here_doc LIMITER "grep -i hello" "sort -r" "uniq -c" outfile
     grep -i hello << LIMITER | sort -r | uniq -c >> outfile
     ```
  
   * Test `here_doc` avec erreurs:
     ```bash
     ./pipex here_doc LIMITER "nonexistentcmd" "wc -l" outfile
     nonexistentcmd << LIMITER | wc -l >> outfile
     ```

   * Test `here_doc` avec sleep:
     ```bash
     ./pipex here_doc LIMITER "sleep 1" "echo 'test'" "wc -l" outfile
     sleep 1 << LIMITER | echo 'test' | wc -l >> outfile
     ```

   * Test `here_doc` avec chemin:
     ```bash
     ./pipex here_doc LIMITER "/bin/cat /etc/passwd" "grep root" "wc -l" outfile
     /bin/cat /etc/passwd << LIMITER | grep root | wc -l >> outfile
     ```
