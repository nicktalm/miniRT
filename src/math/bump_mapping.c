/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:52:10 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/15 11:01:15 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_checkerboard_color(float u, float v, t_hitpoint *hit)
{
	t_vec3	color1 = {1.0, 1.0, 1.0};
	t_vec3	color2 = {0.0, 0.0, 0.0};
	float	scaled_u;
	float	scaled_v;
	int		tile_count;
	int		u_tile;
	int		v_tile;

	tile_count = 20;
	scaled_u = u * tile_count;
	scaled_v = v * tile_count;
	u_tile = (int)floor(scaled_u);
	v_tile = (int)floor(scaled_v);
	if ((u_tile + v_tile) % 2 == 0)
		hit->obj_color = color2;
	else
		hit->obj_color = color1;
}

t_vec3	get_map_color(float u, float v, xpm_t *map)
{
	t_vec3	color;
	int		index;

	index = ((int)v * map->texture.width + (int)u) * 4;
	color.x = map->texture.pixels[index] / 255.0;
	color.y = map->texture.pixels[index + 1] / 255.0;
	color.z = map->texture.pixels[index + 2] / 255.0;
	return (color);
}

t_vec3	get_tangent(t_vec3 normal)
{
	t_vec3	up = {0, 1, 0};
	t_vec3	right = {1, 0, 0};
	t_vec3	into = {0, 0, 1};

	if (dot(normal, up) != 1)
		return (up);
	else if (dot(normal, right) != 1)
		return (right);
	return (into);
}

void	get_map_normal(t_hitpoint *hit, t_vec3 *uv, xpm_t *bump_map)
{
	t_vec3	deltau;
	t_vec3	deltav;
	t_vec3	tangent;
	t_vec3	bitangent;

	deltau = dev_vec_wnbr(sub_vec(
				get_map_color(uv->x + 4, uv->y, bump_map),
				get_map_color(uv->x, uv->y, bump_map)), 4.0);
	deltav = dev_vec_wnbr(sub_vec(
				get_map_color(uv->x, uv->y + 4, bump_map),
				get_map_color(uv->x, uv->y, bump_map)), 4.0);
	tangent = get_tangent(hit->normal);
	tangent = cross_vec(hit->normal, tangent);
	bitangent = cross_vec(hit->normal, tangent);
	hit->normal = norm_vec(add_vec_wnbr(
				add_vec_wnbr(hit->normal, dot(deltau, tangent)),
				dot(deltav, bitangent)));
}
