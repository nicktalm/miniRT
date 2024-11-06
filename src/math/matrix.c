/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:42:39 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/06 22:01:30 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

#include <stdbool.h>

bool	create_m_inverse(float m[4][4], float inverse[4][4])
{
	float temp[4][4];
	int i, j, k;
	float ratio;

	// Kopiere m in temp und initialisiere inverse als Einheitsmatrix
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			temp[i][j] = m[i][j];
			inverse[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}

	// Gauss-Jordan-Elimination
	for (i = 0; i < 4; i++) {
		// Suche nach Pivot-Element, wenn temp[i][i] = 0
		if (temp[i][i] == 0.0) {
			for (j = i + 1; j < 4; j++) {
				if (temp[j][i] != 0.0) {
					// Zeilen tauschen
					for (k = 0; k < 4; k++) {
						float swap = temp[i][k];
						temp[i][k] = temp[j][k];
						temp[j][k] = swap;

						swap = inverse[i][k];
						inverse[i][k] = inverse[j][k];
						inverse[j][k] = swap;
					}
					break;
				}
			}
			if (temp[i][i] == 0.0) {
				// Singuläre Matrix, keine Inverse vorhanden
				return false;
			}
		}

		// Pivot-Division
		ratio = temp[i][i];
		for (j = 0; j < 4; j++) {
			temp[i][j] /= ratio;
			inverse[i][j] /= ratio;
		}

		// Gauss-Jordan-Schritte für jede Zeile außer der Pivotzeile
		for (k = 0; k < 4; k++) {
			if (k != i) {
				ratio = temp[k][i];
				for (j = 0; j < 4; j++) {
					temp[k][j] -= ratio * temp[i][j];
					inverse[k][j] -= ratio * inverse[i][j];
				}
			}
		}
	}

	return true; // Inverse erfolgreich berechnet
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