/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:41:35 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/04 22:14:50 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_cn(t_cone cn, t_ray ray, t_hitpoint *hit, int i)
{
	t_abc	formal;
	t_vec3	tmp;

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
			if (fabsf(tmp.y) < cn.height / 2.0)
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
	float	len;

	oc = sub_vec(hit->p, cn.coords);
	len = dot(oc, cn.coords);
	center = add_vec(cn.coords, multi_vec_wnbr(cn.norm, len));
	center = sub_vec(hit->p, center);
	hit->normal = norm_vec(sub_vec(center, multi_vec_wnbr(cn.norm, len * cn.angle)));
}

// void	cn_bottom()
// {
	
// }

void	create_m_cn(t_cone *cn)
{
	float	angle_x;
	float	angle_z;
	float	t[4][4];
	float	tmp[4][4];
	float	full_r[4][4];
	t_vec3	test = {0,0,0};

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle_cn(cn, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	translation(t, sub_vec(test, cn->coords));
	multi_m(cn->mt, full_r, t);
	copy_m(tmp, cn->mt);
	create_m_inverse(tmp, cn->mti);
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