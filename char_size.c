/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 04:07:40 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/05 23:32:47 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**__resize(char **Array, char *new)
{
	int		len;
	char	**tmp;
	int		i;

	if (!Array)
		len = 0;
	else
		len = ft_size_tab(Array);
	tmp = (char **)malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (i < len)
	{
		tmp[i] = strdup(Array[i]);
		// printf("--------->%s \n", tmp[i]);
		i++;
	}
	tmp[len] = strdup(new);
	tmp[len + 1] = NULL;
	if(Array)
		free (Array);
	// printf("\n--> `%s` <--\n", tmp[i]);
	return (tmp);
}

void	ft_close_pipe(t_cmd *ls, int **fds)
{
	int	i;

	i = 0;
	while (i < ft_lstsize(ls))
	{
		close (fds[i][0]);
		close (fds[i][1]);
		i++;
	}
}
