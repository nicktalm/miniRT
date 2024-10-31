/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:14:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/31 15:29:32 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	t_abc	formal;
	t_vec3	oc;

	formal.t = 0.0;
	oc = sub_vec(sp.coords, ray.origin);
	formal.a = dot(ray.direction, ray.direction);
	formal.b = dot(ray.direction, oc);
	formal.c = dot(oc, oc) - sp.radius * sp.radius;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	if (formal.dis > 0.0)
	{
		formal.t = (formal.b - sqrt(formal.dis)) / formal.a;
		if (formal.t <= 0.0 || formal.t >= INFINITY)
		{
			formal.t = (formal.b + sqrt(formal.dis) / formal.a);
			if (formal.t <= 0.0 || formal.t >= INFINITY)
				formal.t = __FLT_MAX__;
		}
		if (hit->t > formal.t)
		{
			hit->p = ray_vec(ray.origin, formal.t, ray.direction);
			hit->normal = norm_vec(sub_vec(hit->p, sp.coords));
			hit->t = formal.t;
			hit->i = i;
		}
	}
}

void	create_m_sp(t_sphere *sp)
{
	float	full_r[4][4];
	float	t[4][4];
	float	tmp[4][4];

	translation(t, sp->coords);
	get_full_r(full_r, 0.0, 0.0, 0.0);
	multi_m(sp->mt, full_r, t);
	copy_m(tmp, sp->mt);
	create_m_inverse(tmp, sp->mti);
}
