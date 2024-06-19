/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:00:50 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/14 14:37:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_echo(char **cmd, t_ms *ms_data)
{
	int	nl;
	int	i;

	nl = 0;
	i = 1;
	if (cmd[i] != NULL && ft_strncmp(cmd[i], "-n", 2, 1) == 0)
	{
		nl = 1;
		i++;
	}
	if (ms_data->readfile == 1 || ms_data->wait_write == 1)
	{
		if (nl == 0)
			printf("\n");
		return ;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i] != NULL)
			printf(" ");
	}
	if (nl == 0)
		printf("\n");
}

void	new_pwd(size_t size)
{
	char	*buffer;

	buffer = malloc(size);
	if (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		return ;
	}
	printf("%s\n", buffer);
	free(buffer);
}

void	new_env(t_ms *ms_data)
{
	int	i;

	i = 0;
	while (ms_data->envp[i])
	{
		printf("%s\n", ms_data->envp[i]);
		i++;
	}
}

void	new_exit2(t_pipe *pipee, t_ms *ms_data)
{
	if (ms_data->wait_write == 1)
		unlink("Here_Docc");
	free_tab_tab(pipee->cmds);
	free (pipee->ij);
	freee2 (pipee->pipefd, ms_data);
	free (pipee);
}

void	new_exit(t_ms *ms_data)
{
	free_tab(ms_data->env);
	free_tab(ms_data->envp);
	free_struct(ms_data);
	free(ms_data);
	rl_clear_history();
	exit (0);
}
