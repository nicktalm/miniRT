/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:13:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/10 17:20:31 by lbohm            ###   ########.fr       */
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

t_vec	multi_vec(t_vec s1, t_vec s2)
{
	t_vec	result;

	result.x = s1.x * s2.x;
	result.y = s1.y * s2.y;
	result.z = s1.z * s2.z;
	return (result);
}

t_vec	multi_vec_wnbr(t_vec s1, float nbr)
{
	t_vec	result;

	result.x = s1.x * nbr;
	result.y = s1.y * nbr;
	result.z = s1.z * nbr;
	return (result);
}

t_vec	dev_vec(t_vec s1, t_vec s2)
{
	t_vec	result;

	result.x = s1.x / s2.x;
	result.y = s1.y / s2.y;
	result.z = s1.z / s2.z;
	return (result);
}

t_vec	dev_vec_wnbr(t_vec s1, float nbr)
{
	t_vec	result;

	result.x = s1.x / nbr;
	result.y = s1.y / nbr;
	result.z = s1.z / nbr;
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

t_vec	add_vec_wnbr(t_vec s1, float nbr)
{
	t_vec	result;

	result.x = s1.x + nbr;
	result.y = s1.y + nbr;
	result.z = s1.z + nbr;
	return (result);
}

t_vec	ray_vec(t_vec origin, float t, t_vec dir)
{
	return (add_vec(origin, multi_vec_wnbr(dir, t)));
}

t_vec	cross_vec(t_vec s1, t_vec s2)
{
	t_vec	result;

	result.x = (s1.y * s2.z) - (s1.z * s2.y);
	result.y = (s1.z * s2.x) - (s1.x * s2.z);
	result.z = (s1.z * s2.y) - (s1.y * s2.x);
	return (result);
}
