/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/14 14:48:59 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_img(t_data *data)
{
	t_vec3		coords;
	t_hitpoint	hit;

	coords.y = 0.0;
	coords.z = 0.0;
	init_viewport(data);
	while (coords.y < data->height)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			hit.color.x = 0.0;
			hit.color.y = 0.0;
			hit.color.z = 0.0;
			trace_ray((float)coords.x, (float)coords.y, &hit, data);
			mlx_put_pixel(data->img, coords.x, coords.y,
				create_color(hit.color.x,
					hit.color.y,
					hit.color.z, 255));
			coords.x++;
		}
		coords.y++;
	}
	data->moved = false;
}

int	create_color(float x, float y, float z, float w)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = 255.0 * x;
	g = 255.0 * y;
	b = 255.0 * z;
	a = 255.0 * w;
	r < 0 ? r = 0 : r > 255 ? r = 255 : r;
	g < 0 ? g = 0 : g > 255 ? g = 255 : g;
	b < 0 ? b = 0 : b > 255 ? b = 255 : b;
	a < 0 ? a = 0 : a > 255 ? a = 255 : a;
	return (r << 24 | g << 16 | b << 8 | a);
}

void	in_out_object(t_ray ray, t_hitpoint *hit)
{
	if (dot(ray.direction, hit->normal) > 0.0)
		hit->normal
			= multi_vec_wnbr(hit->normal, -1.0);
}

void	trace_ray(float x, float y, t_hitpoint *hit, t_data *data)
{
	t_vec3		pixle_center;
	t_ray		ray;

	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
	{
		ray.origin = data->set.cam.coords;
		pixle_center = add_vec(add_vec(data->vp.p00, \
		multi_vec_wnbr(data->vp.du, x)), multi_vec_wnbr(data->vp.dv, y));
		ray.direction = sub_vec(pixle_center, data->set.cam.coords);
		// printf("x = %f y = %f z = %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
		get_obj_color(data, ray, hit);
	}
}

void	get_obj_color(t_data *data, t_ray ray, t_hitpoint *hit)
{
	if (data->name)
		lighting(data, ray, hit);
}

void	lighting(t_data *data, t_ray ray, t_hitpoint *hit)
{
	t_lighting	nlight;
	int			re;
	int			befor;

	re = 0;
	befor = 0;
	while (re++ < 2)
	{
		check_hit(ray, hit, data);
		if (hit->t != __FLT_MAX__)
		{
			nlight.light = multi_vec_wnbr(data->set.light[0].color, data->set.light[0].brightness);
			nlight.light_dir = norm_vec(sub_vec(data->set.light[0].coords, hit->p));
			nlight.diffuse_strength = dot(hit->normal, nlight.light_dir);
			nlight.diffuse_strength < 0.0 ? nlight.diffuse_strength = 0 : nlight.diffuse_strength;
			nlight.diffuse = multi_vec_wnbr(nlight.light, nlight.diffuse_strength);
			if (re == 1)
			{
				befor = hit->i;
				ray.origin = ray_vec(hit->p, 0.0001f, hit->normal);
				ray.direction = nlight.light_dir;
			}
			if (re == 2)
			{
				if (leangth_vec(sub_vec(data->set.light[0].coords, hit->p)) > leangth_vec(sub_vec(data->set.obj[hit->i].form.cy.coords ,hit->p)))
				{
					if (data->set.obj[befor].type == SPHERE)
						hit->color = multi_vec(add_vec(add_vec(nlight.light, nlight.diffuse), data->set.ambient.color), data->set.obj[befor].form.sp.color);
					else if (data->set.obj[befor].type == CYLINDER)
						hit->color = multi_vec(add_vec(add_vec(nlight.light, nlight.diffuse), data->set.ambient.color), data->set.obj[befor].form.cy.color);
					else
						hit->color = multi_vec(add_vec(add_vec(nlight.light, nlight.diffuse), data->set.ambient.color), data->set.obj[befor].form.pl.color);
				}
				break ;
			}
			if (data->set.obj[hit->i].type == PLANE)
				hit->color = multi_vec(add_vec(add_vec(nlight.light, nlight.diffuse), data->set.ambient.color), data->set.obj[befor].form.pl.color);
			else if (data->set.obj[hit->i].type == SPHERE)
				hit->color = multi_vec(add_vec(add_vec(nlight.light, nlight.diffuse), data->set.ambient.color), data->set.obj[befor].form.sp.color);
			else
				hit->color = multi_vec(add_vec(add_vec(nlight.light, nlight.diffuse), data->set.ambient.color), data->set.obj[hit->i].form.cy.color);
		}
		else
		{
			if (re == 2)
				break ;
			hit->color = data->bg;
		}
	}
}
