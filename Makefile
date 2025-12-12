# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 21:59:30 by mcolin            #+#    #+#              #
#    Updated: 2025/12/12 15:52:39 by mcolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME = pipex
SRCS_DIR = srcs/
SRCS_DIR_BONUS = srcs_bonus/
SOURCES =	$(SRCS_DIR)main.c			\
			$(SRCS_DIR)arg.c			\
			$(SRCS_DIR)cmd.c			\
			$(SRCS_DIR)process.c		\
			$(SRCS_DIR)process_utils.c	\

SOURCES_BONUS =	$(SRCS_DIR_BONUS)main_bonus.c			\
				$(SRCS_DIR_BONUS)arg_bonus.c			\
				$(SRCS_DIR_BONUS)cmd_bonus.c			\
				$(SRCS_DIR_BONUS)process_bonus.c		\
				$(SRCS_DIR_BONUS)process_utils_bonus.c	\

OBJ_DIR = .build/
OBJ_DIR_BONUS = .build_bonus/
OBJS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)
OBJS_BONUS = $(SOURCES_BONUS:$(SRCS_DIR_BONUS)%.c=$(OBJ_DIR_BONUS)%.o)

CFLAGS = -Wall -Werror -Wextra -g
INCLUDE = -I includes/ -I libft/includes/
INCLUDE_BONUS = -I includes_bonus/ -I libft/includes/

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) --no-print-directory -C libft/
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDE) libft/libft.a -o $(NAME)

bonus: $(OBJS_BONUS)
	$(MAKE) --no-print-directory -C libft/
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(INCLUDE_BONUS) libft/libft.a -o $(NAME)

$(OBJ_DIR_BONUS)%.o: $(SRCS_DIR_BONUS)%.c
	@mkdir -p .build_bonus/
	$(CC) $(CFLAGS) $(INCLUDE_BONUS) $< -c -o $@

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p .build/
	$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

gdb: $(NAME)
	gdb -tui $(NAME)

fclean: clean
	$(MAKE) fclean -C libft/
	rm -rf $(NAME)

clean:
	$(MAKE) clean --no-print-directory -C libft/
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)

re: fclean all

.PHONY: all bonus fclean clean re gdb