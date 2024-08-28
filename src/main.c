/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/28 17:22:54 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	t_data	data;

	init_data(&data);
	data.aspect_ratio = 16.0 / 9.0;
	data.color.x = 10;
	data.color.y = 10;
	data.color.z = 255;
	init_mlx(&data);
	calc_vpw(&data);
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
	data->set.sp[0].coords.z = 4;
	data->set.sp[0].diameter = 2;
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
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(1600, 900, "miniRT", true);
	data->img = mlx_new_image(data->window, 1600, 900);
}

// void	test(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	int		r;
// 	int		g;
// 	int		b;
// 	float	grade;

// 	data->aspect_ratio = 16.0 / 9.0;
// 	i = 0;
// 	j = 0;
// 	grade = 0.0;
// 	while (j < 900)
// 	{
// 		i = 0;
// 		while (i < 1600)
// 		{
// 			grade = (float)j / 900.0;
// 			r = (1 - grade) * data->color.x + grade * 255;
// 			g = (1 - grade) * data->color.y + grade * 255;
// 			b = (1 - grade) * data->color.z + grade * 255;
// 			r > 255 ? r = 255 : r;
// 			g > 255 ? g = 255 : g;
// 			b > 255 ? b = 255 : b;
// 			if (!hit_sphere(data, view_point_x(i), view_point_y(j)))
// 				mlx_put_pixel(data->img, i, j, get_color(r, g, b, 255));
// 			else
// 				mlx_put_pixel(data->img, i, j, get_color(data->set.sp->color.x, data->set.sp->color.y, data->set.sp->color.z, 255));
// 			i++;
// 		}
// 		j++;
// 	}
// }

void	test(t_data *data)
{
	int	x;
	int	y;
	int	i;
	float	grade;
	t_vec	sub;

	x = 0;
	y = 0;
	i = 0;
	data->vph = data->vpw * (1600 / 900);
	while (y < 900)
	{
		x = 0;
		while (x < 1600)
		{
			i = 0;
			while (i < 3)
			{
				grade = hit_sphere(view_point_x(x, data), view_point_y(y, data), &data->set.sp[i]);
				if (grade)
				{
					sub.x = grade;
					sub.y = grade;
					sub.z = grade;
					sub = sub_vec(sub, )
					data->set.sp[i].color = grade_color(data->set.sp[i].color, grade);
					mlx_put_pixel(data->img, x, y, get_color(data->set.sp[i].color.x, data->set.sp[i].color.y, data->set.sp[i].color.z, 255));
				}
				i++;
			}
			x++;
		}
		y++;
	}
}

t_vec	grade_color(t_vec color, float grade)
{
	t_vec	result;

	result.x = (1.0 - grade) * color.x + grade * 255.0;
	result.y = (1.0 - grade) * color.y + grade * 0.0;
	result.z = (1.0 - grade) * color.z + grade * 0.0;
	return (result);
}

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// float	view_point_x(int value, t_data *data)
// {
// 	return (((((float)value - (float)data->set.cam.coords.x) - 1600.0 / 2) / 1600.0) * data->vpw);
// }

// float	view_point_y(int value, t_data *data)
// {
// 	return ((900.0 / 2 - ((float)value) - (float)data->set.cam.coords.y) / 900.0 * data->vph);
// }

float	view_point_x(int value, t_data *data)
{
	float	result;

	result = ((float)value + 0.5) / 1600.0;
	return ((2.0 * result - 1.0) * data->aspect_ratio * tan(data->set.cam.fov / 2.0));
}

float	view_point_y(int value, t_data *data)
{
	float	result;

	result = ((float)value + 0.5) / 900.0;
	return (1.0 - 2.0 * result * tan(data->set.cam.fov / 2.0));
}

float	hit_sphere(float x, float y, t_sphere *sp)
{
	float	a;
	float	b;
	float	c;
	float	r;
	t_vec	start;
	t_vec	soll;
	float	result;

	// printf("x = %f y = %f\n", x, y);
	start.x = sp->coords.x;
	start.y = sp->coords.y;
	start.z = sp->coords.z;
	soll.x = x;
	soll.y = y;
	soll.z = 1;
	r = sp->diameter / 2;
	a = multi_vec(soll, soll);
	b = 2.0 * multi_vec(start, soll);
	c = multi_vec(start, start) - r * r;
	result = (b * b) - (4 * a * c);
	if (result > 0)
		return ((-b - sqrt(result)) / 2.0 * a);
	else
		return (0);
}

float	multi_vec(t_vec s1, t_vec s2)
{
	return (s1.x * s2.x + s1.y * s2.y + s1.z * s2.z);
}

t_vec	sub_vec(t_vec s1, t_vec s2)
{
	t_vec	result;

	result.x = s1.x - s2.x;
	result.y = s1.y - s2.y;
	result.z = s1.z - s2.z;
	return (result);
}

t_vec	norm_vec(t_vec s1)
{
	t_vec	result;
	float	magnitude;

	magnitude = sqrt(s1.x * s1.x + s1.y * s1.y + s1.z * s1.z);
	result.x = s1.x / magnitude;
	result.y = s1.y / magnitude;
	result.z = s1.z / magnitude;
	return (result);
}

void	calc_vpw(t_data *data)
{
	data->vpw = 2 * 1 * tan(data->set.cam.fov);
}
