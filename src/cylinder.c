/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lucabohn          #+#    #+#             */
/*   Updated: 2024/10/29 16:30:34 by lbohm            ###   ########.fr       */
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
	t_vec3	oc;

	oc = ray_vec(cy.coords, cy.height / -2.0, cy.norm);
	// ray.origin.y -= cy.height / 2.0;
	top_bottom(cy, hit, ray, i, oc);
	// ray.origin.y += cy.height;
	// top_bottom(cy, hit, ray, i);
	// ray.origin.y -= cy.height / 2.0;
	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - cy.radius * cy.radius;
	dis = (b * b) - (4.0f * a * c);
	if (dis > 0.0)
	{
		t = (-b - sqrt(dis)) / (2.0f * a);
		if (t <= 0.0 || t >= INFINITY)
		{
			t = (-b + sqrt(dis)) / (2.0f * a);
			if (t <= 0.0 || t >= INFINITY)
				t = __FLT_MAX__;
		}
		if (hit->t > t)
		{
			hit->p = ray_vec(ray.origin, t, ray.direction);
			if (fabsf(hit->p.y) < cy.height / 2.0)
			{
				cy_norm_calc(cy, hit, hit->p);
				hit->p = convert_to_vec3(r_vec(cy.mti, convert_to_vec4(hit->p, 1)));
				// printf("hit p side x = %f y = %f z = %f\n", hit->p.x, hit->p.y, hit->p.z);
				hit->t = t;
				hit->i = i;
			}
		}
	}
}

void	top_bottom(t_cylinder cy, t_hitpoint *hit, t_ray ray, int i, t_vec3 oc)
{
	float	dis;
	float	t;
	t_vec4	hitp;
	t_vec3	test;

	test.x = 0.0;
	test.y = 1.0;
	test.z = 0.0;

	t = -dot(test, sub_vec(ray.origin, oc)) / dot(test, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		hit->p = ray_vec(ray.origin, t, ray.direction);
		dis = pow(hit->p.x, 2.0) + pow(hit->p.z, 2.0);
		if (dis <= cy.radius * cy.radius)
		{
			hit->p = convert_to_vec3(r_vec(cy.mti, convert_to_vec4(hit->p, 0)));
			hit->normal = cy.norm;
			hit->t = t;
			hit->i = i;
		}
	}
}

void	init_tmp(t_cylinder cy, t_ray ray, t_tmp *tmp)
{
	t_vec4	tmp1;

	tmp->zdir.x = 0.0;
	tmp->zdir.y = 1.0;
	tmp->zdir.z = 0.0;
	tmp->zdir.w = 0.0;
	tmp1.x = cy.coords.x;
	tmp1.y = cy.coords.y;
	tmp1.z = cy.coords.z;
	tmp1.w = 0.0;
	tmp1.x = ray.direction.x;
	tmp1.y = ray.direction.y;
	tmp1.z = ray.direction.z;
	tmp1.w = 0.0;
	tmp->rrdir = r_vec(cy.mt, tmp1);
	tmp1.x = ray.origin.x;
	tmp1.y = ray.origin.y;
	tmp1.z = ray.origin.z;
	tmp1.w = 1.0;
	tmp->rrori = r_vec(cy.mt, tmp1);
}

void	cy_norm_calc(t_cylinder cy, t_hitpoint *hit, t_vec3 hitp)
{
	float	diff_z;
	t_vec3	coordsn;
	t_vec3	normal;

	diff_z = hit->p.y - cy.coords.y;
	coordsn.x = 0.0;
	coordsn.y = diff_z;
	coordsn.z = 0.0;
	normal = norm_vec(sub_vec(hitp, coordsn));
	hit->normal = convert_to_vec3(r_vec(cy.mti, convert_to_vec4(normal, 0)));
}

void	create_m_cy(t_data *data, t_cylinder *cy)
{
	float	angle_x;
	float	angle_z;
	float	t[4][4];
	float	tmp[4][4];
	float	full_r[4][4];
	t_vec3	test = {0,0,0};

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle_cy(cy, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	translation(t, sub_vec(test, cy->coords));
	multi_m(cy->mt, full_r, t);
	copy_m(tmp, cy->mt);
	create_m_inverse(tmp, cy->mti);
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
