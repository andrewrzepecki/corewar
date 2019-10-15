/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:19:57 by eviana            #+#    #+#             */
/*   Updated: 2018/11/16 22:31:07 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	j;
	size_t			n;
	char			*str;

	i = 0;
	j = 1;
	if (!s)
		return (NULL);
	n = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (ft_strnew(0));
	while (s[n - j] == ' ' || s[n - j] == '\n' || s[n - j] == '\t')
		j++;
	str = ft_strsub(s, i, (size_t)(n - i - j + 1));
	return (str);
}
