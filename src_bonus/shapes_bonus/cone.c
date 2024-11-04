/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:41:35 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/04 16:08:10 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_cone(t_cone cn, t_ray ray, t_hitpoint *hit, int i)
{
	t_abc	formal;
	t_vec3	tmp;

	formal.a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	formal.b = (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
	formal.c = pformalow(ray.origin.x, 2) + pow(ray.origin.z, 2) - cn.radius * cn.radius;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	if (formal.dis > 0.0)
	{
		formal.t = (-formal.b - sqrt(formal.dis)) / (formal.a);
		if (formal.t <= 0.0 || formal.t >= INFINITY)
		{
			formal.t = (-formal.b + sqrt(formal.dis)) / (formal.a);
			if (formal.t <= 0.0 || formal.t >= INFINITY)
				formal.t = __FLT_MAX__;
		}
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			if (fabsf(tmp.y) < cn.height / 2.0)
			{
				hit->p = convert_to_vec3(r_vec(cn.mti, convert_to_vec4(tmp, 1)));
				// cy_norm_calc(cn, hit);
				hit->t = formal.t;
				hit->i = i;
			}
		}
	}
}

void	cn_norm_calc(t_cone cn, t_hitpoint *hit)
{

}

void	cn_bottom()
{
	
}
