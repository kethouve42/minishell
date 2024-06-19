/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:40:01 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/15 01:52:50 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_var2(char *envp, int n)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(envp) - n + 1));
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
	char	*temp;

	i = 0;
	res = NULL;
	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[++i])
		dest[i - 1] = s[i];
	dest[i - 1] = '\0';
	i = -1;
	while (envp[++i])
	{
		temp = ft_strjoin(dest, "=");
		if (ft_strncmp(temp, envp[i], ft_strlen(dest) + 1, 0) == 0)
		{
			res = dup_var2(envp[i], ft_strlen(dest) + 1);
			return (free (temp), free(dest), res);
		}
		free(temp);
	}
	return (free(dest), ft_strdup(""));
}

void	createfile(char *file, t_ms *ms_data)
{
	int	fd;

	if (ms_data->put_in_file == 1)
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0664);
	else if (ms_data->concat_file == 1)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	else
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0664);
	close(fd);
}

void	next_cd(t_ms *ms_data)
{
	char	*temp2;
	char	*temp;

	temp2 = dup_var("$PWD", ms_data->envp);
	temp = ft_strjoin("OLDPWD=", temp2);
	ms_data->envp = new_export(ms_data, temp);
	free(temp2);
	free(temp);
}

void	new_cd(char *cmd, t_ms *ms_data)
{
	int		i;
	char	*no_arg;
	char	*temp;
	char	*buffer;

	i = 0;
	buffer = malloc(sizeof(char) * 256);
	if (!cmd)
	{
		no_arg = dup_var("$HOME", ms_data->envp);
		i = chdir(no_arg);
		free(no_arg);
	}
	else
		i = chdir(cmd);
	if (i == -1)
	{
		printf("%s est un chemin invalide\n", cmd);
		return (free(buffer));
	}
	next_cd(ms_data);
	temp = ft_strjoin("PWD=", getcwd(buffer, 256));
	ms_data->envp = new_export(ms_data, temp);
	free(temp);
	free(buffer);
}
