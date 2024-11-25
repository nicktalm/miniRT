/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:26:20 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/22 20:02:26 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	ft_count(t_data *data, char **line)
{
	check_param_nbr(data, line);
	light_count(data, line);
	obj_count(data, line);
}

void	parse_coords(t_vec3 *coords, char *param, t_data *data)
{
	char	**values;

	values = ft_split(param, ',');
	if (ft_count_params(values) != 3)
	{
		error("Coordinates must have 3 values", data);
	}
	coords->x = ft_atof(values[0]);
	coords->y = ft_atof(values[1]);
	coords->z = ft_atof(values[2]);
	free_double_p(values);
}

void	parse_color(t_vec3 *color, char *param, t_data *data)
{
	char	**values;

	values = ft_split(param, ',');
	if (ft_count_params(values) != 3)
	{
		error("RGB values must have 3 values", data);
	}
	color->x = ft_atof(values[0]);
	color->y = ft_atof(values[1]);
	color->z = ft_atof(values[2]);
	if (!is_valid_float(values[0]) || !is_valid_float(values[1])
		|| !is_valid_float(values[2]))
	{
		free_double_p(values);
		error("RGB values must be floats", data);
	}
	free_double_p(values);
	if (color->x < 0 || color->x > 255 || color->y < 0 || color->y > 255
		|| color->z < 0 || color->z > 255)
	{
		error("RGB values must be between 0 and 255", data);
	}
	*color = dev_vec_wnbr(*color, 255.0);
}

void	parse_normalized_vector(t_vec3 *vec, char *param, t_data *data)
{
	char	**values;

	values = ft_split(param, ',');
	if (ft_count_params(values) != 3)
	{
		free_double_p(values);
		error("Normalized vector must have 3 values", data);
	}
	vec->x = ft_atof(values[0]);
	vec->y = ft_atof(values[1]);
	vec->z = ft_atof(values[2]);
	if (!is_valid_float(values[0]) || !is_valid_float(values[1])
		|| !is_valid_float(values[2]))
	{
		free_double_p(values);
		error("Normalized vector values must be floats", data);
	}
	free_double_p(values);
	if (vec->x < -1 || vec->x > 1 || vec->y < -1 || vec->y > 1
		|| vec->z < -1 || vec->z > 1)
	{
		error("Normalized vector must be between -1 and 1", data);
	}
}

void	parse_surface(t_plane *pl, char *param, t_data *data)
{
	char	**values;

	values = ft_split(param, ',');
	if (ft_count_params(values) != 2)
	{
		free_double_p(values);
		error("Surface must have 2 values", data);
	}
	pl->length = ft_atof(values[0]);
	pl->width = ft_atof(values[1]);
	if (!is_valid_float(values[0]) || !is_valid_float(values[1]))
	{
		free_double_p(values);
		error("Surface values must be floats", data);
	}
	free_double_p(values);
	if (pl->length < 0 || pl->width < 0)
	{
		error("Surface width must be positive", data);
	}
}
