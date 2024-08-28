/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/28 11:33:32 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_sphere(t_data *data, char **line)
{
	static int	i = 0;
	char		**params;
	char		**coords;
	char		**color;

	params = ft_split(*line, ' ');
	if (ft_strncmp(params[0], "sp", 2) != 0)
		return ;
	coords = ft_split(params[1], ',');
	color = ft_split(params[3], ',');
	data->set.sp[i].coords.x = ft_atof(coords[0]);
	data->set.sp[i].coords.y = ft_atof(coords[1]);
	data->set.sp[i].coords.z = ft_atof(coords[2]);
	data->set.sp[i].diameter = ft_atof(params[2]);
	data->set.sp[i].color.x = ft_atof(color[0]);
	if (data->set.sp[i].color.x < 0 || data->set.sp[i].color.x > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.sp[i].color.y = ft_atof(color[1]);
	if (data->set.sp[i].color.y < 0 || data->set.sp[i].color.y > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.sp[i].color.z = ft_atof(color[2]);
	if (data->set.sp[i].color.z < 0 || data->set.sp[i].color.z > 255)
		error("Error: RGB values must be between 0 and 255\n");
	i++;
}

void	parse_plane(t_data *data, char **line)
{
	static int	i = 0;
	char		**params;
	char		**coords;
	char		**normalized;
	char		**color;

	params = ft_split(*line, ' ');
	if (ft_strncmp(params[0], "pl", 2) != 0)
		return ;
	coords = ft_split(params[1], ',');
	normalized = ft_split(params[2], ',');
	color = ft_split(params[3], ',');
	data->set.pl[i].coords.x = ft_atof(coords[0]);
	data->set.pl[i].coords.y = ft_atof(coords[1]);
	data->set.pl[i].coords.z = ft_atof(coords[2]);
	data->set.pl[i].normalized.x = ft_atof(normalized[0]);
	if (data->set.pl[i].normalized.x < -1 || data->set.pl[i].normalized.x > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.pl[i].normalized.y = ft_atof(normalized[1]);
	if (data->set.pl[i].normalized.y < -1 || data->set.pl[i].normalized.y > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.pl[i].normalized.z = ft_atof(normalized[2]);
	if (data->set.pl[i].normalized.z < -1 || data->set.pl[i].normalized.z > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.pl[i].color.x = ft_atof(color[0]);
	if (data->set.pl[i].color.x < 0 || data->set.pl[i].color.x > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.pl[i].color.y = ft_atof(color[1]);
	if (data->set.pl[i].color.y < 0 || data->set.pl[i].color.y > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.pl[i].color.z = ft_atof(color[2]);
	if (data->set.pl[i].color.z < 0 || data->set.pl[i].color.z > 255)
		error("Error: RGB values must be between 0 and 255\n");
	i++;
}

void	parse_cylinder(t_data *data, char **line)
{
	static int	i = 0;
	char		**params;
	char		**coords;
	char		**normalized;
	char		**color;

	params = ft_split(*line, ' ');
	if (ft_strncmp(params[0], "cy", 2) != 0)
		return ;
	coords = ft_split(params[1], ',');
	normalized = ft_split(params[2], ',');
	color = ft_split(params[5], ',');
	data->set.cy[i].coords.x = ft_atof(coords[0]);
	data->set.cy[i].coords.y = ft_atof(coords[1]);
	data->set.cy[i].coords.z = ft_atof(coords[2]);
	data->set.cy[i].normalized.x = ft_atof(normalized[0]);
	if (data->set.cy[i].normalized.x < -1 || data->set.cy[i].normalized.x > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.cy[i].normalized.y = ft_atof(normalized[1]);
	if (data->set.cy[i].normalized.y < -1 || data->set.cy[i].normalized.y > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.cy[i].normalized.z = ft_atof(normalized[2]);
	if (data->set.cy[i].normalized.z < -1 || data->set.cy[i].normalized.z > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.cy[i].diameter = ft_atof(params[3]);
	data->set.cy[i].height = ft_atof(params[4]);
	data->set.cy[i].color.x = ft_atof(color[0]);
	if (data->set.cy[i].color.x < 0 || data->set.cy[i].color.x > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.cy[i].color.y = ft_atof(color[1]);
	if (data->set.cy[i].color.y < 0 || data->set.cy[i].color.y > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.cy[i].color.z = ft_atof(color[2]);
	if (data->set.cy[i].color.z < 0 || data->set.cy[i].color.z > 255)
		error("Error: RGB values must be between 0 and 255\n");
	i++;
}
