# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:33:34 by dmelessa          #+#    #+#              #
#    Updated: 2020/09/15 17:35:50 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	RT
DIR_SRC		:=	srcs/
DIR_BIN		:=	bin/
DIR_INCLUDE :=	include/
DIR_LIBFT	:=	Libs/libft/
SDL 		:= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx
CC			:=	gcc
CFLAGS		:=	-g #-Wextra -Werror -Wall
HEADERS		:=	libft.h rt.h get_next_line.h gui.h
LIBFT		:=	libft.a
REMOVE		:=	rm -rf

SRC			:=	main.c \
		main_gui.c gui_xyz.c gui_button.c\
		gui_gradient.c mouse.c keyboard.c \
		gui_tab_bar.c gui_progress_bar.c \
		gui_render_text.c gui_checkbox.c \
		qjulia.c qjulia_color.c qjulia_init.c


OBJS 		:= $(SRC:.c=.o)
LIBFT		:= $(addprefix $(DIR_LIBFT), $(LIBFT))

MAKE_LIBFT	:= make -C $(DIR_LIBFT)

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDE)

all: make_lft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(addprefix $(DIR_BIN), $(OBJS)) $(SDL) -framework openGL -framework openCL $(LIBFT) -o $@

$(OBJS):%.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) -c $(CFLAGS) $< -o $(DIR_BIN)$@ -I $(DIR_INCLUDE)

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
