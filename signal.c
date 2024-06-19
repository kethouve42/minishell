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
