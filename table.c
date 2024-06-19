/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:39:51 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/20 01:34:30 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid1;

int	get_temp_cmd(t_ms *ms_data, char *test)
{
	int		i;
	char	**cmd_temp;
	char	***cmd_temp2;

	i = -1;
	cmd_temp = ft_split(test, '|');
	while (cmd_temp[++i])
		ms_data->data->n_cmd++;
	i = 0;
	cmd_temp2 = malloc(sizeof(char **) * (ms_data->data->n_cmd + 2));
	while (cmd_temp[i])
	{
		cmd_temp2[i] = ft_split2(cmd_temp[i], ' ');
		i++;
	}
	cmd_temp2[i] = NULL;
	if (verif_operator(cmd_temp2, ms_data) == 1)
		return (printf("operator incorrect\n"),
			free_tab(cmd_temp), free_tab_tab(cmd_temp2), 1);
	ms_data->data->cmd = malloc(sizeof(char **) * (ms_data->data->n_cmd + 1));
	malloc_cmd(ms_data, cmd_temp2);
	final_cmd(ms_data, cmd_temp2);
	free_tab(cmd_temp);
	free_tab_tab(cmd_temp2);
	return (0);
}

void	get_cmd(t_ms *ms_data, char *test)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, SIG_IGN);
	ms_data->data = malloc(sizeof(t_cmd_file));
	ms_data->data->keyword = NULL;
	ms_data->data->n_cmd = 0;
	ms_data->data->file1 = NULL;
	ms_data->data->file2 = NULL;
	ms_data->concat_file = 0;
	ms_data->readfile = 0;
	ms_data->put_in_file = 0;
	ms_data->wait_write = 0;
	ms_data->only_heredoc = 0;
	ms_data->data->cmd = NULL;
	ms_data->env = get_env(ms_data->envp);
	if (quote_in_word(test) == 1 || get_temp_cmd(ms_data, test) == 1)
		return (free_struct(ms_data), free(test));
	free(test);
	if (verif_pash_exist(ms_data, -1, 0) == 1)
		return ;
	verif_absolute_path(ms_data);
	execution(ms_data);
	free_struct(ms_data);
}

void	debut_minishell(t_ms *ms_data)
{
	char	*test;

	while (1)
	{
		g_pid1 = 0;
		signal(SIGINT, handle_sigint_parent);
		signal(SIGQUIT, SIG_IGN);
		test = readline("\U0001F972 Minishell>");
		add_history(test);
		if (test == NULL)
		{
			free(ms_data->tilde);
			free_tab(ms_data->envp);
			free(ms_data);
			free(test);
			rl_clear_history();
			break ;
		}
		else if (!ft_strncmp(test, "$?", 2, 0))
			print_status(ms_data);
		else if (test[0] != '\0')
			get_cmd(ms_data, test);
		else
			free(test);
	}
}

char	**get_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5, 0) == 0)
			env = ft_split_env(envp[i], ':');
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms_data;
	int		i;

	i = 0;
	if (argc == 0 && argv[0])
		return (0);
	ms_data = malloc(sizeof(t_ms));
	ms_data->status = 0;
	ms_data->env = NULL;
	ms_data->tilde = NULL;
	while (envp[i])
		i++;
	ms_data->envp = malloc(sizeof(char *) * (i + 1));
	ms_data->envp[i] = NULL;
	i = 0;
	while (envp[i])
	{
		ms_data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	ms_data->tilde = dup_var("$HOME", ms_data->envp);
	debut_minishell(ms_data);
}
