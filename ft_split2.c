/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:59:24 by kethouve          #+#    #+#             */
/*   Updated: 2024/06/18 18:10:52 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_ope_debut(char const *s, char **dest, t_split *d_s)
{
	d_s->index = 0;
	if ((s[d_s->index] == '<' && s[d_s->i + 1] == '<')
		|| (s[d_s->index] == '>' && s[d_s->i + 1] == '>'))
	{
		while (s[d_s->i] == '>' || s[d_s->i] == '<')
			d_s->i++;
		dest[d_s->j] = put_words(s, d_s->index, d_s->i);
		d_s->j++;
		d_s->index = -1;
	}
	else if (s[d_s->index] == '<' || s[d_s->index] == '>')
	{
		while (s[d_s->i] == '>' || s[d_s->i] == '<')
			d_s->i++;
		dest[d_s->j] = put_words(s, d_s->index, d_s->i);
		d_s->j++;
		d_s->index = -1;
	}
}

void	next_split2(char const *s, char **dest, t_split	*d_s)
{
	dest[d_s->j] = put_words(s, d_s->index, d_s->i);
	if (d_s->i != ft_strlen(s) && (s[d_s->i + 1] == '>'
			|| s[d_s->i + 1] == '<' || s[d_s->i] == '>' || s[d_s->i] == '<'))
	{
		d_s->j++;
		if (s[d_s->i] == ' ' && (s[d_s->i + 1] == '<'
				|| (s[d_s->i + 1] == '>' && s[d_s->i] != '>')))
			d_s->i++;
		d_s->index = d_s->i;
		while (s[d_s->i + 1] == '<' || s[d_s->i + 1] == '>'
			|| (s[d_s->i + 1] == ' ' && (s[d_s->i + 2] == ' '
					|| s[d_s->i + 2] == '>' || s[d_s->i + 2] == '<')))
			d_s->i++;
		dest[d_s->j] = put_words(s, d_s->index, (d_s->i + 1));
		if (s[d_s->i] != '<' && s[d_s->i] != '>')
			d_s->i--;
	}
	d_s->index = -1;
	d_s->j++;
}

char	**ft_split2(char const *s, char c)
{
	t_split	*d_s;
	char	**dest;

	d_s = malloc(sizeof(t_split));
	d_s->i = 0;
	d_s->j = 0;
	d_s->qs = 0;
	d_s->index = -1;
	dest = malloc((tabs_size(s, c) + 2) * sizeof(char *));
	if (!s || !dest)
		return (0);
	if (s[0] == '<' || s[0] == '>')
		split_ope_debut(s, dest, d_s);
	while (d_s->i <= ft_strlen(s))
	{
		quote_analyse(s[d_s->i], &d_s->qs);
		if (s[d_s->i] != c && d_s->index < 0)
			d_s->index = d_s->i;
		else if ((s[d_s->i] == c || s[d_s->i] == '>' || s[d_s->i] == '<'
				|| d_s->i == ft_strlen(s)) && d_s->index >= 0 && d_s->qs == 0)
			next_split2(s, dest, d_s);
		d_s->i++;
	}
	dest[d_s->j] = NULL;
	return (free(d_s), dest);
}
