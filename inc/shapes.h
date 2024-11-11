/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:29:16 by lucabohn          #+#    #+#             */
/*   Updated: 2024/11/11 12:56:42 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "minimath.h"

typedef struct s_cone
{
	t_vec3		coords;
	t_vec3		norm;
	t_vec3		color;
	float		diameter;
	float		radius;
	float		height;
	float		angle;
	float		tangle;
	t_matrix	side;
	t_matrix	bottom;
}				t_cone;

typedef struct s_cylinder
{
	t_vec3		coords;
	t_vec3		norm;
	t_vec3		color;
	t_matrix	side;
	t_matrix	top;
	t_matrix	bottom;
	float		diameter;
	float		radius;
	float		height;
}				t_cylinder;

typedef struct s_plane
{
	t_vec3		coords;
	t_vec3		norm;
	t_vec3		color;
	t_matrix	side;
	float		length;
	float		width;
}				t_plane;

typedef struct s_sphere
{
	t_vec3		coords;
	t_vec3		color;
	t_matrix	side;
	float		diameter;
	float		radius;
}				t_sphere;

typedef union u_obj
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
	t_cone		cn;
}				t_obj;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
}			t_type;

typedef struct s_objects
{
	t_obj	form;
	t_type	type;
}				t_objects;

#endif