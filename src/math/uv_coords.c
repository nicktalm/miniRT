/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_coords.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:51:19 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/14 12:56:52 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_uv_coords_sp(xpm_t *map, t_hitpoint *hit, t_vec3 *uv)
{
	float	phi;
	float	theta;
	int		index;

	theta = acosf(hit->normal.y);
	phi = atan2f(hit->normal.z, hit->normal.x);
	uv->x = (phi + M_PI) / (2 * M_PI) * (map->texture.width - 1);
	uv->y = (theta / M_PI) * (map->texture.height - 1);
}

void	get_uv_coords_pl(t_plane pl, xpm_t *map, t_vec3 tmp, t_vec3 *uv)
{
	int		index;

	tmp.x = tmp.x / pl.width / 2.0;
	tmp.y = tmp.y / pl.length / 2.0;
	tmp.x = (tmp.x + 1) / 2.0;
	tmp.y = (tmp.y + 1) / 2.0;
	uv->x = tmp.x * map->texture.width;
	uv->y = tmp.y * map->texture.height;
}

void	get_uv_coords_cy()
{
	
}

void	get_uv_coords_cn()
{
	
}
