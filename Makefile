# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:33:34 by dmelessa          #+#    #+#              #
#    Updated: 2020/10/21 16:01:05 by user             ###   ########.fr        #
=======
#    By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:33:34 by dmelessa          #+#    #+#              #
#    Updated: 2020/10/30 13:08:09 by dmelessa         ###   ########.fr        #
>>>>>>> fixing
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
<<<<<<< HEAD
=======
		 -I/Users/dmelessa/rt2/Libs/SDL2_image.framework/Headers\
		 -I./Libs/SDL2\
		 -I./Libs/SDL2_ttf/include\
>>>>>>> fixing
		 -g
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
<<<<<<< HEAD
SRCS =aabb.c                  main.c                  swap.c\
bvh.c                                         random.c         \
camera.c                     matrix.c                read_data.c             utils.c\
catch_event.c                 matrix_manager.c        rt.c                    vector.c\
                          rt_ocl.c                window.c\
color.c                               object_manager.c        rt_options.c\
create_program.c        init.c                                 sampler.c\
error_handling.c        instance_manager.c                     sampler_manager.c\
                                 scene.c\
main_gui.c	gui_render_text.c	gui_tab_bar.c	gui_primitives.c	gui_button.c	gui_init.c\
gui_utils.c	texture_manager.c	texture.c	perlin.c\
=======
SRCS =aabb.c			instance_manager.c	perlin.c		sampler_manager.c\
bvh.c			light_manager.c		random.c		scene.c\
camera.c		main.c			read_data.c		swap.c\
catch_event.c		material.c		resource_manager.c	texture.c\
color.c			material_manager.c	rt.c			texture_manager.c\
create_program.c	matrix.c		rt_ocl.c		utils.c\
error_handling.c	matrix_manager.c	rt_options.c		vector.c\
init.c			object_manager.c	sampler.c		window.c\

>>>>>>> fixing

	# gui_gradient.c



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
