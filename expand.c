/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 22:23:53 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/06 07:51:53 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_quotline(char *line, int *flag)
{
    int i;

    i = 0;
    if(line[i] == '\'' && *flag == 0)
        *flag = 1;
    else if(line[0] == '\'' && *flag == 1)
        *flag = 0;
    if(line[0] == '"' && *flag == 0)
        *flag = 2;
    else if(line[0] == '"' && *flag == 2)
        *flag = 0;
    return(*flag);
}

int     ft_size_nam(char *str, char c)
{
    int i = 0;
    while(str[i] != c)
        i++;
    return(i);
}
char    *var_expand(char *line, int *start)
{
    int i;
    int size=0;
    char *ret;

    i = (*start);
    while(line[*start] && line[*start] != ' ' && line[*start] != '$')
    {
        size++;
        (*start)++;
    }
    ret = ft_substr(line, i, size);
    return(ret);
}
char    *ret_expand_val(char *str, char **env)
{
    int i = 0;
    char *value;
    
    value = NULL;
    while(env[i])
    {
         if(ft_strncmp(env[i], str, ft_size_nam(env[i],'=')))
             i++;
         else
             break;
    }
    if(env[i])
        value = ft_substr(env[i], ft_size_nam(env[i], '=') + 1,ft_strlen(env[i]));
    return(value);
}

char    *expand_ret(char *line, char **env)
{
    int i = 0;
    char   *var =NULL;
    char *res= NULL;
    char    *str= NULL;
    char *value;
    int size = 0;
    int start;
    start = i;
    while(line[i])
    {
        size = 0;
        while(line[i] != '$')
        {
            size++;
            i++;
        }
        res = ft_substr(line, start, size);
        i++;
        var = var_expand(line, &i);
        start = i;
        value = ret_expand_val(var, env);
        if(var)
            free(var);
        res = ft_strjoin(res, value);
        str = ft_strjoin(str, res);
        if(value)
            free(value);
    }
    return(str);
}