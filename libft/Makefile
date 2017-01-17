# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epillot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:38:05 by epillot           #+#    #+#              #
#    Updated: 2017/01/17 12:49:38 by epillot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAG = -Wall -Wextra -Werror
OPTION = -c
SRC = ft_atoi.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_bzero.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isprint.c\
	  ft_isspace.c\
	  ft_lstadd.c\
	  ft_lstadd_back.c\
	  ft_lstiter.c\
	  ft_lstdelone.c\
	  ft_lstdel.c\
	  ft_memalloc.c\
	  ft_itoa.c\
	  ft_lstnew.c\
	  ft_memchr.c\
	  ft_memccpy.c\
	  ft_lstmap.c\
	  ft_memcmp.c\
	  ft_memdel.c\
	  ft_memcpy.c\
	  ft_putchar.c\
	  ft_putnchar.c\
	  ft_putchar_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_memset.c\
	  ft_memmove.c\
	  ft_putstr.c\
	  ft_putnbr.c\
	  ft_putstr_fd.c\
	  ft_putnbr_base.c\
	  ft_putnbr_fd.c\
	  ft_strcat.c\
	  ft_strclr.c\
	  ft_strchr.c\
	  ft_strcmp.c\
	  ft_strdel.c\
	  ft_strcpy.c\
	  ft_striter.c\
	  ft_strdup.c\
	  ft_strequ.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strnjoin.c\
	  ft_strlen.c\
	  ft_strlcat.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_split_whitespace.c\
	  ft_strncpy.c\
	  ft_strncmp.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strnequ.c\
	  ft_strrchr.c\
	  ft_strstr.c\
	  ft_strsub.c\
	  ft_tolower.c\
	  ft_strupcase.c\
	  ft_strsplit_lst.c\
	  ft_toupper.c\
	  ft_strtrim.c\
	  ft_strsplit.c\
	  ft_print_memory.c\
	  get_next_line.c\
	  ft_abs.c\
	  ft_print_bits.c\
	  ft_putwchar.c\
	  ft_putwchar_fd.c\
	  ft_putwstr_fd.c\
	  ft_putwstr.c\
	  ft_itoa_base.c\
	  ft_max.c\
	  c_convert.c\
	  d_convert.c\
	  encode_unicode.c\
	  ft_printf.c\
	  ft_sprintf.c\
	  ft_printf_fd.c\
	  get_option.c\
	  get_param.c\
	  s_convert.c\
	  str_format.c\
	  tools_for_convert.c\
	  tools_for_convert2.c\
	  u_convert.c\
	  wc_convert.c\
	  ws_convert.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAG) $(OPTION) $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
