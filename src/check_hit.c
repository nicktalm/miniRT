/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:46:05 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/18 18:56:05 by lbohm            ###   ########.fr       */
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
	// printf("ray origin x = %f y = %f z = %f ray direction x = %f y = %f z = %f\n", ray.origin.x, ray.origin.y, ray.origin.z, ray.direction.x, ray.direction.y, ray.direction.z);
	while (i < data->set.obj_count)
	{
		if (data->set.obj[i].type == SPHERE)
			calc_sp(data->set.obj[i].form.sp, ray, hit, i);
		else if (data->set.obj[i].type == PLANE)
			calc_pl(data->set.obj[i].form.pl, ray, hit, i);
		// else if (data->set.obj[i].type == CYLINDER)
		// 	calc_cy(data->set.obj[i].form.cy, ray, hit, i);
		i++;
	}
}

void	check_reflect(t_ray ray, t_hitpoint *hit, t_data *data)
{
	int		i;
	float	t;

	i = 0;
	t = 0.0;
	hit->i = 0;
	hit->t = __FLT_MAX__;
	while (i < data->set.obj_count)
	{
		if (data->set.obj[i].type == SPHERE)
			calc_sp(data->set.obj[i].form.sp, ray, hit, i);
		// else if (data->set.obj[i].type == CYLINDER)
		// 	calc_cy(data->set.obj[i].form.cy, ray, hit, i);
		i++;
	}
}

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	t_vec	oc;
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
	float	denom;

	t = 0.0;
	denom = dot(pl.normalized, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		t = -dot(pl.normalized, sub_vec(ray.origin, pl.coords)) / dot(pl.normalized, ray.direction);
		if (t > 0.0 && hit->t > t)
		{
			hit->i = i;
			hit->t = t;
		}
	}
}

// void	calc_cy(t_cylinder pl, t_ray ray, t_hitpoint *hit, int i)
// {

// }
