/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:19:03 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/19 16:17:03 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	creat_img_multi(t_data *data)
{
	int		i;
	t_vec3	min;

	i = 0;
	min.x = 0;
	min.y = 0;
	min.z = 0;
	data->x_max = data->width / 10;
	data->y_max = data->height / 20;
	while (i < 200)
	{
		fill_range(data->range, &min, i, data);
		data->range[i].th_nbr = i;
		data->range[i].data = data;
		pthread_create(&data->range[i].p, NULL, loop_thread, &data->range[i]);
		i++;
	}
	i = 0;
	while (i < 200)
	{
		pthread_join(data->range[i].p, NULL);
		i++;
	}
}

void	fill_range(t_range *range, t_vec3 *min, int i, t_data *data)
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
	t_hitpoint	hit;
	int			x;
	int			y;

	range = param;
	y = range->y_min;
	while (y < range->y_max)
	{
		x = range->x_min;
		while (x < range->x_max)
		{
			hit.color.x = 0.0;
			hit.color.y = 0.0;
			hit.color.z = 0.0;
			super_sampling(range->data, &hit, x, y, range->data->width);
			x++;
		}
		y++;
	}
	return (NULL);
}
