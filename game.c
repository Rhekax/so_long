/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:34:03 by mdursun           #+#    #+#             */
/*   Updated: 2025/04/15 06:54:37 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "Get_next_line/get_next_line.h"

size_t	getcol(char *path)
{
	int colmn = 0;
	int fd = open(path, O_RDONLY);
	if (fd == -1)
		exit (1);
	char *line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		colmn++;
	}
	close(fd);
	return (colmn);
}

char **checkmap(char *path)
{
	char	**map;
	char	*line;
	size_t	colmn;
	int		fd;
	int		i;

	colmn = getcol(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit (1);
	if (colmn < 3 )
		exit (1);
	map = malloc (sizeof(char *) * (colmn + 1));
	map[colmn] = NULL;
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = ft_strtrim(line," \n\t");
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (map);
}

void	put_player(t_vars *vars, int keysym)
{
	int new_x = vars->img.player.x;
	int new_y = vars->img.player.y;

	if (keysym == XK_w)
		new_y -= 64;
	else if (keysym == XK_s)
		new_y += 64;
	else if (keysym == XK_a)
		new_x -= 64;
	else if (keysym == XK_d)
		new_x += 64;
	else
		return;

	int map_x = new_x / 64;
	int map_y = new_y / 64;

	if (map_y < 0 || map_y >= (int)getcol(vars->path) ||
		map_x < 0 || map_x >= (int)ft_strlen(vars->map[0]) ||
		vars->map[map_y][map_x] == '1')
		return;

	if (vars->map[map_y][map_x] == 'E' && vars->img.cc.x == 0)
	{
		ft_printf("YOU WIN\n");
		destroy(vars);
	}
	if (vars->map[map_y][map_x] == 'E' && vars->img.cc.x != 0)
		return;
	if (vars->map[map_y][map_x] == 'C')
		vars->img.cc.x--;

	vars->map[vars->img.player.y / 64][vars->img.player.x / 64] = '0';
	vars->map[map_y][map_x] = 'P';
	vars->img.cc.y++;
	vars->img.player.x = new_x;
	vars->img.player.y = new_y;
}


void destroy(t_vars *vars)
{
	free_2d(vars -> map);
	mlx_destroy_image(vars->mlx, vars->img.map.img);
	mlx_destroy_image(vars->mlx, vars->img.player.img);
	mlx_destroy_image(vars->mlx, vars->img.wall.img);
	mlx_destroy_image(vars->mlx, vars->img.exit.img);
	mlx_destroy_image(vars->mlx, vars->img.cc.img);
	mlx_destroy_window(vars -> mlx, vars -> win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit (0);
}
int int_destroy(t_vars *vars)
{
	free_2d(vars -> map);
	mlx_destroy_image(vars->mlx, vars->img.map.img);
	mlx_destroy_image(vars->mlx, vars->img.player.img);
	mlx_destroy_image(vars->mlx, vars->img.wall.img);
	mlx_destroy_image(vars->mlx, vars->img.exit.img);
	mlx_destroy_image(vars->mlx, vars->img.cc.img);
	mlx_destroy_window(vars -> mlx, vars -> win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit (0);
	return (0);
}
void	check_img(t_vars *vars, int j, int i)
{
	if ((vars->map)[j][i] == 'C')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.cc.img, (i * 64), (64 * j));
	if ((vars->map)[j][i] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.exit.img, (i * 64), (64 * j));
	if ((vars->map)[j][i] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.wall.img, (i * 64), (64 * j));
	if ((vars->map)[j][i] == '0')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.map.img, (i * 64), (64 * j));
	if ((vars->map)[j][i] == 'P')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.player.img, (i * 64), (64 * j));
}
void	render_img (t_vars *vars, int keysym)
{
	int	i;
	int j;
	int	a;

	i = 0;
	j = 0;
	a = i;
	put_player(vars, keysym);
	while (j < (int)getcol(vars->path))
	{
		i = a;
		while (i < (int)ft_strlen((vars -> map)[0]))
		{
			check_img(vars, j, i);
			i++;
		}
		j++;
	}
	ft_printf("Steps: %d\n", vars->img.cc.y);
}

int	close1(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		destroy(vars);
	mlx_clear_window(vars->mlx, vars->win);
	render_img(vars, keysym);
	return (0);
}

void	start_p(t_vars *vars, char *path)
{
	int i = strlen(*(vars -> map));
	int j = getcol(path);
	int	a = j;

	while (i--)
	{
		j = a;
		while (j--)
		{
			if ((vars->map)[j][i] == 'P')
			{
				vars->img.player.x = i * 64;
				vars->img.player.y = j * 64;
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.map.img, (i * 64), (64 * j));
			}
		}
	}
}
void	free_2d(char **map)
{
	int i = 0;
	if (!map)
		return;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_both_maps(t_vars *vars)
{
	free_2d(vars->map);
	free_2d(vars->map2);
	vars->map = NULL;
	vars->map2 = NULL;
}


void	init_image(t_vars *vars, char *path, int *k, int *z)
{
	int i;
	int j;

	i = ft_strlen(*(vars -> map));
	j = (int)getcol(path);
	vars -> mlx = mlx_init();
	vars -> win = mlx_new_window(vars -> mlx, i * 64, j * 64, "Hello world!");
	vars -> img.map.img = mlx_xpm_file_to_image(vars -> mlx, "wall.xpm", k,z);
	vars -> img.wall.img = mlx_xpm_file_to_image(vars -> mlx, "bw.xpm", k,z);
	vars -> img.cc.img = mlx_xpm_file_to_image(vars -> mlx, "rs.xpm", k,z);
	vars -> img.exit.img = mlx_xpm_file_to_image(vars -> mlx, "exi.xpm", k,z);
	vars -> img.player.img = mlx_xpm_file_to_image(vars -> mlx, "pacman.xpm", k , z);
	start_p(vars,path);
	render_img(vars, XK_z);
}
int	main(int argc, char *argv[])
{
	t_vars vars;
	int z = 1;
	int k = 1;

	if (argc != 2)
		err();
	vars.path = argv[1];
	path_check(vars.path);
	vars.map = checkmap(vars.path);
	count_coin(&vars, vars.path);
	vars.map2 = ft_mapdup(vars.map);
	validate_map_walls(&vars);
	check_flood_fill(&vars, vars.img.cc.x);
	free_2d(vars.map2);
	vars.map2 = NULL;
	init_image(&vars, vars.path, &k, &z);
	vars.img.map.addr = mlx_get_data_addr(vars.img.map.img, &vars.img.map.bits_per_pixel, &vars.img.map.line_length, &vars.img.map.endian);
	vars.img.player.addr = mlx_get_data_addr(vars.img.player.img, &vars.img.player.bits_per_pixel, &vars.img.player.line_length, &vars.img.player.endian);
	vars.img.cc.addr = mlx_get_data_addr(vars.img.cc.img, &vars.img.cc.bits_per_pixel, &vars.img.cc.line_length, &vars.img.cc.endian);
	vars.img.wall.addr = mlx_get_data_addr(vars.img.wall.img, &vars.img.wall.bits_per_pixel, &vars.img.wall.line_length, &vars.img.wall.endian);
	vars.img.exit.addr = mlx_get_data_addr(vars.img.exit.img, &vars.img.exit.bits_per_pixel, &vars.img.exit.line_length, &vars.img.exit.endian);
	mlx_key_hook(vars.win, close1, &vars);
	mlx_hook(vars.win, 17, 0, int_destroy, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
