# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:33:34 by dmelessa          #+#    #+#              #
#    Updated: 2020/11/23 20:40:35 by aapricot         ###   ########.fr        #
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
		 -I./Libs//SDL2_image.framework/Headers\
		 -I./Libs/SDL2\
		 -I./Libs/SDL2_ttf/include\
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


	# SDL		= -lSDL2_image\
	# 		 -lSDL2_ttf\
	# 		 -lSDL2_gfx

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
SRCS =aabb.c                  get_first_values.c      gui_tab_bar.c           material.c              pars_texture.c          sampler.c \
bvh.c                   get_light_type.c        gui_utils.c             material_manager.c      parser.c                sampler_manager.c \
camera.c                get_obj_mat_types.c     init.c                  matrix.c                perlin.c                scene.c \
catch_event.c           get_tex_cam_types.c     instance_handler.c      matrix_manager.c        random.c                swap.c \
cl                      gui_button.c            instance_manager.c      object_manager.c        read_data.c             texture.c \
color.c                 gui_gradient.c          light_manager.c         pars_camera.c           resource_manager.c      texture_manager.c \
create_program.c        gui_init.c              logs.c                  pars_light.c            rt.c                    utils.c \
error_handling.c        gui_primitives.c        main.c                  pars_obj.c              rt_ocl.c                vector.c \
get_default.c           gui_render_text.c       main_gui.c              pars_option.c           rt_options.c            window.c \
pars_material.c			get_tracer_type.c		init_parsed_scene.c\

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
