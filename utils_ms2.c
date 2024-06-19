/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:58:53 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/18 17:07:31 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_in_s(char *s)
{
	int	i;
	int	quote_status;

	i = 0;
	quote_status = 0;
	while (s[i])
	{
		quote_analyse(s[i], &quote_status);
		if (s[i] == '$' && (quote_status == 0 || quote_status == 2))
			return (1);
		i++;
	}
	return (0);
}

int	quote_analyse(char c, int *quote_status)
{
	if (c == 39 && (*quote_status == 1 || *quote_status == 0))
	{
		if (*quote_status == 1)
			*quote_status = 0;
		else
			*quote_status = 1;
		return (1);
	}
	else if (c == 34 && (*quote_status == 2 || *quote_status == 0))
	{
		if (*quote_status == 2)
			*quote_status = 0;
		else
			*quote_status = 2;
		return (1);
	}
	return (0);
}

int	quote_in_word(char *s)
{
	int	i;
	int	quote_status;
	int	quote;

	i = 0;
	quote_status = 0;
	quote = 0;
	while (s[i])
	{
		if (quote_analyse(s[i], &quote_status) == 1)
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return (0);
	return (printf("Quote number incorect\n"), 1);
}

void	dup_quote_next(const char *s, char *dest, int j)
{
	int	i;
	int	k;
	int	quote_status;

	i = 0;
	k = 0;
	quote_status = 0;
	while (s[i])
	{
		if (quote_analyse(s[i], &quote_status) == 1 && j != 0)
		{
			i++;
			j--;
			if (!s[i])
				break ;
		}
		else
		{
			dest[k] = s[i];
			i++;
			k++;
		}
	}
	dest[k] = '\0';
}

char	*dup_quote(const char *s)
{
	int		quote_status;
	int		i;
	int		j;
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
	dup_quote_next(s, dest, j);
	return (dest);
}
