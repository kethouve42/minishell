/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:17:24 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/24 17:42:49 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab_tab(char ***tab_tab)
{
	int	i;
	int	j;

	i = 0;
	if (!tab_tab)
		return ;
	while (tab_tab[i])
	{
		j = 0;
		while (tab_tab[i][j])
		{
			free(tab_tab[i][j]);
			j++;
		}
		free(tab_tab[i]);
		i++;
	}
	free(tab_tab);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_struct(t_ms *ms_data)
{
	free_tab_tab(ms_data->data->cmd);
	free(ms_data->data->file2);
	free(ms_data->data->keyword);
	free(ms_data->data);
}
