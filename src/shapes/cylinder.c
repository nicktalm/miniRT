/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/14 14:58:00 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_texture_color_cy(xpm_t *map, t_cylinder cy, t_hitpoint *hit, t_vec3 tmp);
void	get_checkerboard_color(float u, float v, t_hitpoint *hit);

void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i)
{
	t_ray	test;

	test.origin = con_to_vec3(
			r_vec(cy.top.m, con_to_vec4(ray.origin, 1)));
	test.direction = con_to_vec3(
			r_vec(cy.top.m, con_to_vec4(ray.direction, 0)));
	if (test_top_bottom_cy(cy, hit, test, cy.top.mi))
		hit->i = i;
	test.origin = con_to_vec3(
			r_vec(cy.bottom.m, con_to_vec4(ray.origin, 1)));
	test.direction = con_to_vec3(
			r_vec(cy.bottom.m, con_to_vec4(ray.direction, 0)));
	if (test_top_bottom_cy(cy, hit, test, cy.bottom.mi))
		hit->i = i;
	test.origin = con_to_vec3(
			r_vec(cy.side.m, con_to_vec4(ray.origin, 1)));
	test.direction = con_to_vec3(
			r_vec(cy.side.m, con_to_vec4(ray.direction, 0)));
	if (test_side_cy(cy, test, hit))
		hit->i = i;
}

bool	test_side_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit)
{
	t_abc	formal;
	t_vec3	tmp;

	formal.a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	formal.b = ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z;
	formal.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - cy.radius * cy.radius;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	if (formal.dis > 0.0)
	{
		calc_t(&formal);
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			if (fabsf(tmp.y) <= cy.height / 2.0)
			{
				hit->p = con_to_vec3(r_vec(cy.side.mi, con_to_vec4(tmp, 1)));
				norm_calc_cy(cy, hit);
				hit->t = formal.t;
				if (cy.texture)
					get_texture_color_cy(cy.texture, cy, hit, tmp);
				else
					hit->obj_color = cy.color;
				return (true);
			}
		}
	}
	return (false);
}

bool	test_top_bottom_cy(t_cylinder cy, t_hitpoint *hit, t_ray ray, float m[4][4])
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
		if (dis <= cy.radius * cy.radius)
		{
			hit->p = con_to_vec3(r_vec(m, con_to_vec4(tmp, 1)));
			hit->normal = cy.norm;
			hit->obj_color = cy.color;
			hit->t = t;
			return (true);
		}
	}
	return (false);
}

void	norm_calc_cy(t_cylinder cy, t_hitpoint *hit)
{
	t_vec3	center;
	t_vec3	oc;

	oc = sub_vec(hit->p, cy.coords);
	center = add_vec(cy.coords, multi_vec_wnbr(cy.norm,
				dot(oc, cy.norm) / dot(cy.norm, cy.norm)));
	hit->normal = norm_vec(sub_vec(hit->p, center));
}

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

void	get_texture_color_cy(xpm_t *map, t_cylinder cy, t_hitpoint *hit, t_vec3 tmp)
{
	float	u;
	float	v;
	int		index;

	u = atan2f(hit->normal.z, hit->normal.x) / (2.0 * M_PI);
	if (u < 0)
		u += 1.0;
	v =  1 - ((tmp.y / (cy.height / 2.0)) + 1) / 2.0;
	u *= (map->texture.width - 1);
	v *= (map->texture.height - 1);
	get_checkerboard_color(u, v, hit);
	// index = ((int)v * map->texture.width + (int)u) * 4;
	// hit->obj_color.x = map->texture.pixels[index] / 255.0;
	// hit->obj_color.y = map->texture.pixels[index + 1] / 255.0;
	// hit->obj_color.z = map->texture.pixels[index + 2] / 255.0;
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
