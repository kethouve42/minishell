/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_no.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:09:43 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 16:47:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_pid1;

void	child_no(t_pipe *pipee, t_ms *ms_data)
{
	if (ms_data->put_in_file == 1)
	{
		pipee->fd2 = open(ms_data->data->file2,
				O_CREAT | O_APPEND | O_WRONLY, 0664);
	}
	else if (ms_data->concat_file == 1)
	{
		pipee->fd2 = open(ms_data->data->file2,
				O_CREAT | O_TRUNC | O_WRONLY, 0664);
	}
	if (ms_data->put_in_file == 1 || ms_data->concat_file == 1)
	{
		dup2(pipee->fd2, 1);
		close(pipee->fd2);
	}
	if (execution2(ms_data, 0, pipee) == 1)
		exit(0);
	execve(pipee->cmd[0], pipee->cmd, ms_data->envp);
}

int	exec_no(char ***cmd, t_ms *ms_data)
{
	t_pipe	*pipee;
	int		status;

	status = 0;
	pipee = malloc(sizeof(t_pipe));
	pipee->i = 0;
	pipee->cmd = ft_strdup2(cmd[0]);
	g_pid1 = fork();
	if (g_pid1 == -1)
		return (0);
	if (g_pid1 == 0)
		child_no(pipee, ms_data);
	waitpid(g_pid1, &status, 0);
	if (ms_data->wait_write == 1)
		unlink("Here_Docc");
	free_tab (pipee->cmd);
	free (pipee);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

void	exec_exec_no(t_pipe *pipee, t_ms *ms_data)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		start2_no(pipee, ms_data);
	while (pipee->cmds[++pipee->j + 1])
	{
		pid1 = fork();
		if (pid1 == -1)
			return ;
		if (pid1 == 0)
			mid2_no(pipee, ms_data);
	}
	pid1 = fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		end2_no(pipee, ms_data);
	closee(pipee, ms_data, 1000, 3);
	waitpid(pid1, &pipee->status, 0);
}

int	verif_no(t_ms *ms_data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (ms_data->data->cmd[++i])
		if ((ms_data->data->cmd[i][0][0] == '/'
			&& access(ms_data->data->cmd[i][0], X_OK) == 0) ||
				execution4(ms_data, i) == 1)
			j++;
	if (i == j)
	{
		if (execution3(ms_data) == 1)
			return (free_struct(ms_data), 1);
		if (ms_data->data->n_cmd == 1)
			ms_data->status = exec_no(ms_data->data->cmd, ms_data);
		else
			ms_data->status = exec2_no(ms_data->data->cmd, ms_data);
		return (free_struct(ms_data), 1);
	}
	return (0);
}

int	verif_pash_exist(t_ms *ms_data, int i, int j)
{
	if (ms_data->wait_write == 1)
		wait_write(ms_data);
	if (verif_no(ms_data) == 1)
		return (1);
	if (ms_data->env != NULL)
		return (0);
	while (ms_data->data->cmd[++i])
		if ((ms_data->data->cmd[i][0][0] == '/'
			&& access(ms_data->data->cmd[i][0], X_OK) == 0) ||
				execution4(ms_data, i) == 1)
			j++;
	if (i == j)
	{
		if (execution3(ms_data) == 1)
			return (free_struct(ms_data), 1);
		if (ms_data->data->n_cmd == 1)
			ms_data->status = exec_no(ms_data->data->cmd, ms_data);
		else
			ms_data->status = exec2_no(ms_data->data->cmd, ms_data);
		return (free_struct(ms_data), 1);
	}
	return (printf("NO PATH\n"), free_struct(ms_data), 1);
}
