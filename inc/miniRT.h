/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/03 10:36:55 by lbohm            ###   ########.fr       */
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

typedef struct s_data
{
	t_settings	set;
	mlx_t		*window;
	mlx_image_t	*img;
	float		aspect_ratio;
	t_vec		t1;
	int			width;
	int			hight;
	int			dpi;
	t_vec		*caches;
	bool		moved;
	int			pos;
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
void	parse_coords(t_vec *vec, char *line, t_data *data);
void	parse_normalized_vector(t_vec *vec, char *line, t_data *data);
void	parse_color(t_vec *vec, char *line, t_data *data);

//error

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
int		check_param_nbr(char **line);


// key_actions

void	hook(void *param);
void	resize(int width, int hight, void *param);
void	key(mlx_key_data_t keydata, void *param);
void	cursor(double xpos, double ypos, void *param);

// vec_calc

t_vec	norm_vec(t_vec s1);
float	dot(t_vec s1, t_vec s2);

// image_creation

void	create_img(t_data *data);
int		get_color(int r, int g, int b, int a);
bool	hit_sphere(t_data *data, t_vec test, t_sphere *sp);

// init_data

void	init_data(t_data *data, int argc, char **argv);
void	init_mlx(t_data *data);

#endif