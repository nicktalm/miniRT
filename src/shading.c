/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:09:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/25 15:44:47 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// t_ray	shading(t_data *data, t_hitpoint *hit, t_vec3 color, int i)
// {
// 	t_lighting	nlight;
// 	t_ray		new;

// 	nlight.light = multi_vec_wnbr(data->set.light[0].color, data->set.light[0].brightness);
// 	nlight.light_dir = norm_vec(sub_vec(data->set.light[0].coords, hit->p));
// 	nlight.diffuse_strength = dot(hit->normal, nlight.light_dir);
// 	nlight.diffuse_strength < 0.0 ? nlight.diffuse_strength = 0.0 : nlight.diffuse_strength;
// 	nlight.diffuse = multi_vec_wnbr(nlight.light, nlight.diffuse_strength);
// 	hit->color = multi_vec(add_vec(nlight.light, nlight.diffuse), color);
// 	new.origin = ray_vec(hit->p, 0.01, hit->normal);
// 	new.direction = nlight.light_dir;
// 	return (new);
// }

t_ray	shading(t_data *data, t_hitpoint *hit, t_vec3 color, int i)
{
	t_lighting	nlight;
	t_ray		new;
	float		len;

	nlight.light_dir = sub_vec(data->set.light[0].coords, hit->p);
	len = leangth_vec(data->set.light[0].coords, hit->p);
	nlight.light_dir = norm_vec(nlight.light_dir);
	nlight.diffuse_strength = dot(hit->normal, nlight.light_dir);
	nlight.light = multi_vec_wnbr(data->set.light[0].color, nlight.diffuse_strength);
	nlight.diffuse_strength < 0.0 ? nlight.diffuse_strength = 0.0 : nlight.diffuse_strength;
	hit->color = multi_vec(dev_vec_wnbr(multi_vec_wnbr(multi_vec(data->set.light[0].color, nlight.light), (0.18 / M_PI) * 10000 * data->set.light[0].brightness), 4.0 * M_PI * pow(len, 2.0)), color);
	new.origin = ray_vec(hit->p, 0.01, hit->normal);
	new.direction = nlight.light_dir;
	return (new);
}
