# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpetras <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/14 07:55:11 by fpetras           #+#    #+#              #
#    Updated: 2018/02/24 14:27:39 by fpetras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

SRC = main.c \
	  display.c \
	  display2.c \
	  keypresses.c \
	  color.c \
	  utilities.c \
	  signals.c \
	  ft_tablen.c \
	  ft_free_tab.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@make -C libft
	@$(CC) $(FLAGS) -o $(NAME) $(SRC) libft/libft.a -ltermcap

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
