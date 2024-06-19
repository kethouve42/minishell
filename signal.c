/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:37:15 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/16 16:36:38 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_pid1;

void	print_3_tab(char ***s)
{
	int	i;
	int	j;

	i = 0;
	printf("---------------DEBUT-----------------\n\n");
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			printf("s[i:%d][j:%d] = %s\n", i, j, s[i][j]);
			j++;
		}
		printf("__________________________________\n");
		i++;
	}
	printf("\n\n---------The End----------------\n\n");
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_pid1 == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		printf("\n");
}

char	**no_export(t_ms *ms_data, char *t)
{
	char	**temp;

	temp = ft_strdup2(ms_data->envp);
	free_tab (ms_data->envp);
	free (t);
	return (temp);
}
