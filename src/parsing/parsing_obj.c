/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/11 16:17:29 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_sphere(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	data->set.obj[*i].type = SPHERE;
	parse_coords(&data->set.obj[*i].form.sp.coords, params[1], data);
	data->set.obj[*i].form.sp.diameter = ft_atof(params[2]);
	data->set.obj[*i].form.sp.radius = data->set.obj[*i].form.sp.diameter / 2.0;
	parse_color(&data->set.obj[*i].form.sp.color, params[3], data);
	create_m_sp(&data->set.obj[*i].form.sp);
	(*i)++;
	free_double_p(params);
}

void	parse_plane(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	if (params[4] == NULL)
	{
		check_param_nbr_2(params, 4, data);
		data->set.obj[*i].form.pl.length = 0.0;
		data->set.obj[*i].form.pl.width = 0.0;
	}
	else
	{
		check_param_nbr_2(params, 5, data);
		parse_surface(&data->set.obj[*i].form.pl, params[4], data);
	}
	data->set.obj[*i].type = PLANE;
	parse_coords(&data->set.obj[*i].form.pl.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.pl.norm, params[2], data);
	parse_color(&data->set.obj[*i].form.pl.color, params[3], data);
	create_m_pl(&data->set.obj[*i].form.pl);
	(*i)++;
	free_double_p(params);
}

void	parse_cylinder(t_data *data, char **line, int *i)
{
	char		**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 6, data);
	data->set.obj[*i].type = CYLINDER;
	parse_coords(&data->set.obj[*i].form.cy.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.cy.norm, params[2], data);
	data->set.obj[*i].form.cy.diameter = ft_atof(params[3]);
	data->set.obj[*i].form.cy.radius = data->set.obj[*i].form.cy.diameter / 2.0;
	data->set.obj[*i].form.cy.height = ft_atof(params[4]);
	parse_color(&data->set.obj[*i].form.cy.color, params[5], data);
	create_m_cy(&data->set.obj[*i].form.cy);
	(*i)++;
	free_double_p(params);
}

void	parse_cone(t_data *data, char **line, int *i)
{
	char	**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 6, data);
	data->set.obj[*i].type = CONE;
	parse_coords(&data->set.obj[*i].form.cn.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.cn.norm, params[2], data);
	data->set.obj[*i].form.cn.height = ft_atof(params[3]);
	data->set.obj[*i].form.cn.diameter = ft_atof(params[4]);
	data->set.obj[*i].form.cn.radius = data->set.obj[*i].form.cn.diameter / 2.0;
	parse_color(&data->set.obj[*i].form.cn.color, params[5], data);
	data->set.obj[*i].form.cn.angle = tanf(atanf(data->set.obj[*i].form.cn.radius / data->set.obj[*i].form.cn.height)) * tanf(atanf(data->set.obj[*i].form.cn.radius / data->set.obj[*i].form.cn.height));
	data->set.obj[*i].form.cn.tangle = atan(data->set.obj[*i].form.cn.radius / data->set.obj[*i].form.cn.height);
	create_m_cn(&data->set.obj[*i].form.cn);
	(*i)++;
	free_double_p(params);
}
