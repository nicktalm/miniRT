/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:03:31 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/21 19:19:00 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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
	render_message(data, x, y);
}

void	render_animation(int *dot)
{
	if (*dot == 1)
		printf(".");
	else if (*dot == 2)
		printf("..");
	else if (*dot == 3)
	{
		printf("...");
		*dot = 0;
	}
	(*dot)++;
}

void	render_message(t_data *data, int x, int y)
{
	static int	dot = 1;
	static int	pixel_counter = 0;

	pixel_counter++;
	if (pixel_counter == 100)
	{
		printf("\033[sRendering image\033[0J");
		render_animation(&dot);
		printf("\033[u");
		printf("\033[?25l");
		pixel_counter = 0;
	}
	if ((x + y * data->width) >= data->width * data->height - 1)
	{
		printf("\033[K");
		printf("\033[32mRendering complete!\033[0m\n");
		printf("\033[?25h");
	}
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
