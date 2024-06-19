/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:19:17 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/19 17:21:42 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_cmd(t_ms *ms_data, char ***ct2, t_tri_index *t_i)
{
	if (ct2[t_i->i][t_i->j] == NULL && ms_data->wait_write == 0)
	{
		t_i->j--;
		return ;
	}
	if (ms_data->wait_write == 1)
		t_i->j--;
	if (quote_in_word(ct2[t_i->i][t_i->j]) == 1)
		ms_data->data->cmd[t_i->i][t_i->k] = ft_strdup(ct2[t_i->i][t_i->j]);
	else
		ms_data->data->cmd[t_i->i][t_i->k] = dup_quote(ct2[t_i->i][t_i->j]);
	t_i->k++;
}

void	type_file_in(t_ms *ms_data, char ***cmd_temp2, t_tri_index *t_i)
{
	if (ft_strncmp(cmd_temp2[t_i->i][t_i->j], "<<", 2, 0) == 0
		|| ft_strncmp(cmd_temp2[t_i->i][t_i->j], "<", 1, 0) == 0)
	{
		t_i->j++;
		if (ft_strncmp(cmd_temp2[t_i->i][t_i->j - 1], "<>", 2, 0) == 0)
		{
			createfile(cmd_temp2[t_i->i][t_i->j], ms_data);
			return (put_cmd(ms_data, cmd_temp2, t_i));
		}
		else if (ft_strncmp(cmd_temp2[t_i->i][t_i->j - 1], "<<", 2, 0) == 0)
		{
			ms_data->wait_write = 1;
			ms_data->data->keyword = dup_quote(cmd_temp2[t_i->i][t_i->j]);
		}
		else if (ft_strncmp(cmd_temp2[t_i->i][t_i->j - 1], "<", 1, 0) == 0)
		{
			if (ms_data->data->file1 != NULL)
				free(ms_data->data->file1);
			ms_data->data->file1 = ft_strdup(cmd_temp2[t_i->i][t_i->j]);
			ms_data->readfile = 1;
			return ;
		}
		t_i->j++;
	}
	put_cmd(ms_data, cmd_temp2, t_i);
}

void	get_file_out(t_ms *ms_data, char ***cmd_temp2, t_tri_index *t_i)
{
	char	*temp;

	if (ft_strncmp(cmd_temp2[t_i->i][t_i->j], ">>", 2, 0) == 0)
		ms_data->put_in_file = 1;
	else
		ms_data->concat_file = 1;
	t_i->j++;
	if (ms_data->data->file2 != NULL)
		free(ms_data->data->file2);
	if (cmd_temp2[t_i->i][t_i->j][0] == '$'
		|| (cmd_temp2[t_i->i][t_i->j][0] == 34
		&& cmd_temp2[t_i->i][t_i->j][1] == '$'))
	{
		temp = dup_quote(cmd_temp2[t_i->i][t_i->j]);
		ms_data->data->file2 = dup_var(temp, ms_data->envp);
		free(temp);
	}
	else if (quote_in_word(cmd_temp2[t_i->i][t_i->j]) == 1)
		ms_data->data->file2 = ft_strdup(cmd_temp2[t_i->i][t_i->j]);
	else
		ms_data->data->file2 = dup_quote(cmd_temp2[t_i->i][t_i->j]);
	if (ms_data->data->file2 != NULL)
		createfile(ms_data->data->file2, ms_data);
}

void	cmd_plus_file(t_ms *ms_data, t_tri_index *t_i)
{
	ms_data->data->cmd[t_i->i][t_i->k] = dup_quote(ms_data->data->file1);
	free(ms_data->data->file1);
	ms_data->data->file1 = NULL;
	t_i->k++;
}

void	final_cmd(t_ms *ms_data, char ***ct2)
{
	t_tri_index	*t_i;

	t_i = malloc(sizeof (t_tri_index));
	verif_var(ct2, t_i, ms_data->envp);
	t_i->i = -1;
	while (ct2[++t_i->i])
	{
		t_i->j = -1;
		t_i->k = 0;
		while (ct2[t_i->i][++t_i->j])
		{
			if (ft_strncmp(ct2[t_i->i][t_i->j], ">>", 2, 0) == 0
				|| ft_strncmp(ct2[t_i->i][t_i->j], ">", 1, 0) == 0)
				get_file_out(ms_data, ct2, t_i);
			else if (ft_strncmp(ct2[t_i->i][t_i->j], ">>", 2, 0) != 0
				&& ft_strncmp(ct2[t_i->i][t_i->j], ">", 1, 0) != 0)
				type_file_in(ms_data, ct2, t_i);
		}
		if (ms_data->data->file1 != NULL)
			cmd_plus_file(ms_data, t_i);
		ms_data->data->cmd[t_i->i][t_i->k] = NULL;
	}
	ms_data->data->cmd[t_i->i] = NULL;
	free(t_i);
}
