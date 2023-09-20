/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:42:54 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 03:22:18 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*----split------*/
void	check_strsplit(char **s, char c, int found_d, int found_s)
{
	while (**s)
	{
		if (**s == c && found_d == 0 && found_s == 0)
			break ;
		if (**s == DQUOTES)
			found_d = 1 - found_d;
		else if (**s == SQUOTE)
			found_s = 1 - found_s;
		(*s)++;
	}
}

static int	ft_num_case(char *s, char c)
{
	int	num;
	int	found_s;
	int	found_d;

	num = 0;
	found_d = 0;
	found_s = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (!(*s))
			return (num);
		check_strsplit(&s, c, found_d, found_s);
		num++;
	}
	return (num);
}

static char	*ft_alloc_case(char *s, char c, int *j)
{
	char	*cases;
	int		i;
	int		len;
	int		found_s;
	int		found_d;

	while (s[*j] && s[*j] == c)
		(*j)++;
	len = len_wordsplit(s, &j, c);
	malloc_wordspl(&cases, len, &found_s, &found_d);
	i = 0;
	while (s[*j])
	{
		if ((s[(*j)] == c && found_d == 0 && found_s == 0))
			break ;
		if (s[(*j)] == DQUOTES)
			found_d = 1 - found_d;
		else if (s[(*j)] == SQUOTE)
			found_s = 1 - found_s;
		cases[i] = s[*j];
		(*j)++;
		i++;
	}
	cases[i] = '\0';
	return (cases);
}

char	**ft_split(char *s, char c)
{
	int		n;
	int		i;
	int		j;
	char	**str;

	if (!s)
		return (NULL);
	n = ft_num_case(s, c);
	str = (char **)malloc((n + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		str[i] = ft_alloc_case(s, c, &j);
		if (!str[i])
		{
			ft_free(str);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}
