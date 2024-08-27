/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/27 11:27:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	t_data	data;

	init_data(&data);
	data.color.x = 10;
	data.color.y = 10;
	data.color.z = 255;
	init_mlx(&data);
	test(&data);
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
	data->set.cam.coords.x = -50.0;
	data->set.cam.coords.y = 0;
	data->set.cam.coords.z = 20;
	data->set.cam.normalized.x = 0.0;
	data->set.cam.normalized.y = 0.0;
	data->set.cam.normalized.z = 1.0;
	data->set.cam.fov = 70;
	data->set.light.coords.x = -40.0;
	data->set.light.coords.y = 50.0;
	data->set.light.coords.z = 0.0;
	data->set.light.brightness = 0.6;
	data->set.light.color.x = 10;
	data->set.light.color.y = 0;
	data->set.light.color.z = 255;
	data->set.sp = (t_sphere *)malloc (sizeof(t_sphere));
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
	data->set.sp[0].coords.z = 20.6;
	data->set.sp[0].diameter = 12.6;
	data->set.sp[0].color.x = 10;
	data->set.sp[0].color.y = 0;
	data->set.sp[0].color.z = 255;
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
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(1600, 900, "miniRT", true);
	data->img = mlx_new_image(data->window, 1600, 900);
}

void	test(t_data *data)
{
	int		i;
	int		j;
	int		r;
	int		g;
	int		b;
	float	grade;

	i = 0;
	j = 0;
	grade = 0.0;
	while (j < 900)
	{
		i = 0;
		while (i < 1600)
		{
			grade = (float)j / 900.0;
			r = (1 - grade) * data->color.x + grade * 255;
			g = (1 - grade) * data->color.y + grade * 255;
			b = (1 - grade) * data->color.z + grade * 255;
			r > 255 ? r = 255 : r;
			g > 255 ? g = 255 : g;
			b > 255 ? b = 255 : b;
			mlx_put_pixel(data->img, i, j, get_color(r, g, b, 255));
			i++;
		}
		j++;
	}
}

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
