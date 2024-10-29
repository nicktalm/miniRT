/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:55:58 by lucabohn          #+#    #+#             */
/*   Updated: 2024/10/29 22:02:59 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H

# include "shapes.h"

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vec4;

typedef struct s_matrix
{
	float	m[4][4];
}				t_matrix;

// matrix

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
void	scaling(float m[4][4], float x, float y, float z);

// vec_calc

float	leangth_vec(t_vec3 s1, t_vec3 s2);
t_vec3	norm_vec(t_vec3 s1);
t_vec4	norm_vec4(t_vec4 s1);
float	dot(t_vec3 s1, t_vec3 s2);
float	dot4(t_vec4 s1, t_vec4 s2);
t_vec3	sub_vec(t_vec3 s1, t_vec3 s2);
t_vec4	sub_vec4(t_vec4 s1, t_vec4 s2);
t_vec3	multi_vec(t_vec3 s1, t_vec3 s2);
t_vec3	multi_vec_wnbr(t_vec3 s1, float nbr);
t_vec4	multi_vec4_wnbr(t_vec4 s1, float nbr);
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