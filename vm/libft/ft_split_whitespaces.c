/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:36:36 by eviana            #+#    #+#             */
/*   Updated: 2019/04/14 17:36:33 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_whitespaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	return (i);
}

static char	**clear(char **tab, int k)
{
	int i;

	i = 0;
	while (i < k)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**addstrings(char *str, char **tab, int i, int j)
{
	int k;
	int l;

	k = 0;
	while (str[i] != '\0')
	{
		l = 0;
		i = skip_whitespaces(str, i);
		if (str[i] == '\0')
			break ;
		j = i;
		while (str[i] != ' ' && str[i] != 9 && str[i] != '\n' && str[i] != '\0')
			i++;
		if (!(tab[k] = (char*)malloc(sizeof(char) * (i - j + 1))))
			return (clear(tab, k));
		while (j + l < i)
		{
			tab[k][l] = str[j + l];
			l++;
		}
		tab[k][l] = '\0';
		k++;
	}
	tab[k] = 0;
	return (tab);
}

char		**ft_split_whitespaces(char *str)
{
	int		i;
	int		j;
	int		words;
	char	**tab;

	i = 0;
	words = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i] == '\0')
			break ;
		words++;
		while (str[i] != ' ' && str[i] != 9 && str[i] != '\n' && str[i] != '\0')
			i++;
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	return (addstrings(str, tab, i, j));
}
