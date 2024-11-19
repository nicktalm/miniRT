/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:29 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/19 12:35:14 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->set.obj = NULL;
	data->set.light = NULL;
	data->cache = NULL;
	if (argc == 2)
	{
		data->width = 1600;
		data->height = 900;
		data->bg.x = 0.0;
		data->bg.y = 0.0;
		data->bg.z = 0.0;
		data->checker = false;
		data->render = false;
		data->aspect_ratio = (float)data->width / (float)data->height;
		data->moved = true;
		data->cache = malloc (data->width * data->height * sizeof(t_vec3));
		if (!data->cache)
			error("malloc", data);
		open_file(argv[1], data);
	}
	else
		error("Wrong nbr of Arguments", data);
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(data->width, data->height, "miniRT", true);
	if (!data->window)
		error("mlx_init", data);
	data->img = mlx_new_image(data->window, data->width, data->height);
	if (!data->img)
		error("img", data);
}

void	init_viewport(t_data *data)
{
	t_vec3	right;
	t_vec3	up;

	up.x = 0.0;
	up.y = 1.0;
	up.z = 0.0;
	if (data->moved)
	{
		right = cross_vec(data->set.cam.direction, up);
		up = cross_vec(right, data->set.cam.direction);
		data->vp.size.x = 2 * tan(data->set.cam.fov / 2);
		data->vp.size.y = (data->vp.size.x / data->aspect_ratio);
		data->vp.size.z = 0;
		data->vp.u = multi_vec_wnbr(right, data->vp.size.x);
		data->vp.v = multi_vec_wnbr(multi_vec_wnbr(up, data->vp.size.y), -1.0);
		data->vp.du = dev_vec_wnbr(data->vp.u, (float)data->width);
		data->vp.dv = dev_vec_wnbr(data->vp.v, (float)data->height);
		data->vp.upper_left = sub_vec(sub_vec(add_vec(\
			data->set.cam.coords, data->set.cam.direction), \
			dev_vec_wnbr(data->vp.u, 2.0)), dev_vec_wnbr(data->vp.v, 2.0));
		data->vp.p00 = add_vec(data->vp.upper_left,
				multi_vec_wnbr(add_vec(data->vp.du, data->vp.dv), 0.5));
	}
}
