/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:40:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/26 16:29:32 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>

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
	int		fov;
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
}				t_data;


// main

int	main(void);

#endif