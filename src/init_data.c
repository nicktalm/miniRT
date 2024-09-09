/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:29 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/09 15:13:46 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	init_data(t_data *data, int argc, char **argv)
{
	if (argc == 2)
	{
		data->set.sp = NULL;
		data->set.pl = NULL;
		data->set.cy = NULL;
		data->caches_t = NULL;
		data->caches_p = NULL;
		data->aspect_ratio = 16.0 / 9.0;
		data->width = 1600;
		data->hight = 900;
		data->dpi = 10;
		data->caches_t = (t_vec *)malloc(sizeof(t_vec) * data->width * data->hight);
		if (!data->caches_t)
			error("malloc failed", data);
		data->caches_p = (t_vec *)malloc(sizeof(t_vec) * data->width * data->hight);
		if (!data->caches_p)
			error("malloc failed", data);
		data->pos = 0;
		data->pos_p = 0;
		data->moved = true;
		open_file(argv[1], data);
		data->set.sp[0].radius = (float)data->set.sp[0].diameter / 2.0;
		data->set.sp[1].radius = (float)data->set.sp[1].diameter / 2.0;
		data->set.light.normalized = norm_vec(data->set.light.coords);
		data->set.light.normalized.x *= -1;
		data->set.light.normalized.y *= -1;
		data->set.light.normalized.z *= -1;
		data->fov_vert = 2 * atan(tan(((float)data->set.cam.fov * (M_PI / 180.0)) / 2.0) / data->aspect_ratio);
		data->viewport.y = 2 * tan(data->fov_vert / 2);
		data->viewport.x = data->viewport.y * data->aspect_ratio;
		data->viewport.z = data->set.cam.normalized.z;
	}
	else
		error("Wrong nbr of Arguments", data);
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(data->width, data->hight, "miniRT", true);
	data->img = mlx_new_image(data->window, data->width, data->hight);
}
