# **Minishell - Projet 42** ⌨️

## **Votre propre shell Unix simplifié**

Implémentation en C d'un interpréteur de commandes respectant les standards POSIX.

---

## **Fonctionnalités Clés** ⚙️

- Commandes simples et pipelines (`cmd1 | cmd2`)
- Redirections (`<`, `>`, `>>`)
- Variables d'environnement (`$USER`)
- Gestion des signaux (`Ctrl-C`/`Ctrl-D`/`Ctrl-\`)

---

## **Builtins Implémentés** 🔨

| Commande   | Description                          | Exemple                  |
|------------|--------------------------------------|--------------------------|
| `echo`     | Affiche les arguments                | `echo "Bonjour"`         |
| `cd`       | Change de répertoire                 | `cd ~/Desktop`           |
| `pwd`      | Affiche le répertoire courant        | `pwd`                    |
| `export`   | Définit une variable d'environ       | `export NAME=value`      |
| `unset`    | Supprime une variable                | `unset NAME`             |
| `env`      | Liste les variables d'environ        | `env`                    |
| `exit`     | Quitte le shell                      | `exit 42`                |

---

## **Compilation & Utilisation** 🛠️

```bash
make && ./minishell
