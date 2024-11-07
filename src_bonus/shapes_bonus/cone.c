/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:41:35 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/07 17:31:35 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_cn(t_cone cn, t_ray ray, t_hitpoint *hit, int i)
{
	t_abc	formal;
	t_vec3	tmp;
	t_vec3	test;
	t_vec3	dir = {0,1,0};

	test = ray.origin;
	ray.origin = ray_vec(test, cn.height, dir);
	cn_bottom(cn, ray, hit, i);
	ray.origin = test;
	formal.a = pow(ray.direction.x, 2.0) + pow(ray.direction.z, 2.0) - pow(ray.direction.y, 2.0) * cn.angle;
	formal.b = ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z - ray.origin.y * ray.direction.y * cn.angle;
	formal.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - pow(ray.origin.y, 2.0) * cn.angle;
	formal.dis = (formal.b * formal.b) - (formal.a * formal.c);
	if (formal.dis > 0.0)
	{
		formal.t = (-formal.b - sqrt(formal.dis)) / formal.a;
		if (formal.t <= 0.0 || formal.t >= INFINITY)
		{
			formal.t = (-formal.b + sqrt(formal.dis)) / formal.a;
			if (formal.t <= 0.0 || formal.t >= INFINITY)
				formal.t = __FLT_MAX__;
		}
		if (hit->t > formal.t)
		{
			tmp = ray_vec(ray.origin, formal.t, ray.direction);
			if (tmp.y >= -cn.height && tmp.y <= 0.0)
			{
				hit->p = convert_to_vec3(r_vec(cn.mti, convert_to_vec4(tmp, 1)));
				cn_norm_calc(cn, hit);
				hit->t = formal.t;
				hit->i = i;
			}
		}
	}
}

void	cn_norm_calc(t_cone cn, t_hitpoint *hit)
{
	t_vec3	center;
	t_vec3	oc;
	t_vec3	scale;

	oc = sub_vec(hit->p, cn.coords);
	center = add_vec(cn.coords, multi_vec_wnbr(cn.norm,
				dot(oc, cn.norm) / dot(cn.norm, cn.norm)));
	hit->normal = sub_vec(hit->p, center);
	scale = multi_vec_wnbr(cn.norm, cos(cn.tangle) / sin(cn.tangle));
	hit->normal = norm_vec(sub_vec(hit->normal, scale));
}

void	cn_bottom(t_cone cn, t_ray ray, t_hitpoint *hit, int i)
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
			test = ray_vec(cn.coords, cn.height, cn.norm);
			add_translation(cn.mti, multi_vec_wnbr(test, -1.0));
			hit->p = convert_to_vec3(r_vec(cn.mti, convert_to_vec4(tmp, 1)));
			hit->normal = multi_vec_wnbr(cn.norm, -1.0);
			hit->t = t;
			hit->i = i;
		}
	}
}

void	create_m_cn(t_cone *cn)
{
	float	angle_x;
	float	angle_z;
	float	t[4][4];
	float	tmp[4][4];
	float	full_r[4][4];

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle_cn(cn, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	cn->norm = norm_vec(cn->norm);
	translation(t, multi_vec_wnbr(cn->coords, -1.0));
	multi_m(cn->mt, full_r, t);
	invert_matrix(cn->mt, cn->mti);
}

void	calc_angle_cn(t_cone *cn, float *x, float *z)
{
	double	ratio;
	t_vec3	test = {0,1,0};
	t_vec3	test2 = cross_vec(cn->norm, test);

	*z = 0.0;
	ratio = sqrt((cn->norm.x * cn->norm.x) + (cn->norm.y * cn->norm.y));
	if (cn->norm.x == 0.0 && cn->norm.y == 0.0 && fabsf(cn->norm.z) == 1.0)
		*x = atan2(cn->norm.z, ratio);
	else
	{
		if (ratio == 0.0)
			*z = M_PI_2;
		else
			*z = acos(cn->norm.y / ratio);
		*x = atan2(cn->norm.z, ratio);
	}
	if (test2.z < 0.0)
		*z *= -1.0;
	if (test2.x < 0.0)
	{
		if (*x > 0.0)
			*x *= -1.0;
	}
	else
	{
		if (*x < 0.0)
			*x *= -1.0;
	}
}
