/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:01:11 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/24 17:46:01 by kethouve         ###   ########.fr       */
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

typedef struct s_cmd_file
{
	char	***cmd;
	char	*file2;
	char	*keyword;
	int		n_cmd;
}	t_cmd_file;

typedef struct s_ms
{
	char		**envp;
	char		**env;
	int			put_in_file;
	int			concat_file;
	int			readfile;
	int			wait_write;
	t_cmd_file	*data;
}	t_ms;

typedef struct s_split
{
	int	i;
	int	j;
	int	index;
	int	qs;
}	t_split;

int		main(int argc, char **argv, char **envp);
char	**get_env(char **envp);
void	debut_minishell(t_ms *ms_data);

void	final_cmd(t_ms *ms_data, char ***cmd_temp2);
void	malloc_cmd(t_ms *ms_data, char ***cmd_temp2);

int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin(char const *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_strdup_quote(const char *s);

int		quote_analyse(char c, int *quote_status);
int		quote_in_word(char *s);

char	**ft_split_env(char const *s, char c);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
int		tabs_size(char const *s, char c);
char	*put_words(char const *s, int debut, int end);

char	**ft_split2(char const *s, char c);

char	*dup_var(char *s, char **envp);

void	free_tab_tab(char ***tab_tab);
void	free_tab(char **tab);
void	free_struct(t_ms *ms_data);
#endif