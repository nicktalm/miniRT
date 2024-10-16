/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:46:05 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/16 12:41:47 by lbohm            ###   ########.fr       */
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
		if (data->set.obj[i].type == SPHERE)
			calc_sp(data->set.obj[i].form.sp, transform_ray(ray, data->set.obj[i]), hit, i);
		else if (data->set.obj[i].type == PLANE)
			calc_pl(data->set.obj[i].form.pl, ray, hit, i);
		else
			calc_cy(data->set.obj[i].form.cy, transform_ray(ray, data->set.obj[i]), hit, i);
		i++;
	}
	// if (hit->t != __FLT_MAX__ && data->set.obj[hit->i].type != CYLINDER)
	// {
	// 	hit->p = ray_vec4(ray.origin, hit->t, ray.direction);
	// 	if (data->set.obj[hit->i].type == SPHERE)
	// 		hit->normal = dev_vec_wnbr(sub_vec(hit->p, data->set.obj[hit->i].form.sp.coords), data->set.obj[hit->i].form.sp.radius);
	// }
	// in_out_object(ray, hit);
}

void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i)
{
	// float	t;

	// t = 0.0;
	// t = -dot(pl.norm, sub_vec(ray.origin, pl.coords)) / dot(pl.norm, ray.direction);
	// if (t > 0.0 && hit->t > t)
	// {
	// 	hit->i = i;
	// 	hit->t = t;
	// 	hit->normal = pl.norm;
	// }
}
