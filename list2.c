/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:51:57 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/09 03:35:47 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char 	*subc_quots(char *str)
{
	int i;
	int j;
	char *ret;
	
	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(str));
	j = 0;
	while(str[i])
	{
		if(str[i] != '\'' && str[i] != '"')
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	printf("||||   %s\n", ret);
	return(ret);
}

t_cmd	*ft_lstnew(char *cmd, char **env)
{
	t_cmd	*l;
	char	*str = NULL;
	// char *new = NULL;
	int		i;
(void)env;
	l = malloc(sizeof(t_cmd));
	l->s_substruct = NULL;
	if (!l)
		return (NULL);
	i = 0;
	// new = expand_ret(cmd, env);
	// printf("new ==> %s\n", new);
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			str = get_quotes(cmd, &i, SQUOTE);
			i++;
		}
		else if (cmd[i] == '"')
		{
			i++;
			str = get_quotes(cmd, &i, DQUOTES);
			i++;
		}
		else if (cmd[i] == '>' || cmd[i] == '<')
		{
			str = get_redirection(cmd, &i);
			if(ft_strlen(str) > 2 || ft_strlen(str) < 1)
			{
				if(str[0] == '>' && str[1] == '>')
				{
					an.exit_status = 255;
					write(2, "minishell: syntax error near unexpected token `>>'\n", 52);
				}
				if(str[0] == '<' && str[1] == '<')
				{
					an.exit_status = 255;
					write(2, "minishell: syntax error near unexpected token `<<'\n", 52);

				}
				return NULL;
			}
		}
		else
			str = get_command(cmd, &i);
		if(str)
		{
			// printf("str <========> %s\n", str);
			n_lstadd_back(&(l->s_substruct), n_lstnew(str));
		}
		while (cmd[i] == ' ')
			i++;
	}
	l->data = cmd;
	l->fileout = 1;
	l->filein = 0;
	l->next = NULL;
	l ->prev = NULL;
	l->i = 0;
	return (l);
}

int	ft_lstsize(t_cmd *lst)
{
	int		cont;
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return (0);
	cont = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		cont++;
	}
	return (cont);
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return (0);
	if (ft_lstsize(tmp) == 1)
		return (tmp);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		return (tmp);
	}
}

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = ft_lstlast(*lst);
	if (*lst)
	{
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
	if (new->prev)
		new->i = new->prev->i + 1;
}
