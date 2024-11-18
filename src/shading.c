/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:09:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/18 15:35:53 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	obj_shading(t_data *data, t_hitpoint *hit, t_ray *ray, t_light light)
{
	t_lighting	in;
	t_vec3		lighting;

	in.light_dir = sub_vec(light.coords, hit->p);
	in.len = leangth_vec(in.light_dir);
	in.light_dir = norm_vec(in.light_dir);
	in.ambient = multi_vec_wnbr(data->set.ambient.color, data->set.ambient.ratio);
	diffuse_light(&in, light, hit);
	specular_light(&in, light, data->set.cam, hit);
	lighting = add_vec(add_vec(in.ambient,
		multi_vec_wnbr(in.diffuse, light.brightness)),
		multi_vec_wnbr(in.specular, light.brightness));
	hit->color = multi_vec(hit->obj_color, lighting);
	ray->origin = ray_vec(hit->p, 0.01, hit->normal);
	ray->direction = in.light_dir;
}

void	shading(t_data *data, t_hitpoint *hit, t_light light)
{
	t_lighting	in;
	t_vec3		lighting;

	in.light_dir = norm_vec(sub_vec(light.coords, hit->p));
	in.ambient = multi_vec_wnbr(data->set.ambient.color, data->set.ambient.ratio);
	diffuse_light(&in, light, hit);
	lighting = add_vec(in.ambient,
		multi_vec_wnbr(in.diffuse, light.brightness));
	hit->color = multi_vec(hit->obj_color, lighting);
}

void	diffuse_light(t_lighting *in, t_light light, t_hitpoint *hit)
{
	float	strength;

	strength = dot(hit->normal, in->light_dir);
	if (strength < 0.0)
		strength = 0.0;
	in->diffuse = multi_vec_wnbr(light.color, strength);
	// in->diffuse = dev_vec_wnbr(in->diffuse, 4.0 * M_PI * pow(in->len, 2.0));
}

void	specular_light(t_lighting *in,
			t_light light, t_camera cam, t_hitpoint *hit)
{
	t_vec3	reflect;
	t_vec3	view_dir;
	float	strength;

	reflect = norm_vec(reflect_light(in->light_dir, hit->normal));
	view_dir = norm_vec(sub_vec(light.coords, cam.coords));
	strength = dot(reflect, view_dir);
	if (strength < 0.0)
		strength = 0.0;
	strength = pow(strength, 32.0);
	in->specular = multi_vec_wnbr(light.color, strength);
	// in->specular = dev_vec_wnbr(in->specular, 4.0 * M_PI * pow(in->len, 2.0));
}

t_vec3	reflect_light(t_vec3 light_dir, t_vec3 normal)
{
	t_vec3	reflect;

	reflect = sub_vec(light_dir, multi_vec_wnbr(normal,
				2.0 * dot(light_dir, normal)));
	return (reflect);
}

void	get_color(t_data *data, t_ray *ray, t_hitpoint *hit)
{
	int		i;
	int		pos;
	t_vec3	full_color = {0, 0, 0};
	t_ray	first;

	first = *ray;
	i = 0;
	pos = 0;
	while (pos < data->set.light_count)
	{
		*ray = first;
		i = 0;
		while (i < data->set.light[pos].end)
		{
			check_hit(ray, hit, data);
			if (hit->t != __FLT_MAX__)
			{
				if (!get_distanz(hit, data->set.light[pos], i))
					break ;
				if (i == 0)
					obj_shading(data, hit, ray, data->set.light[pos]);
				else
					shading(data, hit, data->set.light[pos]);
			}
			else
			{
				if (i == 0)
				{
					hit->color = data->bg;
					return ;
				}
				break ;
			}
			i++;
		}
		full_color = add_vec(full_color, hit->color);
		pos++;
	}
	hit->color = full_color;
}

bool	get_distanz(t_hitpoint *hit, t_light light, int i)
{
	static int		distanz = 0;
	static t_vec3	color;
	static int		ib = 0;
	static t_vec3	pb = {0, 0, 0};

	if (i == 0)
	{
		distanz = leangth_vec(sub_vec(hit->p, light.coords));
		pb = hit->p;
		color = hit->obj_color;
		ib = hit->i;
	}
	else
	{
		if (distanz < leangth_vec(sub_vec(pb, hit->p))
			|| hit->i == ib)
			return (false);
		hit->obj_color = color;
		hit->i = ib;
	}
	return (true);
}
