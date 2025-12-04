# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 12:02:16 by mcolin            #+#    #+#              #
#    Updated: 2025/12/04 16:55:54 by mcolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror -I includes/
SRCS_DIR = srcs/
NAME=libft.a
SOURCES=$(SRCS_DIR)stdlib/ft_atoi.c					\
		$(SRCS_DIR)stdlib/ft_calloc.c				\
		$(SRCS_DIR)stdlib/ft_split.c				\
		$(SRCS_DIR)stdlib/ft_itoa.c					\
		$(SRCS_DIR)stdlib/gnl/get_next_line.c		\
		$(SRCS_DIR)stdlib/gnl/get_next_line_utils.c	\
		$(SRCS_DIR)ctype/ft_isalnum.c				\
		$(SRCS_DIR)ctype/ft_isalpha.c				\
		$(SRCS_DIR)ctype/ft_isascii.c				\
		$(SRCS_DIR)ctype/ft_isdigit.c				\
		$(SRCS_DIR)ctype/ft_isprint.c				\
		$(SRCS_DIR)ctype/ft_tolower.c				\
		$(SRCS_DIR)ctype/ft_toupper.c				\
		$(SRCS_DIR)mem/ft_memchr.c					\
		$(SRCS_DIR)mem/ft_memcmp.c					\
		$(SRCS_DIR)mem/ft_memcpy.c					\
		$(SRCS_DIR)mem/ft_memset.c					\
		$(SRCS_DIR)mem/ft_memmove.c					\
		$(SRCS_DIR)mem/ft_bzero.c					\
		$(SRCS_DIR)str/ft_strchr.c					\
		$(SRCS_DIR)str/ft_strdup.c					\
		$(SRCS_DIR)str/ft_strlcat.c					\
		$(SRCS_DIR)str/ft_strlcpy.c					\
		$(SRCS_DIR)str/ft_strlen.c					\
		$(SRCS_DIR)str/ft_strncmp.c					\
		$(SRCS_DIR)str/ft_strnstr.c					\
		$(SRCS_DIR)str/ft_strrchr.c					\
		$(SRCS_DIR)str/ft_substr.c					\
		$(SRCS_DIR)str/ft_strjoin.c					\
		$(SRCS_DIR)str/ft_strtrim.c					\
		$(SRCS_DIR)str/ft_strmapi.c					\
		$(SRCS_DIR)str/ft_striteri.c				\
		$(SRCS_DIR)stdio/ft_putchar_fd.c			\
		$(SRCS_DIR)stdio/ft_putstr_fd.c				\
		$(SRCS_DIR)stdio/ft_putendl_fd.c			\
		$(SRCS_DIR)stdio/ft_putnbr_fd.c				\
		$(SRCS_DIR)stdio/printf/ft_printf.c			\
		$(SRCS_DIR)stdio/printf/ft_printf_putstr.c	\
		$(SRCS_DIR)stdio/printf/ft_printf_putnbr.c	\
		$(SRCS_DIR)lst/ft_lstnew.c					\
		$(SRCS_DIR)lst/ft_lstadd_front.c			\
		$(SRCS_DIR)lst/ft_lstsize.c					\
		$(SRCS_DIR)lst/ft_lstlast.c					\
		$(SRCS_DIR)lst/ft_lstadd_back.c				\
		$(SRCS_DIR)lst/ft_lstdelone.c				\
		$(SRCS_DIR)lst/ft_lstclear.c				\
		$(SRCS_DIR)lst/ft_lstiter.c					\
		$(SRCS_DIR)lst/ft_lstmap.c

OBJ_DIR = .build/
OBJS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)

CFLAGS = -Wall -Werror -Wextra -g -I includes/

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p .build/
	@mkdir -p .build/str
	@mkdir -p .build/lst
	@mkdir -p .build/mem
	@mkdir -p .build/ctype
	@mkdir -p .build/stdio
	@mkdir -p .build/stdio/printf
	@mkdir -p .build/stdlib
	@mkdir -p .build/stdlib/gnl
	$(CC) $(CFLAGS) $< -c -o $@

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: re fclean all bonus