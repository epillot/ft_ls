# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epillot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/04 16:40:08 by epillot           #+#    #+#              #
#    Updated: 2017/01/18 18:51:19 by epillot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAG = -Wall -Wextra -Werror

SRC = main.c\
	  get_option_ls.c\
	  add_node.c\
	  get_file_list.c\
	  get_additional_part.c\
	  print_content.c\
	  get_long_info.c\
	  print_file.c\
	  print_dir.c\
	  free_list.c\
	  ls_error.c\

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
