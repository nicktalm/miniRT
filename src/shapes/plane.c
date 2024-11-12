/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:51:07 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/12 12:44:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_bump_map_coords_pl(xpm_t *map, t_hitpoint *hit, t_ray ray);

void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i)
{
	float	t;
	t_vec3	tmp;
	t_vec3	dir;

	dir.x = 0.0;
	dir.y = 1.0;
	dir.z = 0.0;
	ray.origin = convert_to_vec3(r_vec(pl.side.m, convert_to_vec4(ray.origin, 1)));
	ray.direction = convert_to_vec3(r_vec(pl.side.m, convert_to_vec4(ray.direction, 0)));
	t = 0.0;
	t = -dot(dir, ray.origin) / dot(dir, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		tmp = ray_vec(ray.origin, t, ray.direction);
		hit->p = convert_to_vec3(r_vec(pl.side.mi, convert_to_vec4(tmp, 1)));
		hit->normal = pl.norm;
		hit->t = t;
		if (pl.bump_map)
			get_bump_map_coords_pl(pl.bump_map, hit, ray);
		hit->obj_color = pl.color;
		hit->i = i;
	}
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

void	get_bump_map_coords_pl(xpm_t *map, t_hitpoint *hit, t_ray ray)
{
	t_vec3	normal_hit;
	float	x;
	float	y;
	int		u;
	int		v;

	normal_hit = norm_vec(hit->p);
	x = (normal_hit.x + 1) / 2;
	y = (normal_hit.y + 1) / 2;
	u = x * (map->texture.width - 1);
}
