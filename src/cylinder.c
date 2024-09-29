/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lucabohn          #+#    #+#             */
/*   Updated: 2024/09/29 21:29:59 by lucabohn         ###   ########.fr       */
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
	t_vec4	rrdir;
	t_vec4	rrori;
	t_vec4	hitp;

	calc_quation(&cy);
	t_vec4	dir;
	t_vec4	coords;

	hitp.w = 0.0;
	hitp.x = 0.0;
	hitp.y = 0.0;
	hitp.z = 0.0;
	dir.w = 0.0;
	dir.x = cy.norm.x;
	dir.y = cy.norm.y;
	dir.z = cy.norm.z;
	coords.w = 0.0;
	coords.x = cy.coords.x;
	coords.y = cy.coords.y;
	coords.z = cy.coords.z;
	coords = multi_quat(multi_quat(cy.q, coords), cy.qi);
	dir = multi_quat(multi_quat(cy.q, dir), cy.qi);
	rrdir.w = 0.0;
	rrdir.x = ray.direction.x;
	rrdir.y = ray.direction.y;
	rrdir.z = ray.direction.z;
	rrori.w = 0.0;
	rrori.x = ray.origin.x - cy.coords.x;
	rrori.y = ray.origin.y - cy.coords.y;
	rrori.z = ray.origin.z - cy.coords.z;
	rrdir = multi_quat(multi_quat(cy.q, rrdir), cy.qi);
	rrori = multi_quat(multi_quat(cy.q, rrori), cy.qi);
	a = pow(rrdir.x, 2) + pow(rrdir.y, 2);
	b = 2 * (rrori.x * rrdir.x + rrori.y * rrdir.y);
	c = pow(rrori.x, 2) + pow(rrori.y, 2) - pow(cy.radius, 2);
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
			hitp = ray_vec4(rrori, t, rrdir);
			if (hitp.z > cy.coords.z - cy.height / 2.0 && hitp.z < cy.coords.z + cy.height / 2.0)
			{
				hitp = multi_quat(multi_quat(cy.qi, hitp), cy.q);
				hit->p.x = hitp.x;
				hit->p.y = hitp.y;
				hit->p.z = hitp.z;
				t_vec3	diff = sub_vec(hit->p, cy.coords);
				t_vec3	coordsn = ray_vec(cy.coords, diff.z, cy.norm);
				t_vec3	N = dev_vec_wnbr(sub_vec(hit->p, coordsn), cy.radius);
				hit->normal.x = N.x;
				hit->normal.y = N.y;
				hit->normal.z = N.z;
				hit->t = t;
				hit->i = i;
			}
			else
				hit->t = __FLT_MAX__;
		}
	}
	coords.z += cy.height / 2.0;
	t = -dot4(dir, sub_vec4(rrori, coords)) / dot4(dir, rrdir);
	if (t > 0.0 && hit->t > t)
	{
		hitp = ray_vec4(rrori, t, rrdir);
		float dis = sqrt(pow(hitp.x - coords.x, 2.0) + pow(hitp.y - coords.y, 2.0));
		if (dis <= cy.radius)
		{
			hitp = multi_quat(multi_quat(cy.qi, hitp), cy.q);
			hit->p.x = hitp.x;
			hit->p.y = hitp.y;
			hit->p.z = hitp.z;
			hit->normal = cy.norm;
			hit->t = t;
			hit->i = i;
		}
	}
	coords.z -= cy.height;
	t = -dot4(dir, sub_vec4(rrori, coords)) / dot4(dir, rrdir);
	if (t > 0.0 && hit->t > t)
	{
		hitp = ray_vec4(rrori, t, rrdir);
		float dis = sqrt(pow(hitp.x - coords.x, 2.0) + pow(hitp.y - coords.y, 2.0));
		if (dis <= cy.radius)
		{
			hitp = multi_quat(multi_quat(cy.qi, hitp), cy.q);
			hit->p.x = hitp.x;
			hit->p.y = hitp.y;
			hit->p.z = hitp.z;
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
	v = cross_vec(cy->norm, y_axis);
	angle = acos(dot(cy->norm, y_axis) / sqrt(dot(cy->norm, cy->norm)));
	cy->q.w = cos(angle / 2.0);
	cy->q.x = v.x * sin(angle / 2.0);
	cy->q.y = v.y * sin(angle / 2.0);
	cy->q.z = v.z * sin(angle / 2.0);
	cy->qi.w = cy->q.w;
	cy->qi.x = -cy->q.x;
	cy->qi.y = -cy->q.y;
	cy->qi.z = -cy->q.z;
}
