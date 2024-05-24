/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:19:17 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/24 17:52:05 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_cmd(t_ms *ms_data, char ***cmd_temp2)
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
			if (ft_strncmp(cmd_temp2[i][j], ">>", 2) != 0
				&& ft_strncmp(cmd_temp2[i][j], ">", 1) != 0)
				j++;
			else
				break ;
		}
		ms_data->data->cmd[i] = malloc(sizeof(char *) * (j + 1));
		ms_data->data->cmd[i][j] = NULL;
		i++;
	}
}
	/*while (cmd_temp2[i])
	{
		j = 0;
		while (cmd_temp2[i][j])
		{
			printf("cmd_temp2[%d][%d]: %s\n", i, j, cmd_temp2[i][j]);
			j++;
		}
		i++;
	}
	i = 0;*/

void	type_file_in(t_ms *ms_data, char ***cmd_temp2, int *i, int *j)
{
	if (ft_strncmp(cmd_temp2[*i][*j], "<<", 2) == 0
		|| ft_strncmp(cmd_temp2[*i][*j], "<", 1) == 0)
	{
		if (ft_strncmp(cmd_temp2[*i][*j], "<<", 2) == 0)
		{
			ms_data->wait_write = 1;
			ms_data->data->keyword = ft_strdup(cmd_temp2[*i][*j + 1]);
		}
		else if (ft_strncmp(cmd_temp2[*i][*j], "<", 1) == 0)
			ms_data->readfile = 1;
	}
}

void	put_cmd(t_ms *ms_data, char *cmd_temp2, int *i, int *k)
{
	if (quote_in_word(cmd_temp2) == 1)
		ms_data->data->cmd[*i][*k] = ft_strdup(cmd_temp2);
	else
		ms_data->data->cmd[*i][*k] = ft_strdup_quote(cmd_temp2);
	(*k)++;
}

void	get_file_out(t_ms *ms_data, char ***cmd_temp2, int *i, int *j)
{
	if (ft_strncmp(cmd_temp2[*i][*j], ">>", 2) == 0)
		ms_data->put_in_file = 1;
	else
		ms_data->concat_file = 1;
	(*j)++;
	if (cmd_temp2[*i][*j][0] == '$' || (cmd_temp2[*i][*j][0] == 34
		&& cmd_temp2[*i][*j][1] == '$'))
		ms_data->data->file2 = dup_var(ft_strdup_quote(cmd_temp2[*i][*j]),
				ms_data->envp);
	else if (quote_in_word(cmd_temp2[*i][*j]) == 1)
		ms_data->data->file2 = ft_strdup(cmd_temp2[*i][*j]);
	else
		ms_data->data->file2 = ft_strdup_quote(cmd_temp2[*i][*j]);
}

void	final_cmd(t_ms *ms_data, char ***cmd_temp2)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (cmd_temp2[++i])
	{
		j = -1;
		k = 0;
		while (cmd_temp2[i][++j])
		{
			if (cmd_temp2[i][j][0] == '$' || (cmd_temp2[i][j][0] == 34
				&& cmd_temp2[i][j][1] == '$'))
				cmd_temp2[i][j] = dup_var(ft_strdup_quote(cmd_temp2[i][j]),
						ms_data->envp);
			if (ft_strncmp(cmd_temp2[i][j], ">>", 2) == 0
				|| ft_strncmp(cmd_temp2[i][j], ">", 1) == 0)
				get_file_out(ms_data, cmd_temp2, &i, &j);
			else if (ft_strncmp(cmd_temp2[i][j], ">>", 2) != 0
				&& ft_strncmp(cmd_temp2[i][j], ">", 1) != 0)
			{
				type_file_in(ms_data, cmd_temp2, &i, &j);
				put_cmd(ms_data, cmd_temp2[i][j], &i, &k);
			}
		}
		ms_data->data->cmd[i][k] = NULL;
	}
	ms_data->data->cmd[i] = NULL;
}
	/*i = 0;
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
	printf("put_in_file: %d,	concat_file: %d,	readfile: %d,	wait_write: %d\n", ms_data->put_in_file, ms_data->concat_file, ms_data->readfile, ms_data->wait_write);*/
