/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/02 16:07:57 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data.set.sp = NULL;
	data.set.pl = NULL;
	data.set.cy = NULL;
	if (argc != 2)
		error("Wrong number of arguments", &data);
	else
		open_file(argv[1], &data);
	free_all(&data);
	return (0);
}
