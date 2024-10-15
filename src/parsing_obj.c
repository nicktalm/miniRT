/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/10/15 12:15:00 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_sphere(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	if (data->name == true)
		check_param_nbr_2(params, 4, data);
	else
		check_param_nbr_2(params, 5, data);
	data->set.obj[*i].type = SPHERE;
	parse_coords(&data->set.obj[*i].form.sp.coords, params[1], data);
	data->set.obj[*i].form.sp.diameter = ft_atof(params[2]);
	data->set.obj[*i].form.sp.radius = data->set.obj[*i].form.sp.diameter / 2.0;
	parse_color(&data->set.obj[*i].form.sp.color, params[3], data);
	if (data->name == false)
		data->set.obj[*i].form.sp.material = ft_atof(params[4]);
	else
		data->set.obj[*i].form.sp.material = 1.0;
	create_m_sp(&data->set.obj[*i].form.sp);
	(*i)++;
	free_double_p(params);
}

void	parse_plane(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	if (data->name == true)
		check_param_nbr_2(params, 4, data);
	else
		check_param_nbr_2(params, 6, data);
	data->set.obj[*i].type = PLANE;
	parse_coords(&data->set.obj[*i].form.pl.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.pl.norm, params[2], data);
	parse_color(&data->set.obj[*i].form.pl.color, params[3], data);
	if (data->name == false)
	{
		data->set.obj[*i].form.pl.material = ft_atof(params[4]);
		parse_surface(&data->set.obj[*i].form.pl, params[5], data);
	}
	else
	{
		data->set.obj[*i].form.pl.material = 1.0;
		data->set.obj[*i].form.pl.length = 0.0;
		data->set.obj[*i].form.pl.width = 0.0;
	}
	(*i)++;
	free_double_p(params);
}

void	parse_cylinder(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	if (data->name == true)
		check_param_nbr_2(params, 6, data);
	else
		check_param_nbr_2(params, 7, data);
	data->set.obj[*i].type = CYLINDER;
	parse_coords(&data->set.obj[*i].form.cy.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.cy.norm, params[2], data);
	data->set.obj[*i].form.cy.diameter = ft_atof(params[3]);
	data->set.obj[*i].form.cy.radius = data->set.obj[*i].form.cy.diameter / 2.0;
	data->set.obj[*i].form.cy.height = ft_atof(params[4]);
	parse_color(&data->set.obj[*i].form.cy.color, params[5], data);
	if (data->name == false)
		data->set.obj[*i].form.cy.material = ft_atof(params[6]);
	else
		data->set.obj[*i].form.cy.material = 1.0;
	create_m_cy(&data->set.obj[*i].form.cy);
	(*i)++;
	free_double_p(params);
}
