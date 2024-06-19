/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:15 by marvin            #+#    #+#             */
/*   Updated: 2024/06/20 00:18:46 by kethouve         ###   ########.fr       */
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
		ms_data->data->cmd[i] = NULL;
		j = 0;
		while (cmd_temp2[i][j])
		{
			if (ft_strncmp(cmd_temp2[i][j], ">>", 2, 0) != 0
				&& ft_strncmp(cmd_temp2[i][j], ">", 1, 0) != 0)
				j++;
			else
				break ;
		}
		ms_data->data->cmd[i] = malloc(sizeof(char *) * (j + 1));
		ms_data->data->cmd[i][j] = NULL;
		i++;
	}
}

void	dup_status(char *s, char *status, char *dest)
{
	int	i;
	int	j;
	int	k;
	int	quote_status;

	i = -1;
	k = -1;
	quote_status = 0;
	while (s[++i])
	{
		quote_analyse(s[i], &quote_status);
		if (quote_status != 1 && s[i] == '$' && s[i + 1] == '?')
		{
			i += 1;
			j = -1;
			while (status[++j])
				dest[++k] = status[j];
		}
		else
			dest[++k] = s[i];
	}
	dest[++k] = '\0';
}

char	*verif_stat_in_s(char *s, t_ms *ms_data)
{
	int		i;
	int		quote_status;
	int		n_status;
	char	*status;
	char	*dest;

	n_status = 0;
	quote_status = 0;
	i = -1;
	while (s[++i])
	{
		quote_analyse(s[i], &quote_status);
		if (quote_status != 1 && s[i] == '$' && s[i + 1] == '?')
		{
			n_status++;
			i++;
		}
	}
	if (n_status == 0)
		return (s);
	status = ft_itoa(ms_data->status);
	dest = malloc(sizeof(char) * (((ft_strlen(s) - (n_status * 2))
					+ (ft_strlen(status) * n_status) + 1)));
	dup_status(s, status, dest);
	return (free(s), free(status), dest);
}

int	verif_arrow(char *s)
{
	if (ft_strncmp(s, "<<<", 3, 0) == 0 || ft_strncmp(s, ">>>", 3, 0) == 0
		|| ft_strncmp(s, "<< ", 3, 0) == 0 || ft_strncmp(s, ">> ", 3, 0) == 0
		|| ft_strncmp(s, "><", 2, 0) == 0 || ft_strncmp(s, "< ", 2, 0) == 0)
		return (1);
	return (0);
}

int	verif_operator(char ***cmd_temp2, t_ms *ms_data)
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
			if (verif_arrow(cmd_temp2[i][j]) == 1)
				return (1);
			else if (ft_strncmp(cmd_temp2[i][j], "~", 1, 0) == 0)
			{
				free(cmd_temp2[i][j]);
				cmd_temp2[i][j] = ft_strdup(ms_data->tilde);
			}
			else
				cmd_temp2[i][j] = verif_stat_in_s(cmd_temp2[i][j], ms_data);
			j++;
		}
		i++;
	}
	return (0);
}
