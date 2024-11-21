/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:19:03 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 10:19:03 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	creat_img_multi(t_data *data)
{
	int		pos;
	int		i;
	t_vec3	min;
	t_range	range[200];

	i = 0;
	min.x = 0;
	min.y = 0;
	min.z = 0;
	data->x_max = data->width / 10;
	data->y_max = data->height / 20;
	i = 0;
	while (i < 200)
	{
		fill_range(&range[i], &min, data);
		range[i].th_nbr = i;
		range[i].data = *data;
		pthread_create(&range[i].p, NULL, loop_thread, &range[i]);
		i++;
	}
	i = 0;
	while (i < 200)
	{
		pthread_join(range[i].p, NULL);
		i++;
	}
}

void	fill_range(t_range *range, t_vec3 *min, t_data *data)
{
	if (min->x < data->width && min->y < data->height)
	{
		range->x_min = min->x;
		range->x_max = min->x + data->x_max;
		range->y_min = min->y;
		range->y_max = min->y + data->y_max;
	}
	else
	{
		min->y += data->y_max;
		min->x = 0;
		range->x_min = min->x;
		range->x_max = min->x + data->x_max;
		range->y_min = min->y;
		range->y_max = min->y + data->y_max;
	}
	min->x = range->x_max;
}

void	*loop_thread(void *param)
{
	t_range		*range;
	int			x;
	int			y;
	int			i;

	i = 0;
	range = param;
	y = range->y_min;
	while (y < range->y_max)
	{
		x = range->x_min;
		while (x < range->x_max)
		{
			super_sampling(&range->data, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}
