/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/06 19:01:22 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	create_color(float x, float y, float z, int a);

void	create(t_data *data)
{
	t_vec	coords;
	t_vec	upper_left;
	t_vec	color;
	t_vec	white;
	t_vec	blue;
	t_vec	test;
	t_vec	normal;
	float	rad;
	float	ratio;
	float	a;
	float	t;

	test.x = 0;
	test.y = 0;
	test.z = 1;
	white.x = 1.0;
	white.y = 1.0;
	white.z = 1.0;
	blue.x = 0.5;
	blue.y = 0.7;
	blue.z = 1.0;
	coords.x = 0;
	coords.y = 0;
	coords.z = 0;
	// rad = (float)data->set.cam.fov * (M_PI / 180.0);
	// ratio = (float)data->width / (float)data->hight;
	// data->vp.size.x = 2 * tan(rad / 2);
	// data->vp.size.y = data->vp.size.x / ratio;
	// data->vp.size.z = 0;
	data->vp.size.y = 2.0;
	data->vp.size.x = data->vp.size.y * ((float)data->width / (float)data->hight);
	data->vp.size.z = 0;
	data->vp.u.x = data->vp.size.x;
	data->vp.u.y = 0;
	data->vp.u.z = 0;
	data->vp.v.x = 0;
	data->vp.v.y = -data->vp.size.y;
	data->vp.v.z = 0;
	data->vp.du = dev_vec_wnbr(data->vp.u, (float)data->width);
	data->vp.dv = dev_vec_wnbr(data->vp.v, (float)data->hight);
	upper_left = sub_vec(sub_vec(sub_vec(data->set.cam.coords, test), dev_vec_wnbr(data->vp.u, 2.0)), dev_vec_wnbr(data->vp.v, 2.0));
	upper_left.z = 1.5;
	data->vp.p00 = add_vec(upper_left, multi_vec_wnbr(add_vec(data->vp.du, data->vp.dv), 0.5));
	while (coords.y < data->hight)
	{
		coords.x = 0;
		while (coords.x < data->width)
		{
			data->now_ray.origin = add_vec(add_vec(data->vp.p00, multi_vec_wnbr(data->vp.du, coords.x)), multi_vec_wnbr(data->vp.dv, coords.y));
			data->now_ray.direction = sub_vec(data->now_ray.origin, data->set.cam.coords);
			t = hit_sphere_test(data->set.sp[0], data->now_ray, data);
			if (t > 0.0)
			{
				normal = norm_vec(sub_vec(ray_vec(data->now_ray.origin, t, data->now_ray.direction), data->set.sp[0].coords));
				color = multi_vec_wnbr(add_vec_wnbr(normal, 1.0), 0.5);
			}
			else
			{
				data->now_ray.direction = norm_vec(data->now_ray.direction);
				a = 0.5 * (data->now_ray.direction.y + 1.0);
				color = add_vec(multi_vec_wnbr(white, (float)(1 - a)), multi_vec_wnbr(blue, a));
			}
			mlx_put_pixel(data->img, coords.x, coords.y, create_color((float)color.x, (float)color.y, (float)color.z, 255));
			coords.x++;
		}
		coords.y++;
	}
}

int	create_color(float x, float y, float z, int a)
{
	int	r;
	int	g;
	int	b;

	r = 255.0 * x;
	g = 255.0 * y;
	b = 255.0 * z;
	r < 0 ? r = 0 : r > 255 ? r = 255 : r;
	g < 0 ? g = 0 : g > 255 ? g = 255 : g;
	b < 0 ? b = 0 : b > 255 ? b = 255 : b;
	return (r << 24 | g << 16 | b << 8 | a);
}

float	hit_sphere_test(t_sphere sp, t_ray ray, t_data *data)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	dis;

	oc = sub_vec(sp.coords, ray.origin);
	a = dot(ray.direction, ray.direction);
	b = dot(ray.direction, oc);
	c = dot(oc, oc) - sp.radius * sp.radius;
	dis = (b * b) - (a * c);
	if (dis > 0.0)
	{
		return ((-b - sqrt(dis)) / a);
	}
	return (-1.0);
}
