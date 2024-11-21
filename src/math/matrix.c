/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:42:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 11:45:43 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	invert_matrix(float m[4][4], float inv[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			inv[i][j] = m[j][i];
			j++;
		}
		i++;
	}
	inv[0][3] = -m[0][3] * inv[0][0] - m[1][3]
		* inv[0][1] - m[2][3] * inv[0][2];
	inv[1][3] = -m[0][3] * inv[1][0] - m[1][3]
		* inv[1][1] - m[2][3] * inv[1][2];
	inv[2][3] = -m[0][3] * inv[2][0] - m[1][3]
		* inv[2][1] - m[2][3] * inv[2][2];
	inv[3][0] = 0.0;
	inv[3][1] = 0.0;
	inv[3][2] = 0.0;
	inv[3][3] = 1.0;
}

void	multi_m(float result[4][4], float m1[4][4], float m2[4][4])
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = 0;
			result[i][j] += m1[i][0] * m2[0][j]
				+ m1[i][1] * m2[1][j]
				+ m1[i][2] * m2[2][j]
				+ m1[i][3] * m2[3][j];
			j++;
		}
		i++;
	}
}

void	calc_base_angles(t_vec3 normal, float *x, float *z)
{
	double	ratio;

	ratio = sqrt((normal.x * normal.x) + (normal.y * normal.y));
	if (normal.x == 0.0 && normal.y == 0.0 && fabsf(normal.z) == 1.0)
		*x = atan2(normal.z, ratio);
	else
	{
		if (ratio == 0.0)
			*z = M_PI_2;
		else
			*z = acos(normal.y / ratio);
		*x = atan2(normal.z, ratio);
	}
}

void	calc_angle(t_vec3 normal, float *x, float *z)
{
	t_vec3	test;
	t_vec3	test2;

	test = (t_vec3){0, 1, 0};
	calc_base_angles(normal, x, z);
	test2 = cross_vec(normal, test);
	if (test2.z < 0.0)
		*z *= -1.0;
	if (test2.x < 0.0)
	{
		if (*x > 0.0)
			*x *= -1.0;
	}
	else
	{
		if (*x < 0.0)
			*x *= -1.0;
	}
}

void	calc_t(t_abc *formal)
{
	formal->t = (-formal->b - sqrt(formal->dis)) / formal->a;
	if (formal->t <= 0.0 || formal->t >= INFINITY)
	{
		formal->t = (-formal->b + sqrt(formal->dis)) / formal->a;
		if (formal->t <= 0.0 || formal->t >= INFINITY)
			formal->t = __FLT_MAX__;
	}
}
