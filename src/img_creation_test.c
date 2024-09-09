/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/09 18:05:51 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	create_color(float x, float y, float z, int a);

void	create(t_data *data)
{
	t_vec		coords;
	t_vec		color;
	t_vec		white;
	t_vec		blue;
	t_vec		test;
	t_hitpoint	hit;
	t_vec		pixle_center;
	float		rad;
	float		ratio;
	float		a;
	int			i;

	i = 0;
	test.x = 0;
	test.y = 0;
	test.z = 1;
	hit.color.x = 0.0;
	hit.color.y = 0.0;
	hit.color.z = 0.0;
	white.x = 1.0;
	white.y = 1.0;
	white.z = 1.0;
	blue.x = 0.5;
	blue.y = 0.7;
	blue.z = 1.0;
	coords.x = 0.0;
	coords.y = 0.0;
	coords.z = 0.0;
	data->width = 1600;
	data->hight = 900;
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
	data->vp.upper_left = sub_vec(sub_vec(sub_vec(data->set.cam.coords, test), dev_vec_wnbr(data->vp.u, 2.0)), dev_vec_wnbr(data->vp.v, 2.0));
	data->vp.p00 = add_vec(data->vp.upper_left, multi_vec_wnbr(add_vec(data->vp.du, data->vp.dv), 0.5));
	data->now_ray.origin = data->set.cam.coords;
	while (coords.y < data->hight)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			i = 0;
			if (test2(coords.x, coords.y, data, &hit))
				i++;
			if (test2(coords.x++, coords.y, data, &hit))
				i++;
			if (test2(coords.x--, coords.y, data, &hit))
				i++;
			if (test2(coords.x, coords.y++, data, &hit))
				i++;
			if (test2(coords.x, coords.y--, data, &hit))
				i++;
			hit.color = dev_vec_wnbr(hit.color, (float)i);
			mlx_put_pixel(data->img, coords.x, coords.y, create_color(hit.color.x, hit.color.y, hit.color.z, 255));
			coords.x += 1.0;
		}
		coords.y += 1.0;
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

bool	hit_sphere_test(t_ray ray, t_hitpoint *hit, t_data *data)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	dis;
	int		i;

	i = 0;
	while (i < data->set.sp_count)
	{
		oc = sub_vec(data->set.sp[i].coords, ray.origin);
		a = dot(ray.direction, ray.direction);
		b = dot(ray.direction, oc);
		c = dot(oc, oc) - data->set.sp[i].radius * data->set.sp[i].radius;
		dis = (b * b) - (a * c);
		if (dis > 0.0)
		{
			hit->t = (b - sqrt(dis)) / a;
			if (hit->t <= 0.0 || hit->t >= INFINITY)
			{
				hit->t = (b + sqrt(dis) / a);
				if (hit->t <= 0.0 || hit->t >= INFINITY)
					return (false);
			}
			hit->p = ray_vec(ray.origin, hit->t, ray.direction);
			hit->normal = norm_vec(dev_vec_wnbr(sub_vec(hit->p, data->set.sp[i].coords), data->set.sp[i].radius));
			in_out_object(ray, hit);
			hit->color = add_vec(hit->color, dev_vec_wnbr(data->set.sp[i].color, 255.0));
			return (true);
		}
		i++;
	}
	return (false);
}

void	in_out_object(t_ray ray, t_hitpoint *hit)
{
	if (dot(ray.direction, hit->normal) > 0.0)
		hit->normal = multi_vec_wnbr(hit->normal, -1.0);
}

bool	test2(int x, int y, t_data *data, t_hitpoint *hit)
{
	t_vec		pixle_center;
	t_vec		white;
	t_vec		blue;
	float		a;
	t_vec		result;

	white.x = 1.0;
	white.y = 1.0;
	white.z = 1.0;
	blue.x = 0.5;
	blue.y = 0.7;
	blue.z = 1.0;
	if (x >= 0 && x < data->width && y >= 0 && y < data->hight)
	{
		pixle_center = add_vec(add_vec(data->vp.p00, multi_vec_wnbr(data->vp.du, x)), multi_vec_wnbr(data->vp.dv, y));
		data->now_ray.direction = sub_vec(pixle_center, data->set.cam.coords);
		if (hit_sphere_test(data->now_ray, hit, data))
		{
			// result = add_vec_wnbr(multi_vec_wnbr(hit->normal, 0.5), 0.5);
		}
		else
		{
			data->now_ray.direction = norm_vec(data->now_ray.direction);
			a = 0.5 * (data->now_ray.direction.y + 1.0);
			result = add_vec(multi_vec_wnbr(white, (float)(1 - a)), multi_vec_wnbr(blue, a));
			hit->color = add_vec(hit->color, result);
		}
		return (true);
	}
	return (false);
}
