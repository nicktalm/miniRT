/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:42:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/10 12:16:49 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_m_inverse(float m[4][4], float inverse[4][4])
{
	int		i;
	int		j;
	int		k;
	int		l;
	float	ratio;

	i = 0;
	k = 0;
	ratio = 0.0;
	identity_m(inverse);
	while (i < 4)
	{
		if (m[i][i] == 0.0)
			break ;
		ratio = m[i][i];
		j = 0;
		while (j < 4)
		{
			m[i][j] /= ratio;
			inverse[i][j] /= ratio;
			j++;
		}
		k = 0;
		while (k < 4)
		{
			if (k != i)
			{
				ratio = m[k][i];
				l = 0;
				while (l < 4)
				{
					m[k][l] -= ratio * m[i][l];
					inverse[k][l] -= ratio * inverse[i][l];
					l++;
				}
			}
			k++;
		}
		i++;
	}
}

void	identity_m(float m[4][4])
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void	copy_m(float result[4][4], float m[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = m[i][j];
			j++;
		}
		i++;
	}
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
			result[i][j] = m1[i][0] * m2[0][j]
				+ m1[i][1] * m2[1][j]
				+ m1[i][2] * m2[2][j]
				+ m1[i][3] * m2[3][j];
			j++;
		}
		i++;
	}
}
