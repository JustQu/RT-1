# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximka <maximka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 22:21:56 by maximka           #+#    #+#              #
#    Updated: 2020/07/08 13:10:23 by maximka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	RT
DIR_SRC		:=	srcs/
DIR_BIN		:=	bin/
DIR_INCLUDE :=	include/
DIR_LIBFT	:=	libft/
SDL 		:= -lSDL2
CC			:=	gcc
CFLAGS		:=	-g -Wextra -Werror -Wall
HEADERS		:=	libft.h rt.h get_next_line.h
LIBFT		:=	libft.a
REMOVE		:=	rm -rf

SRC			:=	main.c 

OBJS 		:= $(SRC:.c=.o)
LIBFT		:= $(addprefix $(DIR_LIBFT), $(LIBFT))

MAKE_LIBFT	:= make -C $(DIR_LIBFT)

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDE)

all: make_lft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(addprefix $(DIR_BIN), $(OBJS)) $(SDL) $(LIBFT) -lm -o $@

$(OBJS):%.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) -c $(CFLAGS) $< -o $(DIR_BIN)$@ -I $(DIR_INCLUDE) -lm

$(DIR_BIN):
	mkdir -p $@

make_lft:
	$(MAKE_LIBFT)

clean:
	$(REMOVE) $(addprefix $(DIR_BIN), $(OBJS))
	$(REMOVE) $(DIR_BIN)
	$(MAKE_LIBFT) clean

fclean: clean
	$(REMOVE) $(NAME)
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: clean fclean all re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) clean fclean re make_lft
