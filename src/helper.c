/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:56:30 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/28 12:40:09 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	sphere_count(t_data *data, char **line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "sp", 2) == 0)
			count++;
		i++;
	}
	data->set.sp = malloc(sizeof(t_sphere) * count);
	data->set.sp_count = count;
}

void	plane_count(t_data *data, char **line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "pl", 2) == 0)
			count++;
		i++;
	}
	data->set.pl = malloc(sizeof(t_plane) * count);
	data->set.pl_count = count;
}

void	cylinder_count(t_data *data, char **line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "cy", 2) == 0)
			count++;
		i++;
	}
	data->set.cy = malloc(sizeof(t_cylinder) * count);
	data->set.cy_count = count;
}

double	ft_atof(const char *str)
{
	double	int_part;
	double	dec_part;
	double	sign;
	int		i;

	int_part = 0.0;
	dec_part = 0.0;
	sign = 1.0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1.0;
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			dec_part += (pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (int_part + dec_part));
}
