/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:29:16 by lucabohn          #+#    #+#             */
/*   Updated: 2024/10/30 08:00:42 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "miniRT.h"
# include "transformation.h"

typedef struct s_cylinder
{
	t_vec3				coords;
	t_vec3				norm;
	float				diameter;
	float				radius;
	float				height;
	t_vec3				color;
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
	float			diameter;
	float			radius;
	t_vec3			color;
	float			material;
	float			mt[4][4];
	float			mti[4][4];
}				t_sphere;

typedef union u_obj
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}				t_obj;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}			t_type;

typedef struct s_objects
{
	t_obj	form;
	t_type	type;
}				t_objects;

// cylinder

void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i);
void	top_bottom(t_cylinder cy, t_hitpoint *hit, t_ray ray, int i);
void	cy_norm_calc(t_cylinder cy, t_hitpoint *hit, t_vec3 hitp);
void	create_m_cy(t_data *data, t_cylinder *cy);
void	calc_angle_cy(t_cylinder *cy, float *x, float *z);

// plane

void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i);
void	create_m_pl(t_plane *pl);
void	calc_angle_pl(t_plane *pl, float *x, float *z);

// sphere

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i);
void	create_m_sp(t_sphere *sp);

#endif