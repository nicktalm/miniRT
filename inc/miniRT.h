/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/10/08 15:16:07 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/mlx/include/MLX42/MLX42.h"

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_vec4
{
	float	w;
	float	x;
	float	y;
	float	z;
}				t_vec4;

typedef struct s_cylinder
{
	t_vec3				coords;
	t_vec3				norm;
	float				diameter;
	float				radius;
	float				height;
	t_vec3				color;
	float				material;
}				t_cylinder;

typedef struct s_plane
{
	t_vec3			coords;
	t_vec3			norm;
	t_vec3			color;
	float			material;
	float			length;
	float			width;
}				t_plane;

typedef struct s_sphere
{
	t_vec3			coords;
	float			diameter;
	float			radius;
	t_vec3			color;
	float			material;
}				t_sphere;

typedef union s_obj
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}				t_obj;

typedef enum s_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}			t_type;

typedef struct s_objects
{
	t_obj	form;
	t_type	type;
}				t_objects;

typedef struct s_light
{
	t_vec3	coords;
	float	brightness;
	t_vec3	color;
	t_vec3	norm;
}				t_light;

typedef struct s_lighting
{
	t_vec3	light;
	t_vec3	light_dir;
	t_vec3	diffuse;
	float	diffuse_strength;
}				t_lighting;

typedef struct s_camera
{
	t_vec3	coords;
	t_vec3	direction;
	float	fov;
}				t_camera;

typedef struct s_ambient
{
	float	ratio;
	t_vec3	color;
}				t_ambient;

typedef struct s_settings
{
	t_ambient	ambient;
	t_camera	cam;
	t_light		*light;
	int			obj_count;
	int			light_count;
	t_objects	*obj;
}				t_settings;

typedef struct s_viewport
{
	t_vec3	size;
	t_vec3	u;
	t_vec3	v;
	t_vec3	du;
	t_vec3	dv;
	t_vec3	upper_left;
	t_vec3	p00;
}				t_viewport;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

typedef struct s_hitpoint
{
	t_vec3		p;
	t_vec3		normal;
	t_vec3		color;
	float		t;
	int			i;
}				t_hitpoint;

typedef struct s_data
{
	bool		name;
	t_settings	set;
	mlx_t		*window;
	mlx_image_t	*img;
	t_viewport	vp;
	t_vec3		bg;
	pthread_mutex_t	random;
	pthread_mutex_t	count;
	struct s_range	*range;
	float		aspect_ratio;
	int			width;
	int			height;
	int			i;
	int			x_max;
	int			y_max;
	bool		moved;
}				t_data;

typedef struct s_range
{
	pthread_t	p;
	t_hitpoint	*hit;
	int			th_nbr;
	int			x_max;
	int			x_min;
	int			y_max;
	int			y_min;
	t_data		data;
}				t_range;

// main

int		main(int argc, char **argv);

//check_file

int		read_lines_from_file(int fd, char ***line, char *argv);
int		process_rt_file(int fd, t_data *data, char *argv);
int		rt_file_check(char *argv);
int		open_file(char *argv, t_data *data);

//parsing

void	parse_ambient(t_data *data, char **line);
void	parse_camera(t_data *data, char **line);
void	parse_light(t_data *data, char **line, int *l);
void	check_wrong_line(char *line, t_data *data);
int		parse_line(t_data *data, char **line);

//parsing_obj

void	parse_sphere(t_data *data, char **line, int *i);
void	parse_plane(t_data *data, char **line, int *i);
void	parse_cylinder(t_data *data, char **line, int *i);

//parsing_helper

void	ft_count(t_data *data, char **line);
void	parse_coords(t_vec3 *vec, char *line, t_data *data);
void	parse_normalized_vector(t_vec3 *vec, char *line, t_data *data);
void	parse_color(t_vec3 *vec, char *line, t_data *data);
void	parse_surface(t_plane *pl, char *param, t_data *data);

//error

void	free_double_p(char **double_p);
void	free_all(t_data *data);
void	error(char *message, t_data *data);
void	error_2(char *message, char *param, t_data *data);

//helper

void	check_param_nbr_2(char **params, int nbr, t_data *data);
void	obj_count(t_data *data, char **line);
void	light_count(t_data *data, char **line);
double	ft_atof(const char *str);
bool	is_valid_float(const char *str);

//helper_2

void	process_line(char *line, char *result);
char	*replace_whitespace(char *line);
char	*clean_line(char *line);
int		check_param_nbr(t_data *data, char **line);

// key_actions

void	hook(void *param);
void	resize(int width, int height, void *param);
void	key(mlx_key_data_t keydata, void *param);

// vec_calc

t_vec3	norm_vec(t_vec3 s1);
float	dot(t_vec3 s1, t_vec3 s2);
t_vec3	sub_vec(t_vec3 s1, t_vec3 s2);
t_vec3	multi_vec(t_vec3 s1, t_vec3 s2);
t_vec3	multi_vec_wnbr(t_vec3 s1, float nbr);
t_vec3	dev_vec(t_vec3 s1, t_vec3 s2);
t_vec3	dev_vec_wnbr(t_vec3 s1, float nbr);
t_vec3	add_vec(t_vec3 s1, t_vec3 s2);
t_vec3	add_vec_wnbr(t_vec3 s1, float nbr);
t_vec3	ray_vec(t_vec3 origin, float t, t_vec3 dir);
t_vec3	cross_vec(t_vec3 s1, t_vec3 s2);
t_vec3	reflect_vec3(t_vec3 s1, t_vec3 s2);
int		cmp_vec(t_vec3 s1, t_vec3 s2);

// init_data

void	init_data(t_data *data, int argc, char **argv);
void	init_mlx(t_data *data);
void	init_viewport(t_data *data);
void	init_data_b(t_data *data);

// img_creation

void	create_img(t_data *data);
int		create_color(float x, float y, float z, int a);
void	in_out_object(t_ray ray, t_hitpoint *hit);
bool	trace_ray(float x, float y, t_hitpoint *hit, t_data *data);
void	get_obj_color(t_data *data, t_ray ray, t_hitpoint *hit);
void	lighting(t_data *data, t_ray ray, t_hitpoint *hit);
void	lighting_b(t_data *data, t_ray ray, t_hitpoint *hit);
float	rando(t_data *data);

// multi_threading

void	calc_pixels(t_data *data);
void	creat_img_multi(t_data *data);
void	fill_range(t_range *range, t_vec3 *min, int i, t_data *data);
void	*loop_thread(void *param);

// check_hit

void	check_hit(t_ray ray, t_hitpoint *hit, t_data *data);
void	check_reflect(t_ray ray, t_hitpoint *hit, t_data *data);
void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i);
void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i);
void	calc_cy(t_cylinder pl, t_ray ray, t_hitpoint *hit, int i);

#endif