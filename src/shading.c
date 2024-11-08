/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:09:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/08 15:51:18 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	shading(t_data *data, t_hitpoint *hit, t_ray *ray)
{
	t_lighting	in;
	t_vec3		lighting;

	in.light_dir = norm_vec(sub_vec(data->set.light[0].coords, hit->p));
	in.ambient = data->set.ambient.color;
	diffuse_light(&in, data->set.light[0], hit);
	specular_light(&in, data->set.light[0], data->set.cam, hit);
	lighting = add_vec(add_vec(multi_vec_wnbr(in.ambient, data->set.ambient.ratio), multi_vec_wnbr(in.diffuse, data->set.light->brightness)), multi_vec_wnbr(in.specular, data->set.light->brightness));
	hit->color = multi_vec(hit->obj_color, lighting);
	ray->origin = ray_vec(hit->p, 0.01, hit->normal);
	ray->direction = in.light_dir;
}

void	diffuse_light(t_lighting *in, t_light light, t_hitpoint *hit)
{
	float	strength;

	strength = dot(hit->normal, in->light_dir);
	if (strength < 0.0)
		strength = 0.0;
	in->diffuse = multi_vec_wnbr(light.color, strength);
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
}

t_vec3	reflect_light(t_vec3 light_dir, t_vec3 normal)
{
	t_vec3	reflect;

	reflect = sub_vec(light_dir, multi_vec_wnbr(normal,
				2.0 * dot(light_dir, normal)));
	return (reflect);
}

// void	shading(t_data *data, t_hitpoint *hit, t_vec3 color, t_ray *ray)
// {
// 	t_lighting	nlight;
// 	t_vec3		intensity;	
// 	t_vec3		ambient;
// 	t_vec3		totall_light;

// 	intensity = calc_light_intensity(data->set.light[0], hit, &nlight);
// 	ambient = multi_vec_wnbr(data->set.ambient.color, data->set.ambient.ratio);
// 	totall_light = add_vec(multi_vec_wnbr(intensity, 0.18 / M_PI), ambient);
// 	hit->color = multi_vec(totall_light, color);
// 	ray->origin = ray_vec(hit->p, 0.01, hit->normal);
// 	ray->direction = nlight.light_dir;
// }

// t_vec3	calc_light_intensity(t_light light, t_hitpoint *hit, t_lighting *nlight)
// {
// 	float		len;
// 	t_vec3		intensity;

// 	nlight->light_dir = sub_vec(light.coords, hit->p);
// 	len = fabsf(leangth_vec(nlight->light_dir));
// 	nlight->light_dir = norm_vec(nlight->light_dir);
// 	nlight->diffuse_strength = dot(hit->normal, nlight->light_dir);
// 	if (nlight->diffuse_strength < 0.0)
// 		nlight->diffuse_strength = 0.0;
// 	nlight->light = multi_vec_wnbr(light.color, nlight->diffuse_strength);
// 	intensity = dev_vec_wnbr(multi_vec_wnbr(nlight->light,
// 				10000 * light.brightness),
// 			4.0 * M_PI * pow(len, 2.0));
// 	return (intensity);
// }

void	get_color(t_data *data, t_ray *ray, t_hitpoint *hit)
{
	int	i;

	i = 0;
	while (i++ < data->set.light[0].end)
	{
		check_hit(ray, hit, data);
		if (hit->t != __FLT_MAX__)
		{
			if (!get_distanz(data, hit, i))
				return ;
			shading(data, hit, ray);
		}
		else
		{
			if (i == 1)
				hit->color = data->bg;
			return ;
		}
	}
}

bool	get_distanz(t_data *data, t_hitpoint *hit, int i)
{
	static int		distanz = 0;
	static t_vec3	color;
	static int		ib = 0;
	static t_vec3	pb = {0, 0, 0};

	if (i == 1)
	{
		distanz = leangth_vec(sub_vec(hit->p, data->set.light[0].coords));
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
