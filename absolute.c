/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:04:20 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/17 16:45:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_abso(char *s)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	j = i;
	while (s[i - 1] != '/')
		i--;
	dest = malloc(sizeof(char) * (j - i + 1));
	j = 0;
	while (s[i])
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	free(s);
	return (dest);
}

void	verif_absolute_path(t_ms *ms_data)
{
	int	i;

	i = 0;
	while (ms_data->data->cmd[i])
	{
		if (ms_data->data->cmd[i][0][0] == '/'
			&& access(ms_data->data->cmd[i][0], X_OK) == 0)
		{
			ms_data->data->cmd[i][0] = get_cmd_abso(ms_data->data->cmd[i][0]);
		}
		i++;
	}
}
