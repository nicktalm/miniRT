/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/18 13:01:48 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_sphere(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	if (ft_strncmp(params[0], "sp", 2) != 0)
		return ;
	data->set.obj[*i].type = SPHERE;
	parse_coords(&data->set.obj[*i].form.sp.coords, params[1], data);
	data->set.obj[*i].form.sp.diameter = ft_atof(params[2]);
	data->set.obj[*i].form.sp.radius = data->set.obj[*i].form.sp.diameter / 2.0;
	parse_color(&data->set.obj[*i].form.sp.color, params[3], data);
	(*i)++;
	free_params(params, 4);
}

void	parse_plane(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	if (ft_strncmp(params[0], "pl", 2) != 0)
		return ;
	data->set.obj[*i].type = PLANE;
	parse_coords(&data->set.obj[*i].form.pl.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.pl.normalized, params[2], data);
	parse_color(&data->set.obj[*i].form.pl.color, params[3], data);
	(*i)++;
	free_params(params, 4);
}

void	parse_cylinder(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 6, data);
	if (ft_strncmp(params[0], "cy", 2) != 0)
		return ;
	data->set.obj[*i].type = CYLINDER;
	parse_coords(&data->set.obj[*i].form.cy.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.cy.normalized, params[2], data);
	data->set.obj[*i].form.cy.diameter = ft_atof(params[3]);
	data->set.obj[*i].form.cy.radius = data->set.obj[*i].form.cy.diameter / 2.0;
	data->set.obj[*i].form.cy.height = ft_atof(params[4]);
	parse_color(&data->set.obj[*i].form.cy.color, params[5], data);
	(*i)++;
	free_params(params, 6);
}
