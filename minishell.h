/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:01:11 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/20 23:52:52 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stddef.h>
# include <signal.h>
# include <termios.h>

typedef struct s_cmd_file
{
	char	***cmd;
	char	*file1;
	char	*file2;
	char	*keyword;
	int		n_cmd;
}	t_cmd_file;

typedef struct s_ms
{
	char		**envp;
	char		**env;
	char		*tilde;
	int			put_in_file;
	int			concat_file;
	int			readfile;
	int			wait_write;
	int			only_heredoc;
	int			status;
	t_cmd_file	*data;
}	t_ms;

typedef struct s_split
{
	int	i;
	int	j;
	int	index;
	int	qs;
}	t_split;

typedef struct s_tri_index
{
	int	i;
	int	j;
	int	k;
}	t_tri_index;

typedef struct s_pipe
{
	char	**env;
	char	**cmd;
	char	***cmds;
	int		i;
	int		*ij;
	int		j;
	int		**pipefd;
	int		fd;
	int		fd2;
	int		status;
}	t_pipe;

int		main(int argc, char **argv, char **envp);
char	**get_env(char **envp);
void	debut_minishell(t_ms *ms_data);

void	final_cmd(t_ms *ms_data, char ***cmd_temp2);

int		ft_strncmp(const char *s1, const char *s2, int n, int cmd);
char	*ft_strjoin(char const *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*dup_quote(const char *s);

int		quote_analyse(char c, int *quote_status);
int		quote_in_word(char *s);
void	malloc_cmd(t_ms *ms_data, char ***cmd_temp2);
int		verif_operator(char ***cmd_temp2, t_ms *ms_data);
int		var_in_s(char *s);

char	**ft_split_env(char const *s, char c);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
int		tabs_size(char const *s, char c);
char	*put_words(char const *s, int debut, int end);

char	**ft_split2(char const *s, char c);

char	*dup_var(char *s, char **envp);
void	createfile(char *file, t_ms *ms_data);
void	new_cd(char *cmd, t_ms *ms_data);

void	free_tab_tab(char ***tab_tab);
void	free_tab(char **tab);
void	free_struct(t_ms *ms_data);

int		exec(char ***cmd, t_ms *ms_data);
void	ft_putstr2(char *a, char ***cmds, int *ij);
void	freee(char **a);
void	freee2(int	**a, t_ms *ms_data);

int		exec2(char ***cmd, t_ms *ms_data);

char	*recup(char *cmd, char *mod);;
char	**new_export(t_ms *ms_data, char *cmd);
char	**new_unset(t_ms *ms_data, char *cmd, char *temp2);

void	put_file(t_ms *ms_data);
void	wait_write(t_ms *ms_data);
int		verif(t_ms *ms_data);
void	execution(t_ms *ms_data);
int		execution2(t_ms *ms_data, int i, t_pipe *pipee);
int		execution3(t_ms *ms_data);
int		execution4(t_ms *ms_data, int i);

void	new_echo(char **cmd, t_ms *ms_data);
void	new_pwd(size_t size);
void	new_env(t_ms *ms_data);
void	new_exit(t_ms *ms_data);
void	new_exit2(t_pipe *pipee, t_ms *ms_data);

char	**ft_strdup2(char **s);
char	***ft_strdup3(char ***s);

void	add_first(char ***cmds);
void	closee(t_pipe *pipee, t_ms *ms_data, int x, int y);
void	closeee(t_pipe *pipee, t_ms *ms_data, int x, int x2);
void	seearsh22(t_pipe *pipee);

void	setexec(t_pipe *pipee, t_ms *ms_data);
void	exec_exec(t_pipe *pipee, t_ms *ms_data);

void	start2(t_pipe *pipee, t_ms *ms_data);
void	end2(t_pipe *pipee, t_ms *ms_data);
void	mid2(t_pipe *pipee, t_ms *ms_data);

void	put_file(t_ms *ms_data);
void	wait_write(t_ms *ms_data);

char	*ft_itoa(int n);

void	handle_sigint_parent(int sig);
void	handle_sigint_child(int sig);
void	handle_sigquit(int sig);
void	get_signal(void);
void	print_status(t_ms *ms_data);
char	**no_export(t_ms *ms_data, char *t);
void	print_3_tab(char ***s);
int		verif_export(char *cmd);

void	verif_absolute_path(t_ms *ms_data);

int		exec2_no(char ***cmd, t_ms *ms_data);
int		exec_no(char ***cmd, t_ms *ms_data);
void	exec_exec_no(t_pipe *pipee, t_ms *ms_data);
void	start2_no(t_pipe *pipee, t_ms *ms_data);
void	end2_no(t_pipe *pipee, t_ms *ms_data);
void	mid2_no(t_pipe *pipee, t_ms *ms_data);
int		verif_no(t_ms *ms_data);
int		verif_pash_exist(t_ms *ms_data, int i, int j);

void	verif_var(char ***ct2, t_tri_index *t_i, char **envp);

void	print_export(t_ms *ms_data);
int		verif_cmd_null(t_ms *ms_data);

#endif