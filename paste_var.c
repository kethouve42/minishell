/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:06:22 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/19 17:21:06 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	place_var_in_s(char *s, char *var, char *dest, t_tri_index *t_i)
{
	t_i->i++;
	while (s[t_i->i] && ((s[t_i->i] >= 'a' && s[t_i->i] <= 'z')
			|| (s[t_i->i] >= 'A' && s[t_i->i] <= 'Z')
			|| (s[t_i->i] >= '0' && s[t_i->i] <= '9') || s[t_i->i] == '_'))
		t_i->i++;
	t_i->i--;
	while (var[++t_i->k])
		dest[++t_i->j] = var[t_i->k];
}

char	*next_var(char *s, char *var, int j, int flag)
{
	t_tri_index	*t_i;
	int			quote_status;
	char		*dest;

	t_i = malloc(sizeof(t_tri_index));
	quote_status = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(var) - j + 1));
	t_i->j = -1;
	t_i->i = -1;
	t_i->k = -1;
	while (s[++t_i->i])
	{
		quote_analyse(s[t_i->i], &quote_status);
		if (s[t_i->i] == '$' && (quote_status == 0 || quote_status == 2)
			&& flag == 0)
		{
			place_var_in_s(s, var, dest, t_i);
			flag = 1;
		}
		else if (s[t_i->i])
			dest[++t_i->j] = s[t_i->i];
	}
	dest[++t_i->j] = '\0';
	free(t_i);
	return (dest);
}

char	*get_var(char *s, int i, char **envp, int *l)
{
	char	*var;
	char	*res;
	int		j;

	j = i - 1;
	while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
		|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_')
	{
		i++;
	}
	var = malloc(sizeof(char) * (i - j) + 1);
	i = 0;
	var[i++] = s[j++];
	while ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z')
		|| (s[j] >= '0' && s[j] <= '9') || s[i] == '_')
	{
		var[i] = s[j];
		i++;
		j++;
	}
	var[i] = '\0';
	*l = ft_strlen(var);
	res = dup_var(var, envp);
	return (free(var), res);
}

char	*replace_var(char *s, char **envp)
{
	int		i;
	int		j;
	int		quote_status;
	char	*dest;
	char	*var;

	i = 0;
	j = 0;
	quote_status = 0;
	dest = NULL;
	var = NULL;
	while (s[i])
	{
		quote_analyse(s[i], &quote_status);
		if (s[i] == '$' && (quote_status == 0 || quote_status == 2))
		{
			var = get_var(s, i + 1, envp, &j);
			dest = next_var(s, var, j, 0);
			return (free(var), dest);
		}
		i++;
	}
	return (free(var), dest);
}

void	verif_var(char ***ct2, t_tri_index *t_i, char **envp)
{
	char	*temp;

	temp = NULL;
	t_i->i = 0;
	t_i->j = 0;
	while (ct2[t_i->i])
	{
		t_i->j = 0;
		while (ct2[t_i->i][t_i->j])
		{
			while (var_in_s(ct2[t_i->i][t_i->j]) == 1)
			{
				temp = replace_var(ct2[t_i->i][t_i->j], envp);
				free(ct2[t_i->i][t_i->j]);
				ct2[t_i->i][t_i->j] = ft_strdup(temp);
				free(temp);
				temp = NULL;
			}
			t_i->j++;
		}
		t_i->i++;
	}
}
