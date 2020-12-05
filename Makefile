# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:33:34 by dmelessa          #+#    #+#              #
#    Updated: 2020/12/05 23:59:40 by dmelessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./RT
CC = gcc
RM = rm -f
CURRENTDIR = .

#UNAME_S = $(shell uname -s)

#SYSTEM:
SYSTEM = $(shell uname)
MACOS = Darwin
LINUX = Linux

CFLAGS = -I$(INCDIR)\
		 -I$(LIBFTINC)\
		 -I$(SDL2INC)\
		 -I./Libs/SDL2_image.framework/Headers\
		 -I./Libs/SDL2\
		 -I./Libs/SDL2_ttf/include\
		 -g
		#  --analyze\
		#  --analyzer-output html\
#		 -Wall\
		 -Werror\
		 -Wextra
ifeq ($(SYSTEM), $(MACOS))

	LDLIBS = -lm\
			 -lft\
			 -framework SDL2\
			 -framework OpenCL\
			 -framework SDL2_image\
			 -framework SDL2_ttf


	# SDL		= -framework SDL2_image\
	# 		 -framework SDL2_ttf\
	# 		 -framework SDL2_gfx


	SDL		= -lSDL2_image\
			 -lSDL2_ttf\
			 -lSDL2_gfx

	LDFLAGS = -L$(LIBFTDIR)\
			  -F $(LIBSDIR)\
			  -rpath $(LIBSDIR)

else ifeq ($(SYSTEM), $(LINUX))

	LDLIBS = -lm\
			 -l SDL2\
			 -l OpenCL
			 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

	LDFLAGS	= $(LIBFT)

endif


LIBSDIR = $(CURRENTDIR)/Libs

LIBFT = $(LIBFTDIR)/libft.a
LIBFTDIR = $(LIBSDIR)/libft
LIBFTINC = $(LIBFTDIR)
LIBFTHEAD = $(LIBFTINC)/libft.h $(LIBFTINC)/get_next_line.h

#MACOS
SDL2DIR = $(LIBSDIR)/SDL2.framework
SDL2INC = ./Libs

INCDIR = $(CURRENTDIR)/include
INCS = *.h
INCS := $(addprefix $(INCDIR)/, $(INCS))

SRCSDIR	= ./srcs/
SRCS =aabb.c			instance_manager.c	perlin.c		sampler_manager.c\
bvh.c			light_manager.c		random.c		scene.c\
camera.c		main.c			read_data.c		swap.c\
catch_event.c		material.c		resource_manager.c\
color.c			material_manager.c	rt.c\
create_program.c	matrix.c		rt_ocl.c		utils.c\
error_handling.c	matrix_manager.c	rt_options.c		vector.c\
init.c			object_manager.c	sampler.c		window.c\
gui.c			gui_render_text.c	gui_tab_bar.c	gui_button.c\
gui_init.c		gui_utils.c			texture_manager.c	texture.c\
gui_utils_2.c		gui_get_data.c		gui_object_vision.c\
gui_get_data_2.c	gui_tab_bar_2.c		gui_utils_3.c	gui_get_data_3.c\



OBJSDIR = ./obj/
OBJS = $(addprefix $(OBJSDIR), $(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(INCS) $(LIBFTHEAD)
	@echo 'making executable'
	$(CC) -o $@ $(OBJS) $(LDLIBS) $(SDL) $(LDFLAGS)
	@echo DONE!


$(LIBFT):
	@make -C $(LIBFTDIR)

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(INCS)

$(OBJSDIR):
	mkdir $@

clean:
	@echo deliting object files
	@$(RM) $(OBJS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@echo deliting executable file
	@$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean

.PHONY: all clean fclean re
re:	fclean all
