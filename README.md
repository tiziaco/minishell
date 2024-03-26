# minishell
Replicate the Linux shell.

Clone the repository including the sub-modules (Libft):

```bash
git clone --recurse-submodules git@github.com:tiziaco/minishell.git
```

Execute the program with Valgrind to check for memory leaks:

```bash
valgrind --suppressions=ignore_readline_leaks.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
```