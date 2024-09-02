/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/02 15:57:27 by lbohm            ###   ########.fr       */
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
	mlx_loop_hook(data.window, hook, &data);
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
	data->set.cam.coords.z = 3.0;
	data->set.cam.normalized.x = 0.0;
	data->set.cam.normalized.y = 0.0;
	data->set.cam.normalized.z = 1.0;
	data->set.cam.fov = 90 * (M_PI / 180);
	data->set.light.coords.x = -10.0;
	data->set.light.coords.y = -10.0;
	data->set.light.coords.z = -4.0;
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
	data->set.sp[0].diameter = 2;
	data->set.sp[0].color.x = 255;
	data->set.sp[0].color.y = 0;
	data->set.sp[0].color.z = 0;
	data->set.sp[1].coords.x = 2.0;
	data->set.sp[1].coords.y = 0.0;
	data->set.sp[1].coords.z = 0.0;
	data->set.sp[1].diameter = 2;
	data->set.sp[1].color.x = 0;
	data->set.sp[1].color.y = 0;
	data->set.sp[1].color.z = 255;
	data->set.sp[2].coords.x = -2.0;
	data->set.sp[2].coords.y = 0.0;
	data->set.sp[2].coords.z = 0.0;
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
	data->width = 1600;
	data->hight = 900;
	data->dpi = 100;
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
	float	light;
	t_vec	color;

	coords.y = 0.0;
	coords.z = -1.0;
	data->set.light.coords = norm_vec(data->set.light.coords);
	data->set.light.coords.x *= -1;
	data->set.light.coords.y *= -1;
	data->set.light.coords.z *= -1;
	while (coords.y < data->hight)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			test.x = (coords.x * 2) / (float)data->width - 1;
			test.y = 1 - ((coords.y * 2) / (float)data->hight);
			test.z = -1.0;
			test.x *= data->aspect_ratio;
			if (hit_sphere(data, test, &data->set.sp[0]))
			{
				light = dot(data->norm_t1, data->set.light.coords);
				light < 0.0 ? light = 0.0 : light;
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(data->set.sp[0].color.x * light, data->set.sp[0].color.y * light, data->set.sp[0].color.z * light, 255));
			}
			else
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(0, 0, 0, 100));
			coords.x++;
		}
		coords.y++;
	}
}

int	get_color(int r, int g, int b, int a)
{
	r > 255 ? r = 255 : r < 0 ? r = 0 : r;
	g > 255 ? g = 255 : g < 0 ? g = 0 : g;
	b > 255 ? b = 255 : b < 0 ? b = 0 : b;
	a > 255 ? a = 255 : a < 0 ? a = 0 : a;
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	hit_sphere(t_data *data, t_vec test, t_sphere *sp)
{
	float	a;
	float	b;
	float	c;
	float	dis;
	float	t1;
	float	t2;

	a = pow(test.x, 2.0) + pow(test.y, 2.0) + pow(test.z, 2.0);
	b = 2.0 * (data->set.cam.coords.x * test.x + data->set.cam.coords.y * test.y + data->set.cam.coords.z * test.z);
	c = pow(data->set.cam.coords.x, 2.0) + pow(data->set.cam.coords.y, 2.0) + pow(data->set.cam.coords.z, 2.0) - pow(sp->diameter / 2.0, 2.0);
	dis = b * b - 4.0 * a * c;
	if (dis >= 0.0)
	{
		t1 = (-b - sqrt(dis)) / 2 * a;
		data->t1.x = data->set.cam.coords.x + (test.x * t1);
		data->t1.y = data->set.cam.coords.y + (test.y * t1);
		data->t1.z = data->set.cam.coords.z + (test.z * t1);
		data->norm_t1.x = data->t1.x - sp->coords.x;
		data->norm_t1.y = data->t1.y - sp->coords.y;
		data->norm_t1.z = data->t1.z - sp->coords.z;
		data->norm_t1 = norm_vec(data->t1);
		return (true);
	}
	return (false);
}

t_vec	norm_vec(t_vec s1)
{
	float	len;

	len = sqrt(pow(s1.x, 2) + pow(s1.y, 2) + pow(s1.z, 2));
	s1.x /= len;
	s1.y /= len;
	s1.z /= len;
	return (s1);
}

float	dot(t_vec s1, t_vec s2)
{
	return (s1.x * s2.x + s1.y * s2.y + s1.z * s2.z);
}

void	resize(int width, int hight, void *param)
{
	t_data	*data;

	data = param;
	data->hight = hight;
	data->width = width;
	data->aspect_ratio = (float)width / (float)hight;
}

void	hook(void *param)
{
	t_data	*data;
	double	time;

	data = param;
	time = mlx_get_time();
	mlx_key_hook(data->window, key, data);
	mlx_cursor_hook(data->window, cursor, data);
	mlx_resize_hook(data->window, resize, data);
	mlx_delete_image(data->window, data->img);
	data->img = mlx_new_image(data->window, data->width, data->hight);
	changed_img(data);
	mlx_image_to_window(data->window, data->img, 0, 0);
	printf("time = %f\n", (mlx_get_time() - time) * 1000);
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_W && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.z -= 0.5;
	if (keydata.key == MLX_KEY_S && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.z += 0.5;
	if (keydata.key == MLX_KEY_A && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.x += 0.5;
	if (keydata.key == MLX_KEY_D && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.x -= 0.5;
	if (keydata.key == MLX_KEY_Q && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.y -= 0.5;
	if (keydata.key == MLX_KEY_E && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.y += 0.5;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
	{
		mlx_delete_image(data->window, data->img);
		mlx_terminate(data->window);
		free(data->set.sp);
		free(data->set.pl);
		free(data->set.cy);
		exit(0);
	}
}

void	cursor(double xpos, double ypos, void *param)
{
	t_data	*data;

	data = param;
	static int	mouseX = 0;
	static int	mouseY = 0;

	if (!mouseX && !mouseY)
	{
		mouseX = xpos / data->dpi;
		mouseY = ypos / data->dpi;
	}
	else
	{
		// printf("xpos = %f ypos = %f\n", xpos, ypos);
		if (mlx_is_mouse_down(data->window, MLX_MOUSE_BUTTON_LEFT))
		{
			data->set.light.coords.x -= ((float)xpos / data->dpi) - (float)mouseX;
			data->set.light.coords.z -= ((float)ypos / data->dpi) - (float)mouseY;
			// printf("light x = %f\n", data->set.light.coords.x);
			// printf("light y = %f\n", data->set.light.coords.y);
			// data->set.light.coords.z -= (float)nowX - (float)mouseX;
			data->set.light.coords = norm_vec(data->set.light.coords);
		}
		else
		{
			mouseX = 0;
			mouseY = 0;
		}
	}
}

void	changed_img(t_data *data)
{
	t_vec	coords;
	t_vec	test;
	float	light;
	t_vec	color;

	coords.y = 0.0;
	coords.z = -1.0;
	while (coords.y < data->hight)
	{
		coords.x = 0.0;
		while (coords.x < data->width)
		{
			test.x = (coords.x * 2) / (float)data->width - 1;
			test.y = 1 - ((coords.y * 2) / (float)data->hight);
			test.z = -1.0;
			test.x *= data->aspect_ratio;
			if (hit_sphere(data, test, &data->set.sp[0]))
			{
				light = dot(data->norm_t1, data->set.light.coords);
				light < 0.0 ? light = 0.0 : light;
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(data->set.sp[0].color.x * light, data->set.sp[0].color.y * light, data->set.sp[0].color.z * light, 255));
			}
			else
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(0, 0, 0, 100));
			coords.x++;
		}
		coords.y++;
	}
}
