/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:46:05 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/04 21:11:54 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	check_hit(t_ray *ray, t_hitpoint *hit, t_data *data)
{
	int		i;

	i = 0;
	hit->i = 0;
	hit->t = __FLT_MAX__;
	while (i < data->set.obj_count)
	{
		if (data->set.obj[i].type == SPHERE)
			calc_sp(data->set.obj[i].form.sp,
				transform_ray(ray, data->set.obj[i]), hit, i);
		else if (data->set.obj[i].type == PLANE)
			calc_pl(data->set.obj[i].form.pl,
				transform_ray(ray, data->set.obj[i]), hit, i);
		else if (data->set.obj[i].type == CYLINDER)
			calc_cy(data->set.obj[i].form.cy,
				transform_ray(ray, data->set.obj[i]), hit, i);
		else
			calc_cn(data->set.obj[i].form.cn,
				transform_ray(ray, data->set.obj[i]), hit, i);
		i++;
	}
	if (data->set.obj_count != 0)
		in_out_object(ray, hit);
}
