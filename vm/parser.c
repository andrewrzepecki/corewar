/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:36:13 by eviana            #+#    #+#             */
/*   Updated: 2019/10/15 17:16:41 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <fcntl.h> // open
#include <unistd.h> // read
#include "op.h"

// int     parser()
// {
//
// }

int     main(int argc, char **argv)
{
    int     fd;
    char    header[sizeof(header_t)];
    char    champ[CHAMP_MAX_SIZE];
    int     res[2];

    fd = open(argv[1], O_RDONLY);
    //printf("sizeof(header_t) : %lu\n", sizeof(header_t));
    //printf("CHAMP_MAX_SIZE : %d\n", CHAMP_MAX_SIZE);
    res[0] = read(fd, header, sizeof(header_t));
    res[1] = read(fd, champ, CHAMP_MAX_SIZE);

    //write(1, header, res[0]);
    write(1, champ, res[1]);
    (void)argc;
    return (0);
}