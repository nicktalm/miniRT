/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:46:05 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/25 17:50:56 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	check_hit(t_ray ray, t_hitpoint *hit, t_data *data)
{
	int		i;
	float	t;

	i = 0;
	t = 0.0;
	hit->i = 0;
	hit->t = __FLT_MAX__;
	while (i < data->set.obj_count)
	{
		if (data->set.obj[i].type == SPHERE)
			calc_sp(data->set.obj[i].form.sp, ray, hit, i);
		else if (data->set.obj[i].type == PLANE)
			calc_pl(data->set.obj[i].form.pl, ray, hit, i);
		else if (data->set.obj[i].type == CYLINDER)
			calc_cy(data->set.obj[i].form.cy, ray, hit, i);
		i++;
	}
	if (hit->t != __FLT_MAX__)
	{
		if (data->set.obj[hit->i].type != CYLINDER)
			hit->p = ray_vec(ray.origin, hit->t, ray.direction);
		if (data->set.obj[hit->i].type == SPHERE)
			hit->normal = dev_vec_wnbr(sub_vec(hit->p, data->set.obj[hit->i].form.sp.coords), data->set.obj[hit->i].form.sp.radius);
		else if (data->set.obj[hit->i].type == CYLINDER)
		{
			if (cmp_vec(hit->normal, data->set.obj[hit->i].form.cy.norm))
				hit->normal = norm_vec(sub_vec(sub_vec(hit->p, data->set.obj[hit->i].form.cy.coords), multi_vec_wnbr(data->set.obj[hit->i].form.cy.norm, dot(sub_vec(hit->p, data->set.obj[hit->i].form.cy.coords), data->set.obj[hit->i].form.cy.norm))));
		}
		else
			hit->normal = data->set.obj[hit->i].form.pl.norm;
		in_out_object(ray, hit);
	}
}

void	calc_sp(t_sphere sp, t_ray ray, t_hitpoint *hit, int i)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t;

	t = 0.0;
	oc = sub_vec(sp.coords, ray.origin);
	a = dot(ray.direction, ray.direction);
	b = dot(ray.direction, oc);
	c = dot(oc, oc) - sp.radius * sp.radius;
	dis = (b * b) - (a * c);
	if (dis > 0.0)
	{
		t = (b - sqrt(dis)) / a;
		if (t <= 0.0 || t >= INFINITY)
		{
			t = (b + sqrt(dis) / a);
			if (t <= 0.0 || t >= INFINITY)
				t = __FLT_MAX__;
		}
		if (hit->t > t)
		{
			hit->t = t;
			hit->i = i;
		}
	}
}

void	calc_pl(t_plane pl, t_ray ray, t_hitpoint *hit, int i)
{
	float	t;

	t = 0.0;
	t = -dot(pl.norm, sub_vec(ray.origin, pl.coords)) / dot(pl.norm, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		hit->i = i;
		hit->t = t;
	}
}

// void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i)
// {
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	dis;
// 	float	t;
// 	float	z;
// 	t_vec3	oc;

// 	t = 0.0;
// 	oc = sub_vec(ray.origin, cy.coords);
// 	a = dot(ray.direction, ray.direction) - pow(dot(ray.direction, cy.norm), 2);
// 	b = 2.0f * (dot(ray.direction, oc) - dot(ray.direction, cy.norm) * dot(oc, cy.norm));
// 	c = dot(oc, oc) - pow(dot(oc, cy.norm), 2) - pow(cy.radius, 2);
// 	dis = (b * b) - (4.0f * a * c);
// 	if (dis > 0.0)
// 	{
// 		t = (-b - sqrt(dis)) / (2.0f * a);
// 		if (t <= 0.0 || t >= INFINITY)
// 		{
// 			t = (-b + sqrt(dis)) / (2.0f * a);
// 			if (t <= 0.0 || t >= INFINITY)
// 				t = __FLT_MAX__;
// 		}
// 		if (t != __FLT_MAX__)
// 		{
// 			z = dot(sub_vec(ray_vec(ray.origin, t, ray.direction), cy.coords), cy.norm);
// 			if (z < (cy.height / 2.0f) * -1 || z > (cy.height / 2.0f))
// 				t = __FLT_MAX__;
// 		}
// 		if (hit->t > t)
// 		{
// 			hit->t = t;
// 			hit->i = i;
// 		}
// 	}
// 	if (dot(ray.direction, cy.norm) < 0.0)
// 	{
// 		t = -dot(cy.norm, sub_vec(ray.origin, ray_vec(cy.coords, cy.height / 2.0f, cy.norm))) / dot(cy.norm, ray.direction);
// 		if (t > 0.0 && hit->t > t)
// 		{
// 			t_vec3	testh = ray_vec(ray.origin, t, ray.direction);
// 			t_vec3	top = ray_vec(cy.coords, cy.height / 2.0f, cy.norm);
// 			float	d = sqrt(pow(testh.x - top.x, 2.0) + pow(testh.y - top.y, 2.0) + pow(testh.z - top.z, 2.0));
// 			if (d <= cy.radius)
// 			{
// 				hit->i = i;
// 				hit->t = t;
// 				hit->normal = cy.norm;
// 			}
// 			else
// 				hit->t = __FLT_MAX__;
// 		}
// 	}
// 	else
// 	{
// 		t = -dot(multi_vec_wnbr(cy.norm, -1.0), sub_vec(ray.origin, ray_vec(cy.coords, cy.height / 2.0f, multi_vec_wnbr(cy.norm, -1.0)))) / dot(multi_vec_wnbr(cy.norm, -1.0), ray.direction);
// 		if (t > 0.0 && hit->t > t)
// 		{
// 			t_vec3	testh = ray_vec(ray.origin, t, ray.direction);
// 			t_vec3	top = ray_vec(cy.coords, cy.height / 2.0f, multi_vec_wnbr(cy.norm, -1.0));
// 			float	d = sqrt(pow(testh.x - top.x, 2.0) + pow(testh.y - top.y, 2.0) + pow(testh.z - top.z, 2.0));
// 			if (d <= cy.radius)
// 			{
// 				hit->i = i;
// 				hit->t = t;
// 				hit->normal = multi_vec_wnbr(cy.norm, -1.0);
// 			}
// 			else
// 				hit->t = __FLT_MAX__;
// 		}
// 	}
// }

void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i)
{
	float	angle;
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t;
	float	t_top;
	float	t_bottom;
	t_vec3	y_axis;
	t_vec3	v;
	t_vec4	q;
	t_vec4	qi;
	t_vec4	rdir;
	t_vec4	rori;
	t_vec4	cdir;
	t_vec4	rrdir;
	t_vec4	rrori;
	t_vec4	rcdir;
	t_vec3	oc;
	t_vec4	hitp;

	y_axis.x = 0;
	y_axis.y = 1;
	y_axis.z = 0;
	v = cross_vec(cy.norm, y_axis);
	angle = acos(dot(cy.norm, y_axis) / sqrt(dot(cy.norm, cy.norm)));
	q.w = cos(angle / 2.0);
	q.x = v.x * sin(angle / 2.0);
	q.y = v.y * sin(angle / 2.0);
	q.z = v.z * sin(angle / 2.0);
	qi.w = q.w;
	qi.x = q.x * -1;
	qi.y = q.y * -1;
	qi.z = q.z * -1;
	rdir.w = 0;
	rdir.x = ray.direction.x;
	rdir.y = ray.direction.y;
	rdir.z = ray.direction.z;
	cdir.w = 0;
	cdir.x = cy.norm.x;
	cdir.y = cy.norm.y;
	cdir.z = cy.norm.z;
	rori.w = 0;
	rori.x = ray.origin.x;
	rori.y = ray.origin.y;
	rori.z = ray.origin.z;
	rrdir = multi_quat(multi_quat(q, rdir), qi);
	rrori = multi_quat(multi_quat(q, rori), qi);
	rcdir = multi_quat(multi_quat(q, cdir), qi);
	a = pow(rrdir.x, 2) + pow(rrdir.z, 2);
	b = 2 * (rrori.x * rrdir.x + rrori.z * rrdir.z);
	c = pow(rrori.x, 2) + pow(rrori.z, 2) - pow(cy.radius, 2);
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
			if (hitp.y > cy.coords.y - cy.height / 2.0 && hitp.y < cy.coords.y + cy.height / 2.0)
			{
				hitp = multi_quat(multi_quat(qi, hitp), q);
				hit->p.x = hitp.x;
				hit->p.y = hitp.y;
				hit->p.z = hitp.z;
				hit->t = t;
				hit->i = i;
			}
			else
				hit->t = __FLT_MAX__;
		}
	}
	t_top = (cy.coords.y + cy.height / 2.0 - rrori.y) / rrdir.y;
	if (t_top > 0.0)
	{
		t_vec4 top_hit = ray_vec4(rrori, t_top, rrdir);
		float dist_top = sqrt(pow(top_hit.x - cy.coords.x, 2) + pow(top_hit.z - cy.coords.z, 2));
		if (dist_top <= cy.radius && hit->t > t_top)
		{
			hitp = multi_quat(multi_quat(qi, top_hit), q);
			hit->p.x = hitp.x;
			hit->p.y = hitp.y;
			hit->p.z = hitp.z;
			hit->t = t_top;
			hit->i = i;
		}
	}
	t_bottom = (cy.coords.y - cy.height / 2.0 - rrori.y) / rrdir.y;
	if (t_bottom > 0.0)
	{
		t_vec4 bottom_hit = ray_vec4(rrori, t_bottom, rrdir);
		float dist_bottom = sqrt(pow(bottom_hit.x - cy.coords.x, 2) + pow(bottom_hit.z - cy.coords.z, 2));
		if (dist_bottom <= cy.radius && hit->t > t_bottom)
		{
			hitp = multi_quat(multi_quat(qi, bottom_hit), q);
			hit->p.x = hitp.x;
			hit->p.y = hitp.y;
			hit->p.z = hitp.z;
			hit->t = t_bottom;
			hit->i = i;
		}
	}
}

t_vec4	ray_vec4(t_vec4 origin, float t, t_vec4 direction)
{
	t_vec4	result;

	result.x = origin.x + t * direction.x;
	result.y = origin.y + t * direction.y;
	result.z = origin.z + t * direction.z;
	return (result);
}
