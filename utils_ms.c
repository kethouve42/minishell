/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:33:29 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/14 19:09:13 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, const char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, int n, int cmd)
{
	int		i;

	i = 0;
	if (!s2 || ft_strlen(s1) < n)
		return (1);
	if (n < 1)
		return (0);
	while (s1[i] == s2[i] && i < n && s1[i])
		i++;
	if (cmd == 0 && i == n)
		return (0);
	else if (cmd == 1 && i == n && s1[i] == '\0')
		return (0);
	return (1);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_strdup2(char **s)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	dest[i] = NULL;
	while (s[j])
	{
		dest[j] = ft_strdup(s[j]);
		j++;
	}
	return (dest);
}

char	***ft_strdup3(char ***s)
{
	char	***dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	dest = malloc(sizeof(char **) * (i + 1));
	dest[i] = NULL;
	while (s[j])
	{
		dest[j] = ft_strdup2(s[j]);
		j++;
	}
	return (dest);
}
