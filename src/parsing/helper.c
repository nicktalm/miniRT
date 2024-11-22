/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:56:30 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/22 15:15:00 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	check_param_nbr_2(char **params, int nbr, t_data *data)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	if (i != nbr)
		error_2("Wrong number of parameters for ", params[0], data);
}

void	light_count(t_data *data, char **line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "L ", 2) == 0)
			count++;
		i++;
	}
	data->set.light = malloc(sizeof(t_light) * count);
	data->set.light_count = count;
}

void	obj_count(t_data *data, char **line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "sp ", 3) == 0)
			count++;
		else if (ft_strncmp(line[i], "pl ", 3) == 0)
			count++;
		else if (ft_strncmp(line[i], "cy ", 3) == 0)
			count++;
		else if (ft_strncmp(line[i], "cn ", 3) == 0)
			count++;
		i++;
	}
	data->set.obj = malloc(sizeof(t_objects) * count);
	data->set.obj_count = count;
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

bool	is_valid_float(const char *str)
{
	int		i;
	bool	has_decimal_point;
	bool	has_digits;

	i = 0;
	has_decimal_point = false;
	has_digits = false;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			has_digits = true;
		else if (str[i] == '.')
		{
			if (has_decimal_point)
				return (false);
			has_decimal_point = true;
		}
		else
			return (false);
		i++;
	}
	return (has_digits);
}
