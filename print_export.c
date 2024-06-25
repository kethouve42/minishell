/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:36:47 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/21 00:51:03 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort(char **export)
{
	int	i;
	int	sorted;

	i = 0;
	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (export[i] && export[i + 1])
		{
			if (ft_strcmp(export[i], export[i + 1]) > 0)
			{
				swap(&export[i], &export[i + 1]);
				sorted = 0;
			}
			i++;
		}
	}
}

char	**copy_ms_envp(t_ms *ms_data)
{
	int		i;
	char	**temp;

	i = 0;
	while (ms_data->envp[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ms_data->envp[i])
	{
		temp[i] = ft_strdup(ms_data->envp[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

void	print_export(t_ms *ms_data)
{
	char	**export;
	int		i;

	i = 0;
	export = copy_ms_envp(ms_data);
	bubble_sort(export);
	while (export[i])
	{
		printf("declare -x %s\n", export[i]);
		i++;
	}
	free_tab(export);
}
