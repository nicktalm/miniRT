/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:19:03 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/16 15:36:34 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_pixels(t_data *data)
{
	int	x_max;
	int	y_max;

	data->x_max = data->width / 10;
	data->y_max = data->height / 20;
}


void	creat_img_multi(t_data *data)
{
	int		i;
	t_vec	max;
	t_vec	min;

	i = 0;
	max.x = 0;
	max.y = 0;
	max.z = 0;
	min.x = 0;
	min.y = 0;
	min.z = 0;
	if (data->moved)
	{
		calc_pixels(data);
		init_viewport(data);
	}
	while (i < 200)
	{
		if (data->moved)
		{
			fill_range(data->range, &max, &min, i, data);
			data->range[i].th_nbr = i;
		}
		data->range[i].data = *data;
		pthread_create(&data->range[i].p, NULL, loop_thread, &data->range[i]);
		i++;
	}
	i = 0;
	while (i < 200)
	{
		pthread_join(data->range[i].p, NULL);
		i++;
	}
	data->moved = false;
	data->i++;
}

void	fill_range(t_range *range, t_vec *max, t_vec *min, int i, t_data *data)
{
	if (min->x < data->width && min->y < data->height)
	{
		range[i].x_min = min->x;
		range[i].x_max = min->x + data->x_max;
		range[i].y_min = min->y;
		range[i].y_max = min->y + data->y_max;
	}
	else
	{
		min->y += data->y_max;
		min->x = 0;
		range[i].x_min = min->x;
		range[i].x_max = min->x + data->x_max;
		range[i].y_min = min->y;
		range[i].y_max = min->y + data->y_max;
	}
	min->x = range[i].x_max;
}

void	*loop_thread(void *param)
{
	t_range		*range;
	int			x;
	int			y;
	t_vec		testc;

	range = param;
	y = range->y_min;
	while (y < range->y_max)
	{
		x = range->x_min;
		while (x < range->x_max)
		{
			trace_ray((float)x, (float)y, &range->hit[x + y * range->x_max], &range->data);
			testc = dev_vec_wnbr(range->hit[x + y * range->x_max].color, (float)range->data.i);
			mlx_put_pixel(range->data.img, x, y,
				create_color(testc.x,
					testc.y,
					testc.z, 255));
			x++;
		}
		y++;
	}
	return (NULL);
}
