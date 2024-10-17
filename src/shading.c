/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:09:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/17 17:04:26 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	shading(t_data *data, t_hitpoint *hit, t_vec3 color, int i)
{
	t_lighting	nlight;

	nlight.light = multi_vec_wnbr(data->set.light[0].color, data->set.light[0].brightness);
	nlight.light_dir = norm_vec(sub_vec(data->set.light[0].coords, hit->p));
	if (i == 2)
	{
		// printf("light dir x = %f y = %f z = %f\n", nlight.light_dir.x, nlight.light_dir.y, nlight.light_dir.z);
		// printf("hit normal x = %f y = %f z = %f\n", hit->normal.x, hit->normal.y, hit->normal.z);
	}
	else if (i > 0)
		nlight.light_dir.z *= -1.0;
	nlight.diffuse_strength = dot(hit->normal, nlight.light_dir);
	nlight.diffuse_strength < 0.0 ? nlight.diffuse_strength = 0 : nlight.diffuse_strength;
	nlight.diffuse = multi_vec_wnbr(data->set.light[0].color, nlight.diffuse_strength);
	hit->color = multi_vec(add_vec(nlight.light, nlight.diffuse), color);
}
