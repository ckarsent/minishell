# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 13:09:06 by qboutel           #+#    #+#              #
#    Updated: 2025/04/17 16:08:35 by qboutel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(HEADER) -g

SRCS :=  \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c	 \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_strnstr.c \
	ft_strdup.c	\
	ft_calloc.c	\
	ft_memcmp.c	\
	ft_memchr.c	\
	ft_substr.c	\
	ft_strjoin.c \
	ft_strtrim.c \
	ft_memmove.c\
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c\
	ft_putchar_fd.c \
	ft_putstr_fd.c\
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_atol.c \
	ft_strlen.c \
	ft_strcmp.c \
	ft_isspace.c

OBJS = $(SRCS:.c=.o)
HEADER = libft.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf  $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
