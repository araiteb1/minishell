/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:11 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/09 04:26:51 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *find_home() {
    t_environement *tmp = an.environement;

    while (tmp) {
        if (strcmp(tmp->cle, "HOME") == 0) {
            return tmp->valeur;
        }
        tmp = tmp->next;
    }
    return NULL;
}

int	search_pwd(char *pwd)
{
	t_environement	*tmp;
	char	*pwd_;

	tmp = an.environement;
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "PWD"))
		{
			free(tmp->valeur);
			tmp->valeur = ft_strdup(pwd);
			free(tmp->env);
			pwd_= ft_strjoin(tmp->cle, "=");
			if (!pwd_)
				return (an.exit_status = 1, perror(""), exit(1), 0);
			tmp->env = ft_strjoin(pwd_, tmp->valeur);
			return (free(pwd_), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char *	search_oldpwd(char *oldpwd)
{
	t_environement	*tmp;
	char	*oldpwd_;
    char *var;

	tmp = an.environement;
    var = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "OLDPWD") )
		{
			free(tmp->valeur);
			tmp->valeur = ft_strdup(oldpwd);
            var = tmp->valeur;
			free(tmp->env);
			oldpwd_ = ft_strjoin(tmp->cle, "=");
			if (!oldpwd_)
				return (an.exit_status = 1, perror(""),exit(1), NULL);
			tmp->env = ft_strjoin(oldpwd_, tmp->valeur);
			free(oldpwd_);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (var);
}

int change_directories(char *pwd) {
    char *pwd_;
    char *oldpwd_;

    oldpwd_ = NULL;
    t_environement *tmp= an.environement;
    char *tt; 
     while(tmp)
    {
        if(ft_strcmp(tmp->cle,"PWD")== 0)
        {
            tt = tmp->valeur;
        }
        tmp = tmp->next;
            
    }
    if (search_oldpwd(tt)) {
        oldpwd_ = ft_strjoin("OLDPWD=", tt);
        if (!oldpwd_) {
            perror("ft_strjoin");
            return 1;
        }
        lstadd_back_environement(&an.environement, creation_node_in_env(oldpwd_, ft_strdup("OLDPWD"), ft_strdup(tt)));
        free(oldpwd_);
    }    
    if (search_pwd(pwd)) {
        pwd_ = ft_strjoin("PWD=", pwd);
        if (!pwd_) {
            perror("ft_strjoin");
            return 1;
        }
        lstadd_back_environement(&an.environement, creation_node_in_env(pwd_, ft_strdup("PWD"), ft_strdup(pwd)));
        free(pwd_);
    }
    return 0;
}

void ft_cd(t_cmd *cmd)
{
    char *to;
    t_substruct *var ;


    var = cmd->s_substruct->next;
    if (!var) 
    {
     to = find_home();
    if (!to)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        an.exit_status = 1;
        return;
    }
    } 
    if (var) 
        to = var->data;
    if (chdir(to)) 
    {
        ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(ft_strjoin(to,": "), 2);
        perror("");
        an.exit_status = 1;
        return ;
    }
    to = getcwd(an.pwd, PATH_MAX);
    if(!to && errno == ENOENT)
    {
        ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
        ft_putstr_fd("cannot access parent directories: ", 2);
        ft_putstr_fd("No such file or directory\n", 2);
        an.exit_status = 0;
        return ;
    }
    else 
        change_directories(to);
    an.exit_status = 0;
}
