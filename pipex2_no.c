/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2_no.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:09:43 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 14:45:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start2_no(t_pipe *pipee, t_ms *ms_data)
{
	dup2(pipee->pipefd[pipee->j][1], 1);
	close(pipee->pipefd[pipee->j][0]);
	closee(pipee, ms_data, pipee->j, 1);
	if (execution2(ms_data, pipee->j, pipee) == 1)
		exit(0);
	execve(pipee->cmds[pipee->j][0], pipee->cmds[pipee->j], ms_data->envp);
	close(pipee->pipefd[pipee->j][1]);
}

void	end2_no(t_pipe *pipee, t_ms *ms_data)
{
	if (ms_data->put_in_file == 1)
		pipee->fd2 = open(ms_data->data->file2,
				O_CREAT | O_APPEND | O_WRONLY, 0664);
	else if (ms_data->concat_file == 1)
		pipee->fd2 = open(ms_data->data->file2,
				O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (ms_data->put_in_file == 1 || ms_data->concat_file == 1)
	{
		dup2(pipee->fd2, 1);
		close(pipee->fd2);
	}
	dup2(pipee->pipefd[pipee->j - 1][0], 0);
	close(pipee->pipefd[pipee->j][1]);
	closee(pipee, ms_data, pipee->j - 1, 0);
	if (execution2(ms_data, pipee->j, pipee) == 1)
		exit(0);
	execve(pipee->cmds[pipee->j][0], pipee->cmds[pipee->j], ms_data->envp);
	close(pipee->pipefd[pipee->j - 1][0]);
}

void	mid2_no(t_pipe *pipee, t_ms *ms_data)
{
	dup2(pipee->pipefd[pipee->j - 1][0], 0);
	dup2(pipee->pipefd[pipee->j][1], 1);
	closeee(pipee, ms_data, pipee->j - 1, pipee->j);
	if (execution2(ms_data, pipee->j, pipee) == 1)
		exit(0);
	execve(pipee->cmds[pipee->j][0], pipee->cmds[pipee->j], ms_data->envp);
	close(pipee->pipefd[pipee->j - 1][0]);
	close(pipee->pipefd[pipee->j][1]);
}

void	seearsh2_no(t_pipe *pipee, t_ms *ms_data)
{
	int		i;

	i = 0;
	pipee->pipefd = malloc(sizeof(int *) * ms_data->data->n_cmd);
	while (i < ms_data->data->n_cmd)
	{
		pipee->pipefd[i] = malloc(sizeof(int) * 2);
		if (pipe(pipee->pipefd[i]) == -1)
			return ;
		i++;
	}
}

int	exec2_no(char ***cmd, t_ms *ms_data)
{
	t_pipe	*pipee;
	int		status;

	status = 0;
	pipee = malloc(sizeof(t_pipe));
	pipee->cmds = ft_strdup3(cmd);
	setexec (pipee, ms_data);
	seearsh2_no(pipee, ms_data);
	exec_exec_no(pipee, ms_data);
	if (ms_data->wait_write == 1)
		unlink("Here_Docc");
	free_tab_tab(pipee->cmds);
	status = pipee->status;
	free (pipee->ij);
	freee2 (pipee->pipefd, ms_data);
	free (pipee);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}
