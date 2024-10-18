/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/17 20:08:50 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	tmp_color(t_data *data, t_ray ray, t_hitpoint *hit);

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
		ray.direction = sub_vec(pixle_center, sub_vec(data->set.cam.coords, data->set.cam.direction));
		tmp_color(data, ray, hit);
	}
}

void	tmp_color(t_data *data, t_ray ray, t_hitpoint *hit)
{
	check_hit(ray, hit, data);
	if (hit->t != __FLT_MAX__)
	{
		if (data->set.obj[hit->i].type == PLANE)
			shading(data, hit, data->set.obj[hit->i].form.pl.color, 0);
		else if (data->set.obj[hit->i].type == SPHERE)
			shading(data, hit, data->set.obj[hit->i].form.sp.color, 2);
		else
			shading(data, hit, data->set.obj[hit->i].form.cy.color, 1);
	}
	else
		hit->color = data->bg;
}
