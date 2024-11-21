/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:48:14 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 13:37:28 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_full_r(float result[4][4], float x, float y, float z)
{
	float	mx[4][4];
	float	my[4][4];
	float	mz[4][4];
	float	tmp[4][4];

	rotate_x(mx, x);
	rotate_y(my, y);
	rotate_z(mz, z);
	multi_m(tmp, mx, my);
	multi_m(result, tmp, mz);
}
