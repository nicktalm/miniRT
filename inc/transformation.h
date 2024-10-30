/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:55:58 by lbohm          #+#    #+#             */
/*   Updated: 2024/10/29 22:02:59 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vec4;

typedef struct s_matrix
{
	float	m[4][4];
}				t_matrix;

#endif