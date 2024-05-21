/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:01:11 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/21 18:15:45 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd_file
{
	char ***cmd;
	char *file2;
	char *keyword;
	int n_cmd;
}	t_cmd_file;

typedef struct s_ms
{
	char	**envp;
	char	**env;
	int		put_in_file; //>>
	int		concat_file; //>
	int		readfile; //<
	int		wait_write; //<<
	t_cmd_file	*data;
}	t_ms;

int		main(int argc, char **argv, char **envp);
char	**get_env(char **envp);
void 	debut_minishell();
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin(char const *s1, const char *s2);
char	**ft_split_env(char const *s, char c);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	**ft_split2(char const *s, char c);

#endif