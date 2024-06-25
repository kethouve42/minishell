/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:37:15 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/19 17:28:05 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_status(t_ms *ms_data)
{
	printf("%d : commande introuvable\n", ms_data->status);
	ms_data->status = 127;
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	printf("\n");
}

void	handle_sigint_parent(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	**no_export(t_ms *ms_data, char *t)
{
	char	**temp;

	temp = ft_strdup2(ms_data->envp);
	free_tab (ms_data->envp);
	free (t);
	return (temp);
}

int	verif_export(char *cmd)
{
	int	i;

	i = 0;
	if ((cmd[0] >= '0' && cmd[0] <= '9'))
		return (1);
	while (cmd[i])
	{
		if (cmd[i] >= '0' && cmd[i] <= '9')
			i++;
		else if (cmd[i] >= 'a' && cmd[i] <= 'z')
			i++;
		else if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			i++;
		else if (cmd[i] == '_')
			i++;
		else if (cmd[i] == '=')
			return (0);
		else
			return (1);
	}
	return (0);
}
