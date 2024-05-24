/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:58:53 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/24 17:34:52 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (0);
		i++;
	}
	return (1);
}
