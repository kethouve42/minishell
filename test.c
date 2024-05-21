/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:39:51 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/21 18:01:00 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	

// flag a la compilation -lreadline

// pour le parse prendre en compte ">" "<" ">>" "<<" "|" "$" "$?"
// "ctrl-C" "ctrl-d" "ctrl-\" 
// "echo(-n)" "cd" "pwd" "export" "unset" "env" "exit"


//faire un tableau de tableau de tableau (char ***) pour cmd ou une structure de cmd a implémenter dans ms_data

void malloc_cmd(t_ms *ms_data, char ***cmd_temp2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_temp2[i])
	{
		j = 0;
		while (cmd_temp2[i][j])
		{
			if (ft_strncmp(cmd_temp2[i][j], ">>", 2) != 0 && ft_strncmp(cmd_temp2[i][j], ">", 1) != 0
				/*&& ft_strncmp(cmd_temp2[i][j], "<", 1) != 0 && ft_strncmp(cmd_temp2[i][j], "<<", 2) != 0*/)
				j++;
			else
				break;
		}
		ms_data->data->cmd[i] = malloc(sizeof(char *) * (j + 1));
		ms_data->data->cmd[i][j] = NULL;
		i++;
	}
}

void final_cmd(t_ms *ms_data, char ***cmd_temp2)
{
	int i;
	int j;
	int k;
	
	i = 0;
	while (cmd_temp2[i])
	{
		j = 0;
		while (cmd_temp2[i][j])
		{
			printf("cmd_temp2[%d][%d]: %s\n", i, j, cmd_temp2[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while(cmd_temp2[i])
	{
		j = 0;
		k = 0;
		while(cmd_temp2[i][j])
		{
			if (ft_strncmp(cmd_temp2[i][j], ">>", 2) == 0 || ft_strncmp(cmd_temp2[i][j], ">", 1) == 0)
			{ 
				if (ft_strncmp(cmd_temp2[i][j], ">>", 2) == 0)
					ms_data->put_in_file = 1;
				else
					ms_data->concat_file = 1;
				//printf("cmd_temp2: %s\n", cmd_temp2[i][j]);
				j++;
				ms_data->data->file2 = ft_strdup(cmd_temp2[i][j]);
				j++;
			}
			else if (ft_strncmp(cmd_temp2[i][j], ">>", 2) != 0 && ft_strncmp(cmd_temp2[i][j], ">", 1) != 0)
			{
				if (ft_strncmp(cmd_temp2[i][j], "<<", 2) == 0 || ft_strncmp(cmd_temp2[i][j], "<", 1) == 0)
				{
					//printf("/////////////tempij0: %c tempij1: %c\n", cmd_temp2[i][j][0], cmd_temp2[i][j][0]);
					if(ft_strncmp(cmd_temp2[i][j], "<<", 2) == 0)
					{
						ms_data->wait_write = 1;
						ms_data->data->keyword = ft_strdup(cmd_temp2[i][j + 1]);
					}
					else if(ft_strncmp(cmd_temp2[i][j], "<", 1) == 0)
						ms_data->readfile = 1;
					//printf("cmd_temp2: %s\n", cmd_temp2[i][j]);
					j++;
					//ms_data->data->cmd[i][j] = ft_strdup(cmd_temp2[i][j]);
				}
				ms_data->data->cmd[i][k] = ft_strdup(cmd_temp2[i][j]);
				//printf("cmd_temp2_after: %s\n", cmd_temp2[i][j]);
				j++;
				k++;
			}
			else
				j++;
		}
		ms_data->data->cmd[i][k] = NULL;
		i++;
	}
	ms_data->data->cmd[i] = NULL;
	i = 0;
	while (ms_data->data->cmd[i])
	{
		j = 0;
		while (ms_data->data->cmd[i][j])
		{
			printf("\nfinal_cmd: %s i: %d j: %d\n", ms_data->data->cmd[i][j], i, j);
			j++;
		}
		i++;
	}
	printf("file_out: %s\n", ms_data->data->file2);
	printf("keyword: %s\n", ms_data->data->keyword);
	printf("put_in_file: %d,	concat_file: %d,	readfile: %d,	wait_write: %d\n", ms_data->put_in_file, ms_data->concat_file, ms_data->readfile, ms_data->wait_write);
}

void	get_temp_cmd(t_ms *ms_data, char *test)
{
	int	i;
	int	j;

	char	**cmd_temp;
	char	***cmd_temp2;
	i = 0;
	ms_data->data->cmd = malloc(sizeof(char **) * (ms_data->data->n_cmd + 1));
	cmd_temp2 = malloc(sizeof(char **) * (ms_data->data->n_cmd + 1));
	cmd_temp = ft_split(test, '|');
	while (cmd_temp[i])
	{
	//	printf("temp: %s\n", cmd_temp[i]);
		cmd_temp2[i] = ft_split2(cmd_temp[i], ' ');
		i++;
	}
	cmd_temp2[i] = NULL;
	i = 0;
	while(cmd_temp2[i])
	{
		j = 0;
		while(cmd_temp2[i][j])
			j++;
		i++;
	}
	malloc_cmd(ms_data, cmd_temp2);
	final_cmd(ms_data, cmd_temp2);
}

void get_cmd(t_ms *ms_data, char *test)
{
	int		i;
	
	i = 0;
	ms_data->data->keyword = NULL;
	ms_data->data->n_file = 0;
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
}

void debut_minishell(t_ms *ms_data)
{
	char	*test;
	int i = 0;
	int j = 0;
	while (1)
	{
		i = 0;
		test = readline("\U0001F972 Minishell>");
		add_history(test);
		if (!ft_strncmp(test, "exit", 4))
			break;
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
	int j = 0;

	if (argc == 0 && argv[0])
		return (0);
	ms_data = malloc(sizeof(t_ms));
	ms_data->data = malloc(sizeof(t_cmd_file));
	ms_data->env = get_env(envp);
	while (envp[j])
		j++;
	ms_data->envp = malloc(sizeof(char *) * (j + 1));
	ms_data->envp[j] = NULL;
	j = 0;
	while (envp[j])
	{
		ms_data->envp[j] = ft_strdup(envp[j]);
		j++;
	}
	debut_minishell(ms_data);
}
