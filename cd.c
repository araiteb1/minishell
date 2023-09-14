/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:11 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/14 02:40:08 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*find_home(void)
{
	t_environement	*tmp;

	tmp = an.environement;
	while (tmp) 
	{
		if (strcmp(tmp->cle, "HOME") == 0)
			return (tmp->valeur);
		tmp = tmp->next;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	an.exit_status = 1;
	return (NULL);
}

void	search_pwd(char *pwd)
{
	t_environement	*tmp;
	char			*pwd_;

	tmp = an.environement;
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "PWD"))
		{
			free(tmp->valeur);
			tmp->valeur = ft_strdup(pwd);
			free(tmp->env);
			pwd_ = ft_strjoin(tmp->cle, "=");
			tmp->env = ft_strjoin(pwd_, tmp->valeur);
		}
		tmp = tmp->next;
	}
}

void	search_oldpwd(char *oldpwd)
{
	t_environement	*tmp;
	char			*oldpwd_;
	char			*var;

	tmp = an.environement;
	var = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "OLDPWD"))
		{
			free(tmp->valeur);
			tmp->valeur = ft_strdup(oldpwd);
			var = tmp->valeur;
			free(tmp->env);
			oldpwd_ = ft_strjoin(tmp->cle, "=");
			tmp->env = ft_strjoin(oldpwd_, tmp->valeur);
			free(oldpwd_);
		}
		tmp = tmp->next;
	}
}

void	change_directories(char *pwd)
{
	t_environement	*tmp;
	char			*tt;

	tmp = an.environement;
	while (tmp)
	{
		if (ft_strcmp(tmp->cle, "PWD") == 0)
			tt = tmp->valeur;
		tmp = tmp->next;
	}
	search_oldpwd(tt);
	search_pwd(pwd);
}

void	ft_cd(t_cmd *cmd)
{
	char		*to;
	t_substruct	*var ;

	var = cmd->s_substruct->next;
	if (!var) 
	{
		to = find_home();
		if (!to)
			return ;
	}
	if (var) 
		to = var->data;
	if (!chedir_error(to)) 
		return ;
	to = getcwd(an.pwd, PATH_MAX);
	if (!cd_not_exist_directory(to))
		return ;
	else 
		change_directories(to);
	an.exit_status = 0;
}
