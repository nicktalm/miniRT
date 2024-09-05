/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creation_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:57:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/05 19:00:54 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	create_color(float x, float y, float z, int a);

void	create(t_data *data)
{
	t_vec	coords;
	t_vec	viewport;
	t_vec	u;
	t_vec	v;
	t_vec	du;
	t_vec	dv;
	t_vec	upper_left;
	t_vec	p;
	t_vec	center;
	t_vec	ray_dir;
	float	rad;
	float	ratio;

	coords.x = 0;
	coords.y = 0;
	coords.z = 0;
	rad = (float)data->set.cam.fov * (M_PI / 180.0);
	ratio = (float)data->width / (float)data->hight;
	viewport.x = 2 * tan(rad / 2);
	viewport.y = viewport.x / ratio;
	viewport.z = 0;
	u.x = viewport.x;
	u.y = 0;
	u.z = 0;
	v.x = 0;
	v.y = -viewport.y;
	v.z = 0;
	du = dev_vec(u, &data->width, 0);
	// du.x = u.x / data->width;
	// du.y = u.y / data->width;
	// du.z = u.z / data->width;
	dv = dev_vec(v, &data->hight, 0);
	// dv.x = v.x / data->hight;
	// dv.y = v.y / data->hight;
	// dv.z = v.z / data->hight;
	upper_left = sub_vec(sub_vec(data->set.cam.coords, dev_vec(u, (void *)2, 0)), dev_vec(v, (void *)2, 0));
	// upper_left.x = data->set.cam.coords.x - (u.x / 2);
	// upper_left.y = data->set.cam.coords.y - (v.y / 2);
	upper_left.z = 1;
	p = add_vec(upper_left, dev_vec(add_vec(du, dv), (void *)2, 0));
	// p.x = upper_left.x + 0.5 * (du.x + dv.x);
	// p.y = upper_left.y + 0.5 * (du.y + dv.y);
	// p.z = upper_left.z + 0.5 * (du.z + dv.z);
	while (coords.y < data->hight)
	{
		coords.x = 0;
		while (coords.x < data->width)
		{
			center = add_vec(add_vec(multi_vec(du, &coords.x, 0), multi_vec(dv, &coords.y, 0)), p);
			// center.x = p.x + (coords.x * du.x);
			// center.y = p.y + (coords.y * dv.y);
			ray_dir = sub_vec(center, data->set.cam.coords);
			mlx_put_pixel(data->img, coords.x, coords.y, create_color((float)coords.x / ((float)data->width - 1.0), (float)coords.y / ((float)data->hight - 1.0), 0.0, 255));
			coords.x++;
		}
		coords.y++;
	}
}

int	create_color(float x, float y, float z, int a)
{
	int	r;
	int	g;
	int	b;

	r = 255 * x;
	g = 255 * y;
	b = 255 * z;
	return (r << 24 | g << 16 | b << 8 | a);
}
