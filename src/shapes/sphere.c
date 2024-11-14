/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:14:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/14 13:03:41 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	t_abc	formal;
	t_vec3	tmp;

	ray.origin = con_to_vec3(r_vec(sp.side.m, con_to_vec4(ray.origin, 1)));
	ray.direction = con_to_vec3(r_vec(sp.side.m, con_to_vec4(ray.direction, 0)));
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
			hit->i = i;
			get_color_and_normal_sp(sp, hit);
		}
	}
}

void	create_m_sp(t_sphere *sp)
{
	translation(sp->side.m, multi_vec_wnbr(sp->coords, -1.0));
	invert_matrix(sp->side.m, sp->side.mi);
}

void	get_color_and_normal_sp(t_sphere sp, t_hitpoint *hit)
{
	int		index;
	t_vec3	uv = {0, 0, 0};
	xpm_t	*map;

	if (sp.texture)
		map = sp.texture;
	else if (sp.bump_map)
		map = sp.bump_map;
	else
		map = NULL;
	if (map)
	{
		get_uv_coords_sp(map, hit, &uv);
		index = ((int)uv.y * map->texture.width + (int)uv.x) * 4;
	}
	if (sp.texture)
	{
		hit->obj_color.x = map->texture.pixels[index] / 255.0;
		hit->obj_color.y = map->texture.pixels[index + 1] / 255.0;
		hit->obj_color.z = map->texture.pixels[index + 2] / 255.0;
	}
	else
		hit->obj_color = sp.color;
	if (sp.bump_map)
	{
		printf("bump_map\n");
	}
}
