/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 21:02:24 by lbohm            ###   ########.fr       */
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

void	get_color_and_normal_cy(t_data *data,
			t_cylinder cy, t_hitpoint *hit, int i)
{
	t_vec3	uv;
	xpm_t	*map;

	map = find_map(cy);
	if (map || data->checker)
	{
		if (i == 0)
			uv = get_uv_coords_cy(data, cy, map, hit->p);
		else
			uv = get_uv_coords_tb(data, cy.radius, map, hit->p);
	}
	if (cy.texture || data->checker)
	{
		if (data->checker)
			get_checkerboard_color(uv.x, uv.y, hit);
		else
			hit->obj_color = get_map_color(uv.x, uv.y, cy.texture);
	}
	else
		hit->obj_color = cy.color;
	if (cy.bump_map)
		get_map_normal(hit, &uv, cy.bump_map);
}

xpm_t	*find_map(t_cylinder cy)
{
	if (cy.texture)
		return (cy.texture);
	else if (cy.bump_map)
		return (cy.bump_map);
	return (NULL);
}
