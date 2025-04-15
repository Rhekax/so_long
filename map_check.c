/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 06:49:47 by mdursun           #+#    #+#             */
/*   Updated: 2025/04/15 06:50:54 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "Get_next_line/get_next_line.h"

void	path_check(char *path)
{
	int	len;

	len = strlen(path);
	if (len < 4)
	{
		ft_printf("Map error\n");
		exit(1);
	}
	if (path[len - 1] != 'r')
		exit(1);
	if (path[len - 2] != 'e')
		exit(1);
	if (path[len - 3] != 'b')
		exit(1);
	if (path[len - 4] != '.')
		exit(1);
}

void	count_coin(t_vars *vars, char *path)
{
	int i = strlen(*(vars -> map));
	int j = getcol(path);
	int	a = j;

	vars->img.cc.y = 0;
	vars->img.cc.x = 0;
	while (i--)
	{
		j = a;
		while (j--)
		{
			if ((vars->map)[j][i] == 'C')
				vars->img.cc.x += 1;
		}
	}
}
void	err()
{
	ft_printf("Error\n");
	exit (1);
}
