/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:28:26 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/21 13:29:10 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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