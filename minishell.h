/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:32 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/08 02:40:07 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<signal.h>
#include<stdbool.h>

# define DQUOTES 0
# define SQUOTE 1

typedef enum e_types
{
	pip,
	word,
	rd_input,
	rd_output,
	rd_output_append,
	heredoc,
	newline
}	t_types;

typedef struct s_subStruct
{
	char				*data;
	int					type;
	int					cls;
	char 				*expand;
	struct s_subStruct	*next;
	struct s_subStruct	*prev;
}	t_substruct;

typedef struct s_cmd{
	char			*data;
	int				i;
	pid_t			*pd;
	int				**fds;
	t_substruct		*s_substruct;
	int				filein;
	int				fileout;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_environement
{
	char			*env;
	char			*cle;
	char			*valeur;
	struct s_environement	*next;
}	t_environement;

typedef struct s_gvar
{
	int		exit_status;
	t_environement	*environement;
	char *pwd;
	int flag_signal;
	int flag_herdoc;
}	t_gvar;

extern t_gvar	an;

// void increment_shlvl();

/*-----function_exect_par------*/

void sigint_herdoc(int sig);
int	here_doc(char *tmps, char *end);
char		**ft_split(const char *s, char c);
int			ft_check_fils(char *name_fd, int mode, int permession);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_get_path(char *argv, char **env);
int			get_ev(char **env);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(const char *s);
char		*ft_substr(const char *s, unsigned int start, size_t len);
void		print_cmds(t_cmd *ls);
int			syntaxe_error(t_cmd *ls);
t_cmd		*ft_lstnew(char *cmd);
int			ft_lstsize(t_cmd *lst);
t_cmd		*ft_lstlast(t_cmd *lst);
void		ft_lstadd_back(t_cmd **lst, t_cmd *new);
int			get_type(char *s);
t_substruct	*n_lstnew(char *cmd);
int			n_lstsize(t_substruct *lst);
t_substruct	*n_lstlast(t_substruct *lst);
void		n_lstadd_back(t_substruct **lst, t_substruct *new);
char		*get_quotes(char *cmd, int *start, int type);
char		*get_redirection(char *cmd, int *start);
char		*get_command(char *cmd, int *start);
char		*ft_strtrim(char const *s1, char const *set);
void		free_sublist(t_substruct **substruct);
void		free_list(t_cmd **substruct);
void		exec_chile(char **option, char **env, t_cmd *list);
int			here_doc(char *tmps, char *end);
void		ft_free(char **str);
int			ft_check_fils(char *name_fd, int mode, int permession);
void		ft_execution(t_cmd *list, char **env);
char		**__resize(char **Array, char *new);
void    	ft_dup(t_cmd *ls, char **option, char **env);
void		ft_close(t_cmd *ls);
void		ft_close_pipe(t_cmd *ls, int **fds);
void		ft_free_matrix(int **str, int size);
void		ft_creat_pipe(int size, int **fds);
int		get_rd(t_substruct **cmd, t_cmd *ls, int **fds);
int		find_equal(char *s, char c);
void	ft_unset(t_cmd *cmd);
t_environement	*create_env(char **tab);
void  ft_cd(t_cmd *cmd);
void	ft_echo(t_cmd *ls);
void	ft_env(t_cmd *cmd);
void ft_exit(t_cmd *lst);
int	ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
int	ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
void ft_pwd(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	free_environement(void);
void	lstadd_back_environement(t_environement **lst, t_environement *new);
t_environement	*creation_node_in_env(char *env, char *key, char *val);
void ft_export(t_cmd *cmd);
void	ft_cd(t_cmd *cmd);
int check_builtins(t_cmd *cmd);
char	*ft_itoa(int n);



#endif
