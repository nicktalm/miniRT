/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:09:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/28 14:59:24 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	shading(t_data *data, t_hitpoint *hit, t_vec3 color, t_ray *ray)
{
	t_lighting	nlight;
	t_vec3		intensity;

	intensity = calc_light_intensity(data->set.light[0], hit, &nlight);
	hit->color = multi_vec(add_vec(multi_vec_wnbr(intensity, 0.18 / M_PI), multi_vec_wnbr(data->set.ambient.color, data->set.ambient.ratio)), color);
	ray->origin = ray_vec(hit->p, 0.01, hit->normal);
	ray->direction = nlight.light_dir;
}

t_vec3	calc_light_intensity(t_light light, t_hitpoint *hit, t_lighting *nlight)
{
	float		len;
	t_vec3		intensity;

	nlight->light_dir = sub_vec(light.coords, hit->p);
	len = leangth_vec(light.coords, hit->p);
	nlight->light_dir = norm_vec(nlight->light_dir);
	nlight->light_dir = norm_vec(nlight->light_dir);
	nlight->diffuse_strength = dot(hit->normal, nlight->light_dir);
	nlight->light = multi_vec_wnbr(light.color, nlight->diffuse_strength);
	if (nlight->diffuse_strength < 0.0)
		nlight->diffuse_strength = 0.0;
	intensity = dev_vec_wnbr(multi_vec_wnbr(nlight->light,
				10000 * light.brightness),
			4.0 * M_PI * pow(len, 2.0));
	return (intensity);
}
