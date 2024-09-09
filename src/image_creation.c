/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:15:44 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/09 14:15:19 by lbohm            ###   ########.fr       */
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
	data->pos = 0;
	data->pos_p = 0;
	while (coords.y < data->hight)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			if (data->moved)
				pixel_to_wspace(coords, data);
			else
			{
				test = data->caches_p[data->pos_p];
				data->pos_p++;
			}
			if (hit_sphere(data, test, &data->set.sp[0]))
			{
				// light = dot(data->caches_t[data->pos], data->set.light.normalized);
				// light < 0.0 ? light = 0.0 : light;
				light = 1;
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
	float	t2;
	t_vec	origin;

	origin = sub_vec(data->set.cam.coords, sp->coords);
	origin.x *= -1;
	origin.y *= -1;
	a = dot(test, test);
	b = 2.0 * dot(origin, test);
	c = dot(origin, origin) - (sp->radius * sp->radius);
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
			data->caches_t[data->pos] = norm_vec(data->t1);
		}
		return (true);
	}
	return (false);
}

void	pixel_to_wspace(t_vec s1, t_data *data)
{
	data->caches_p[data->pos_p].x = s1.x * (data->viewport.x / (float)data->width);
	data->caches_p[data->pos_p].y = s1.y * (data->viewport.y / (float)data->hight);
	data->caches_p[data->pos_p].z = data->viewport.z;
	data->caches_p[data->pos_p].x = (2.0 * data->caches_p[data->pos_p].x) / data->viewport.x - 1.0;
	data->caches_p[data->pos_p].y = 1.0 - (data->caches_p[data->pos_p].y * 2.0) / data->viewport.y;
	data->caches_p[data->pos_p].x *= data->aspect_ratio;
	data->pos_p++;
}
