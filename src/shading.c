/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:09:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/30 17:44:08 by lbohm            ###   ########.fr       */
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
	len = fabsf(leangth_vec(light.coords, hit->p));
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

void	get_color(t_data *data, t_ray *ray, t_hitpoint *hit)
{
	t_hitpoint	hitb;
	int			i;
	int			end;
	float		distanz;

	i = 0;
	if (data->set.light[0].brightness > 0.0)
		end = 2;
	else
		end = 1;
	while (i++ < 2)
	{
		check_hit(ray, hit, data);
		if (hit->t != __FLT_MAX__)
		{
			if (i == 1)
			{
				distanz = fabsf(leangth_vec(hit->p, data->set.light[0].coords));
				hitb = *hit;
			}
			else
			{
				if (distanz < fabsf(leangth_vec(hitb.p, hit->p)))
					return ;
				hit->i = hitb.i;
			}
			if (data->set.obj[hit->i].type == PLANE)
				shading(data, hit, data->set.obj[hit->i].form.pl.color, ray);
			else if (data->set.obj[hit->i].type == SPHERE)
				shading(data, hit, data->set.obj[hit->i].form.sp.color, ray);
			else
			{
				// hit->color = data->set.obj[hit->i].form.cy.color;
				shading(data, hit, data->set.obj[hit->i].form.cy.color, ray);
			}
		}
		else
		{
			if (i == 1)
				hit->color = data->bg;
			return ;
		}
	}
}
