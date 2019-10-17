/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:05:19 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/07 16:05:22 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

# include "libft.h"

int     autocomplete_word(char *str, char **dictionary);  // returns number of completed chars as an (int) for [tab] or deleting
int     autocomplete_str(char *str, char **dictionary);

#endif