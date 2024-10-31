/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:51:07 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/31 15:29:24 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i)
{
	float	t;

	t = 0.0;
	t = -dot(pl.norm, sub_vec(ray.origin, pl.coords)) \
			/ dot(pl.norm, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		hit->i = i;
		hit->t = t;
		hit->normal = pl.norm;
		hit->p = ray_vec(ray.origin, t, ray.direction);
	}
}
