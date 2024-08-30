/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:24:59 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/30 13:30:49 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	process_line(char *line, char *result)
{
	int	i;
	int	j;
	int	in_space;

	i = 0;
	j = 0;
	in_space = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n' || line[i] == ' ')
		{
			if (!in_space)
			{
				result[j++] = ' ';
				in_space = 1;
			}
		}
		else
		{
			result[j++] = line[i];
			in_space = 0;
		}
		i++;
	}
	result[j] = '\0';
}

char	*replace_whitespace(char *line)
{
	char	*result;

	if (!line)
		return (NULL);
	result = malloc(ft_strlen(line) + 1);
	if (!result)
		return (NULL);
	process_line(line, result);
	return (result);
}

char	*clean_line(char *line)
{
	char	*intermediate_result;
	char	*trimmed_result;

	intermediate_result = replace_whitespace(line);
	if (!intermediate_result)
		return (NULL);
	trimmed_result = ft_strtrim(intermediate_result, " ");
	printf("trimmed_result: %s\n", trimmed_result);
	free(intermediate_result);
	return (trimmed_result);
}

int	check_param_nbr(char **line)
{
	int	count_a;
	int	count_c;
	int	count_l;
	int	i;

	i = 0;
	count_a = 0;
	count_c = 0;
	count_l = 0;
	while (line[i] != NULL)
	{
		if (ft_strncmp(line[i], "A ", 2) == 0)
			count_a++;
		else if (ft_strncmp(line[i], "C ", 2) == 0)
			count_c++;
		else if (ft_strncmp(line[i], "L ", 2) == 0)
			count_l++;
		i++;
	}
	if (count_a == 1 && count_c == 1 && count_l == 1)
		return (0);
	error("Wrong number of parameters\n");
	return (1);
}
