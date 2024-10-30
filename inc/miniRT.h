/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/10/30 09:15:29 by lucabohn         ###   ########.fr       */
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
# include "shapes.h"
# include "transformation.h"
# include "camera.h"
# include "lighting.h"

typedef struct s_settings
{
	t_ambient	ambient;
	t_camera	cam;
	t_light		*light;
	int			obj_count;
	int			light_count;
	t_objects	*obj;
}				t_settings;

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
	t_vec3		*cache;
	float		aspect_ratio;
	int			width;
	int			height;
	bool		moved;
}				t_data;

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

//helper_2

void	process_line(char *line, char *result);
char	*replace_whitespace(char *line);
char	*clean_line(char *line);
int		check_param_nbr(t_data *data, char **line);

// key_actions

void	hook(void *param);
void	resize(int width, int height, void *param);
void	key(mlx_key_data_t keydata, void *param);

// init_data

void	init_data(t_data *data, int argc, char **argv);
void	init_mlx(t_data *data);
void	init_viewport(t_data *data);
// void	init_data_b(t_data *data);

// img_creation

void	create_img(t_data *data);
int		create_color(float x, float y, float z, float w);
void	in_out_object(t_ray *ray, t_hitpoint *hit);
void	trace_ray(float x, float y, t_hitpoint *hit, t_data *data);
// void	get_obj_color(t_data *data, t_ray ray, t_hitpoint *hit);
// void	lighting(t_data *data, t_ray ray, t_hitpoint *hit);
// void	lighting_b(t_data *data, t_ray ray, t_hitpoint *hit);
// float	rando(t_data *data);

// multi_threading

// void	calc_pixels(t_data *data);
// void	creat_img_multi(t_data *data);
// void	fill_range(t_range *range, t_vec3 *min, int i, t_data *data);
// void	*loop_thread(void *param);

// check_hit

void	check_hit(t_ray *ray, t_hitpoint *hit, t_data *data);
// void	check_reflect(t_ray ray, t_hitpoint *hit, t_data *data);
t_vec4	ray_vec4(t_vec4 origin, float t, t_vec4 direction);

// shading

void	shading(t_data *data, t_hitpoint *hit, t_vec3 color, t_ray *ray);
t_vec3	calc_light_intensity(t_light light, t_hitpoint *hit, t_lighting *nlight);
void	get_color(t_data *data, t_ray *ray, t_hitpoint *hit);

#endif