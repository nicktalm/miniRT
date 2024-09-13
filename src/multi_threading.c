/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:19:03 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/13 17:12:47 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_pixels(t_data *data)
{
	int	all_p;
	int	x_max;
	int	y_max;

	all_p = data->width * data->height;
	data->x_max = all_p / 200;
	data->y_max = all_p / 200;
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
	calc_pixels(data);
	while (i < 200)
	{
		fill_range(data->range, &max, &min, i, data);
		pthread_create(&data->c.hit->p, NULL, loop_thread, data);
	}
}

void	fill_range(t_range *range, t_vec *max, t_vec *min, int i, t_data *data)
{
	if (min->x < data->x_max && min->y < data->height)
	{
		range[i].x_min = min->x;
		range[i].x_max = max->x + data->x_max;
		range[i].y_min = min->y;
		range[i].y_max = max->y + data->y_max;
	}
	else
	{
		min->y += data->y_max;
		min->x = 0;
		max->x = data->x_max;
		range[i].x_min = min->x;
		range[i].x_max = max->x + data->x_max;
		range[i].y_min = min->y;
		range[i].y_max = max->y + data->y_max;
	}
	min->x = range[i].x_max;
	min->y = range[i].y_max;
}

void	loop_thread(t_data *data)
{
	
}
