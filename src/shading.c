/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:09:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/25 13:35:31 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	obj_shading(t_data *data, t_hitpoint *hit, t_ray *ray, t_light light)
{
	t_lighting	in;
	t_vec3		lighting;

	in.light_dir = norm_vec(sub_vec(light.coords, hit->p));
	in.ambient = multi_vec_wnbr(data->set.ambient.color,
			data->set.ambient.ratio);
	diffuse_light(&in, light, hit);
	specular_light(&in, light, data->set.cam, hit);
	lighting = add_vec(in.ambient,
			add_vec(multi_vec_wnbr(in.diffuse, light.brightness),
				multi_vec_wnbr(in.specular, light.brightness)));
	hit->color = multi_vec(hit->obj_color, lighting);
	ray->origin = ray_vec(hit->p, 0.01, hit->normal);
	ray->direction = in.light_dir;
}

void	shading(t_data *data, t_hitpoint *hit, t_light light)
{
	t_lighting	in;
	t_vec3		lighting;

	in.light_dir = norm_vec(sub_vec(light.coords, hit->p));
	in.ambient = multi_vec_wnbr(data->set.ambient.color,
			data->set.ambient.ratio);
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
}

void	specular_light(t_lighting *in,
			t_light light, t_camera cam, t_hitpoint *hit)
{
	t_vec3	reflect;
	t_vec3	view_dir;
	float	strength;

	reflect = norm_vec(reflect_light(in->light_dir, hit->normal));
	view_dir = norm_vec(sub_vec(hit->p, cam.coords));
	strength = dot(reflect, view_dir);
	if (strength < 0.0)
		strength = 0.0;
	strength = pow(strength, 5.0);
	in->specular = multi_vec_wnbr(light.color, strength);
}

t_vec3	reflect_light(t_vec3 light_dir, t_vec3 normal)
{
	t_vec3	reflect;

	reflect = sub_vec(light_dir, multi_vec_wnbr(normal,
				2.0 * dot(light_dir, normal)));
	return (reflect);
}
