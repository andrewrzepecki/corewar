# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eviana <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/15 11:24:10 by eviana            #+#    #+#              #
#    Updated: 2019/04/15 11:24:16 by eviana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS	= -Wall -Werror -Wextra
NAME = libft.a

SRC = ft_putchar_fd.c ft_putnbr.c ft_putendl.c ft_putstr.c ft_putchar.c	\
	  ft_itoa.c ft_strsplit.c ft_strtrim.c ft_strjoin.c ft_strsub.c		\
	  ft_strnequ.c ft_strequ.c ft_strmapi.c ft_strmap.c ft_striteri.c	\
	  ft_striter.c ft_strclr.c ft_strdel.c ft_strnew.c ft_memdel.c		\
	  ft_memalloc.c ft_tolower.c ft_toupper.c ft_isprint.c ft_isascii.c	\
	  ft_isalnum.c ft_isdigit.c ft_isalpha.c ft_atoi.c ft_strncmp.c		\
	  ft_strcmp.c ft_strnstr.c ft_strstr.c ft_strrchr.c ft_strlcat.c	\
	  ft_strchr.c ft_strncat.c ft_strcat.c ft_strncpy.c ft_strcpy.c		\
	  ft_memcmp.c ft_memchr.c ft_memmove.c ft_memccpy.c ft_memcpy.c		\
	  ft_bzero.c ft_strlen.c ft_memset.c ft_putnbr_fd.c ft_putendl_fd.c	\
	  ft_putstr_fd.c ft_strdup.c ft_ltoa.c ft_lltoa.c ft_strrev.c 		\
	  ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c	\
	  ft_lstmap.c ft_foreach.c ft_factorial.c	ft_strcount.c			\
	  ft_power.c ft_fibonacci.c ft_sqrt.c ft_is_prime.c					\
	  ft_utoa.c ft_ultoa.c ft_ulltoa.c ft_convert_base.c ft_putull.c	\
	  ft_size_long.c ft_strallchr.c get_next_line.c	ft_issort.c			\
	  ft_atol.c ft_split_whitespaces.c ft_swap.c

HEADER = ../includes/

OBJ = $(SRC:.c=.o) 														\

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -c $(SRC) -I $(HEADER)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

.PHONY: clean fclean

clean:
	@/bin/rm -f $(OBJ) libft.h.gch

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
