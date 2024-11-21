/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 20:05:45 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_img(t_data *data)
{
	t_vec3		coords;
	int			resolution;

	coords.y = 0.0;
	coords.z = 0.0;
	if (!data->render)
		resolution = data->res;
	else
		resolution = 1;
	init_viewport(data);
	pixel_loop(data, coords, resolution);
	data->moved = false;
}

void	pixel_loop(t_data *data, t_vec3 coords, int resolution)
{
	while (coords.y < data->height)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			if (data->moved)
			{
				data->cache_use = false;
				if (!data->render)
					down_sampling(data, (int)coords.x, (int)coords.y);
				else
				{
					super_sampling(data, (int)coords.x, (int)coords.y);
					data->cache_use = true;
				}
			}
			else
				data->cache_use = true;
			coords.x += resolution;
		}
		coords.y += resolution;
	}
}

void	in_out_object(t_ray *ray, t_hitpoint *hit)
{
	if (dot(ray->direction, hit->normal) > 0.0)
	{
		hit->normal = multi_vec_wnbr(hit->normal, -1.0);
	}
}

void	trace_ray(float x, float y, t_hitpoint *hit, t_data *data)
{
	t_vec3		pixle_center;
	t_ray		ray;

	ray.origin = data->set.cam.coords;
	pixle_center = add_vec(add_vec(data->vp.p00, \
	multi_vec_wnbr(data->vp.du, x)), multi_vec_wnbr(data->vp.dv, y));
	ray.direction = sub_vec(pixle_center, data->set.cam.coords);
	get_color(data, &ray, hit);
}
