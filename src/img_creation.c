/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/14 21:45:16 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vec3	super_sampling(t_data *data, t_hitpoint *hit, int x, int y);
void	down_sampling(t_data *data, t_hitpoint *hit, int x, int y);

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
			if (data->moved)
			{
				hit.color.x = 0.0;
				hit.color.y = 0.0;
				hit.color.z = 0.0;
				// trace_ray(coords.x, coords.y, &hit, data);
				// data->cache[(int)coords.x + (int)coords.y * data->width] = hit.color;
				data->cache[(int)coords.x + (int)coords.y * data->width] = super_sampling(data, &hit, coords.x, coords.y);
				// down_sampling(data, &hit, coords.x, coords.y);
			}
			mlx_put_pixel(data->img, coords.x, coords.y,
				create_color(data->cache[(int)coords.x + (int)coords.y * data->width].x,
					data->cache[(int)coords.x + (int)coords.y * data->width].y,
					data->cache[(int)coords.x + (int)coords.y * data->width].z, 255));
			// printf("x = %f y = %f\n", coords.x, coords.y);
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

t_vec3	super_sampling(t_data *data, t_hitpoint *hit, int x, int y)
{
	t_vec3	full_color = {0, 0, 0};
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			trace_ray((float)x + ((float)i / 4.0) - 0.375,
				(float)y + ((float)j / 4.0) - 0.375, hit, data);
			full_color = add_vec(full_color, hit->color);
			j++;
		}
		i++;
	}
	return (dev_vec_wnbr(full_color, 16.0));
}

void	down_sampling(t_data *data, t_hitpoint *hit, int x, int y)
{
	static int	pos = 0;
	int			i;
	int			j;

	j = 0;
	trace_ray((float)x, (float)y, hit, data);
	while (j < 2)
	{
		i = 0;
		while (i < 2)
		{
			if (x + i < data->width && y + j < data->height)
			{
				mlx_put_pixel(data->img, x + i, y + j,
					create_color(hit->color.x, hit->color.y, hit->color.z, 255));
				data->cache[pos] = hit->color;
				pos++;
			}
			i++;
		}
		j++;
	}
}
