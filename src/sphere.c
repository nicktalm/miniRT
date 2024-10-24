/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:14:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/21 16:10:52 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t;
	t_vec3	oc;

	t = 0.0;
	oc = sub_vec(sp.coords, ray.origin);
	a = dot(ray.direction, ray.direction);
	b = dot(ray.direction, oc);
	c = dot(oc, oc) - sp.radius * sp.radius;
	dis = (b * b) - (a * c);
	if (dis > 0.0)
	{
		// printf("\033[0;31mdis = %f\n\033[0m", dis);
		t = (b - sqrt(dis)) / a;
		if (t <= 0.0 || t >= INFINITY)
		{
			t = (b + sqrt(dis) / a);
			if (t <= 0.0 || t >= INFINITY)
				t = __FLT_MAX__;
		}
		if (hit->t > t)
		{
			// printf("\033[0;31msphere origin x = %f y = %f z = %f\n\033[0m", ray.origin.x, ray.origin.y, ray.origin.z);
			// printf("\033[0;31msphere direction x = %f y = %f z = %f\n\033[0m", ray.direction.x, ray.direction.y, ray.direction.z);
			hit->p = ray_vec(ray.origin, t, ray.direction);
			// hit->p = convert_to_vec3(r_vec(sp.mti, convert_to_vec4(hit->p, 1)));
			// printf("\033[0;31msphere hit p x = %f y = %f z = %f\n\033[0m", hit->p.x, hit->p.y, hit->p.z);
			hit->normal = norm_vec(sub_vec(hit->p, sp.coords));
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
