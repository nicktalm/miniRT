/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/29 12:51:21 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_sphere(t_data *data, char **line)
{
	static int	i;
	char		**params;

	params = ft_split(*line, ' ');
	if (ft_strncmp(params[0], "sp", 2) != 0)
		return ;
	parse_coords(&data->set.sp[i].coords, params[1]);
	data->set.sp[i].diameter = ft_atof(params[2]);
	parse_color(&data->set.sp[i].color, params[3]);
	i++;
}

void	parse_plane(t_data *data, char **line)
{
	static int	i;
	char		**params;

	params = ft_split(*line, ' ');
	if (ft_strncmp(params[0], "pl", 2) != 0)
		return ;
	parse_coords(&data->set.pl[i].coords, params[1]);
	parse_normalized_vector(&data->set.pl[i].normalized, params[2]);
	parse_color(&data->set.pl[i].color, params[3]);
	i++;
}

void	parse_cylinder(t_data *data, char **line)
{
	static int	i;
	char		**params;

	params = ft_split(*line, ' ');
	if (ft_strncmp(params[0], "cy", 2) != 0)
		return ;
	parse_coords(&data->set.cy[i].coords, params[1]);
	parse_normalized_vector(&data->set.cy[i].normalized, params[2]);
	data->set.cy[i].diameter = ft_atof(params[3]);
	data->set.cy[i].height = ft_atof(params[4]);
	parse_color(&data->set.cy[i].color, params[5]);
	i++;
}
