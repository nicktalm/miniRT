/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/02 21:46:56 by lucabohn         ###   ########.fr       */
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

int		main(void);
void	init_data(t_data *data);
void	init_mlx(t_data *data);
void	create_img(t_data *data);
int		get_color(int r, int g, int b, int a);
bool	hit_sphere(t_data *data, t_vec test, t_sphere *sp);
t_vec	norm_vec(t_vec s1);
float	dot(t_vec s1, t_vec s2);
void	resize(int width, int hight, void *param);
void	hook(void *param);
void	key(mlx_key_data_t keydata, void *param);
void	cursor(double xpos, double ypos, void *param);
void	changed_img(t_data *data);

#endif