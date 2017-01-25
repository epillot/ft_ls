# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epillot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/04 16:40:08 by epillot           #+#    #+#              #
#    Updated: 2017/01/25 16:08:08 by epillot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAG = -Wall -Wextra -Werror

SRC_NAME = 	main.c\
	  		get_option_ls.c\
	  		create_node.c\
	  		add_node.c\
	  		get_flist.c\
	  		get_additional_part.c\
	  		get_long_info.c\
	  		print_files.c\
	  		print_dir.c\
	  		free_list.c\
	  		ls_error.c\

SRC_PATH = srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj/

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

INC = ./includes/

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc $(FLAG) -o $(NAME) $(OBJ) -I $(INC) -L ./libft/ -lft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p obj
	gcc $(FLAG) -c -I $(INC) $< -o $@

clean:
	make fclean -C libft/
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
