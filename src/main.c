/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/29 18:06:16 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	t_data	data;

	init_data(&data);
	init_mlx(&data);
	create_img(&data);
	mlx_image_to_window(data.window, data.img, 0, 0);
	mlx_loop(data.window);
	mlx_delete_image(data.window, data.img);
	mlx_terminate(data.window);
	free(data.set.sp);
	free(data.set.pl);
	free(data.set.cy);
	return (0);
}

void	init_data(t_data *data)
{
	data->set.ambient.range = 0.2;
	data->set.ambient.color.x = 255;
	data->set.ambient.color.y = 255;
	data->set.ambient.color.z = 255;
	data->set.cam.coords.x = 0.0;
	data->set.cam.coords.y = 0.0;
	data->set.cam.coords.z = -2.0;
	data->set.cam.normalized.x = 0.0;
	data->set.cam.normalized.y = 0.0;
	data->set.cam.normalized.z = 1.0;
	data->set.cam.fov = 90 * (M_PI / 180);
	data->set.light.coords.x = -40.0;
	data->set.light.coords.y = 50.0;
	data->set.light.coords.z = 0.0;
	data->set.light.brightness = 0.6;
	data->set.light.color.x = 10;
	data->set.light.color.y = 0;
	data->set.light.color.z = 255;
	data->set.sp = (t_sphere *)malloc (3 * sizeof(t_sphere));
	if (!data->set.sp)
		return ;
	data->set.pl = (t_plane *)malloc (sizeof(t_plane));
	if (!data->set.pl)
		return ;
	data->set.cy = (t_cylinder *)malloc (sizeof(t_cylinder));
	if (!data->set.cy)
		return ;
	data->set.sp[0].coords.x = 0.0;
	data->set.sp[0].coords.y = 0.0;
	data->set.sp[0].coords.z = 0.0;
	data->set.sp[0].diameter = 0.5;
	data->set.sp[0].color.x = 255;
	data->set.sp[0].color.y = 0;
	data->set.sp[0].color.z = 0;
	data->set.sp[1].coords.x = 2.0;
	data->set.sp[1].coords.y = 0.0;
	data->set.sp[1].coords.z = 20;
	data->set.sp[1].diameter = 2;
	data->set.sp[1].color.x = 0;
	data->set.sp[1].color.y = 0;
	data->set.sp[1].color.z = 255;
	data->set.sp[2].coords.x = -2.0;
	data->set.sp[2].coords.y = 0.0;
	data->set.sp[2].coords.z = 5;
	data->set.sp[2].diameter = 2;
	data->set.sp[2].color.x = 0;
	data->set.sp[2].color.y = 255;
	data->set.sp[2].color.z = 0;
	data->set.pl[0].coords.x = 0.0;
	data->set.pl[0].coords.y = 0.0;
	data->set.pl[0].coords.z = -10.0;
	data->set.pl[0].normalized.x = 0.0;
	data->set.pl[0].normalized.y = 1.0;
	data->set.pl[0].normalized.z = 0.0;
	data->set.pl[0].color.x = 0;
	data->set.pl[0].color.y = 0;
	data->set.pl[0].color.z = 225;
	data->set.cy[0].coords.x = 50.0;
	data->set.cy[0].coords.y = 0.0;
	data->set.cy[0].coords.z = 20.6;
	data->set.cy[0].normalized.x = 0.0;
	data->set.cy[0].normalized.y = 0.0;
	data->set.cy[0].normalized.z = 1.0;
	data->set.cy[0].diameter = 14.2;
	data->set.cy[0].height = 21.42;
	data->set.cy[0].color.x = 10;
	data->set.cy[0].color.y = 0;
	data->set.cy[0].color.z = 255;
	data->aspect_ratio = 16.0 / 9.0;
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(1600, 900, "miniRT", true);
	data->img = mlx_new_image(data->window, 1600, 900);
}

void	create_img(t_data *data)
{
	t_vec	coords;
	t_vec	test;
	t_vec	color;

	coords.y = 0.0;
	coords.z = -1.0;
	while (coords.y < 900.0)
	{
		coords.x = 0.0;
		while (coords.x < 1600.0)
		{
			test.x = (coords.x * 2) / 1600.0 - 1;
			test.y = 1 - ((coords.y * 2) / 900.0);
			test.z = -1.0;
			if (hit_sphere(data, test))
			{
				color.x = 255 * data->t1.x;
				color.y = 0 * data->t1.y;
				color.z = 0 * data->t1.z;
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(color.x, color.y, color.z, 255));
			}
			coords.x++;
		}
		coords.y++;
	}
}

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	hit_sphere(t_data *data, t_vec test)
{
	float	a;
	float	b;
	float	c;
	float	dis;

	a = pow(test.x, 2.0) + pow(test.y, 2.0) + pow(test.z, 2.0);
	b = 2.0 * (data->set.cam.coords.x * test.x + data->set.cam.coords.y * test.y + data->set.cam.coords.z * test.z);
	c = pow(data->set.cam.coords.x, 2.0) + pow(data->set.cam.coords.y, 2.0) + pow(data->set.cam.coords.z, 2.0) - pow(data->set.sp->diameter / 2.0, 2.0);
	dis = b * b - 4.0 * a * c;
	if (dis > 0.0)
	{
		data->t1.x = (-b - sqrt(dis)) / 2 * a;
		data->t1.y = data->set.cam.coords.x + (test.x * data->t1.x);
		data->t2.x = (-b + sqrt(dis)) / 2 * a;
		data->t2.y = data->set.cam.coords.y + (test.y * data->t2.x);
		return (true);
	}
	else if (dis == 0.0)
	{
		data->t1.x = 0.0;
		data->t1.y = 0.0;
		data->t1.z = 0.0;
		data->t2.x = 0.0;
		data->t2.y = 0.0;
		data->t2.z = 0.0;
		return (true);
	}
	return (false);
}
