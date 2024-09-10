/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/10 16:42:22 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_img(t_data *data)
{
	t_vec		coords;
	t_hitpoint	hit;

	hit.color.x = 0.0;
	hit.color.y = 0.0;
	hit.color.z = 0.0;
	coords.x = 0.0;
	coords.y = 0.0;
	coords.z = 0.0;
	data->now_ray.origin = data->set.cam.coords;
	init_viewport(data);
	while (coords.y < data->hight)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			super_sampling(data, &hit, coords.x, coords.y);
			mlx_put_pixel(data->img, coords.x, coords.y,
				create_color(hit.color.x, hit.color.y, hit.color.z, 255));
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
	float	t;
	int		i;
	t_vec	light;
	t_vec	light_dir;
	t_vec	diffuse;
	t_vec	result;
	t_vec	test;
	float	diffuse_strength;

	i = 0;
	t = 0.0;
	hit->sp_i = 0;
	hit->t = __FLT_MAX__;
	while (i < data->set.sp_count)
	{
		oc = sub_vec(data->set.sp[i].coords, ray.origin);
		a = dot(ray.direction, ray.direction);
		b = dot(ray.direction, oc);
		c = dot(oc, oc) - data->set.sp[i].radius * data->set.sp[i].radius;
		dis = (b * b) - (a * c);
		if (dis > 0.0)
		{
			t = (b - sqrt(dis)) / a;
			if (t <= 0.0 || t >= INFINITY)
			{
				t = (b + sqrt(dis) / a);
				if (t <= 0.0 || t >= INFINITY)
					return (false);
			}
			if (hit->t > t)
			{
				hit->t = t;
				hit->sp_i = i;
			}
		}
		i++;
	}
	if (hit->t != __FLT_MAX__)
	{
		hit->p = ray_vec(ray.origin, hit->t, ray.direction);
		hit->normal = norm_vec(dev_vec_wnbr(sub_vec(hit->p, data->set.sp[hit->sp_i].coords), data->set.sp[hit->sp_i].radius));
		in_out_object(ray, hit);
		light = multi_vec_wnbr(data->set.light.color, data->set.light.brightness);
		light_dir = norm_vec(sub_vec(data->set.light.coords, hit->p));
		diffuse_strength = dot(hit->normal, light_dir);
		diffuse_strength < 0.0 ? diffuse_strength = 0 : diffuse_strength;
		diffuse = multi_vec_wnbr(data->set.light.color, diffuse_strength);
		hit->color = add_vec(hit->color, multi_vec(add_vec(light, diffuse), dev_vec_wnbr(data->set.sp[hit->sp_i].color, 255.0)));
		return (true);
	}
	return (false);
}

void	in_out_object(t_ray ray, t_hitpoint *hit)
{
	if (dot(ray.direction, hit->normal) > 0.0)
		hit->normal = multi_vec_wnbr(hit->normal, -1.0);
}

bool	trace_ray(float x, float y, t_data *data, t_hitpoint *hit)
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

void	init_viewport(t_data *data)
{
	t_vec	z_distanz;

	z_distanz.x = 0.0;
	z_distanz.y = 0.0;
	z_distanz.z = 1.0;
	data->vp.size.x = 2 * tan(data->set.cam.fov / 2);
	data->vp.size.y = data->vp.size.x / data->aspect_ratio;
	data->vp.size.z = 0;
	data->vp.u.x = data->vp.size.x;
	data->vp.u.y = 0;
	data->vp.u.z = 0;
	data->vp.v.x = 0;
	data->vp.v.y = -data->vp.size.y;
	data->vp.v.z = 0;
	data->vp.du = dev_vec_wnbr(data->vp.u, (float)data->width);
	data->vp.dv = dev_vec_wnbr(data->vp.v, (float)data->hight);
	data->vp.upper_left = sub_vec(sub_vec(\
		sub_vec(data->set.cam.coords, z_distanz), \
		dev_vec_wnbr(data->vp.u, 2.0)), dev_vec_wnbr(data->vp.v, 2.0));
	data->vp.p00 = add_vec(data->vp.upper_left,
			multi_vec_wnbr(add_vec(data->vp.du, data->vp.dv), 0.5));
}

void	super_sampling(t_data *data, t_hitpoint *hit, int x, int y)
{
	int	i;

	i = 0;
	hit->color.x = 0.0;
	hit->color.y = 0.0;
	hit->color.z = 0.0;
	if (trace_ray((float )x, (float)y, data, hit))
		i++;
	if (trace_ray((float)x + 0.5, (float)y, data, hit))
		i++;
	if (trace_ray((float)x - 0.5, (float)y, data, hit))
		i++;
	if (trace_ray((float)x, (float)y + 0.5, data, hit))
		i++;
	if (trace_ray((float)x, (float)y - 0.5, data, hit))
		i++;
	if (trace_ray((float)x - 0.5, (float)y - 0.5, data, hit))
		i++;
	if (trace_ray((float)x + 0.5, (float)y + 0.5, data, hit))
		i++;
	if (trace_ray((float)x + 0.5, (float)y - 0.5, data, hit))
		i++;
	if (trace_ray((float)x - 0.5, (float)y + 0.5, data, hit))
		i++;
	hit->color = dev_vec_wnbr(hit->color, (float)i);
}
