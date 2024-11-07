/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/07 17:26:47 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i)
{
	float	t;
	float	a;
	float	b;
	float	c;
	float	dis;
	t_ray	test;
	t_vec3	tmp;

	test.origin = convert_to_vec3(r_vec(cy.mtt, convert_to_vec4(ray.origin, 1)));
	test.direction = convert_to_vec3(r_vec(cy.mtt, convert_to_vec4(ray.direction, 0)));
	top_bottom(cy, hit, test, i, cy.mtit);
	test.origin = convert_to_vec3(r_vec(cy.mtb, convert_to_vec4(ray.origin, 1)));
	test.direction = convert_to_vec3(r_vec(cy.mtb, convert_to_vec4(ray.direction, 0)));
	top_bottom(cy, hit, test, i, cy.mtib);
	ray.origin = convert_to_vec3(r_vec(cy.mt, convert_to_vec4(ray.origin, 1)));
	ray.direction = convert_to_vec3(r_vec(cy.mt, convert_to_vec4(ray.direction, 0)));
	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z;
	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - cy.radius * cy.radius;
	dis = (b * b) - (a * c);
	if (dis > 0.0)
	{
		t = (-b - sqrt(dis)) / a;
		if (t <= 0.0 || t >= INFINITY)
		{
			t = (-b + sqrt(dis)) / a;
			if (t <= 0.0 || t >= INFINITY)
				t = __FLT_MAX__;
		}
		if (hit->t > t)
		{
			tmp = ray_vec(ray.origin, t, ray.direction);
			if (fabsf(tmp.y) <= cy.height / 2.0)
			{
				hit->p = convert_to_vec3(r_vec(cy.mti, convert_to_vec4(tmp, 1)));
				cy_norm_calc(cy, hit);
				hit->t = t;
				hit->i = i;
			}
		}
	}
}

void	top_bottom(t_cylinder cy, t_hitpoint *hit, t_ray ray, int i, float m[4][4])
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
			hit->p = convert_to_vec3(r_vec(m, convert_to_vec4(tmp, 1)));
			hit->normal = cy.norm;
			hit->t = t;
			hit->i = i;
		}
	}
}

void	cy_norm_calc(t_cylinder cy, t_hitpoint *hit)
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
	float	tmp[4][4];
	float	full_r[4][4];

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle_cy(cy, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	cy->norm = norm_vec(cy->norm);
	translation(t, multi_vec_wnbr(cy->coords, -1.0));
	multi_m(cy->mt, full_r, t);
	invert_matrix(cy->mt, cy->mti);
	translation(t, multi_vec_wnbr(
			ray_vec(cy->coords, cy->height / 2.0, cy->norm), -1.0));
	multi_m(cy->mtt, full_r, t);
	invert_matrix(cy->mtt, cy->mtit);
	translation(t, multi_vec_wnbr(
			ray_vec(cy->coords, cy->height / -2.0, cy->norm), -1.0));
	multi_m(cy->mtb, full_r, t);
	invert_matrix(cy->mtb, cy->mtib);
}

void	calc_angle_cy(t_cylinder *cy, float *x, float *z)
{
	double	ratio;
	t_vec3	test = {0,1,0};
	t_vec3	test2 = cross_vec(cy->norm, test);

	*z = 0.0;
	ratio = sqrt((cy->norm.x * cy->norm.x) + (cy->norm.y * cy->norm.y));
	if (cy->norm.x == 0.0 && cy->norm.y == 0.0 && fabsf(cy->norm.z) == 1.0)
		*x = atan2(cy->norm.z, ratio);
	else
	{
		if (ratio == 0.0)
			*z = M_PI_2;
		else
			*z = acos(cy->norm.y / ratio);
		*x = atan2(cy->norm.z, ratio);
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
