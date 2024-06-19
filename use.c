/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:26:30 by marvin            #+#    #+#             */
/*   Updated: 2024/06/07 16:20:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freee(char **a)
{
	int	i;

	i = -1;
	while (a[++i])
		free(a[i]);
	free (a);
}

void	freee2(int	**a, t_ms *ms_data)
{
	int	i;

	i = 0;
	while (i < ms_data->data->n_cmd)
	{
		free (a[i]);
		i++;
	}
	free (a);
}

void	ft_putstr2(char *a, char ***cmds, int *ij)
{
	int	i;

	i = 0;
	while (a[i])
	{
		write(2, &a[i], 1);
		i++;
	}
	write(2, "\n", 1);
	free_tab_tab (cmds);
	free (ij);
}

void	setexec(t_pipe *pipee, t_ms *ms_data)
{
	pipee->env = ms_data->env;
	pipee->j = 0;
	pipee->ij = malloc(sizeof(int) * ms_data->data->n_cmd);
	while (pipee->j < ms_data->data->n_cmd)
	{
		pipee->ij[pipee->j] = 0;
		pipee->j++;
	}
	pipee->j = 0;
}

void	exec_exec(t_pipe *pipee, t_ms *ms_data)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		start2(pipee, ms_data);
	while (pipee->cmds[++pipee->j + 1])
	{
		pid1 = fork();
		if (pid1 == -1)
			return ;
		if (pid1 == 0)
			mid2(pipee, ms_data);
	}
	pid1 = fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		end2(pipee, ms_data);
	closee(pipee, ms_data, 1000, 3);
	waitpid(pid1, &pipee->status, 0);
}
