/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:14:01 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/13 17:59:04 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	t_abc	formal;
	t_vec3	tmp;

	ray.origin = convert_to_vec3(r_vec(sp.side.m, convert_to_vec4(ray.origin, 1)));
	ray.direction = convert_to_vec3(r_vec(sp.side.m, convert_to_vec4(ray.direction, 0)));
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
			hit->p = convert_to_vec3(r_vec(sp.side.mi, convert_to_vec4(tmp, 1)));
			if (sp.bump_map)
				get_normal_sp();
			else
				hit->normal = norm_vec(sub_vec(hit->p, sp.coords));
			hit->t = formal.t;
			if (sp.texture)
				get_texture_color_sp(sp.texture, hit->normal, hit);
			else
				hit->obj_color = sp.color;
			hit->i = i;
		}
	}
}

void	create_m_sp(t_sphere *sp)
{
	translation(sp->side.m, multi_vec_wnbr(sp->coords, -1.0));
	invert_matrix(sp->side.m, sp->side.mi);
}

void	get_texture_color_sp(xpm_t *map, t_vec3 normal, t_hitpoint *hit)
{
	float	phi;
	float	theta;
	int		x;
	int		y;
	int		index;

	theta = acosf(normal.y);
	phi = atan2f(normal.z, normal.x);
	x = (phi + M_PI) / (2 * M_PI) * (map->texture.width - 1);
	y = (theta / M_PI) * (map->texture.height - 1);
	index = (y * map->texture.width + x) * 4;
	hit->obj_color.x = map->texture.pixels[index] / 255.0;
	hit->obj_color.y = map->texture.pixels[index + 1] / 255.0;
	hit->obj_color.z = map->texture.pixels[index + 2] / 255.0;
}
