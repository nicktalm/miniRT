/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:52:10 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/22 10:46:41 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_checkerboard_color(float u, float v, t_hitpoint *hit)
{
	t_vec3	color1;
	t_vec3	color2;
	int		u_tile;
	int		v_tile;

	color1.x = 1.0;
	color1.y = 1.0;
	color1.z = 1.0;
	color2.x = 0.0;
	color2.y = 0.0;
	color2.z = 0.0;
	u = u * 20;
	v = v * 20;
	u_tile = (int)floor(u);
	v_tile = (int)floor(v);
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
	t_vec3	up;
	t_vec3	right;
	t_vec3	tangent;

	up.x = 0.0;
	up.y = 1.0;
	up.z = 0.0;
	right.x = 1.0;
	right.y = 0.0;
	right.z = 0.0;
	if (fabs(normal.y) > 0.99)
		up = right;
	tangent = cross_vec(normal, up);
	return (norm_vec(tangent));
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
