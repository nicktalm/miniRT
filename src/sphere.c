/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:14:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/18 17:30:40 by lbohm            ###   ########.fr       */
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

	t = 0.0;
	a = dot(ray.direction, ray.direction);
	b = dot(ray.direction, ray.origin);
	c = dot(ray.origin, ray.origin) - sp.radius * sp.radius;
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
			hit->p = ray_vec(ray.origin, t, ray.direction);
			printf("hit p before x = %f y = %f z = %f\n", hit->p.x, hit->p.y, hit->p.z);
			hit->p = convert_to_vec3(r_vec(sp.mti, convert_to_vec4(hit->p, 1)));
			printf("hit p x = %f y = %f z = %f\n", hit->p.x, hit->p.y, hit->p.z);
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
	t_vec3	test = {0,0,50};

	translation(t, sub_vec(sp->coords, test));
	get_full_r(full_r, 0.0, 0.0, 0.0);
	multi_m(sp->mt, full_r, t);
	copy_m(tmp, sp->mt);
	create_m_inverse(tmp, sp->mti);
}
