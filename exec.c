/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:58:02 by marvin            #+#    #+#             */
/*   Updated: 2024/06/19 17:22:09 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif2(t_ms *ms_data, char ***cmds, int *ij)
{
	int		i;
	char	*temp;

	i = -1;
	while (cmds[++i])
	{
		while (ms_data->env[++ij[i]] != NULL)
		{
			temp = ft_strjoin(ms_data->env[ij[i]], cmds[i][0]);
			if (execution4(ms_data, i) == 1)
				break ;
			if (access(temp, X_OK) >= 0)
				break ;
			free(temp);
			temp = NULL;
		}
		if (temp != NULL)
		{
			free(temp);
			temp = NULL;
		}
		if (ms_data->env[ij[i]] == NULL)
			return (ft_putstr2("cmds", cmds, ij), 1);
	}
	return (0);
}

int	verif(t_ms *ms_data)
{
	int		i;
	char	***cmds;
	int		*ij;

	i = 0;
	cmds = ft_strdup3(ms_data->data->cmd);
	ij = malloc(sizeof(int) * ms_data->data->n_cmd);
	while (i < ms_data->data->n_cmd)
	{
		if (cmds[i][0] == NULL)
			return (ms_data->status = 127, free (ij), free_tab_tab (cmds), 1);
		ij[i] = -1;
		i++;
	}
	add_first (cmds);
	if (verif2(ms_data, cmds, ij) == 1)
		return (ms_data->status = 127, 1);
	free_tab_tab (cmds);
	free (ij);
	return (0);
}

int	execution2(t_ms *ms_data, int i, t_pipe *pipee)
{
	if (ft_strncmp(ms_data->data->cmd[0][0], "cd", 2, 1) == 0)
		return (1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "exit", 4, 1) == 0)
		return (new_exit2(pipee, ms_data), 1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "echo", 4, 1) == 0)
		return (new_echo(ms_data->data->cmd[0], ms_data), 1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "env", 3, 1) == 0)
		return (new_env(ms_data), 1);
	if (ft_strncmp(ms_data->data->cmd[i][0], "pwd", 3, 1) == 0)
		return (new_pwd(256), 1);
	return (0);
}

int	execution3(t_ms *ms_data)
{
	if (ms_data->only_heredoc == 1)
		return (unlink("Here_Docc"), 1);
	if (ft_strncmp(ms_data->data->cmd[0][0], "exit", 4, 1) == 0)
		return (new_exit(ms_data), 1);
	if (ft_strncmp(ms_data->data->cmd[0][0], "cd", 2, 1) == 0)
	{
		if (ms_data->data->n_cmd == 1)
			return (new_cd(ms_data->data->cmd[0][1], ms_data), 1);
	}
	if (ft_strncmp(ms_data->data->cmd[0][0], "export", 6, 1) == 0)
	{
		if (!ms_data->data->cmd[0][1])
			return (new_env(ms_data), 1);
		ms_data->envp = new_export(ms_data, ms_data->data->cmd[0][1]);
		return (1);
	}
	if (ft_strncmp(ms_data->data->cmd[0][0], "unset", 5, 1) == 0)
	{
		if (!ms_data->data->cmd[0][1])
			return (1);
		ms_data->envp = new_unset(ms_data, ms_data->data->cmd[0][1],
				ft_strjoin(ms_data->data->cmd[0][1], "="));
		return (1);
	}
	return (0);
}

void	execution(t_ms *ms_data)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, SIG_IGN);
	if (ms_data->data->cmd[0][0] == NULL)
		return ;
	if (execution3(ms_data) == 1)
		return ;
	if (verif(ms_data) == 1)
		return ;
	if (ms_data->data->n_cmd == 1)
		ms_data->status = exec(ms_data->data->cmd, ms_data);
	else
		ms_data->status = exec2(ms_data->data->cmd, ms_data);
}
