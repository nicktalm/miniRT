/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/07 17:26:32 by lbohm            ###   ########.fr       */
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
# include "minimath.h"
# include "camera.h"
# include "lighting.h"
# include "shapes.h"
# include "ray.h"

typedef struct s_settings
{
	t_ambient	ambient;
	t_camera	cam;
	t_light		*light;
	t_objects	*obj;
	int			obj_count;
	int			light_count;
}				t_settings;

typedef struct s_data
{
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
	bool		name;
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
void	check_interval(int *nbr);
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
bool	get_distanz(t_data *data, t_hitpoint *hit, int i);

// cone

void	calc_cn(t_cone cn, t_ray ray, t_hitpoint *hit, int i);
void	cn_norm_calc(t_cone cn, t_hitpoint *hit);
void	cn_bottom(t_cone cn, t_ray ray, t_hitpoint *hit, int i);
void	create_m_cn(t_cone *cn);
void	calc_angle_cn(t_cone *cn, float *x, float *z);

// cylinder

void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i);
void	top_bottom(t_cylinder cy, t_hitpoint *hit, t_ray ray, int i, float m[4][4]);
void	cy_norm_calc(t_cylinder cy, t_hitpoint *hit);
void	create_m_cy(t_cylinder *cy);
void	calc_angle_cy(t_cylinder *cy, float *x, float *z);

// plane

void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i);
void	create_m_pl(t_plane *pl);
void	calc_angle_pl(t_plane *pl, float *x, float *z);

// sphere

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i);
void	create_m_sp(t_sphere *sp);

// matrix

void	invert_matrix(float m[4][4], float inv[4][4]);
void	create_m_inverse(float m[4][4], float inverse[4][4]);
void	identity_m(float m[4][4]);
void	copy_m(float result[4][4], float m[4][4]);
void	multi_m(float result[4][4], float m1[4][4], float m2[4][4]);
void	print_m(float m[4][4]);

// transformation

void	get_full_r(float result[4][4], float x, float y, float z);
t_ray	transform_ray(t_ray *ray, t_objects obj);
void	rotate_x(float m[4][4], float angle);
void	rotate_y(float m[4][4], float angle);
void	rotate_z(float m[4][4], float angle);
void	translation(float m[4][4], t_vec3 t);
void	add_translation(float m[4][4], t_vec3 t);
void	scaling(float m[4][4], float x, float y, float z);

// vec_calc

float	leangth_vec(t_vec3 s1);
t_vec4	norm_vec4(t_vec4 s1);
t_vec4	sub_vec4(t_vec4 s1, t_vec4 s2);
t_vec4	multi_vec4_wnbr(t_vec4 s1, float nbr);
t_vec3	norm_vec(t_vec3 s1);
float	dot(t_vec3 s1, t_vec3 s2);
float	dot4(t_vec4 s1, t_vec4 s2);
t_vec3	sub_vec(t_vec3 s1, t_vec3 s2);
t_vec3	multi_vec(t_vec3 s1, t_vec3 s2);
t_vec3	multi_vec_wnbr(t_vec3 s1, float nbr);
t_vec3	dev_vec(t_vec3 s1, t_vec3 s2);
t_vec3	dev_vec_wnbr(t_vec3 s1, float nbr);
t_vec4	dev_vec4_wnbr(t_vec4 s1, float nbr);
t_vec3	add_vec(t_vec3 s1, t_vec3 s2);
t_vec4	add_vec4(t_vec4 s1, t_vec4 s2);
t_vec3	add_vec_wnbr(t_vec3 s1, float nbr);
t_vec3	ray_vec(t_vec3 origin, float t, t_vec3 dir);
t_vec3	cross_vec(t_vec3 s1, t_vec3 s2);
t_vec3	reflect_vec3(t_vec3 s1, t_vec3 s2);
int		cmp_vec(t_vec3 s1, t_vec3 s2);
t_vec3	copy_vec(t_vec3 s1);
t_vec4	r_vec(float m[4][4], t_vec4 v);
t_vec3	convert_to_vec3(t_vec4 s1);
t_vec4	convert_to_vec4(t_vec3 s1, float w);

#endif