/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lucabohn          #+#    #+#             */
/*   Updated: 2024/10/10 14:33:38 by lbohm            ###   ########.fr       */
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

	init_tmp(cy, ray, &tmp);
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
				tmp.hitp = r_vec(cy.mti, tmp.hitp);
				cy_norm_calc(cy, hit, tmp);
				hit->p.x = tmp.hitp.x;
				hit->p.y = tmp.hitp.y;
				hit->p.z = tmp.hitp.z;
				hit->t = t;
				hit->i = i;
			}
		}
	}
	tmp.coords.x = 0.0;
	tmp.coords.y = 0.0;
	tmp.coords.z = cy.coords.z;
	tmp.coords.z += cy.height / 2.0;
	top_bottom(cy, hit, tmp, i);
	tmp.coords.z -= cy.height;
	top_bottom(cy, hit, tmp, i);
}

void	top_bottom(t_cylinder cy, t_hitpoint *hit, t_tmp tmp, int i)
{
	float	t;
	float	dis;

	t = -dot4(tmp.zdir, tmp.rrori) / dot4(tmp.zdir, tmp.rrdir);
	if (t > 0.0 && hit->t > t)
	{
		tmp.hitp = ray_vec4(tmp.rrori, t, tmp.rrdir);
		dis = sqrt(pow(tmp.hitp.x, 2.0)
				+ pow(tmp.hitp.z, 2.0));
		if (dis <= cy.radius)
		{
			tmp.hitp = r_vec(cy.mti, tmp.hitp);
			hit->p.x = tmp.hitp.x;
			hit->p.y = tmp.hitp.y;
			hit->p.z = tmp.hitp.z;
			hit->normal = multi_vec_wnbr(cy.norm, -1.0);
			hit->t = t;
			hit->i = i;
		}
	}
}

void	calc_quation(t_cylinder *cy)
{
	float	angle;
	t_vec3	y_axis;
	t_vec3	v;

	y_axis.x = 0;
	y_axis.y = 0;
	y_axis.z = 1;
	if (cy->norm.z < 0.0)
		cy->norm.z *= -1.0;
	v = cross_vec(cy->norm, y_axis);
	angle = acos(dot(cy->norm, y_axis)) / sqrt(dot(cy->norm, cy->norm) * sqrt(dot(y_axis, y_axis)));
	cy->q.w = cos(angle / 2.0);
	cy->q.x = v.x * sin(angle / 2.0);
	cy->q.y = v.y * sin(angle / 2.0);
	cy->q.z = v.z * sin(angle / 2.0);
	cy->qi.w = cy->q.w;
	cy->qi.x = -cy->q.x;
	cy->qi.y = -cy->q.y;
	cy->qi.z = -cy->q.z;
}

void	init_tmp(t_cylinder cy, t_ray ray, t_tmp *tmp)
{
	t_vec4	tmp1;

	tmp->zdir.x = 0.0;
	tmp->zdir.y = 1.0;
	tmp->zdir.z = 0.0;
	tmp->zdir.z = 0.0;
	tmp1.x = cy.coords.x;
	tmp1.y = cy.coords.y;
	tmp1.z = cy.coords.z;
	tmp1.w = 0.0;
	tmp->coords = r_vec(cy.mt, tmp1);
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
	t_vec4	diff;
	t_vec4	coordsn;
	t_vec4	n;

	diff = sub_vec4(tmp.hitp, tmp.coords);
	coordsn = ray_vec4(tmp.coords, diff.z, tmp.zdir);
	n = norm_vec4(sub_vec4(tmp.hitp, coordsn));
	hit->normal.x = n.x;
	hit->normal.y = n.y;
	hit->normal.z = n.z;
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
