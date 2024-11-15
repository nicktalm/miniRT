/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_coords.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:51:19 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/15 12:14:38 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_uv_coords_sp(t_data *data, xpm_t *map, t_vec3 *uv, t_vec3 tmp)
{
	tmp = norm_vec(tmp);
	uv->x = atan2f(tmp.z, tmp.x) / (2 * M_PI) + 0.5;
	uv->y = tmp.y * 0.5 + 0.5;
	if (!data->checker)
	{
		uv->x = uv->x * (map->texture.width - 1);
		uv->y = (map->texture.height - 1) - (uv->y * (map->texture.height - 1));
	}
}

void	get_uv_coords_pl(t_data *data, t_plane pl, xpm_t *map, t_vec3 tmp, t_vec3 *uv)
{
	uv->x = tmp.x / (pl.width / 2.0);
	uv->y = tmp.z / (pl.length / 2.0);
	uv->x = (uv->x + 1) / 2.0;
	uv->y = (uv->y + 1) / 2.0;
	if (!data->checker)
	{
		uv->x = uv->x * (map->texture.width - 1);
		uv->y = uv->y * (map->texture.height - 1);
	}
}

void	get_uv_coords_cy(t_cylinder cy, xpm_t *map, t_vec3 tmp, t_vec3 *uv)
{
	tmp.x /= cy.radius;
	tmp.z /= cy.radius;
	tmp.y /= cy.height;
	uv->x = atan2f(tmp.z, tmp.x) / (2.0 * M_PI) + 0.5;
	uv->y = tmp.y * 0.5 + 0.5;
	uv->x *= (map->texture.width - 1);
	uv->y *= (map->texture.height - 1);
}

void	get_uv_coords_tb(float radius, xpm_t *map, t_vec3 tmp, t_vec3 *uv)
{
	uv->x = tmp.x / radius;
	uv->y = tmp.z / radius;
	uv->x = (uv->x + 1) / 2.0;
	uv->y = (uv->y + 1) / 2.0;
	uv->x = uv->x * (map->texture.width - 1);
	uv->y = uv->y * (map->texture.height - 1);
}

void	get_uv_coords_cn(t_cone cn, xpm_t *map, t_vec3 tmp, t_vec3 *uv)
{
	tmp.x /= cn.radius;
	tmp.z /= cn.radius;
	tmp.y /= cn.height;
	uv->x = atan2f(tmp.z, tmp.x) / (2.0 * M_PI) + 0.5;
	uv->y = tmp.y * 0.5 + 0.5;
	uv->x *= (map->texture.width - 1);
	uv->y *= (map->texture.height - 1);
}
