/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/02 21:56:59 by lucabohn         ###   ########.fr       */
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
	free(data.caches);
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
	data->set.sp[0].radius = data->set.sp[0].diameter / 2;
	data->set.sp[0].color.x = 255;
	data->set.sp[0].color.y = 0;
	data->set.sp[0].color.z = 0;
	data->set.sp[1].coords.x = 2.0;
	data->set.sp[1].coords.y = 0.0;
	data->set.sp[1].coords.z = 0.0;
	data->set.sp[1].diameter = 2;
	data->set.sp[1].radius = data->set.sp[1].diameter / 2;
	data->set.sp[1].color.x = 0;
	data->set.sp[1].color.y = 0;
	data->set.sp[1].color.z = 255;
	data->set.sp[2].coords.x = -2.0;
	data->set.sp[2].coords.y = 0.0;
	data->set.sp[2].coords.z = 0.0;
	data->set.sp[2].diameter = 2;
	data->set.sp[2].radius = data->set.sp[2].diameter / 2;
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
	data->width = 900;
	data->hight = 900;
	data->aspect_ratio = data->width / data->hight;
	data->dpi = 10;
	data->caches = (t_vec *)malloc(sizeof(t_vec) * data->width * data->hight);
	if (!data->caches)
		return ;
	data->pos = 0;
	data->moved = true;
	data->set.light.normalized = norm_vec(data->set.light.coords);
	data->set.light.normalized.x *= -1;
	data->set.light.normalized.y *= -1;
	data->set.light.normalized.z *= -1;
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(data->width, data->hight, "miniRT", true);
	data->img = mlx_new_image(data->window, data->width, data->hight);
}

void	create_img(t_data *data)
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
				light = dot(data->caches[data->pos], data->set.light.normalized);
				light < 0.0 ? light = 0.0 : light;
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(data->set.sp[0].color.x * light, data->set.sp[0].color.y * light, data->set.sp[0].color.z * light, 255));
			}
			else
				mlx_put_pixel(data->img, coords.x, coords.y, get_color(0, 0, 0, 100));
			coords.x++;
		}
		coords.y++;
	}
	data->moved = false;
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

	a = (test.x * test.x) + (test.y * test.y)+ (test.z * test.z);
	b = 2.0 * (data->set.cam.coords.x * test.x + data->set.cam.coords.y * test.y + data->set.cam.coords.z * test.z);
	c = (data->set.cam.coords.x * data->set.cam.coords.x) + (data->set.cam.coords.y * data->set.cam.coords.y) + (data->set.cam.coords.z * data->set.cam.coords.z) - (sp->radius * sp->radius);
	dis = b * b - 4.0 * a * c;
	if (dis >= 0.0)
	{
		if (data->moved)
		{
			t1 = (-b - sqrt(dis)) / 2 * a;
			data->t1.x = data->set.cam.coords.x + (test.x * t1);
			data->t1.y = data->set.cam.coords.y + (test.y * t1);
			data->t1.z = data->set.cam.coords.z + (test.z * t1);
			data->t1.x -= sp->coords.x;
			data->t1.y -= sp->coords.y;
			data->t1.z -= sp->coords.z;
			data->caches[data->pos] = norm_vec(data->t1);
		}
		if (data->pos == data->hight * data->width)
				data->pos = 0;
		data->pos++;
		return (true);
	}
	if (data->pos == data->hight * data->width)
		data->pos = 0;
	data->pos++;
	return (false);
}

t_vec	norm_vec(t_vec s1)
{
	float	len;

	len = sqrt((s1.x * s1.x) + (s1.y * s1.y) + (s1.z * s1.z));
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
	data->moved = true;
	data->pos = 0;
	free(data->caches);
	data->caches = (t_vec *)malloc (sizeof(t_vec) * data->width * data->hight);
	if (!data->caches)
		printf("error\n");
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
	create_img(data);
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
		free(data->caches);
		exit(0);
	}
	data->moved = true;
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
		if (mlx_is_mouse_down(data->window, MLX_MOUSE_BUTTON_LEFT))
		{
			data->set.light.coords.x -= ((float)xpos / data->dpi) - (float)mouseX;
			data->set.light.coords.z -= ((float)ypos / data->dpi) - (float)mouseY;
			data->set.light.normalized = norm_vec(data->set.light.coords);
			data->set.light.normalized.x *= -1;
			data->set.light.normalized.y *= -1;
			data->set.light.normalized.z *= -1;
		}
		else
		{
			mouseX = 0;
			mouseY = 0;
		}
	}
	data->moved = true;
}

// void	changed_img(t_data *data)
// {
// 	t_vec	coords;
// 	t_vec	test;
// 	float	light;
// 	t_vec	color;

// 	coords.y = 0.0;
// 	coords.z = -1.0;
// 	while (coords.y < data->hight)
// 	{
// 		coords.x = 0.0;
// 		while (coords.x < data->width)
// 		{
// 			test.x = (coords.x * 2) / (float)data->width - 1;
// 			test.y = 1 - ((coords.y * 2) / (float)data->hight);
// 			test.z = -1.0;
// 			test.x *= data->aspect_ratio;
// 			if (hit_sphere(data, test, &data->set.sp[0]))
// 			{
// 				light = dot(data->caches[data->pos], data->set.light.coords);
// 				light < 0.0 ? light = 0.0 : light;
// 				mlx_put_pixel(data->img, coords.x, coords.y, get_color(data->set.sp[0].color.x * light, data->set.sp[0].color.y * light, data->set.sp[0].color.z * light, 255));
// 			}
// 			else
// 				mlx_put_pixel(data->img, coords.x, coords.y, get_color(0, 0, 0, 100));
// 			coords.x++;
// 		}
// 		coords.y++;
// 	}
// 	data->moved = false;
// }
