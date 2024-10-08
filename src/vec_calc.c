/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:13:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/25 10:41:18 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vec3	norm_vec(t_vec3 s1)
{
	float	len;

	len = sqrt((s1.x * s1.x) + (s1.y * s1.y) + (s1.z * s1.z));
	s1.x /= len;
	s1.y /= len;
	s1.z /= len;
	return (s1);
}

float	dot(t_vec3 s1, t_vec3 s2)
{
	return (s1.x * s2.x + s1.y * s2.y + s1.z * s2.z);
}

t_vec3	sub_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x - s2.x;
	result.y = s1.y - s2.y;
	result.z = s1.z - s2.z;
	return (result);
}

t_vec3	multi_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x * s2.x;
	result.y = s1.y * s2.y;
	result.z = s1.z * s2.z;
	return (result);
}

t_vec3	multi_vec_wnbr(t_vec3 s1, float nbr)
{
	t_vec3	result;

	result.x = s1.x * nbr;
	result.y = s1.y * nbr;
	result.z = s1.z * nbr;
	return (result);
}

t_vec3	dev_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x / s2.x;
	result.y = s1.y / s2.y;
	result.z = s1.z / s2.z;
	return (result);
}

t_vec3	dev_vec_wnbr(t_vec3 s1, float nbr)
{
	t_vec3	result;

	result.x = s1.x / nbr;
	result.y = s1.y / nbr;
	result.z = s1.z / nbr;
	return (result);
}

t_vec3	add_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x + s2.x;
	result.y = s1.y + s2.y;
	result.z = s1.z + s2.z;
	return (result);
}

t_vec3	add_vec_wnbr(t_vec3 s1, float nbr)
{
	t_vec3	result;

	result.x = s1.x + nbr;
	result.y = s1.y + nbr;
	result.z = s1.z + nbr;
	return (result);
}

t_vec3	ray_vec(t_vec3 origin, float t, t_vec3 dir)
{
	return (add_vec(origin, multi_vec_wnbr(dir, t)));
}

t_vec3	cross_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = (s1.y * s2.z) - (s1.z * s2.y);
	result.y = (s1.z * s2.x) - (s1.x * s2.z);
	result.z = (s1.z * s2.y) - (s1.y * s2.x);
	return (result);
}

t_vec3	reflect_vec3(t_vec3 s1, t_vec3 s2)
{
	return (sub_vec(s1, multi_vec_wnbr(s2, 2 * dot(s1, s2))));
}

int	cmp_vec(t_vec3 s1, t_vec3 s2)
{
	if (s1.x == s2.x)
	{
		if (s1.y == s2.y)
		{
			if (s1.z == s2.z)
				return (0);
		}
	}
	return (1);
}
