/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:40:01 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/24 17:47:53 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_var2(char *envp, int n)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (ft_strlen(envp) - n));
	while (envp[n])
	{
		res[i] = envp[n];
		i++;
		n++;
	}
	res[i] = '\0';
	return (res);
}

char	*dup_var(char *s, char **envp)
{
	int		i;
	char	*dest;
	char	*res;

	i = 1;
	res = NULL;
	dest = malloc(sizeof(char *) * (ft_strlen(s) - 1));
	while (s[i])
	{
		dest[i - 1] = s[i];
		i++;
	}
	dest[i - 1] = '\0';
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(ft_strjoin(dest, "="), envp[i],
				ft_strlen(dest) + 1) == 0)
		{
			res = dup_var2(envp[i], ft_strlen(dest) + 1);
			return (free(dest), res);
		}
		i++;
	}
	return ("\0");
}
