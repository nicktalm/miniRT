/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:46:05 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/07 21:37:54 by lucabohn         ###   ########.fr       */
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
			calc_sp(data->set.obj[i].form.sp, *ray, hit, i);
		else if (data->set.obj[i].type == PLANE)
			calc_pl(data->set.obj[i].form.pl, *ray, hit, i);
		else if (data->set.obj[i].type == CYLINDER)
			calc_cy(data->set.obj[i].form.cy, *ray, hit, i);
		else
			calc_cn(data->set.obj[i].form.cn, *ray, hit, i);
		i++;
	}
	if (data->set.obj_count != 0)
		in_out_object(ray, hit);
}
