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
