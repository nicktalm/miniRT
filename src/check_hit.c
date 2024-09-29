/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:46:05 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/29 18:14:38 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	check_hit(t_ray ray, t_hitpoint *hit, t_data *data)
{
	int		i;
	float	t;

	i = 0;
	t = 0.0;
	hit->i = 0;
	hit->t = __FLT_MAX__;
	while (i < data->set.obj_count)
	{
		// if (data->set.obj[i].type == SPHERE)
		// 	calc_sp(data->set.obj[i].form.sp, ray, hit, i);
		// else if (data->set.obj[i].type == PLANE)
		// 	calc_pl(data->set.obj[i].form.pl, ray, hit, i);
		if (data->set.obj[i].type == CYLINDER)
			calc_cy(data->set.obj[i].form.cy, ray, hit, i);
		i++;
	}
	// if (hit->t != __FLT_MAX__)
	// {
	// 	if (data->set.obj[hit->i].type != CYLINDER)
	// 		hit->p = ray_vec(ray.origin, hit->t, ray.direction);
	// 	if (data->set.obj[hit->i].type == SPHERE)
	// 		hit->normal = dev_vec_wnbr(sub_vec(hit->p, data->set.obj[hit->i].form.sp.coords), data->set.obj[hit->i].form.sp.radius);
	in_out_object(ray, hit);
	// }
}

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t;

	t = 0.0;
	oc = sub_vec(sp.coords, ray.origin);
	a = dot(ray.direction, ray.direction);
	b = dot(ray.direction, oc);
	c = dot(oc, oc) - sp.radius * sp.radius;
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
			hit->t = t;
			hit->i = i;
		}
	}
}

void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i)
{
	float	t;

	t = 0.0;
	t = -dot(pl.norm, sub_vec(ray.origin, pl.coords)) / dot(pl.norm, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		hit->i = i;
		hit->t = t;
	}
}
