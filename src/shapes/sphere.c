/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:14:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/20 12:47:55 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	calc_sp(t_data *data, t_sphere sp, t_ray ray, t_hitpoint *hit)
{
	t_abc	formal;
	t_vec3	tmp;

	ray.origin = con_to_vec3(r_vec(sp.side.m, con_to_vec4(ray.origin, 1)));
	ray.direction = con_to_vec3(
			r_vec(sp.side.m, con_to_vec4(ray.direction, 0)));
	formal.t = 0.0;
	formal.a = dot(ray.direction, ray.direction);
	formal.b = dot(ray.direction, ray.origin);
	formal.c = dot(ray.origin, ray.origin) - sp.radius * sp.radius;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	if (formal.dis > 0.0)
	{
		calc_t(&formal);
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			hit->p = con_to_vec3(r_vec(sp.side.mi, con_to_vec4(tmp, 1)));
			hit->normal = norm_vec(sub_vec(hit->p, sp.coords));
			hit->t = formal.t;
			get_color_and_normal_sp(data, sp, hit, tmp);
			return (true);
		}
	}
	return (false);
}

void	create_m_sp(t_sphere *sp)
{
	translation(sp->side.m, multi_vec_wnbr(sp->coords, -1.0));
	invert_matrix(sp->side.m, sp->side.mi);
}

void	get_color_and_normal_sp(t_data *data, t_sphere sp,
			t_hitpoint *hit, t_vec3 tmp)
{
	t_vec3	uv;
	xpm_t	*map;

	if (sp.texture)
		map = sp.texture;
	else if (sp.bump_map)
		map = sp.bump_map;
	else
		map = NULL;
	if (map || data->checker)
		get_uv_coords_sp(data, map, &uv, tmp);
	if (sp.texture || data->checker)
	{
		if (data->checker)
			get_checkerboard_color(uv.x, uv.y, hit);
		else
			hit->obj_color = get_map_color(uv.x, uv.y, sp.texture);
	}
	else
		hit->obj_color = sp.color;
	if (sp.bump_map)
		get_map_normal(hit, &uv, sp.bump_map);
}
