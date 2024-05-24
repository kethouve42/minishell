/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:39:51 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/24 17:33:52 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_temp_cmd(t_ms *ms_data, char *test)
{
	int		i;
	char	**cmd_temp;
	char	***cmd_temp2;

	i = 0;
	ms_data->data->cmd = malloc(sizeof(char **) * (ms_data->data->n_cmd + 1));
	cmd_temp2 = malloc(sizeof(char **) * (ms_data->data->n_cmd + 1));
	cmd_temp = ft_split(test, '|');
	while (cmd_temp[i])
	{
		cmd_temp2[i] = ft_split2(cmd_temp[i], ' ');
		i++;
	}
	cmd_temp2[i] = NULL;
	malloc_cmd(ms_data, cmd_temp2);
	final_cmd(ms_data, cmd_temp2);
	free_tab(cmd_temp);
	free_tab_tab(cmd_temp2);
}

void	get_cmd(t_ms *ms_data, char *test)
{
	int		i;

	i = 0;
	ms_data->data = malloc(sizeof(t_cmd_file));
	ms_data->data->keyword = NULL;
	ms_data->data->n_cmd = 1;
	ms_data->data->file2 = NULL;
	ms_data->concat_file = 0;
	ms_data->readfile = 0;
	ms_data->put_in_file = 0;
	ms_data->wait_write = 0;
	while (test[i])
	{
		if (test[i] == '|')
			ms_data->data->n_cmd++;
		i++;
	}
	get_temp_cmd(ms_data, test);
	//execution(ms_data);
	free_struct(ms_data);
}

void	debut_minishell(t_ms *ms_data)
{
	char	*test;
	int		i;
	int		j;
	char	*quote_test;

	i = 0;
	j = 0;
	while (1)
	{
		i = 0;
		test = readline("\U0001F972 Minishell>");
		add_history(test);
		if (!ft_strncmp(test, "exit", 4))
		{
			free_tab(ms_data->env);
			free_tab(ms_data->envp);
			free(ms_data);
			rl_clear_history();
			free(test);
			break ;
		}
		else if (!ft_strncmp(test, "qe", 2))
		{
			quote_test = ft_strdup_quote(test);
			printf("quote_res: %s\n", quote_test);
		}
		else if (!ft_strncmp(test, "$", 1))
		{
			test = dup_var(test, ms_data->envp);
			printf("var_test: %s\n", test);
		}
		else if (!ft_strncmp(test, "hello", 5))
			printf("Coucou toi\n");
		else if (!ft_strncmp(test, "env", 3))
		{
			while (ms_data->envp[i])
			{
				j = 0;
				while (ms_data->envp[i][j])
				{
					write(1, &ms_data->envp[i][j], 1);
					j++;
				}
				write(1, "\n", 1);
				i++;
			}
		}
		else if (test[i] != '\0')
			get_cmd(ms_data, test);
		free(test);
	}
}

char	**get_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
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
	ms_data->env = get_env(envp);
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
	debut_minishell(ms_data);
}
