/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:09:43 by marvin            #+#    #+#             */
/*   Updated: 2024/06/19 17:19:24 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_pipe *pipee, t_ms *ms_data)
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
	execve(ft_strjoin(pipee->env[pipee->i],
			pipee->cmd[0]), pipee->cmd, ms_data->envp);
}

int	seearsh(t_pipe *pipee)
{
	char	*temp;
	char	*temp2;

	temp2 = ft_strjoin("/", pipee->cmd[0]);
	free(pipee->cmd[0]);
	pipee->cmd[0] = ft_strdup(temp2);
	free (temp2);
	temp2 = NULL;
	while (pipee->env[pipee->i] != NULL)
	{
		temp = ft_strjoin(pipee->env[pipee->i], pipee->cmd[0]);
		if (access(temp, X_OK) >= 0)
			break ;
		pipee->i++;
		free(temp);
		temp = NULL;
	}
	free(temp);
	if (pipee->env[pipee->i] == NULL)
		return (1);
	return (0);
}

int	exec(char ***cmd, t_ms *ms_data)
{
	t_pipe	*pipee;
	int		status;
	pid_t	pid1;

	status = 0;
	pipee = malloc(sizeof(t_pipe));
	pipee->i = 0;
	pipee->cmd = ft_strdup2(cmd[0]);
	pipee->env = ms_data->env;
	seearsh(pipee);
	pid1 = fork();
	if (pid1 == -1)
		return (0);
	if (pid1 == 0)
		child(pipee, ms_data);
	waitpid(pid1, &status, 0);
	if (ms_data->wait_write == 1)
		unlink("Here_Docc");
	free_tab (pipee->cmd);
	free (pipee);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}
