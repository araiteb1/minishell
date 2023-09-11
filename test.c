#include "minishell.h"

char **get_env_values(t_environement *env_list)
{
    // Comptons d'abord combien d'éléments sont présents dans la liste
    int count = 0;
    t_environement *current = env_list;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    // Allouons de la mémoire pour le tableau de chaînes de caractères
    char **env_values = (char **)malloc((count + 1) * sizeof(char *));
    if (env_values == NULL)
    {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Remplissons le tableau avec les valeurs de env
    current = env_list;
    int i = 0;
    while (current != NULL)
    {
        env_values[i] = current->env;
        i++;
        current = current->next;
    }
    env_values[i] = NULL; // Ajout d'un pointeur NULL à la fin du tableau

    return env_values;
}

int main()
{
    // Exemple d'utilisation de la fonction
    char **env_values = get_env_values(an.environement);

    // Affichage des valeurs de env
    int i = 0;
    while (env_values[i] != NULL)
    {
        printf("env[%d]: %s\n", i, env_values[i]);
        i++;
    }

    // N'oubliez pas de libérer la mémoire allouée pour le tableau
    free(env_values);

    return 0;
}
// #include "minishell.h"

// char **get_env_values(t_environement *env_list)
// {
//     // Comptons d'abord combien d'éléments sont présents dans la liste
//     int count = 0;
//     t_environement *current = env_list;
//     while (current != NULL)
//     {
//         count++;
//         current = current->next;
//     }

//     // Allouons de la mémoire pour le tableau de chaînes de caractères
//     char **env_values = (char **)malloc((count + 1) * sizeof(char *));
//     if (env_values == NULL)
//     {
//         perror("Erreur lors de l'allocation de mémoire");
//         exit(EXIT_FAILURE);
//     }

//     // Remplissons le tableau avec les valeurs de env
//     current = env_list;
//     int i = 0;
//     while (current != NULL)
//     {
//         env_values[i] = current->env;
//         i++;
//         current = current->next;
//     }
//     env_values[i] = NULL; // Ajout d'un pointeur NULL à la fin du tableau

//     return env_values;
// }

// int main()
// {
//     // Exemple d'utilisation de la fonction
//     char **env_values = get_env_values(an.environement);

//     // Affichage des valeurs de env
//     int i = 0;
//     while (env_values[i] != NULL)
//     {
//         printf("env[%d]: %s\n", i, env_values[i]);
//         i++;
//     }

//     // N'oubliez pas de libérer la mémoire allouée pour le tableau
//     free(env_values);

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main() {
//     int fd[2]; // Descripteurs de fichier pour le tube
//     pid_t child_pid;
//     // printf("       ------>fd 0: %d", fd[0]);
//     //  printf("       ------>fd 1: %d", fd[1]);
//     // Créer un tube
//     if (pipe(fd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     // Créer un processus enfant
//     if ((child_pid = fork()) == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (child_pid == 0) {
//         // Code du processus enfant
//         close(fd[1]); // Fermer le descripteur d'écriture du tube

//         char buffer[256];
//         ssize_t bytes_read = read(fd[0], buffer, sizeof(buffer));
//         if (bytes_read > 0) {
//             printf("Processus enfant a lu : %.*s", (int)bytes_read, buffer);
//         }
//         close(fd[0]);
//     } else {
//         // Code du processus parent
//         close(fd[0]); // Fermer le descripteur de lecture du tube

//         char message[] = "Bonjour, processus enfant!";
//         write(fd[1], message, sizeof(message));
//         close(fd[1]);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <fcntl.h>

// int main() {
//     int file = open("sortie.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

//     // Rediriger la sortie standard (STDOUT_FILENO) vers le fichier "sortie.txt"
//     dup2(file, STDOUT_FILENO);

//     // À partir de maintenant, tout ce qui serait écrit sur la sortie standard va aller dans "sortie.txt"

//     printf("Ceci sera écrit dans le fichier.\n");
//     printf("Et cela aussi.\n");

//     // Ne pas oublier de fermer le descripteur de fichier après utilisation
//     close(file);

//     return 0;
// }

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file = open("sortie.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    // Dupliquer le descripteur de fichier vers le premier descripteur disponible
    int new_fd = dup(file);

    // À partir de maintenant, new_fd et file pointent vers le même fichier

    // Écrire dans le fichier en utilisant le nouveau descripteur
    dprintf(new_fd, "Ceci sera écrit dans le fichier.\n");

    // Fermer les descripteurs de fichier
    close(file);
    close(new_fd);

    return 0;
}

