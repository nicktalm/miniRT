/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:41:35 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/25 11:17:29 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	calc_cn(t_data *data, t_cone cn, t_ray ray, t_hitpoint *hit)
{
	t_ray	tmp;
	int		r_value;

	r_value = 0;
	tmp.origin = con_to_vec3(
			r_vec(cn.bottom.m, con_to_vec4(ray.origin, 1)));
	tmp.direction = con_to_vec3(
			r_vec(cn.bottom.m, con_to_vec4(ray.direction, 0)));
	if (test_bottom_cn(data, cn, hit, tmp))
		r_value = 1;
	tmp.origin = con_to_vec3(
			r_vec(cn.side.m, con_to_vec4(ray.origin, 1)));
	tmp.direction = con_to_vec3(
			r_vec(cn.side.m, con_to_vec4(ray.direction, 0)));
	if (test_side_cn(data, cn, tmp, hit))
		r_value = 1;
	return (r_value);
}

t_abc	calc_quadratic_formal(t_ray ray, t_cone cn)
{
	t_abc	formal;

	formal.a = pow(ray.direction.x, 2.0) + pow(ray.direction.z, 2.0)
		- pow(ray.direction.y, 2.0) * cn.angle;
	formal.b = ray.origin.x * ray.direction.x + ray.origin.z
		* ray.direction.z - ray.origin.y * ray.direction.y * cn.angle;
	formal.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2)
		- pow(ray.origin.y, 2.0) * cn.angle;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	return (formal);
}

bool	test_side_cn(t_data *data, t_cone cn, t_ray ray, t_hitpoint *hit)
{
	t_vec3	tmp;
	t_abc	formal;

	formal = calc_quadratic_formal(ray, cn);
	if (formal.dis > 0.0)
	{
		calc_t(&formal);
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			if (tmp.y >= -cn.height && tmp.y <= 0.0)
			{
				hit->p = con_to_vec3(r_vec(cn.side.mi, con_to_vec4(tmp, 1)));
				norm_calc_cn(cn, hit);
				hit->t = formal.t;
				get_color_and_normal_cn(data, cn, hit, tmp);
				return (true);
			}
		}
	}
	return (false);
}

bool	test_bottom_cn(t_data *data, t_cone cn, t_hitpoint *hit, t_ray ray)
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
		if (dis <= cn.radius * cn.radius)
		{
			hit->p = con_to_vec3(
					r_vec(cn.bottom.mi, con_to_vec4(tmp, 1)));
			hit->normal = multi_vec_wnbr(cn.norm, -1.0);
			hit->t = t;
			get_color_and_normal_tb_cn(data, cn, hit, tmp);
			return (true);
		}
	}
	return (false);
}

void	norm_calc_cn(t_cone cn, t_hitpoint *hit)
{
	t_vec3	center;
	t_vec3	oc;
	t_vec3	ch;
	t_vec3	tangent;

	oc = sub_vec(hit->p, cn.coords);
	center = add_vec(cn.coords, multi_vec_wnbr(cn.norm,
				dot(oc, cn.norm) / dot(cn.norm, cn.norm)));
	ch = sub_vec(hit->p, center);
	tangent = cross_vec(oc, ch);
	hit->normal = norm_vec(cross_vec(tangent, oc));
}
