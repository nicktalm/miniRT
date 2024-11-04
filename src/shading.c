/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:09:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/04 15:13:05 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	shading(t_data *data, t_hitpoint *hit, t_vec3 color, t_ray *ray)
{
	t_lighting	nlight;
	t_vec3		intensity;	
	t_vec3		ambient;
	t_vec3		totall_light;

	intensity = calc_light_intensity(data->set.light[0], hit, &nlight);
	ambient = multi_vec_wnbr(data->set.ambient.color, data->set.ambient.ratio);
	totall_light = add_vec(multi_vec_wnbr(intensity, 0.18 / M_PI), ambient);
	hit->color = multi_vec(totall_light, color);
	ray->origin = ray_vec(hit->p, 0.01, hit->normal);
	ray->direction = nlight.light_dir;
}

t_vec3	calc_light_intensity(t_light light, t_hitpoint *hit, t_lighting *nlight)
{
	float		len;
	t_vec3		intensity;

	nlight->light_dir = sub_vec(light.coords, hit->p);
	len = fabsf(leangth_vec(nlight->light_dir));
	nlight->light_dir = norm_vec(nlight->light_dir);
	nlight->diffuse_strength = dot(hit->normal, nlight->light_dir);
	if (nlight->diffuse_strength < 0.0)
		nlight->diffuse_strength = 0.0;
	nlight->light = multi_vec_wnbr(light.color, nlight->diffuse_strength);
	intensity = dev_vec_wnbr(multi_vec_wnbr(nlight->light,
				10000 * light.brightness),
			4.0 * M_PI * pow(len, 2.0));
	return (intensity);
}

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
			if (data->set.obj[hit->i].type == PLANE)
				shading(data, hit, data->set.obj[hit->i].form.pl.color, ray);
			else if (data->set.obj[hit->i].type == SPHERE)
				shading(data, hit, data->set.obj[hit->i].form.sp.color, ray);
			else
				shading(data, hit, data->set.obj[hit->i].form.cy.color, ray);
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
	if (i == 1)
	{
		hit->distanz = leangth_vec(sub_vec(hit->p, data->set.light[0].coords));
		hit->ib = hit->i;
		hit->pb = hit->p;
	}
	else
	{
		if (hit->distanz < leangth_vec(sub_vec(hit->pb, hit->p))
			|| hit->i == hit->ib)
			return (false);
		hit->i = hit->ib;
	}
	return (true);
}
