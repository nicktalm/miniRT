/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:13:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/05 19:01:34 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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

t_vec	sub_vec(t_vec s1, t_vec s2)
{
	t_vec	result;

	result.x = s1.x - s2.x;
	result.y = s1.y - s2.y;
	result.z = s1.z - s2.z;
	return (result);
}

t_vec	multi_vec(t_vec s1, void *s2, int check)
{
	t_vec	result;
	t_vec	tmp;
	float	tmpd;

	if (check)
	{
		tmp = *(t_vec *)s2;
		result.x = s1.x * tmp.x;
		result.y = s1.y * tmp.y;
		result.z = s1.z * tmp.z;
	}
	else
	{
		tmpd = *(float *)s2;
		result.x = s1.x * tmpd;
		result.y = s1.y * tmpd;
		result.z = s1.z * tmpd;
	}
	return (result);
}

t_vec	dev_vec(t_vec s1, void *s2, int check)
{
	t_vec	result;
	t_vec	tmp;
	float	tmpd;

	if (check)
	{
		tmp = *(t_vec *)s2;
		result.x = s1.x / tmp.x;
		result.y = s1.y / tmp.y;
		result.z = s1.z / tmp.z;
	}
	else
	{
		tmpd = *(float *)s2;
		printf("tmpd = %f\n", tmpd);
		result.x = s1.x / tmpd;
		result.y = s1.y / tmpd;
		result.z = s1.z / tmpd;
	}
	return (result);
}

t_vec	add_vec(t_vec s1, t_vec s2)
{
	t_vec	result;

	result.x = s1.x + s2.x;
	result.y = s1.y + s2.y;
	result.z = s1.z + s2.z;
	return (result);
}

