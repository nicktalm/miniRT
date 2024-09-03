/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:15:44 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/03 10:19:41 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_img(t_data *data)
{
	t_vec	coords;
	t_vec	test;
	float	light;

	coords.y = 0.0;
	coords.z = -1.0;
	while (coords.y < data->hight)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			test.x = (coords.x * 2) / (float)data->width - 1;
			test.y = 1 - ((coords.y * 2) / (float)data->hight);
			test.z = -1.0;
			test.x *= data->aspect_ratio;
			if (hit_sphere(data, test, &data->set.sp[0]))
			{
				light = dot(data->caches[data->pos], data->set.light.normalized);
				light < 0.0 ? light = 0.0 : light;
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(data->set.sp[0].color.x * light, data->set.sp[0].color.y * light, data->set.sp[0].color.z * light, 255));
			}
			else
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(0, 0, 0, 100));
			coords.x++;
		}
		coords.y++;
	}
	data->moved = false;
}

int	get_color(int r, int g, int b, int a)
{
	r > 255 ? r = 255 : r < 0 ? r = 0 : r;
	g > 255 ? g = 255 : g < 0 ? g = 0 : g;
	b > 255 ? b = 255 : b < 0 ? b = 0 : b;
	a > 255 ? a = 255 : a < 0 ? a = 0 : a;
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	hit_sphere(t_data *data, t_vec test, t_sphere *sp)
{
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t1;

	a = (test.x * test.x) + (test.y * test.y)+ (test.z * test.z);
	b = 2.0 * (data->set.cam.coords.x * test.x + data->set.cam.coords.y * test.y + data->set.cam.coords.z * test.z);
	c = (data->set.cam.coords.x * data->set.cam.coords.x) + (data->set.cam.coords.y * data->set.cam.coords.y) + (data->set.cam.coords.z * data->set.cam.coords.z) - (sp->radius * sp->radius);
	dis = b * b - 4.0 * a * c;
	if (data->pos == data->hight * data->width)
		data->pos = 0;
	data->pos++;
	if (dis >= 0.0)
	{
		if (data->moved)
		{
			t1 = (-b - sqrt(dis)) / 2 * a;
			data->t1.x = data->set.cam.coords.x + (test.x * t1);
			data->t1.y = data->set.cam.coords.y + (test.y * t1);
			data->t1.z = data->set.cam.coords.z + (test.z * t1);
			data->t1.x -= sp->coords.x;
			data->t1.y -= sp->coords.y;
			data->t1.z -= sp->coords.z;
			data->caches[data->pos] = norm_vec(data->t1);
		}
		return (true);
	}
	return (false);
}
