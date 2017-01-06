# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epillot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/04 16:40:08 by epillot           #+#    #+#              #
#    Updated: 2017/01/06 14:21:54 by epillot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAG = -Wall -Wextra -Werror

SRC = main.c\
	  get_right.c\
	  get_time.c\
	  get_option_ls.c\
	  get_file_list.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft/
	gcc $(FLAG) -c $(SRC)
	gcc -o $(NAME) $(OBJ) -L ./libft/ -lft

clean:
	make fclean -C libft/
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
