/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:46:12 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:46:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_first(char ***cmds)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmds[i])
	{
		temp = ft_strjoin("/", cmds[i][0]);
		free (cmds[i][0]);
		cmds[i][0] = ft_strdup(temp);
		free (temp);
		temp = NULL;
		i++;
	}
}

void	closee(t_pipe *pipee, t_ms *ms_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < ms_data->data->n_cmd)
	{
		if (i == x)
		{
			if (y == 1)
				close(pipee->pipefd[i][0]);
			else
				close(pipee->pipefd[i][1]);
			i++;
		}
		close(pipee->pipefd[i][0]);
		close(pipee->pipefd[i][1]);
		i++;
	}
}

void	closeee(t_pipe *pipee, t_ms *ms_data, int x, int x2)
{
	int	i;

	i = 0;
	while (i < ms_data->data->n_cmd)
	{
		if (i == x)
		{
			close(pipee->pipefd[i][1]);
			i++;
		}
		if (i == x2)
		{
			close(pipee->pipefd[i][0]);
			i++;
		}
		close(pipee->pipefd[i][0]);
		close(pipee->pipefd[i][1]);
		i++;
	}
}

void	seearsh22(t_pipe *pipee)
{
	int		i;
	char	*temp;

	i = 0;
	while (pipee->cmds[i])
	{
		while (pipee->env[pipee->ij[i]] != NULL)
		{
			temp = ft_strjoin(pipee->env[pipee->ij[i]], pipee->cmds[i][0]);
			if (access(temp, X_OK) >= 0)
				break ;
			pipee->ij[i]++;
			free(temp);
			temp = NULL;
		}
		free(temp);
		temp = NULL;
		if (pipee->env[pipee->ij[i]] == NULL)
			return ;
		i++;
	}
}

int	execution4(t_ms *ms_data, int i)
{
	if (ft_strncmp(ms_data->data->cmd[i][0], "echo", 4, 1) == 0)
		return (1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "env", 3, 1) == 0)
		return (1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "pwd", 3, 1) == 0)
		return (1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "cd", 2, 1) == 0)
		return (1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "export", 6, 1) == 0)
		return (1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "unset", 5, 1) == 0)
		return (1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "exit", 4, 1) == 0)
		return (1);
	return (0);
}
