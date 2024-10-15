/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:14:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/15 12:25:53 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	// t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t;

	t = 0.0;
	// oc = sub_vec(sp.coords, ray.origin);
	a = dot4(ray.direction, ray.direction);
	b = dot4(ray.direction, ray.origin);
	c = dot4(ray.origin, ray.origin) - sp.radius * sp.radius;
	dis = (b * b) - (a * c);
	if (dis > 0.0)
	{
		t = (b - sqrt(dis)) / a;
		if (t <= 0.0 || t >= INFINITY)
		{
			t = (b + sqrt(dis) / a);
			if (t <= 0.0 || t >= INFINITY)
				t = __FLT_MAX__;
		}
		if (hit->t > t)
		{
			hit->p = convert_to_vec3(ray_vec4(ray.origin, t, ray.direction));
			hit->normal = dev_vec_wnbr(sub_vec(hit->p, sp.coords), sp.radius);
			hit->t = t;
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
