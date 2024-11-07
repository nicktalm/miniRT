/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:42:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/07 17:32:15 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	invert_matrix(float m[4][4], float inv[4][4])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			inv[i][j] = m[j][i];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		inv[i][3] = 0.0;
		inv[3][i] = 0.0;
		for (int j = 0; j < 3; j++)
		{
			inv[i][3] -= inv[i][j] * m[j][3];
		}
	}
	inv[3][3] = 1.0;
}

void	identity_m(float m[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}
}

void	swap_rows(float m[4][4], int row1, int row2)
{
	for (int i = 0; i < 4; i++)
	{
		float temp = m[row1][i];
		m[row1][i] = m[row2][i];
		m[row2][i] = temp;
	}
}

void	create_m_inverse(float m[4][4], float inverse[4][4])
{
	int	i, j, k;
	float ratio;

	identity_m(inverse);

	// Create augmented matrix [m | I]
	float augmented[4][8];
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			augmented[i][j] = m[i][j];
			augmented[i][j + 4] = inverse[i][j];
		}
	}

	// Perform Gaussian elimination with partial pivoting
	for (i = 0; i < 4; i++)
	{
		// Partial pivoting
		int max_row = i;
		for (k = i + 1; k < 4; k++)
		{
			if (fabs(augmented[k][i]) > fabs(augmented[max_row][i]))
			{
				max_row = k;
			}
		}
		if (max_row != i)
		{
			for (j = 0; j < 8; j++)
			{
				float temp = augmented[i][j];
				augmented[i][j] = augmented[max_row][j];
				augmented[max_row][j] = temp;
			}
		}

		// Check for singular matrix
		if (fabs(augmented[i][i]) < 1e-6)
		{
			fprintf(stderr, "Matrix is singular and cannot be inverted.\n");
			return;
		}

		// Normalize the pivot row
		ratio = augmented[i][i];
		for (j = 0; j < 8; j++)
		{
			augmented[i][j] /= ratio;
		}

		// Eliminate the current column in other rows
		for (k = 0; k < 4; k++)
		{
			if (k != i)
			{
				ratio = augmented[k][i];
				for (j = 0; j < 8; j++)
				{
					augmented[k][j] -= ratio * augmented[i][j];
				}
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			inverse[i][j] = augmented[i][j + 4];
		}
	}
}

// void	create_m_inverse(float m[4][4], float inverse[4][4])
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		l;
// 	float	ratio;

// 	i = 0;
// 	k = 0;
// 	ratio = 0.0;
// 	identity_m(inverse);
// 	while (i < 4)
// 	{
// 		if (m[i][i] == 0.0)
// 			break ;
// 		ratio = m[i][i];
// 		j = 0;
// 		while (j < 4)
// 		{
// 			m[i][j] /= ratio;
// 			inverse[i][j] /= ratio;
// 			j++;
// 		}
// 		k = 0;
// 		while (k < 4)
// 		{
// 			if (k != i)
// 			{
// 				ratio = m[k][i];
// 				l = 0;
// 				while (l < 4)
// 				{
// 					m[k][l] -= ratio * m[i][l];
// 					inverse[k][l] -= ratio * inverse[i][l];
// 					l++;
// 				}
// 			}
// 			k++;
// 		}
// 		i++;
// 	}
// }

// void	identity_m(float m[4][4])
// {
// 	m[0][0] = 1;
// 	m[0][1] = 0;
// 	m[0][2] = 0;
// 	m[0][3] = 0;
// 	m[1][0] = 0;
// 	m[1][1] = 1;
// 	m[1][2] = 0;
// 	m[1][3] = 0;
// 	m[2][0] = 0;
// 	m[2][1] = 0;
// 	m[2][2] = 1;
// 	m[2][3] = 0;
// 	m[3][0] = 0;
// 	m[3][1] = 0;
// 	m[3][2] = 0;
// 	m[3][3] = 1;
// }

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

void	print_m(float m[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("m[%i][%i] = %f ", i, j, m[i][j]);
		printf("\n");
	}
	printf("\n");
}
