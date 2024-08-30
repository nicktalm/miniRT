/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:26:20 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/30 12:52:21 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	ft_count(t_data *data, char **line)
{
	check_param_nbr(line);
	sphere_count(data, line);
	plane_count(data, line);
	cylinder_count(data, line);
}

void	parse_coords(t_vec *coords, char *param)
{
	char	**values;

	values = ft_split(param, ',');
	if (!values[0] || !values[1] || !values[2])
		error("Coordinates must have 3 values\n");
	coords->x = ft_atof(values[0]);
	coords->y = ft_atof(values[1]);
	coords->z = ft_atof(values[2]);
}

void	parse_color(t_vec *color, char *param)
{
	char	**values;

	values = ft_split(param, ',');
	if (!values[0] || !values[1] || !values[2])
		error("RGB values must have 3 values\n");
	color->x = ft_atof(values[0]);
	if (color->x < 0 || color->x > 255)
		error("RGB values must be between 0 and 255\n");
	color->y = ft_atof(values[1]);
	if (color->y < 0 || color->y > 255)
		error("RGB values must be between 0 and 255\n");
	color->z = ft_atof(values[2]);
	if (color->z < 0 || color->z > 255)
		error("RGB values must be between 0 and 255\n");
}

void	parse_normalized_vector(t_vec *vec, char *param)
{
	char	**values;

	values = ft_split(param, ',');
	if (!values[0] || !values[1] || !values[2])
		error("Normalized vector must have 3 values\n");
	vec->x = ft_atof(values[0]);
	if (vec->x < -1 || vec->x > 1)
		error("Normalized vector must be between -1 and 1\n");
	vec->y = ft_atof(values[1]);
	if (vec->y < -1 || vec->y > 1)
		error("Normalized vector must be between -1 and 1\n");
	vec->z = ft_atof(values[2]);
	if (vec->z < -1 || vec->z > 1)
		error("Normalized vector must be between -1 and 1\n");
}
