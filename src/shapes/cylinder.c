/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/07 21:23:00 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i)
{
	t_ray	test;

	test.origin = convert_to_vec3(r_vec(cy.top.m, convert_to_vec4(ray.origin, 1)));
	test.direction = convert_to_vec3(r_vec(cy.top.m, convert_to_vec4(ray.direction, 0)));
	if (test_top_bottom_cy(cy, hit, test, cy.top.mi))
		hit->i = i;
	test.origin = convert_to_vec3(r_vec(cy.bottom.m, convert_to_vec4(ray.origin, 1)));
	test.direction = convert_to_vec3(r_vec(cy.bottom.m, convert_to_vec4(ray.direction, 0)));
	if (test_top_bottom_cy(cy, hit, test, cy.bottom.mi))
		hit->i = i;
	test.origin = convert_to_vec3(r_vec(cy.side.m, convert_to_vec4(ray.origin, 1)));
	test.direction = convert_to_vec3(r_vec(cy.side.m, convert_to_vec4(ray.direction, 0)));
	if (test_side_cy(cy, test, hit))
		hit->i = i;
}

bool	test_side_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit)
{
	t_abc	formal;
	t_vec3	tmp;

	formal.a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	formal.b = ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z;
	formal.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - cy.radius * cy.radius;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	if (formal.dis > 0.0)
	{
		calc_t(&formal);
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			if (fabsf(tmp.y) <= cy.height / 2.0)
			{
				hit->p = convert_to_vec3(r_vec(cy.side.mi, convert_to_vec4(tmp, 1)));
				norm_calc_cy(cy, hit);
				hit->t = formal.t;
				return (true);
			}
		}
	}
	return (false);
}

bool	test_top_bottom_cy(t_cylinder cy, t_hitpoint *hit, t_ray ray, float m[4][4])
{
	float	dis;
	float	t;
	t_vec3	tmp;
	t_vec3	test;

	test.x = 0.0;
	test.y = 1.0;
	test.z = 0.0;
	t = -dot(test, ray.origin) / dot(test, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		tmp = ray_vec(ray.origin, t, ray.direction);
		dis = pow(tmp.x, 2.0) + pow(tmp.z, 2.0);
		if (dis <= cy.radius * cy.radius)
		{
			hit->p = convert_to_vec3(r_vec(m, convert_to_vec4(tmp, 1)));
			hit->normal = cy.norm;
			hit->t = t;
			return (true);
		}
	}
	return (false);
}

void	norm_calc_cy(t_cylinder cy, t_hitpoint *hit)
{
	t_vec3	center;
	t_vec3	oc;

	oc = sub_vec(hit->p, cy.coords);
	center = add_vec(cy.coords, multi_vec_wnbr(cy.norm,
				dot(oc, cy.norm) / dot(cy.norm, cy.norm)));
	hit->normal = norm_vec(sub_vec(hit->p, center));
}

void	create_m_cy(t_cylinder *cy)
{
	float	angle_x;
	float	angle_z;
	float	t[4][4];
	float	full_r[4][4];

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle(cy->norm, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	cy->norm = norm_vec(cy->norm);
	translation(t, multi_vec_wnbr(cy->coords, -1.0));
	multi_m(cy->side.m, full_r, t);
	invert_matrix(cy->side.m, cy->side.mi);
	translation(t, multi_vec_wnbr(
			ray_vec(cy->coords, cy->height / 2.0, cy->norm), -1.0));
	multi_m(cy->top.m, full_r, t);
	invert_matrix(cy->top.m, cy->top.mi);
	translation(t, multi_vec_wnbr(
			ray_vec(cy->coords, cy->height / -2.0, cy->norm), -1.0));
	multi_m(cy->bottom.m, full_r, t);
	invert_matrix(cy->bottom.m, cy->bottom.mi);
}
