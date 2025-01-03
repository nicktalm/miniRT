/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/25 16:26:37 by ntalmon          ###   ########.fr       */
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

typedef struct s_garbage
{
	char		**line;
	char		**params;
}			t_garbage;

typedef struct s_data
{
	t_settings		set;
	mlx_t			*window;
	mlx_image_t		*img;
	t_viewport		vp;
	t_vec3			bg;
	float			aspect_ratio;
	int				win_w_max;
	int				win_h_max;
	int				width;
	int				height;
	int				res;
	bool			moved;
	bool			cache_use;
	bool			checker;
	bool			render;
	t_garbage		garbage;
}				t_data;

// main

int		main(int argc, char **argv);
void	get_resolution(t_data *data);
int		create_color(float x, float y, float z, float w);
void	check_interval(int *nbr);

// bump_mapping

void	get_checkerboard_color(float u, float v, t_hitpoint *hit);
t_vec3	get_map_color(float u, float v, xpm_t *map);
t_vec3	get_tangent(t_vec3 normal);
void	get_map_normal(t_hitpoint *hit, t_vec3 *uv, xpm_t *bump_map);

// matrix

void	invert_matrix(float m[4][4], float inv[4][4]);
void	multi_m(float result[4][4], float m1[4][4], float m2[4][4]);
void	calc_base_angles(t_vec3 normal, float *x, float *z);
void	calc_angle(t_vec3 normal, float *x, float *z);
void	calc_t(t_abc *formal);

//transformation_1

void	get_full_r(float result[4][4], float x, float y, float z);

//transformation_2

void	rotate_x(float m[4][4], float angle);
void	rotate_y(float m[4][4], float angle);
void	rotate_z(float m[4][4], float angle);
void	translation(float m[4][4], t_vec3 t);
void	scaling(float m[4][4], float x, float y, float z);

//uv_coords

void	get_uv_coords_sp(t_data *data, xpm_t *map, t_vec3 *uv, t_vec3 tmp);
t_vec3	get_uv_coords_pl(t_data *data, t_plane pl, xpm_t *map, t_vec3 tmp);
t_vec3	get_uv_coords_cy(t_data *data, t_cylinder cy, xpm_t *map, t_vec3 tmp);
t_vec3	get_uv_coords_tb(t_data *data, float radius, xpm_t *map, t_vec3 tmp);
t_vec3	get_uv_coords_cn(t_data *data, t_cone cn, xpm_t *map, t_vec3 tmp);

// vec_calc_1

float	leangth_vec(t_vec3 s1);
t_vec3	norm_vec(t_vec3 s1);
float	dot(t_vec3 s1, t_vec3 s2);
t_vec3	sub_vec(t_vec3 s1, t_vec3 s2);
t_vec3	multi_vec(t_vec3 s1, t_vec3 s2);

// vec_calc_2

t_vec3	multi_vec_wnbr(t_vec3 s1, float nbr);
t_vec3	dev_vec(t_vec3 s1, t_vec3 s2);
t_vec3	dev_vec_wnbr(t_vec3 s1, float nbr);
t_vec3	add_vec(t_vec3 s1, t_vec3 s2);
t_vec3	add_vec_wnbr(t_vec3 s1, float nbr);

// vec_calc_3

t_vec3	ray_vec(t_vec3 origin, float t, t_vec3 dir);
t_vec3	cross_vec(t_vec3 s1, t_vec3 s2);
t_vec4	r_vec(float m[4][4], t_vec4 v);
t_vec3	con_to_vec3(t_vec4 s1);
t_vec4	con_to_vec4(t_vec3 s1, float w);

//check_file

int		count_rows(int fd);
int		read_lines_from_file(int fd, char *argv, t_data *data);
int		process_rt_file(int fd, t_data *data, char *argv);
int		rt_file_check(char *argv);
int		open_file(char *argv, t_data *data);

//helper_2

void	process_line(char *line, char *result);
char	*replace_whitespace(char *line);
char	*clean_line(char *line);
int		check_param_nbr(t_data *data, char **line);

//helper

void	check_param_nbr_2(char **params, int nbr, t_data *data);
void	obj_count(t_data *data, char **line);
void	light_count(t_data *data, char **line);
double	ft_atof(const char *str);
bool	is_valid_float(const char *str);

// init_data

void	init_data(t_data *data, int argc, char **argv);
void	init_mlx(t_data *data);
void	init_viewport(t_data *data);

//parsing_helper

void	ft_count(t_data *data, char **line);
void	parse_coords(t_vec3 *vec, char *line, t_data *data);
void	parse_normalized_vector(t_vec3 *vec, char *param, t_data *data);
void	parse_color(t_vec3 *vec, char *line, t_data *data);
void	parse_surface(t_plane *pl, char *param, t_data *data);

//parsing_helper_2

int		ft_count_params(char **params);
void	parse_textures(t_data *data, char *texture, xpm_t **obj);
void	parse_bump_map(t_data *data, char *bump_map, xpm_t **obj);
int		is_texture(char *param);
int		is_bump_map(char *param);

//parsing_obj

void	parse_common_params(t_data *data, char **params, int *i,
			void (*parse_specific_params)(t_data *, char **, int *));
void	parse_sphere(t_data *data, char *line, int *i);
void	parse_plane(t_data *data, char *line, int *i);
void	parse_cylinder(t_data *data, char *line, int *i);
void	parse_cone(t_data *data, char *line, int *i);

//parsing

void	parse_ambient(t_data *data, char *line);
void	parse_camera(t_data *data, char *line);
void	parse_light(t_data *data, char *line, int *l);
void	check_wrong_line(char *line, t_data *data);
int		parse_line(t_data *data, char *line);

//parsing_obj_helper

void	parse_txt_bump(t_data *data, char *param,
			xpm_t **texture, xpm_t **bump_map);
void	parse_sp_specific(t_data *data, char **params, int *i);
void	parse_pl_specific(t_data *data, char **params, int *i);
void	parse_cy_specific(t_data *data, char **params, int *i);
void	parse_cone_specific(t_data *data, char **params, int *i);

// cone_inter

bool	calc_cn(t_data *data, t_cone cn, t_ray ray, t_hitpoint *hit);
bool	test_side_cn(t_data *data, t_cone cn, t_ray ray, t_hitpoint *hit);
bool	test_bottom_cn(t_data *data, t_cone cn, t_hitpoint *hit, t_ray ray);
void	norm_calc_cn(t_cone cn, t_hitpoint *hit);

// cone_utils

void	create_m_cn(t_cone *cn);
void	get_color_and_normal_cn(t_data *data,
			t_cone cn, t_hitpoint *hit, t_vec3 tmp);
void	get_color_and_normal_tb_cn(t_data *data,
			t_cone cn, t_hitpoint *hit, t_vec3 tmp);

// cylinder_inter

bool	calc_cy(t_data *data, t_cylinder cy, t_ray ray, t_hitpoint *hit);
t_abc	calc_quadratic_formal_cy(t_ray ray, t_cylinder cy);
bool	test_side_cy(t_data *data, t_cylinder cy, t_ray ray, t_hitpoint *hit);
bool	test_top_bottom_cy(t_data *data,
			t_cylinder cy, t_hitpoint *hit, t_ray ray);
void	norm_calc_cy(t_cylinder cy, t_hitpoint *hit);

// cylinder_utils

void	create_m_cy(t_cylinder *cy);
void	get_color_and_normal_cy(t_data *data,
			t_cylinder cy, t_hitpoint *hit, int i);
xpm_t	*find_map(t_cylinder cy);

// plane

bool	calc_pl(t_data *data, t_plane pl, t_ray ray, t_hitpoint *hit);
bool	test_inf_pl(t_plane pl, t_ray ray, t_hitpoint *hit);
bool	test_bounded_pl(t_data *data, t_plane pl, t_ray ray, t_hitpoint *hit);
void	create_m_pl(t_plane *pl);
void	get_color_and_normal_pl(t_data *data, t_plane pl,
			t_hitpoint *hit, t_vec3 tmp);

// sphere

bool	calc_sp(t_data *data, t_sphere sp, t_ray ray, t_hitpoint *hit);
void	create_m_sp(t_sphere *sp);
void	get_color_and_normal_sp(t_data *data, t_sphere sp,
			t_hitpoint *hit, t_vec3 tmp);

// check_hit

void	check_hit(t_ray *ray, t_hitpoint *hit, t_data *data);
void	check_obj(t_data *data, t_hitpoint *hit, t_ray *ray, int i);

//error

void	free_double_p(char **double_p);
void	free_all(t_data *data);
void	delete_bump_texture(t_data *data);
void	error_2(char *message, char *param, t_data *data);
void	error(char *message, t_data *data);

// error_2

void	check_bump_texture(xpm_t *bump_map, xpm_t *texture);

// hooks

void	hook(void *param);
void	resize(int width, int height, void *param);

// key_actions

void	key(mlx_key_data_t keydata, void *param);
bool	wasd(mlx_key_data_t key, t_data *data);
bool	lrud(mlx_key_data_t key, t_data *data, t_vec3 t);
bool	cr(mlx_key_data_t key, t_data *data, int i);

// img_creation

void	create_img(t_data *data);
void	pixel_loop(t_data *data, t_vec3 coords, int resolution);
void	in_out_object(t_ray *ray, t_hitpoint *hit);
void	trace_ray(float x, float y, t_hitpoint *hit, t_data *data);

// sampling

void	super_sampling(t_data *data, int x, int y);
void	render_animation(int *dot);
void	render_message(t_data *data, int x, int y);
void	down_sampling(t_data *data, int x, int y);

// shading_2

void	get_color(t_data *data, t_ray *ray, t_hitpoint *hit);
bool	get_distanz(t_hitpoint *hit, t_light light, int i);
bool	light_loop(t_data *data, t_ray *ray, t_hitpoint *hit, t_vec3 index);

// shading

void	obj_shading(t_data *data, t_hitpoint *hit, t_ray *ray, t_light light);
void	shading(t_data *data, t_hitpoint *hit, t_light light);
void	diffuse_light(t_lighting *intensity, t_light light, t_hitpoint *hit);
void	specular_light(t_lighting *in,
			t_light light, t_camera cam, t_hitpoint *hit);
t_vec3	reflect_light(t_vec3 light_dir, t_vec3 normal);

#endif