/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:23:54 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/25 11:35:52 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_m_cn(t_cone *cn)
{
	float	angle_x;
	float	angle_z;
	float	t[4][4];
	float	full_r[4][4];

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle(cn->norm, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	cn->norm = norm_vec(cn->norm);
	translation(t, multi_vec_wnbr(cn->coords, -1.0));
	multi_m(cn->side.m, full_r, t);
	invert_matrix(cn->side.m, cn->side.mi);
	translation(t, multi_vec_wnbr(
			ray_vec(cn->coords, -cn->height, cn->norm), -1.0));
	multi_m(cn->bottom.m, full_r, t);
	invert_matrix(cn->bottom.m, cn->bottom.mi);
}

void	get_color_and_normal_cn(t_data *data,
	t_cone cn, t_hitpoint *hit, t_vec3 tmp)
{
	t_vec3	uv;
	xpm_t	*map;

	if (cn.texture)
		map = cn.texture;
	else if (cn.bump_map)
		map = cn.bump_map;
	else
		map = NULL;
	if (map || data->checker)
		uv = get_uv_coords_cn(data, cn, map, tmp);
	if (cn.texture || data->checker)
	{
		if (data->checker)
			get_checkerboard_color(uv.x, uv.y, hit);
		else
			hit->obj_color = get_map_color(uv.x, uv.y, cn.texture);
	}
	else
		hit->obj_color = cn.color;
	if (cn.bump_map)
		get_map_normal(hit, &uv, cn.bump_map);
}

void	get_color_and_normal_tb_cn(t_data *data,
	t_cone cn, t_hitpoint *hit, t_vec3 tmp)
{
	t_vec3	uv;
	xpm_t	*map;

	if (cn.texture)
		map = cn.texture;
	else if (cn.bump_map)
		map = cn.bump_map;
	else
		map = NULL;
	if (map || data->checker)
		uv = get_uv_coords_tb(data, cn.radius, map, tmp);
	if (cn.texture || data->checker)
	{
		if (data->checker)
			get_checkerboard_color(uv.x, uv.y, hit);
		else
			hit->obj_color = get_map_color(uv.x, uv.y, cn.texture);
	}
	else
		hit->obj_color = cn.color;
	if (cn.bump_map)
		get_map_normal(hit, &uv, cn.bump_map);
}
