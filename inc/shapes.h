/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:29:16 by lucabohn          #+#    #+#             */
/*   Updated: 2024/11/04 19:47:31 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "minimath.h"

typedef struct s_cone
{
	t_vec3	coords;
	t_vec3	norm;
	t_vec3	color;
	float	diameter;
	float	radius;
	float	height;
	float	angle;
	float	material;
	float	mt[4][4];
	float	mti[4][4];
}				t_cone;

typedef struct s_cylinder
{
	t_vec3				coords;
	t_vec3				norm;
	t_vec3				color;
	float				diameter;
	float				radius;
	float				height;
	float				material;
	float				mt[4][4];
	float				mti[4][4];
}				t_cylinder;

typedef struct s_plane
{
	t_vec3			coords;
	t_vec3			norm;
	t_vec3			color;
	float			material;
	float			length;
	float			width;
	float			mt[4][4];
	float			mti[4][4];
}				t_plane;

typedef struct s_sphere
{
	t_vec3			coords;
	t_vec3			color;
	float			diameter;
	float			radius;
	float			material;
	float			mt[4][4];
	float			mti[4][4];
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