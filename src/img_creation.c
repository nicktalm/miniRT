/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/16 13:47:52 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_img(t_data *data)
{
	t_vec		coords;
	t_vec		testc;

	coords.x = 0.0;
	coords.y = 0.0;
	coords.z = 0.0;
	init_viewport(data);
	while (coords.y < data->height)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			// trace_ray((float)coords.x, (float)coords.y, data);
			// super_sampling(data, coords.x, coords.y);
			testc = dev_vec_wnbr(data->c.hit[data->c.pos].color, (float)data->i);
			mlx_put_pixel(data->img, coords.x, coords.y,
				create_color(testc.x,
					testc.y,
					testc.z, 255));
			data->c.pos++;
			coords.x++;
		}
		coords.y++;
	}
	data->moved = false;
	data->c.pos = 0;
	data->i++;
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

void	hit_sphere(t_ray ray, t_hitpoint *hit, t_data *data)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t;
	int		i;

	i = 0;
	t = 0.0;
	hit->i = 0;
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
					t = __FLT_MAX__;
			}
			if (hit->t > t)
			{
				hit->t = t;
				hit->i = i;
			}
		}
		i++;
	}
}

void	hit_cylinder(t_ray ray, t_data *data)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t;
	int		i;

	i = 0;
	t = 0.0;
	data->c.hit[data->c.pos].i = 0;
	while (i < data->set.cy_count)
	{
		oc = sub_vec(data->set.cy[i].coords, ray.origin);
		a = dot(ray.direction, ray.direction);
		b = dot(ray.direction, oc);
		c = dot(oc, oc) - data->set.cy[i].radius * data->set.cy[i].radius;
		dis = (b * b) - (a * c);
		if (dis > 0.0)
		{
			t = (b - sqrt(dis)) / a;
			if (t <= 0.0 || t >= INFINITY)
			{
				t = (b + sqrt(dis) / a);
				if (t <= 0.0 || t >= INFINITY)
					t = __FLT_MAX__;
			}
			if (data->c.hit[data->c.pos].t > t)
			{
				data->c.hit[data->c.pos].t = t;
				data->c.hit[data->c.pos].i = i;
			}
		}
		i++;
	}
}

void	in_out_object(t_ray ray, t_data *data)
{
	if (dot(ray.direction, data->c.hit[data->c.pos].normal) > 0.0)
		data->c.hit[data->c.pos].normal
			= multi_vec_wnbr(data->c.hit[data->c.pos].normal, -1.0);
}

bool	trace_ray(float x, float y, t_hitpoint *hit, t_data *data)
{
	t_vec		pixle_center;
	t_ray		ray;

	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
	{
		pixle_center = add_vec(add_vec(data->vp.p00, \
		multi_vec_wnbr(data->vp.du, x)), multi_vec_wnbr(data->vp.dv, y));
		ray.origin = data->set.cam.coords;
		ray.direction = sub_vec(pixle_center, data->set.cam.coords);
		get_obj_color(data, ray, hit);
		return (true);
	}
	return (false);
}

// void	super_sampling(t_data *data, int x, int y)
// {
// 	int			i;
// 	t_hitpoint	hit;

// 	i = 1;
// 	if (trace_ray((float)x + 0.5f, (float)y, &hit, data))
// 		i++;
// 	if (trace_ray((float)x - 0.5f, (float)y, &hit, data))
// 		i++;
// 	if (trace_ray((float)x, (float)y + 0.5f, &hit, data))
// 		i++;
// 	if (trace_ray((float)x, (float)y - 0.5f, &hit, data))
// 		i++;
// 	if (trace_ray((float)x - 0.5f, (float)y - 0.5f, &hit, data))
// 		i++;
// 	if (trace_ray((float)x + 0.5f, (float)y + 0.5f, &hit, data))
// 		i++;
// 	if (trace_ray((float)x + 0.5f, (float)y - 0.5f, &hit, data))
// 		i++;
// 	if (trace_ray((float)x - 0.5f, (float)y + 0.5f, &hit, data))
// 		i++;
// 	data->c.hit[data->c.pos].color
// 		= dev_vec_wnbr(data->c.hit[data->c.pos].color, (float)i);
// }

void	get_obj_color(t_data *data, t_ray ray, t_hitpoint *hit)
{
	t_vec		light;
	t_vec		light_dir;
	t_vec		diffuse;
	t_vec		r;
	float		diffuse_strength;
	int			re;
	float		multi;

	multi = 1.0f;
	re = 0;
	while (re++ < 5)
	{
		hit_sphere(ray, hit, data);
		if (hit->t != __FLT_MAX__)
		{
			hit->p = ray_vec(ray.origin, hit->t, ray.direction);
			hit->normal = dev_vec_wnbr(sub_vec(hit->p, data->set.sp[hit->i].coords), data->set.sp[hit->i].radius);
			in_out_object(ray, data);
			light = multi_vec_wnbr(data->set.light.color, data->set.light.brightness);
			light_dir = norm_vec(sub_vec(data->set.light.coords, hit->p));
			diffuse_strength = dot(hit->normal, light_dir);
			diffuse_strength < 0.0 ? diffuse_strength = 0 : diffuse_strength;
			diffuse = multi_vec_wnbr(data->set.light.color, diffuse_strength);
			hit->color = add_vec(hit->color, multi_vec_wnbr(multi_vec(add_vec(light, diffuse), data->set.sp[hit->i].color), multi));
			multi *= 0.5f;
			r.x = rando();
			r.y = rando();
			r.z = rando();
			ray.origin = ray_vec(hit->p, 0.0001f, hit->normal);
			ray.direction = reflect_vec(ray.direction, add_vec(hit->normal, multi_vec_wnbr(r, data->set.sp[hit->i].material)));
		}
		else
		{
			hit->color = add_vec(hit->color, multi_vec_wnbr(data->bg, multi));
			break ;
		}
	}
}

float	rando(void)
{
	float	nbr;

	nbr = (float)rand() / (float)RAND_MAX;
	nbr = (nbr * 1.0f) - 0.5f;
	return (nbr);
}
