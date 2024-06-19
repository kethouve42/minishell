/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:46:59 by marvin            #+#    #+#             */
/*   Updated: 2024/06/14 14:30:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_file(t_ms *ms_data)
{
	int	i;

	i = 0;
	while (ms_data->data->cmd[0][i])
	{
		if (ft_strncmp(ms_data->data->cmd[0][i],
			ms_data->data->keyword, ft_strlen(ms_data->data->keyword), 0) == 0)
		{
			if (ft_strncmp(ms_data->data->cmd[0][0], "ls", 2, 0) == 0)
				ms_data->data->cmd[0][i] = NULL;
			else
			{
				free(ms_data->data->cmd[0][i]);
				ms_data->data->cmd[0][i] = ft_strdup("Here_Docc");
			}
			if (i == 0)
				ms_data->only_heredoc = 1;
			break ;
		}
		i++;
	}
}

void	wait_write(t_ms *ms_data)
{
	char	*test;
	int		fd;

	fd = open("Here_Docc", O_CREAT | O_APPEND | O_WRONLY, 0664);
	while (1)
	{
		test = readline(">");
		if (ft_strncmp(test, ms_data->data->keyword, ft_strlen(test), 1) == 0)
			break ;
		write(fd, test, ft_strlen(test));
		write(fd, "\n", 1);
		free (test);
	}
	free (test);
	close(fd);
	put_file(ms_data);
}
