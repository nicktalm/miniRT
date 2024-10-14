/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lucabohn          #+#    #+#             */
/*   Updated: 2024/10/12 14:23:36 by lucabohn         ###   ########.fr       */
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
	t_tmp	tmp;
	t_vec4	test;

	init_tmp(cy, ray, &tmp);
	// test = tmp.rrori;
	// test.y -= cy.height / 2.0;
	// t = -dot4(tmp.zdir, test) / dot4(tmp.zdir, tmp.rrdir);
	// top_bottom(cy, hit, tmp, i, t);
	// test.y += cy.height;
	// t = -dot4(tmp.zdir, test) / dot4(tmp.zdir, tmp.rrdir);
	// top_bottom(cy, hit, tmp, i, t);
	a = pow(tmp.rrdir.x, 2) + pow(tmp.rrdir.z, 2);
	b = 2 * (tmp.rrori.x * tmp.rrdir.x + tmp.rrori.z * tmp.rrdir.z);
	c = pow(tmp.rrori.x, 2) + pow(tmp.rrori.z, 2) - 1.0;
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
			tmp.hitp = ray_vec4(tmp.rrori, t, tmp.rrdir);
			if (fabsf(tmp.hitp.y) < cy.height / 2.0)
			{
				cy_norm_calc(cy, hit, tmp);
				tmp.hitp = r_vec(cy.mti, tmp.hitp);
				hit->p.x = tmp.hitp.x;
				hit->p.y = tmp.hitp.y;
				hit->p.z = tmp.hitp.z;
				hit->t = t;
				hit->i = i;
			}
		}
	}
}

void	top_bottom(t_cylinder cy, t_hitpoint *hit, t_tmp tmp, int i, float t)
{
	float	dis;

	if (t > 0.0 && hit->t > t)
	{
		tmp.hitp = ray_vec4(tmp.rrori, t, tmp.rrdir);
		dis = pow(tmp.hitp.x, 2.0) + pow(tmp.hitp.z, 2.0);
		if (dis <= cy.radius)
		{
			tmp.hitp = r_vec(cy.mti, tmp.hitp);
			hit->p.x = tmp.hitp.x;
			hit->p.y = tmp.hitp.y;
			hit->p.z = tmp.hitp.z;
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

void	cy_norm_calc(t_cylinder cy, t_hitpoint *hit, t_tmp tmp)
{
	float	diff_z;
	t_vec4	coordsn;
	t_vec4	normal;

	diff_z = tmp.hitp.y - tmp.coords.y;
	coordsn.x = 0.0;
	coordsn.y = diff_z;
	coordsn.z = 0.0;
	coordsn.w = 0.0;
	normal = norm_vec4(sub_vec4(tmp.hitp, coordsn));
	normal = r_vec(cy.mti, normal);
	hit->normal.x = normal.x;
	hit->normal.y = normal.y;
	hit->normal.z = normal.z;
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
