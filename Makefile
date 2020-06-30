# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 22:21:56 by maximka           #+#    #+#              #
#    Updated: 2020/06/29 18:40:55 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = RTv1

# SRC = main.c \
# 		vector.c\
# 		useful.c\
# 		useful2.c\
# 		light.c\
# 		parse.c\
# 		move.c\
# 		init_vectors.c\
# 		parse_shape.c\
# 		init_shape.c\
# 		init.c\
# 		free.c\
# 		errors.c\
# 		rotate.c\
# 		matrix.c\
# 		useful3.c\
# 		check.c\
# 		useful4.c\
# 		useful5.c

# libft = ./libft/libft.a

# FLAGS = -g -Wall -Wextra -Werror

# SDL = -lSDL2

# HEADER = rtv1.h

# OBJ = main.o \
# 		vector.o\
# 		useful.o\
# 		useful2.o\
# 		light.o\
# 		parse.o\
# 		move.o\
# 		init_vectors.o\
# 		parse_shape.o\
# 		init_shape.o\
# 		init.o\
# 		free.o\
# 		errors.o\
# 		rotate.o\
# 		matrix.o\
# 		useful3.o\
# 		check.o\
# 		useful4.o\
# 		useful5.o

# LIB = lib

# all: $(NAME)

# $(NAME): $(LIB) $(OBJ)
# 	gcc $(SRC) $(FLAGS) -lm -o $(NAME) $(SDL) $(libft)

# $(LIB):
# 	make -C ./libft/

# %.o:%.c $(HEADER)
# 	gcc -L libft -lft -o $@ -c $<

# clean:
# 	make -C libft clean
# 	rm -f $(OBJ)

# fclean: clean
# 	make -C libft fclean
# 	rm -f $(NAME)

# re:fclean all

NAME		:=	RTv1
DIR_SRC		:=	srcs/
DIR_BIN		:=	bin/
DIR_INCLUDE :=	include/
DIR_LIBFT	:=	libft/
SDL 		:= -lSDL2
CC			:=	gcc
CFLAGS		:=	-g -Wextra -Werror -Wall
HEADERS		:=	libft.h rtv1.h get_next_line.h
LIBFT		:=	libft.a
REMOVE		:=	rm -rf

SRC			:=	main.c \
		vector.c\
		useful.c\
		useful2.c\
		light.c\
		parse.c\
		move.c\
		init_vectors.c\
		parse_shape.c\
		init_shape.c\
		init.c\
		free.c\
		errors.c\
		rotate.c\
		matrix.c\
		useful3.c\
		check.c\
		useful4.c\
		useful5.c

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
