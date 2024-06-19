/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:13:24 by marvin            #+#    #+#             */
/*   Updated: 2024/06/18 17:07:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recup(char *cmd, char *mod)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == mod[0])
			break ;
		i++;
	}
	if (i == 0 || !cmd[i])
		return (NULL);
	temp = malloc(sizeof(char) * (i + 2));
	temp[i + 1] = '\0';
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == mod[0])
			break ;
		temp[i] = cmd[i];
		i++;
	}
	temp[i] = 61;
	return (temp);
}

char	**new_export2(t_ms *ms_data, char **temp, char *cmd, char *t)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms_data->envp[j])
	{
		if (ft_strncmp(t, ms_data->envp[j],
				ft_strlen(t), 0) == 0)
		{
			free(ms_data->envp[j]);
			temp[j] = ft_strdup(cmd);
			j++;
			i++;
		}
		if (!ms_data->envp[j])
			break ;
		temp[j] = ft_strdup(ms_data->envp[j]);
		free(ms_data->envp[j]);
		j++;
	}
	if (i == 0)
		temp[j] = ft_strdup(cmd);
	free(ms_data->envp);
	return (temp);
}

char	**new_export(t_ms *ms_data, char *cmd)
{
	char	**temp;
	int		j;
	char	*t;
	int		i;

	j = 0;
	i = 0;
	t = recup(cmd, "=");
	if (t == NULL)
		return (no_export(ms_data, t));
	while (ms_data->envp[j])
	{
		j++;
		if (ft_strncmp(t,
				ms_data->envp[j], ft_strlen(t), 0) == 1)
			i++;
	}
	if (i == j)
		j++;
	temp = malloc(sizeof(char *) * (j + 1));
	temp[j] = NULL;
	temp = new_export2(ms_data, temp, cmd, t);
	free (t);
	return (temp);
}

char	**new_unset2(t_ms *ms_data, char **temp, char *cmd, char *temp2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (ms_data->envp[j])
	{
		if (ft_strncmp(temp2,
				ms_data->envp[j], ft_strlen(cmd) + 1, 0) == 0)
			j++;
		if (!ms_data->envp[j])
			break ;
		temp[i] = ft_strdup(ms_data->envp[j]);
		j++;
		i++;
	}
	free_tab(ms_data->envp);
	free (temp2);
	return (temp);
}

char	**new_unset(t_ms *ms_data, char *cmd, char *temp2)
{
	char	**temp;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (ms_data->envp[j])
	{
		j++;
		if (ft_strncmp(temp2,
				ms_data->envp[j], ft_strlen(cmd) + 1, 0) == 1)
			i++;
	}
	if (i == j)
	{
		temp = malloc(sizeof(char *) * (j + 1));
		temp[j] = NULL;
	}
	else
	{
		temp = malloc(sizeof(char *) * (j));
		temp[j - 1] = NULL;
	}
	temp = new_unset2(ms_data, temp, cmd, temp2);
	return (temp);
}
