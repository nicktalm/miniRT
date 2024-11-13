/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:51:07 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/13 17:58:10 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	test_inf_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i);
void	test_bounded_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i);
void	get_texture_color_pl(xpm_t *map, t_hitpoint *hit, t_plane pl, t_vec3 tmp);

void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i)
{
	ray.origin = convert_to_vec3(
			r_vec(pl.side.m, convert_to_vec4(ray.origin, 1)));
	ray.direction = convert_to_vec3(
			r_vec(pl.side.m, convert_to_vec4(ray.direction, 0)));
	if (pl.width == 0.0 && pl.length == 0.0)
		test_inf_pl(pl, ray, hit, i);
	else
		test_bounded_pl(pl, ray, hit, i);
}

void	test_inf_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i)
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
		hit->p = convert_to_vec3(r_vec(pl.side.mi, convert_to_vec4(tmp, 1)));
		hit->normal = pl.norm;
		hit->t = t;
		hit->i = i;
		hit->obj_color = pl.color;
	}
}

void	test_bounded_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i)
{
	float	t;
	t_vec3	tmp;
	t_vec3	dir;
	t_vec3	uv;
	t_vec3	right;
	t_vec3	into;

	dir.x = 0.0;
	dir.y = 1.0;
	dir.z = 0.0;
	right.x = 1.0;
	right.y = 0.0;
	right.z = 0.0;
	into.x = 0.0;
	into.y = 0.0;
	into.z = 1.0;
	t = 0.0;
	t = -dot(dir, ray.origin) / dot(dir, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		tmp = ray_vec(ray.origin, t, ray.direction);
		uv.x = dot(tmp, right);
		uv.y = dot(tmp, into);
		if (uv.x <= pl.width / 2.0 && uv.x >= pl.width / -2.0 && uv.y <= pl.length / 2.0 && uv.y >= pl.length / -2.0)
		{
			hit->p = convert_to_vec3(r_vec(pl.side.mi, convert_to_vec4(tmp, 1)));
			hit->normal = pl.norm;
			hit->t = t;
			hit->i = i;
			if (pl.texture)
				get_texture_color_pl(pl.texture, hit, pl, uv);
			else
				hit->obj_color = pl.color;
		}
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

void	get_texture_color_pl(xpm_t *map, t_hitpoint *hit, t_plane pl, t_vec3 tmp)
{
	float	u;
	float	v;
	int		index;

	tmp.x = tmp.x / pl.width / 2.0;
	tmp.y = tmp.y / pl.length / 2.0;
	tmp.x = (tmp.x + 1) / 2.0;
	tmp.y = (tmp.y + 1) / 2.0;
	u = tmp.x * map->texture.width;
	v = tmp.y * map->texture.height;
	index = ((int)v * map->texture.width + (int)u) * 4;
	hit->obj_color.x = map->texture.pixels[index] / 255.0;
	hit->obj_color.y = map->texture.pixels[index + 1] / 255.0;
	hit->obj_color.z = map->texture.pixels[index + 2] / 255.0;
}
