/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lucabohn          #+#    #+#             */
/*   Updated: 2024/10/15 12:39:17 by lbohm            ###   ########.fr       */
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
	t_vec4	test;
	t_vec4	hitp;

	test.x = 0.0;
	test.y = 1.0;
	test.z = 0.0;
	test.w = 0.0;
	ray.origin.y -= cy.height / 2.0;
	t = -dot4(test, ray.origin) / dot4(test, ray.direction);
	top_bottom(cy, hit, ray, i, t);
	ray.origin.y += cy.height;
	t = -dot4(test, ray.origin) / dot4(test, ray.direction);
	top_bottom(cy, hit, ray, i, t);
	ray.origin.y -= cy.height / 2.0;
	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1.0;
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
			hitp = ray_vec4(ray.origin, t, ray.direction));
			if (fabsf(hitp.y) < cy.height / 2.0)
			{
				cy_norm_calc(cy, hit, hitp);
				hit->p = convert_to_vec3(r_vec(cy.mti, hitp));
				hit->t = t;
				hit->i = i;
			}
		}
	}
}

void	top_bottom(t_cylinder cy, t_hitpoint *hit, t_ray ray, int i, float t)
{
	float	dis;
	t_vec4	hitp;

	if (t > 0.0 && hit->t > t)
	{
		hitp = ray_vec4(ray.origin, t, ray.direction);
		dis = pow(hitp.x, 2.0) + pow(hitp.z, 2.0);
		if (dis <= cy.radius)
		{
			hit->p = convert_to_vec3(r_vec(cy.mti, hitp));
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

void	cy_norm_calc(t_cylinder cy, t_hitpoint *hit, t_vec4 hitp)
{
	float	diff_z;
	t_vec4	coordsn;
	t_vec4	normal;

	diff_z = hit->p.y - cy.coords.y;
	coordsn.x = 0.0;
	coordsn.y = diff_z;
	coordsn.z = 0.0;
	coordsn.w = 0.0;
	normal = norm_vec4(sub_vec4(hitp, coordsn));
	normal = r_vec(cy.mti, normal);
	if (normal.w == 0.0 || normal.w == 1)
	{
		hit->normal.x = normal.x;
		hit->normal.y = normal.y;
		hit->normal.z = normal.z;
	}
	else
	{
		hit->normal.x = normal.x / normal.w;
		hit->normal.y = normal.y / normal.w;
		hit->normal.z = normal.z / normal.w;
	}
}

void	print_m(float m[4][4])
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			printf("m[%i][%i] = %f ", i, j, m[i][j]);
		}
		printf("\n");
	}
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
	calc_angle(cy, &angle_x, &angle_z);
	get_full_r(full_r, angle_x, 0.0, angle_z);
	translation(t, cy->coords);
	multi_m(cy->mt, full_r, t);
	copy_m(tmp, cy->mt);
	create_m_inverse(tmp, cy->mti);
}
