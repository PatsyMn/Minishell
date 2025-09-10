/*
Un shell est un programme interactif où l’utilisateur tape des commandes.
Pendant son fonctionnement :
- L’utilisateur peut appuyer sur Ctrl+C pour interrompre une commande (envoyer un signal SIGINT).
- Il peut appuyer sur Ctrl+Z pour suspendre un processus (SIGTSTP).

Le shell doit réagir :
- Interrompre la commande en cours sans fermer le shell.
- Ignorer certains signaux quand il est en mode lecture.
- Gérer proprement les processus enfants (les commandes lancées).

SIGINT	Interruption (Ctrl+C)	Interrompt la commande en cours
SIGQUIT	Quit (Ctrl+)	Quitte un processus, crée core dump
SIGTSTP	Suspend (Ctrl+Z)	Suspend un processus (stop)
SIGCHLD	Un processus enfant s’est terminé	Permet au shell de gérer la fin

en resume :
- Dans le shell (parent) :
Installer un handler custom pour SIGINT (Ctrl+C) comme dans l’exemple que je t’ai donné, pour que Ctrl+C n’arrête pas le shell mais seulement la commande en cours.

- Dans le processus enfant (fork + exec) :
Remettre le comportement par défaut des signaux (signal(SIGINT, SIG_DFL)) pour que Ctrl+C interrompe la commande enfant.
*/
