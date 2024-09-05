/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/02 11:43:19 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_sphere(t_data *data, char **line)
{
	static int	i;
	char		**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	if (ft_strncmp(params[0], "sp", 2) != 0)
		return ;
	parse_coords(&data->set.sp[i].coords, params[1], data);
	data->set.sp[i].diameter = ft_atof(params[2]);
	parse_color(&data->set.sp[i].color, params[3], data);
	i++;
	free(params[0]);
	free(params[1]);
	free(params[2]);
	free(params[3]);
	free(params);
}

void	parse_plane(t_data *data, char **line)
{
	static int	i;
	char		**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	if (ft_strncmp(params[0], "pl", 2) != 0)
		return ;
	parse_coords(&data->set.pl[i].coords, params[1], data);
	parse_normalized_vector(&data->set.pl[i].normalized, params[2], data);
	parse_color(&data->set.pl[i].color, params[3], data);
	i++;
	free(params[0]);
	free(params[1]);
	free(params[2]);
	free(params[3]);
	free(params);
}

void	parse_cylinder(t_data *data, char **line)
{
	static int	i;
	char		**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 6, data);
	if (ft_strncmp(params[0], "cy", 2) != 0)
		return ;
	parse_coords(&data->set.cy[i].coords, params[1], data);
	parse_normalized_vector(&data->set.cy[i].normalized, params[2], data);
	data->set.cy[i].diameter = ft_atof(params[3]);
	data->set.cy[i].height = ft_atof(params[4]);
	parse_color(&data->set.cy[i].color, params[5], data);
	i++;
	free(params[0]);
	free(params[1]);
	free(params[2]);
	free(params[3]);
	free(params[4]);
	free(params[5]);
	free(params);
}