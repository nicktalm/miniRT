/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/28 16:38:12 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
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
	t_vec			color;
}				t_sphere;

typedef struct s_light
{
	t_vec	coords;
	float	brightness;
	t_vec	color;
}				t_light;

typedef struct s_camera
{
	t_vec	coords;
	t_vec	normalized;
	float	fov;
}				t_camera;

typedef struct s_ambient
{
	float	range;
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
}				t_settings;

typedef struct s_data
{
	t_settings	set;
	mlx_t		*window;
	mlx_image_t	*img;
	t_vec		color;
	float		aspect_ratio;
	int			vpw;
	int			vph;
}				t_data;

// main

int		main(void);
void	init_data(t_data *data);
void	init_mlx(t_data *data);
void	test(t_data *data);
t_vec	grade_color(t_vec color, float grade);
int		get_color(int r, int g, int b, int a);
float	view_point_x(int value, t_data *data);
float	view_point_y(int value, t_data *data);
float	hit_sphere(float x, float y, t_sphere *sp);
t_vec	sub_vec(t_vec s1, t_vec s2);
float	multi_vec(t_vec s1, t_vec s2);
t_vec	norm_vec(t_vec s1);
void	calc_vpw(t_data *data);

#endif