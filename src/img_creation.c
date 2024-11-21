/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 11:31:16 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_img(t_data *data)
{
	t_vec3		coords;
	int			resolution;

	coords.y = 0.0;
	coords.z = 0.0;
	if (!data->render)
		resolution = data->res;
	else
		resolution = 1;
	init_viewport(data);
	while (coords.y < data->height)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			if (data->moved)
			{
				if (!data->render)
				{
					down_sampling(data, (int)coords.x, (int)coords.y);
					data->cache_use = false;
				}
				else
				{
					super_sampling(data, (int)coords.x, (int)coords.y);
					data->cache_use = true;
				}
			}
			else
				data->cache_use = true;
			coords.x += resolution;
		}
		coords.y += resolution;
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
	check_interval(&r);
	check_interval(&g);
	check_interval(&b);
	check_interval(&a);
	return (r << 24 | g << 16 | b << 8 | a);
}

void	check_interval(int *nbr)
{
	if (*nbr > 255)
		*nbr = 255;
	else if (*nbr < 0)
		*nbr = 0;
}

void	in_out_object(t_ray *ray, t_hitpoint *hit)
{
	if (dot(ray->direction, hit->normal) > 0.0)
	{
		hit->normal = multi_vec_wnbr(hit->normal, -1.0);
	}
}

void	trace_ray(float x, float y, t_hitpoint *hit, t_data *data)
{
	t_vec3		pixle_center;
	t_ray		ray;

	ray.origin = data->set.cam.coords;
	pixle_center = add_vec(add_vec(data->vp.p00, \
	multi_vec_wnbr(data->vp.du, x)), multi_vec_wnbr(data->vp.dv, y));
	ray.direction = sub_vec(pixle_center, data->set.cam.coords);
	get_color(data, &ray, hit);
}

void	super_sampling(t_data *data, int x, int y)
{
	t_vec3		full_color;
	t_hitpoint	hit;
	int			i;
	int			j;

	full_color.x = 0.0;
	full_color.y = 0.0;
	full_color.z = 0.0;
	j = 0;
	while (j < 2)
	{
		i = 0;
		while (i < 2)
		{
			hit.color.x = 0.0;
			hit.color.y = 0.0;
			hit.color.z = 0.0;
			trace_ray((float)x + ((float)i / 2.0) - 0.25,
				(float)y + ((float)j / 2.0) - 0.25, &hit, data);
			full_color = add_vec(full_color, hit.color);
			i++;
		}
		j++;
	}
	full_color = dev_vec_wnbr(full_color, 4.0);
	mlx_put_pixel(data->img, x, y,
			create_color(full_color.x, full_color.y, full_color.z, 255));
}

void	down_sampling(t_data *data, int x, int y)
{
	t_hitpoint	hit;
	int			i;
	int			j;

	j = 0;
	hit.color.x = 0.0;
	hit.color.y = 0.0;
	hit.color.z = 0.0;
	trace_ray((float)x, (float)y, &hit, data);
	while (j < data->res)
	{
		i = 0;
		while (i < data->res)
		{
			if (x + i < data->width && y + j < data->height)
			{
				mlx_put_pixel(data->img, x + i, y + j,
					create_color(hit.color.x, hit.color.y, hit.color.z, 255));
			}
			i++;
		}
		j++;
	}
}
