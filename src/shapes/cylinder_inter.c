/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:52:00 by lucabohn          #+#    #+#             */
/*   Updated: 2024/11/21 21:45:16 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	calc_cy(t_data *data, t_cylinder cy, t_ray ray, t_hitpoint *hit)
{
	t_ray	tmp;
	int		r_value;

	r_value = 0;
	tmp.origin = con_to_vec3(r_vec(cy.top.m, con_to_vec4(ray.origin, 1)));
	tmp.direction = con_to_vec3(r_vec(cy.top.m, con_to_vec4(ray.direction, 0)));
	if (test_top_bottom_cy(data, cy, hit, tmp))
	{
		hit->p = con_to_vec3(r_vec(cy.top.mi, con_to_vec4(hit->p, 1)));
		r_value = 1;
	}
	tmp.origin = con_to_vec3(r_vec(cy.bottom.m, con_to_vec4(ray.origin, 1)));
	tmp.direction = con_to_vec3(
			r_vec(cy.bottom.m, con_to_vec4(ray.direction, 0)));
	if (test_top_bottom_cy(data, cy, hit, tmp))
	{
		hit->p = con_to_vec3(r_vec(cy.bottom.mi, con_to_vec4(hit->p, 1)));
		r_value = 1;
	}
	tmp.origin = con_to_vec3(r_vec(cy.side.m, con_to_vec4(ray.origin, 1)));
	tmp.direction = con_to_vec3(
			r_vec(cy.side.m, con_to_vec4(ray.direction, 0)));
	if (test_side_cy(data, cy, tmp, hit))
		r_value = 1;
	return (r_value);
}

t_abc	calc_quadratic_formal_cy(t_ray ray, t_cylinder cy)
{
	t_abc	formal;

	formal.a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	formal.b = ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z;
	formal.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2)
		- cy.radius * cy.radius;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	return (formal);
}

bool	test_side_cy(t_data *data, t_cylinder cy, t_ray ray, t_hitpoint *hit)
{
	t_abc	formal;
	t_vec3	tmp;

	formal = calc_quadratic_formal_cy(ray, cy);
	if (formal.dis > 0.0)
	{
		calc_t(&formal);
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			if (fabsf(tmp.y) <= cy.height / 2.0)
			{
				hit->p = tmp;
				norm_calc_cy(cy, hit);
				hit->t = formal.t;
				get_color_and_normal_cy(data, cy, hit, 0);
				hit->p = con_to_vec3(r_vec(cy.side.mi, con_to_vec4(tmp, 1)));
				return (true);
			}
		}
	}
	return (false);
}

bool	test_top_bottom_cy(t_data *data,
	t_cylinder cy, t_hitpoint *hit, t_ray ray)
{
	float	dis;
	float	t;
	t_vec3	tmp;
	t_vec3	dir;

	dir.x = 0.0;
	dir.y = 1.0;
	dir.z = 0.0;
	t = -dot(dir, ray.origin) / dot(dir, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		tmp = ray_vec(ray.origin, t, ray.direction);
		dis = pow(tmp.x, 2.0) + pow(tmp.z, 2.0);
		if (dis <= cy.radius * cy.radius)
		{
			hit->p = tmp;
			hit->normal = cy.norm;
			hit->t = t;
			get_color_and_normal_cy(data, cy, hit, 1);
			return (true);
		}
	}
	return (false);
}

void	norm_calc_cy(t_cylinder cy, t_hitpoint *hit)
{
	t_vec3	center;
	t_vec3	oc;
	t_vec3	tmp;

	tmp = con_to_vec3(r_vec(cy.side.mi, con_to_vec4(hit->p, 1)));
	oc = sub_vec(tmp, cy.coords);
	center = add_vec(cy.coords, multi_vec_wnbr(cy.norm,
				dot(oc, cy.norm) / dot(cy.norm, cy.norm)));
	hit->normal = norm_vec(sub_vec(tmp, center));
}
