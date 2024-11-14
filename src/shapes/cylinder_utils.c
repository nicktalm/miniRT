/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/14 21:03:19 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_m_cy(t_cylinder *cy)
{
	float	angle_x;
	float	angle_z;
	float	t[4][4];
	float	full_r[4][4];

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle(cy->norm, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	cy->norm = norm_vec(cy->norm);
	translation(t, multi_vec_wnbr(cy->coords, -1.0));
	multi_m(cy->side.m, full_r, t);
	invert_matrix(cy->side.m, cy->side.mi);
	translation(t, multi_vec_wnbr(
			ray_vec(cy->coords, cy->height / 2.0, cy->norm), -1.0));
	multi_m(cy->top.m, full_r, t);
	invert_matrix(cy->top.m, cy->top.mi);
	translation(t, multi_vec_wnbr(
			ray_vec(cy->coords, cy->height / -2.0, cy->norm), -1.0));
	multi_m(cy->bottom.m, full_r, t);
	invert_matrix(cy->bottom.m, cy->bottom.mi);
}

void	get_color_and_normal_cy(t_cylinder cy, t_hitpoint *hit, t_vec3 tmp, int i)
{
	int		index;
	t_vec3	uv;
	xpm_t	*map;

	if (cy.texture)
		map = cy.texture;
	else if (cy.bump_map)
		map = cy.bump_map;
	else
		map = NULL;
	if (map)
	{
		if (i == 0)
			get_uv_coords_cy(cy, map, tmp, &uv);
		else
			get_uv_coords_tb(cy.radius, map, tmp, &uv);
		index = ((int)uv.y * map->texture.width + (int)uv.x) * 4;
	}
	if (cy.texture)
	{
		// get_checkerboard_color(uv.x, uv.y, hit);
		hit->obj_color.x = map->texture.pixels[index] / 255.0;
		hit->obj_color.y = map->texture.pixels[index + 1] / 255.0;
		hit->obj_color.z = map->texture.pixels[index + 2] / 255.0;
	}
	else
		hit->obj_color = cy.color;
	if (cy.bump_map)
	{
		printf("bump_map\n");
	}
}

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
