/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:29 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/16 15:21:59 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->set.sp = NULL;
	data->set.pl = NULL;
	data->set.cy = NULL;
	if (argc == 2)
	{
		data->width = 1600;
		data->height = 900;
		data->moved = true;
		data->c.hit = NULL;
		data->c.pos = 0;
		data->bg.x = 0.4;
		data->bg.y = 0.5;
		data->bg.z = 0.6;
		data->i = 1;
		data->c.hit = (t_hitpoint *)malloc
			(data->width * data->height * sizeof(t_hitpoint));
		data->range = (t_range *)malloc (200 * sizeof(t_range));
		if (!data->c.hit || !data->range)
			error("malloc failed", data);
		for (int i = 0; i < 200; i++)
		{
			data->range[i].hit = (t_hitpoint *)malloc (data->width * data->height * sizeof(t_hitpoint));
			if (!data->range[i].hit)
				error("malloc failed", data);
		}
		data->aspect_ratio = (float)data->width / (float)data->height;
		open_file(argv[1], data);
		data->now_ray.origin = data->set.cam.coords;
		data->set.sp[0].material = 0.0f;
		data->set.sp[1].material = 0.0f;
		data->set.sp[2].material = 0.1f;
	}
	else
		error("Wrong nbr of Arguments", data);
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(data->width, data->height, "miniRT", true);
	data->img = mlx_new_image(data->window, data->width, data->height);
}

void	init_viewport(t_data *data)
{
	t_vec	right;
	t_vec	up;

	up.x = 0.0;
	up.y = 1.0;
	up.z = 0.0;
	right = cross_vec(up, data->set.cam.direction);
	right = norm_vec(right);
	up = cross_vec(data->set.cam.direction, right);
	data->vp.size.x = 2 * tan(data->set.cam.fov / 2);
	data->vp.size.y = data->vp.size.x / data->aspect_ratio;
	data->vp.size.z = 0;
	data->vp.u = multi_vec_wnbr(right, data->vp.size.x);
	data->vp.v = multi_vec_wnbr(up, data->vp.size.y);
	data->vp.du = dev_vec_wnbr(data->vp.u, (float)data->width);
	data->vp.dv = dev_vec_wnbr(data->vp.v, (float)data->height);
	data->vp.upper_left = sub_vec(sub_vec(\
		sub_vec(data->set.cam.coords, data->set.cam.direction), \
		dev_vec_wnbr(data->vp.u, 2.0)), dev_vec_wnbr(data->vp.v, 2.0));
	data->vp.p00 = add_vec(data->vp.upper_left,
			multi_vec_wnbr(add_vec(data->vp.du, data->vp.dv), 0.5));
}
