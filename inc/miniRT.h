/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/10 17:04:19 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/mlx/include/MLX42/MLX42.h"

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}				t_vec;

typedef struct s_cylinder
{
	t_vec				coords;
	t_vec				normalized;
	float				diameter;
	float				height;
	t_vec				color;
}				t_cylinder;

typedef struct s_plane
{
	t_vec			coords;
	t_vec			normalized;
	t_vec			color;
}				t_plane;

typedef struct s_sphere
{
	t_vec			coords;
	float			diameter;
	float			radius;
	t_vec			color;
}				t_sphere;

typedef struct s_light
{
	t_vec	coords;
	float	brightness;
	t_vec	color;
	t_vec	normalized;
}				t_light;

typedef struct s_camera
{
	t_vec	coords;
	t_vec	normalized;
	float	fov;
}				t_camera;

typedef struct s_ambient
{
	float	ratio;
	t_vec	color;
}				t_ambient;

typedef struct s_settings
{
	t_ambient	ambient;
	t_camera	cam;
	t_light		light;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	int			sp_count;
	int			pl_count;
	int			cy_count;
}				t_settings;

typedef struct s_viewport
{
	t_vec	size;
	t_vec	u;
	t_vec	v;
	t_vec	du;
	t_vec	dv;
	t_vec	upper_left;
	t_vec	p00;
}				t_viewport;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}				t_ray;

typedef struct s_hitpoint
{
	t_vec	p;
	t_vec	normal;
	t_vec	color;
	float	t;
	int		sp_i;
}				t_hitpoint;

typedef struct s_data
{
	t_settings	set;
	mlx_t		*window;
	mlx_image_t	*img;
	t_viewport	vp;
	t_ray		now_ray;
	float		aspect_ratio;
	int			width;
	int			hight;
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
void	parse_light(t_data *data, char **line);
void	check_wrong_line(char *line, t_data *data);
int		parse_line(t_data *data, char **line);

//parsing_obj

void	parse_sphere(t_data *data, char **line);
void	parse_plane(t_data *data, char **line);
void	parse_cylinder(t_data *data, char **line);

//parsing_helper

void	ft_count(t_data *data, char **line);
void	free_values(char **values);
void	parse_coords(t_vec *vec, char *line, t_data *data);
void	parse_normalized_vector(t_vec *vec, char *line, t_data *data);
void	parse_color(t_vec *vec, char *line, t_data *data);

//error

void	free_params(char **params, int count);
void	free_all(t_data *data);
void	error(char *message, t_data *data);
void	error_2(char *message, char *param, t_data *data);

//helper

void	check_param_nbr_2(char **params, int nbr, t_data *data);
void	sphere_count(t_data *data, char **line);
void	plane_count(t_data *data, char **line);
void	cylinder_count(t_data *data, char **line);
double	ft_atof(const char *str);

//helper_2

void	process_line(char *line, char *result);
char	*replace_whitespace(char *line);
char	*clean_line(char *line);
int		check_param_nbr(t_data *data, char **line);


// key_actions

void	hook(void *param);
void	resize(int width, int hight, void *param);
void	key(mlx_key_data_t keydata, void *param);
void	cursor(double xpos, double ypos, void *param);

// vec_calc

t_vec	norm_vec(t_vec s1);
float	dot(t_vec s1, t_vec s2);
t_vec	sub_vec(t_vec s1, t_vec s2);
t_vec	multi_vec(t_vec s1, t_vec s2);
t_vec	multi_vec_wnbr(t_vec s1, float nbr);
t_vec	dev_vec(t_vec s1, t_vec s2);
t_vec	dev_vec_wnbr(t_vec s1, float nbr);
t_vec	add_vec(t_vec s1, t_vec s2);
t_vec	add_vec_wnbr(t_vec s1, float nbr);
t_vec	ray_vec(t_vec origin, float t, t_vec dir);

// image_creation

void	create_img(t_data *data);
int		get_color(int r, int g, int b, int a);
bool	hit_sphere(t_data *data, t_vec test, t_sphere *sp);
void	pixel_to_wspace(t_vec s1, t_data *data);

// init_data

void	init_data(t_data *data, int argc, char **argv);
void	init_mlx(t_data *data);

// img_creation_test

void	create_img(t_data *data);
int		create_color(float x, float y, float z, int a);
bool	hit_sphere_test(t_ray ray, t_hitpoint *hit, t_data *data);
void	in_out_object(t_ray ray, t_hitpoint *hit);
bool	trace_ray(float x, float y, t_data *data, t_hitpoint *hit);
void	init_viewport(t_data *data);
void	super_sampling(t_data *data, t_hitpoint *hit, int x, int y);

#endif