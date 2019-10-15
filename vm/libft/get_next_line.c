/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 09:33:00 by eviana            #+#    #+#             */
/*   Updated: 2019/04/14 17:28:37 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char	*sp_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*str;

	if (!s1 || !s2 || !(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	str = ft_strcpy(str, s1);
	free((void*)s1);
	return (ft_strncat(str, s2, n));
}

static int	gnl_noendl_memory(char **line, char **str, int fd, char *buff)
{
	size_t	i;
	int		nbread;

	if (!(*line = ft_strsub(str[fd], 0, ft_strlen(str[fd]))))
		return (-1);
	while (!ft_strchr(str[fd], '\n')
			&& (nbread = read(fd, buff, BUFF_SIZE)) > 0)
	{
		i = 0;
		buff[nbread] = '\0';
		while (buff[i] && buff[i] != '\n')
			i++;
		if (!(*line = sp_strnjoin(*line, buff, i)))
			return (-1);
		if (ft_strchr(buff, '\n'))
		{
			str[fd] = ft_strncpy(str[fd], (buff + i + 1), ft_strlen(buff) - i);
			ft_strdel(&str[fd] + ft_strlen(buff) - i - 1);
			return (1);
		}
	}
	ft_strdel(&str[fd]);
	if (nbread == 0 && ft_strlen(*line))
		return (1);
	return (nbread < 0 ? -1 : 0);
}

static int	gnl_endl_memory(char **line, char **str, int fd)
{
	size_t	i;

	i = 0;
	while (str[fd][i] && str[fd][i] != '\n')
		i++;
	if (!(*line = ft_strsub(str[fd], 0, i)))
		return (-1);
	str[fd] = ft_strncpy(str[fd], (str[fd] + (i + 1)),
			(ft_strlen(str[fd]) - (i + 1)));
	ft_bzero(str[fd] + ft_strlen(str[fd]) - (i + 1), (i + 1));
	return (1);
}

static int	ft_error(char *buff)
{
	free(buff);
	return (-1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*str[MAX_FD + 1];
	char		*buff;
	int			res;

	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (fd < 0 || BUFF_SIZE < 1 || !line
			|| read(fd, buff, 0) < 0)
		return (ft_error(buff));
	if (!str[fd])
		if (!(str[fd] = ft_strnew(BUFF_SIZE)))
			return (ft_error(buff));
	if (!ft_strchr(str[fd], '\n'))
	{
		res = gnl_noendl_memory(line, str, fd, buff);
		free(buff);
		return (res);
	}
	else
	{
		free(buff);
		return (gnl_endl_memory(line, str, fd));
	}
}
