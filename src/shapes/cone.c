/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:41:35 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/14 21:07:20 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_cn(t_cone cn, t_ray ray, t_hitpoint *hit, int i)
{
	t_ray	test;

	test.origin = con_to_vec3(
			r_vec(cn.bottom.m, con_to_vec4(ray.origin, 1)));
	test.direction = con_to_vec3(
			r_vec(cn.bottom.m, con_to_vec4(ray.direction, 0)));
	if (test_bottom_cn(cn, hit, test))
		hit->i = i;
	test.origin = con_to_vec3(
			r_vec(cn.side.m, con_to_vec4(ray.origin, 1)));
	test.direction = con_to_vec3(
			r_vec(cn.side.m, con_to_vec4(ray.direction, 0)));
	if (test_side_cn(cn, test, hit))
		hit->i = i;
}

bool	test_side_cn(t_cone cn, t_ray ray, t_hitpoint *hit)
{
	t_abc	formal;
	t_vec3	tmp;

	formal.a = pow(ray.direction.x, 2.0) + pow(ray.direction.z, 2.0) - pow(ray.direction.y, 2.0) * cn.angle;
	formal.b = ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z - ray.origin.y * ray.direction.y * cn.angle;
	formal.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - pow(ray.origin.y, 2.0) * cn.angle;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	if (formal.dis > 0.0)
	{
		calc_t(&formal);
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			if (tmp.y >= -cn.height && tmp.y <= 0.0)
			{
				hit->p = con_to_vec3(r_vec(cn.side.mi, con_to_vec4(tmp, 1)));
				norm_calc_cn(cn, hit);
				hit->t = formal.t;
				get_color_and_normal_cn(cn, hit, tmp, 0);
				return (true);
			}
		}
	}
	return (false);
}

bool	test_bottom_cn(t_cone cn, t_hitpoint *hit, t_ray ray)
{
	float	dis;
	float	t;
	t_vec3	tmp;
	t_vec3	test;

	test.x = 0.0;
	test.y = 1.0;
	test.z = 0.0;
	t = -dot(test, ray.origin) / dot(test, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		tmp = ray_vec(ray.origin, t, ray.direction);
		dis = pow(tmp.x, 2.0) + pow(tmp.z, 2.0);
		if (dis <= cn.radius * cn.radius)
		{
			hit->p = con_to_vec3(
					r_vec(cn.bottom.mi, con_to_vec4(tmp, 1)));
			hit->normal = multi_vec_wnbr(cn.norm, -1.0);
			hit->t = t;
			get_color_and_normal_cn(cn, hit, tmp, 1);
			return (true);
		}
	}
	return (false);
}

void	norm_calc_cn(t_cone cn, t_hitpoint *hit)
{
	t_vec3	center;
	t_vec3	oc;
	t_vec3	ch;
	t_vec3	tangent;

	oc = sub_vec(hit->p, cn.coords);
	center = add_vec(cn.coords, multi_vec_wnbr(cn.norm,
				dot(oc, cn.norm) / dot(cn.norm, cn.norm)));
	ch = sub_vec(hit->p, center);
	tangent = cross_vec(oc, ch);
	hit->normal = norm_vec(cross_vec(tangent, oc));
}


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

void	get_color_and_normal_cn(t_cone cn, t_hitpoint *hit, t_vec3 tmp, int i)
{
	int		index;
	t_vec3	uv;
	xpm_t	*map;

	if (cn.texture)
		map = cn.texture;
	else if (cn.bump_map)
		map = cn.bump_map;
	else
		map = NULL;
	if (map)
	{
		if (i == 0)
			get_uv_coords_cn(cn, map, tmp, &uv);
		else
			get_uv_coords_tb(cn.radius, map, tmp, &uv);
		index = ((int)uv.y * map->texture.width + (int)uv.x) * 4;
	}
	if (cn.texture)
	{
		// get_checkerboard_color(uv.x, uv.y, hit);
		hit->obj_color.x = map->texture.pixels[index] / 255.0;
		hit->obj_color.y = map->texture.pixels[index + 1] / 255.0;
		hit->obj_color.z = map->texture.pixels[index + 2] / 255.0;
	}
	else
		hit->obj_color = cn.color;
	if (cn.bump_map)
	{
		printf("bump_map\n");
	}
}
