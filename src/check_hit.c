/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:46:05 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/23 17:43:41 by lbohm            ###   ########.fr       */
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
	t_vec	oc;
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

void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i)
{
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t;
	float	z;
	t_vec	oc;

	t = 0.0;
	oc = sub_vec(ray.origin, cy.coords);
	a = dot(ray.direction, ray.direction) - pow(dot(ray.direction, cy.norm), 2);
	b = 2.0f * (dot(ray.direction, oc) - dot(ray.direction, cy.norm) * dot(oc, cy.norm));
	c = dot(oc, oc) - pow(dot(oc, cy.norm), 2) - pow(cy.radius, 2);
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
		if (t != __FLT_MAX__)
		{
			z = dot(sub_vec(ray_vec(ray.origin, t, ray.direction), cy.coords), cy.norm);
			if (z < (cy.height / 2.0f) * -1 || z > (cy.height / 2.0f))
				t = __FLT_MAX__;
		}
		if (hit->t > t)
		{
			hit->t = t;
			hit->i = i;
		}
	}
	if (hit->t == __FLT_MAX__)
	{
		if (dot(ray.direction, cy.norm) < 0.0)
		{
			t = -dot(cy.norm, sub_vec(ray.origin, ray_vec(cy.coords, cy.height / 2.0f, cy.norm))) / dot(cy.norm, ray.direction);
			if (t > 0.0 && hit->t > t)
			{
				t_vec	testh = ray_vec(ray.origin, t, ray.direction);
				t_vec	top = ray_vec(cy.coords, cy.height / 2.0f, cy.norm);
				float	d = sqrt(pow(testh.x - top.x, 2.0) + pow(testh.y - top.y, 2.0) + pow(testh.z - top.z, 2.0));
				if (d <= cy.radius)
				{
					hit->i = i;
					hit->t = t;
					hit->normal = cy.norm;
				}
				else
					hit->t = __FLT_MAX__;
			}
		}
		else
		{
			t = -dot(multi_vec_wnbr(cy.norm, -1.0), sub_vec(ray.origin, ray_vec(cy.coords, cy.height / 2.0f, multi_vec_wnbr(cy.norm, -1.0)))) / dot(multi_vec_wnbr(cy.norm, -1.0), ray.direction);
			if (t > 0.0 && hit->t > t)
			{
				t_vec	testh = ray_vec(ray.origin, t, ray.direction);
				t_vec	top = ray_vec(cy.coords, cy.height / 2.0f, multi_vec_wnbr(cy.norm, -1.0));
				float	d = sqrt(pow(testh.x - top.x, 2.0) + pow(testh.y - top.y, 2.0) + pow(testh.z - top.z, 2.0));
				if (d <= cy.radius)
				{
					hit->i = i;
					hit->t = t;
					hit->normal = multi_vec_wnbr(cy.norm, -1.0);
				}
				else
					hit->t = __FLT_MAX__;
			}
		}
	}
}
