/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:33:29 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/24 17:28:18 by kethouve         ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!s2)
		return (1);
	if (n < 1)
		return (0);
	while (s1[i] == s2[i] && i < n && s1[i])
		i++;
	if (i == n)
		return (0);
	return (1);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_strlen(s) + 1 * sizeof(char));
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

char	*ft_strdup_quote(const char *s)
{
	int		quote_status;
	int		i;
	int		j;
	int		k;
	char	*dest;

	quote_status = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (quote_analyse(s[i], &quote_status) == 1)
			j++;
		i++;
	}
	if (quote_status != 0 && (j % 2) != 0)
		j--;
	dest = malloc(sizeof(char) * (ft_strlen(s) - j + 1));
	i = 0;
	k = 0;
	quote_status = 0;
	while (s[i])
	{
		if (quote_analyse(s[i], &quote_status) == 1 && j != 0)
		{
			i++;
			j--;
		}
		if (!s[i])
			break ;
		dest[k] = s[i];
		i++;
		k++;
	}
	dest[k] = '\0';
	return (dest);
}
