/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:58:41 by kethouve          #+#    #+#             */
/*   Updated: 2024/05/21 18:15:33 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*put_words(char const *s, int debut, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(((end - debut) + 1) * sizeof(char));
	if (!word)
		return (0);
	while (debut < end)
	{
		word[i] = s[debut];
		i++;
		debut++;
	}
	word[i] = '\0';
	return (word);
}

int	tabs_size(char const *s, char c)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && count == 0)
		{
			count = 1;
			j++;
		}
		else if (s[i] == c || ((s[i] == '>' || s[i] == '<') && s[i - 1] != ' '))
				count = 0;
		if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<'))
			i += 2;
		else
			i++;
	}
	return (j);
}

char	**ft_split_env(char const *s, char c)
{
	int			i;
	int			j;
	int				index;
	char			**dest;

	i = 5;
	j = 0;
	index = -1;
	dest = malloc((tabs_size(s, c) + 1) * sizeof(char *));
	if (!s || !dest)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			dest[j] = put_words(s, index, i);
			index = -1;
			j++;
		}
		i++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	**dest;

	i = 0;
	j = 0;
	index = -1;
	dest = malloc((tabs_size(s, c) + 2) * sizeof(char *));
	if (!s || !dest)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			dest[j] = put_words(s, index, i);
			index = -1;
			j++;
		}
		i++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split2(char const *s, char c)
{
	int			i;
	int			j;
	int				index;
	char			**dest;

	i = 0;
	j = 0;
	index = -1;
	dest = malloc((tabs_size(s, c) + 2) * sizeof(char *));
	//printf("s: %s\n\n", s);
	if (!s || !dest)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || s[i] == '|' || s[i] == '>' || s[i] == '<' || i == ft_strlen(s)) && index >= 0)
		{
			//printf("enter: %c\n", s[i]);
			dest[j] = put_words(s, index, i);
			if (i != ft_strlen(s) && (s[i + 1] == '>' || s[i + 1] == '<' || s[i] == '>'))
			{
				//printf("s: %c, 1\n\n", s[i]);
				if(s[i] == ' ' || s[i + 1] == '<' || (s[i + 1] == '>' && s[i] != '>'))
				{
				//	printf("s:%c, 2\n\n", s[i]);
					i++;
				//	printf("s:%c, 3\n\n", s[i]);
				}
				j++;
				index = i;
				if (s[i + 1] == '<' || s[i + 1] == '>')
					i++;
				//printf("s:%c, 4\n\n", s[i]);
				dest[j] = put_words(s, index, (i + 1));
				if (s[i] != '<' && s[i] != '>')
					i--;
			}
			index = -1;
			j++;
		}
		i++;
	}
	dest[j] = NULL;
	return (dest);
}
