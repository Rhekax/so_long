/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 06:49:45 by mdursun           #+#    #+#             */
/*   Updated: 2025/04/15 07:04:12 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_mapdup(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	copy[i] = NULL;
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	return (copy);
}

void	fill(char **map, int x, int y, t_fill *f)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return;

	if (map[y][x] == 'P')
		f->player_count++;
	else if (map[y][x] == 'E')
	{
		f->exit_count++;
		map[y][x] = 'F';
		return;
	}
	else if (map[y][x] == 'C')
		f->collected_count++;
	map[y][x] = 'F';
	if (f->exit_count > 1 || f->player_count > 1)
		return;
	fill(map, x + 1, y, f);
	fill(map, x - 1, y, f);
	fill(map, x, y + 1, f);
	fill(map, x, y - 1, f);
}
void	map_fail(t_vars *vars)
{
	free_both_maps(vars);
	ft_printf("Error\nMap Invalid\n");
	exit(1);
}

void	check_flood_fill(t_vars *vars, int total_collectibles)
{
	t_fill	f;
	int	x;
	int	y;

	y = 0;
	x = 0;
	f.player_count = 0;
	f.exit_count = 0;
	f.collected_count = 0;

	while (vars -> map2[y])
	{
		x = 0;
		while (vars -> map2[y][x])
		{
			if (vars -> map2[y][x] == 'P')
				break;
			x++;
		}
		if (vars -> map2[y][x] == 'P')
			break;
		y++;
	}

	fill(vars -> map2, x, y, &f);

	if (f.player_count != 1 || f.exit_count != 1)
	{
		map_fail(vars);
	}
	if (f.collected_count != total_collectibles)
	{
		map_fail(vars);
	}
}

void	validate_map_walls(t_vars *vars)
{
	int i = 0;
	int row_len = ft_strlen(vars -> map[0]);
	int	j = getcol(vars->path);

	while (vars -> map[0][i])
	{
		if (vars -> map[0][i] != '1' || vars -> map[j - 1][i] != '1')
		{
			free_both_maps(vars);
			ft_printf("Error\nMap Invalid\n");
			exit(1);
		}
		i++;
	}

	for (i = 0; vars -> map[i]; i++)
	{
		if (vars -> map[i][0] != '1' || vars -> map[i][row_len - 1] != '1')
		{
			free_both_maps(vars);
			ft_printf("Error\nMap Invalid\n");
			exit(1);
		}
	}
}
