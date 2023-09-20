/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:21:17 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 03:23:31 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_wordsplit(char *s, int **j, char c)
{
	int	found_s;
	int	found_d;
	int	len;

	len = 0;
	found_s = 0;
	found_d = 0;
	while (s[**j] && s[(**j) + len])
	{
		if ((s[(**j) + len] == c && found_d == 0 && found_s == 0))
			break ;
		if (s[(**j) + len] == DQUOTES)
			found_d = 1 - found_d;
		else if (s[(**j) + len] == SQUOTE)
			found_s = 1 - found_s;
		len++;
	}
	return (len);
}

void	malloc_wordspl(char **cases, int len, int *found_s, int *found_d)
{
	*cases = malloc((len + 1) * sizeof(char));
	if (!(*cases))
		return ;
	*found_s = 0;
	*found_d = 0;
}
