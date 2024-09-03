/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:29 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/03 10:17:54 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	init_data(t_data *data)
{
	data->set.ambient.range = 0.2;
	data->set.ambient.color.x = 255;
	data->set.ambient.color.y = 255;
	data->set.ambient.color.z = 255;
	data->set.cam.coords.x = 0.0;
	data->set.cam.coords.y = 0.0;
	data->set.cam.coords.z = 3.0;
	data->set.cam.normalized.x = 0.0;
	data->set.cam.normalized.y = 0.0;
	data->set.cam.normalized.z = 1.0;
	data->set.cam.fov = 90 * (M_PI / 180);
	data->set.light.coords.x = -10.0;
	data->set.light.coords.y = -10.0;
	data->set.light.coords.z = -4.0;
	data->set.light.brightness = 0.6;
	data->set.light.color.x = 10;
	data->set.light.color.y = 0;
	data->set.light.color.z = 255;
	data->set.sp = (t_sphere *)malloc (3 * sizeof(t_sphere));
	if (!data->set.sp)
		return ;
	data->set.pl = (t_plane *)malloc (sizeof(t_plane));
	if (!data->set.pl)
		return ;
	data->set.cy = (t_cylinder *)malloc (sizeof(t_cylinder));
	if (!data->set.cy)
		return ;
	data->set.sp[0].coords.x = 0.0;
	data->set.sp[0].coords.y = 0.0;
	data->set.sp[0].coords.z = 0.0;
	data->set.sp[0].diameter = 2;
	data->set.sp[0].radius = data->set.sp[0].diameter / 2;
	data->set.sp[0].color.x = 255;
	data->set.sp[0].color.y = 0;
	data->set.sp[0].color.z = 0;
	data->set.sp[1].coords.x = 2.0;
	data->set.sp[1].coords.y = 0.0;
	data->set.sp[1].coords.z = 0.0;
	data->set.sp[1].diameter = 2;
	data->set.sp[1].radius = data->set.sp[1].diameter / 2;
	data->set.sp[1].color.x = 0;
	data->set.sp[1].color.y = 0;
	data->set.sp[1].color.z = 255;
	data->set.sp[2].coords.x = -2.0;
	data->set.sp[2].coords.y = 0.0;
	data->set.sp[2].coords.z = 0.0;
	data->set.sp[2].diameter = 2;
	data->set.sp[2].radius = data->set.sp[2].diameter / 2;
	data->set.sp[2].color.x = 0;
	data->set.sp[2].color.y = 255;
	data->set.sp[2].color.z = 0;
	data->set.pl[0].coords.x = 0.0;
	data->set.pl[0].coords.y = 0.0;
	data->set.pl[0].coords.z = -10.0;
	data->set.pl[0].normalized.x = 0.0;
	data->set.pl[0].normalized.y = 1.0;
	data->set.pl[0].normalized.z = 0.0;
	data->set.pl[0].color.x = 0;
	data->set.pl[0].color.y = 0;
	data->set.pl[0].color.z = 225;
	data->set.cy[0].coords.x = 50.0;
	data->set.cy[0].coords.y = 0.0;
	data->set.cy[0].coords.z = 20.6;
	data->set.cy[0].normalized.x = 0.0;
	data->set.cy[0].normalized.y = 0.0;
	data->set.cy[0].normalized.z = 1.0;
	data->set.cy[0].diameter = 14.2;
	data->set.cy[0].height = 21.42;
	data->set.cy[0].color.x = 10;
	data->set.cy[0].color.y = 0;
	data->set.cy[0].color.z = 255;
	data->width = 900;
	data->hight = 900;
	data->aspect_ratio = data->width / data->hight;
	data->dpi = 10;
	data->caches = (t_vec *)malloc(sizeof(t_vec) * data->width * data->hight);
	if (!data->caches)
		return ;
	data->pos = 0;
	data->moved = true;
	data->set.light.normalized = norm_vec(data->set.light.coords);
	data->set.light.normalized.x *= -1;
	data->set.light.normalized.y *= -1;
	data->set.light.normalized.z *= -1;
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(data->width, data->hight, "miniRT", true);
	data->img = mlx_new_image(data->window, data->width, data->hight);
}
