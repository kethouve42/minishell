/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:14:59 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/05 18:27:35 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*tmp;

	tmp = s;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}

void	ft_putitoa(char *dest, int n, int ndigit)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		n = -214748364;
		ndigit--;
		dest[ndigit] = '8';
	}
	if (n < 0)
	{
		n = n * -1;
		dest[0] = '-';
		i++;
	}
	while (i < ndigit)
	{
		ndigit--;
		dest[ndigit] = (n % 10) + '0';
		n = n / 10;
	}
}

int	count_digit(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n = n * -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		ndigit;

	ndigit = count_digit(n);
	if (n < 0 || ndigit == 0)
		ndigit++;
	dest = malloc(ndigit + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	ft_bzero(dest, ndigit + 1);
	ft_putitoa(dest, n, ndigit);
	return (dest);
}
