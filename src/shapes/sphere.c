/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:14:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/08 15:33:39 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	t_abc	formal;
	t_vec3	tmp;

	ray.origin = convert_to_vec3(r_vec(sp.side.m, convert_to_vec4(ray.origin, 1)));
	ray.direction = convert_to_vec3(r_vec(sp.side.m, convert_to_vec4(ray.direction, 0)));
	formal.t = 0.0;
	formal.a = dot(ray.direction, ray.direction);
	formal.b = dot(ray.direction, ray.origin);
	formal.c = dot(ray.origin, ray.origin) - sp.radius * sp.radius;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	if (formal.dis > 0.0)
	{
		calc_t(&formal);
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			hit->p = convert_to_vec3(r_vec(sp.side.mi, convert_to_vec4(tmp, 1)));
			hit->normal = norm_vec(sub_vec(hit->p, sp.coords));
			hit->t = formal.t;
			hit->obj_color = sp.color;
			hit->i = i;
		}
	}
}

void	create_m_sp(t_sphere *sp)
{
	translation(sp->side.m, multi_vec_wnbr(sp->coords, -1.0));
	invert_matrix(sp->side.m, sp->side.mi);
}
