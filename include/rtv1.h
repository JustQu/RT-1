/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 20:18:58 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 18:49:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

# define HEIGHT 800
# define WIDTH 800
# define PI 3.1415926535

typedef struct		s_sol
{
	float			d_cap;
	float			dx;
	float			dy;
	float			dz;
	float			a;
	float			b;
	float			c;
	double			n[3];
	double			m[3];
	double			k[4][4];
}					t_sol;

typedef	struct		s_color
{
	int				a;
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_rotation
{
	double			angle_x;
	double			angle_y;
	double			angle_z;
}					t_rotation;

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
	float			l;
}					t_vector;

typedef struct		s_plane
{
	float			a;
	float			b;
	float			c;
	float			d;
	t_rotation		r;
	t_color			col;
	t_sol			sol;
}					t_plane;

typedef struct		s_cone
{
	t_vector		o;
	float			a;
	float			b;
	float			c;
	t_rotation		r;
	t_color			col;
	t_sol			sol;
}					t_cone;

typedef struct		s_cilin
{
	t_vector		c;
	float			a;
	float			b;
	t_rotation		r;
	t_color			col;
	t_sol			sol;
}					t_cilin;

typedef struct		s_sphere
{
	t_vector		c;
	t_color			col;
	t_rotation		r;
	float			radius;
	t_sol			sol;
}					t_sphere;

typedef struct		s_shape
{
	t_sphere		*sph;
	t_cilin			*cilin;
	t_cone			*cone;
	t_plane			*plane;
	float			t_closest;
	int				specular;
	t_rotation		r;
	struct s_shape	*next;
}					t_shape;

typedef struct		s_light
{
	float			intensity;
	int				type;
	t_vector		dir;
	t_vector		center;
	t_color			col;
	struct s_light	*next;
}					t_light;

typedef struct		s_lvectors
{
	t_vector		n;
	t_vector		l;
	t_vector		p_cap;
	t_vector		r;
	t_vector		v;
}					t_lvectors;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Event		event;
}					t_sdl;

typedef struct		s_tclose
{
	float			t;
	float			t_closest;
	t_shape			*closest_shape;
	t_shape			*shape;
}					t_tclose;

typedef struct		s_plight
{
	t_light			*start;
	t_light			*light;
}					t_plight;

typedef struct		s_pshape
{
	t_shape			*start;
	t_shape			*shape;
}					t_pshape;

typedef struct		s_fatoi
{
	int				minus;
	char			c[100];
	int				i;
	float			n;
}					t_fatoi;

typedef struct		s_rtv1
{
	t_sdl			sdl;
	t_shape			*shape;
	t_light			*light;
	t_vector		*cam;
	t_vector		*dir;
	double			angle_x;
	double			angle_y;
	double			angle_z;
}					t_rtv1;

void				define_mega_matrix(double k[4][4], t_vector *c,
					t_rotation *r);

float				scal(t_vector a, t_vector b);

t_shape				*free_shape(t_shape *shp);

t_light				*free_light(t_light *light);

void				incorrect_scene(t_rtv1 rtv1, char **line, char ***elem);

void				usage(void);

void				free_elem_line(char **line, char ***elem);

float				vec_len(t_vector	a);

void				init_rtv1(t_rtv1 *rtv1, char *name);

void				sdl_init(t_rtv1 *rtv1);

void				norm_vec(t_vector *a);

float				solution_of_sphere(t_sphere *sph,
					t_vector *cam, t_vector *p);

float				solution_of_cone(t_cone *cone, t_vector *cam,
					t_vector *p);

float				solution_of_cilin(t_cilin
					*cilin, t_vector *cam, t_vector *p);

float				solution_of_plane(t_plane *plane,
					t_vector *cam, t_vector *p);

t_color				take_color(t_shape *shp);

float				add_light(t_light *light,
					t_shape *shape, t_vector *p, t_rtv1 rtv1);

t_shape				*list_of_shapes(t_rtv1 rtv1, int fd);

void				average_light(t_light *light);

t_vector			*define_dir(t_rtv1 rtv1, int fd);

int					check_one(char **elem);

int					check_p(char **elem);

int					check_d(char **elem);

int					check_valid_letters(char **elem);

int					check_len(char **elem);

int					check_c(char **elem);

int					check_two(char **elem);

int					check_zero(char **elem);

int					check_three(char **elem);

t_vector			*define_camera(t_rtv1 rtv1, int fd);

t_light				*list_of_light(t_rtv1 rtv1, int fd);

void				free_elem(char **elem);

void				free_elem(char **elem);

int					draw(t_rtv1 rtv1);

void				keyboard(t_rtv1 rtv1);

float				light_shape(t_light *light,
					t_shape *shape, t_vector *p, t_rtv1 rtv1);

t_lvectors			vectors_init(t_shape *shape, t_light *light, t_vector *p,
					t_rtv1 rtv1);

t_vector			normal_vector(t_vector p, t_shape *shape);

t_vector			normal_vector_second(t_vector p, t_shape *shape);

double				solution(t_shape *shape1, t_vector p, t_vector l);

t_tclose			init_close(t_rtv1 rtv1);

t_color				set_color(void);

void				ft_light(t_rtv1 rtv1, t_shape *closest_shape,
					t_color *color, t_vector p);

t_vector			p_vector(t_rtv1 rtv1, int x, int y);

t_pshape			ft_psphere(t_pshape shape, char **elem);

t_pshape			ft_pcilin(t_pshape shape, char **elem);

t_pshape			ft_pcone(t_pshape shape, char **elem);

t_pshape			ft_pplane(t_pshape shape, char **elem);

t_shape				*init_plane(char **elem);

t_shape				*init_sphere(char **elem);

t_shape				*init_cone(char **elem);

t_shape				*init_cilin(char **elem);

t_vector			define_vector(int fd);

t_light				*init_dir(int fd);

t_light				*init_amb(int fd);

t_light				*init_point(char **elem);

t_plight			ft_plight(t_plight light, char **elem);

void				rotate(t_rotation r, t_vector *p);

double				rad(float degree);

void				free_all(t_rtv1 rtv1);

float				ft_atoi_for_float(char *str);

float				choose_t(float t1, float t2);

void				rotate_x_axis(float *y, float *z, double angle_x);

void				rotate_y_axis(float *x, float *z, double angle_y);

void				rotate_z_axis(float *x, float *y, float z);

int					check_elem(char ***elem, char *line);

int					is_it_in_cone(t_cone *cone, t_vector *cam);

void				fill_sol_cilin(t_sol *sol, t_vector *cam, t_vector *p,
						t_cilin *cilin);

void				fill_sol_cone(t_sol *sol, t_vector *cam, t_vector *p,
						t_cone *cone);

void				average_light(t_light *light);

#endif
