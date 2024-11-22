/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/22 17:29:29 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_common_params(t_data *data, char **params, int *i,
			void (*parse_specific_params)(t_data *, char **, int *))
{
	parse_specific_params(data, params, i);
	(*i)++;
}

void	parse_sphere(t_data *data, char *line, int *i)
{
	int		nbr_params;

	data->garbage.params = ft_split(line, ' ');
	nbr_params = ft_count_params(data->garbage.params);
	data->set.obj[*i].form.sp.bump_map = NULL;
	data->set.obj[*i].form.sp.texture = NULL;
	if (nbr_params < 4 || nbr_params > 6)
		error("Invalid number of parameters", data);
	parse_common_params(data, data->garbage.params, i, parse_sp_specific);
	free_double_p(data->garbage.params);
	data->garbage.params = NULL;
}

void	parse_plane(t_data *data, char *line, int *i)
{
	int		nbr_params;

	data->garbage.params = ft_split(line, ' ');
	nbr_params = ft_count_params(data->garbage.params);
	data->set.obj[*i].form.pl.bump_map = NULL;
	data->set.obj[*i].form.pl.texture = NULL;
	data->set.obj[*i].form.pl.length = 0.0;
	data->set.obj[*i].form.pl.width = 0.0;
	if (nbr_params < 4 || nbr_params > 7)
		error("Invalid number of parameters", data);
	parse_common_params(data, data->garbage.params, i, parse_pl_specific);
	free_double_p(data->garbage.params);
	data->garbage.params = NULL;
}

void	parse_cylinder(t_data *data, char *line, int *i)
{
	int		nbr_params;

	data->garbage.params = ft_split(line, ' ');
	nbr_params = ft_count_params(data->garbage.params);
	data->set.obj[*i].form.cy.bump_map = NULL;
	data->set.obj[*i].form.cy.texture = NULL;
	if (nbr_params < 6 || nbr_params > 8)
		error("Invalid number of parameters", data);
	parse_common_params(data, data->garbage.params, i, parse_cy_specific);
	free_double_p(data->garbage.params);
	data->garbage.params = NULL;
}

void	parse_cone(t_data *data, char *line, int *i)
{
	int		nbr_params;

	data->garbage.params = ft_split(line, ' ');
	nbr_params = ft_count_params(data->garbage.params);
	data->set.obj[*i].form.cn.bump_map = NULL;
	data->set.obj[*i].form.cn.texture = NULL;
	if (nbr_params < 6 || nbr_params > 8)
		error("Invalid number of parameters", data);
	parse_common_params(data, data->garbage.params, i, parse_cone_specific);
	free_double_p(data->garbage.params);
	data->garbage.params = NULL;
}
