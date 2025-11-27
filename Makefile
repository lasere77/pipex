# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 21:59:30 by mcolin            #+#    #+#              #
#    Updated: 2025/11/26 15:15:19 by mcolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME = pipex
SRCS_DIR = srcs/
SOURCES =	$(SRCS_DIR)main.c				\
			$(SRCS_DIR)process.c			\


OBJ_DIR = .build/
OBJS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)

CFLAGS = -Wall -Werror -Wextra -g -I includes/

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) bonus --no-print-directory -C libft/
	$(CC) $(OBJS) $(CFLAGS) libft/libft.a -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p .build/
	$(CC) $(CFLAGS) $< -c -o $@

gdb: $(NAME)
	gdb -tui $(NAME)

fclean: clean
	$(MAKE) fclean -C libft/
	rm -rf $(NAME)

clean:
	$(MAKE) clean --no-print-directory -C libft/
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all fclean clean re gdb