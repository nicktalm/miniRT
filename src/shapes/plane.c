/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:51:07 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 20:16:38 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	calc_pl(t_data *data, t_plane pl, t_ray ray, t_hitpoint *hit)
{
	ray.origin = con_to_vec3(
			r_vec(pl.side.m, con_to_vec4(ray.origin, 1)));
	ray.direction = con_to_vec3(
			r_vec(pl.side.m, con_to_vec4(ray.direction, 0)));
	if (pl.width == 0.0 && pl.length == 0.0)
	{
		if (test_inf_pl(pl, ray, hit))
			return (true);
	}
	else
	{
		if (test_bounded_pl(data, pl, ray, hit))
			return (true);
	}
	return (false);
}

bool	test_inf_pl(t_plane pl, t_ray ray, t_hitpoint *hit)
{
	float	t;
	t_vec3	tmp;
	t_vec3	dir;

	dir.x = 0.0;
	dir.y = 1.0;
	dir.z = 0.0;
	t = 0.0;
	t = -dot(dir, ray.origin) / dot(dir, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		tmp = ray_vec(ray.origin, t, ray.direction);
		hit->p = con_to_vec3(r_vec(pl.side.mi, con_to_vec4(tmp, 1)));
		hit->normal = pl.norm;
		hit->t = t;
		hit->obj_color = pl.color;
		return (true);
	}
	return (false);
}

bool	test_bounded_pl(t_data *data, t_plane pl, t_ray ray, t_hitpoint *hit)
{
	float	t;
	t_vec3	tmp;
	t_vec3	dir;

	dir.x = 0.0;
	dir.y = 1.0;
	dir.z = 0.0;
	t = 0.0;
	t = -dot(dir, ray.origin) / dot(dir, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		tmp = ray_vec(ray.origin, t, ray.direction);
		if (tmp.x <= pl.width / 2.0 && tmp.x >= pl.width / -2.0
			&& tmp.z <= pl.length / 2.0 && tmp.z >= pl.length / -2.0)
		{
			hit->p = con_to_vec3(r_vec(pl.side.mi, con_to_vec4(tmp, 1)));
			hit->normal = pl.norm;
			hit->t = t;
			get_color_and_normal_pl(data, pl, hit, tmp);
			return (true);
		}
	}
	return (false);
}

void	create_m_pl(t_plane *pl)
{
	float	angle_x;
	float	angle_z;
	float	t[4][4];
	float	full_r[4][4];

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle(pl->norm, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	translation(t, multi_vec_wnbr(pl->coords, -1.0));
	multi_m(pl->side.m, full_r, t);
	invert_matrix(pl->side.m, pl->side.mi);
}

void	get_color_and_normal_pl(t_data *data, t_plane pl,
	t_hitpoint *hit, t_vec3 tmp)
{
	t_vec3	uv;
	xpm_t	*map;

	if (pl.texture)
		map = pl.texture;
	else if (pl.bump_map)
		map = pl.bump_map;
	else
		map = NULL;
	if (map || data->checker)
		uv = get_uv_coords_pl(data, pl, map, tmp);
	if (pl.texture || data->checker)
	{
		if (data->checker)
			get_checkerboard_color(uv.x, uv.y, hit);
		else
			hit->obj_color = get_map_color(uv.x, uv.y, pl.texture);
	}
	else
		hit->obj_color = pl.color;
	if (pl.bump_map)
		get_map_normal(hit, &uv, pl.bump_map);
}
