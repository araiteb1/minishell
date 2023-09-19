/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:42:54 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 00:02:47 by nait-ali         ###   ########.fr       */
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
