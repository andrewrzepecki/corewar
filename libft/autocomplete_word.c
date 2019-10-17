/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:05:39 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/07 16:05:40 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

int     print_match(char *complete)
{
    ft_printf("%s", complete);
    return (ft_strlen(complete));
}

int     search_dictionary(char *word, char **dictionary)
{
    int i;

    i = 0;
    while (dictionary && dictionary[i])
    {
        if (ft_strlen(dictionary[i]) > ft_strlen(word))
            if (ft_strnstr(dictionary[i], word, (size_t)ft_strlen(word)))
                return (i);
        i++;
    }
    return (-1);
}

int     get_last_word(char **words)
{
    int i;

    i = 0;
    while (words[i + 1])
        i++;
    if (words[i])
        return (i);
    else
        return (-1);
}

int     autocomplete_word(char *str, char **dictionary)
{
    int     i;
    int     ret;
    char    **words;

    ret = 0;
    if (!(words = ft_strsplit(str, ' ')))
        return (0);
    if ((i = get_last_word(words)) > -1)
    {
        if ((ret = search_dictionary(words[i], dictionary)) != -1)
            ret = print_match(dictionary[ret] + ft_strlen(words[i]));
        else
            return (0);
    }
    return (ret);
}