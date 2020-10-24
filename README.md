# 42 project
- project name: minishell
- summary: *"The objective of this project is for you to create a simple shell. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors."*

# readings 

### algo
- principle http://paysdu42.fr/?page=minishell.c&fbclid=IwAR3BDgRVFdwilQd3NcXHJ1FaWG76C607FIxGKqScSvjMHTuxbM_YqYsrZYA
- principle https://segfault42.github.io/posts/minishell/
- example https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
- example https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe

### syscalls
- getcwd() http://manpagesfr.free.fr/man/man3/getcwd.3.html
- file management
  - stat() http://manpagesfr.free.fr/man/man2/stat.2.html
  - access() https://pubs.opengroup.org/onlinepubs/007904975/functions/access.html
- process management
  - fork() https://www.geeksforgeeks.org/fork-system-call/
  - wait() http://manpagesfr.free.fr/man/man2/wait.2.html

### pipes
- simple explanation for how pipes work in Bash https://stackoverflow.com/questions/9834086/what-is-a-simple-explanation-for-how-pipes-work-in-bash
- unix pipes http://web.cse.ohio-state.edu/~mamrak.1/CIS762/pipes_lab_notes.html
- pipe chaining https://stackoverflow.com/questions/43030966/pipe-chaining-in-my-own-shell-implementation

### redirections
- wiki https://fr.wikibooks.org/wiki/Le_syst%C3%A8me_d%27exploitation_GNU-Linux/Redirection_des_entr%C3%A9es/sorties
- oc course https://openclassrooms.com/fr/courses/43538-reprenez-le-controle-a-laide-de-linux/40444-les-flux-de-redirection
- > https://github.com/PimpMy42Sh/depot/blob/f45695ba20c6acece4fe722640f8b246156c43f0/REDIRECTIONS/chevron_droite.c
- > and >> https://serverfault.com/questions/196734/bash-difference-between-and-operator

### good to know
- PATH_MAX https://stackoverflow.com/questions/9449241/where-is-path-max-defined-in-linux
- Variables en shell Bash http://www.epons.org/shell-bash-variables.php
- $? https://stackoverflow.com/questions/35457979/what-is-echo-in-linux-terminal

### intra ressources
- https://elearning.intra.42.fr/notions/27/subnotions/929/videos/1020
- https://elearning.intra.42.fr/notions/57/subnotions/245/videos/203
