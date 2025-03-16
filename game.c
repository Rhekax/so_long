/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:34:03 by mdursun           #+#    #+#             */
/*   Updated: 2025/03/16 19:20:48 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "Get_next_line/get_next_line.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


size_t	getcol(char *path)
{
	int i = 0;
	int colmn = 0;
	int fd = open(path, O_RDONLY);
	if (fd == -1)
		exit (1);
	char *line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);
		colmn++;
	}
	return (colmn);
}

char **checkmap(char *path)
{
	char	**map;
	char	*line;
	size_t		colmn;
	int		fd;
	int		i;

	colmn = getcol(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit (1);
	if (colmn < 3 )
		exit (1);
	map = malloc (sizeof(char *) * colmn);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = malloc (ft_strlen(line) + 1);
		ft_strncpy (*map, line, ft_strlen(line));
		*((map[i]) + ft_strlen(line)) = 0;
		ft_strtrim(map[i]," ");
		line = get_next_line(fd);
	}
	return (map);
}

int	close1(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(vars->mlx, vars->img.map.img);
		mlx_destroy_image(vars->mlx, vars->img.player.img);
		mlx_destroy_window(vars -> mlx, vars -> win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit (0);
	}
	if (keysym == XK_w)
		vars->img.player.y -= 64;
	if (keysym == XK_s)
		vars->img.player.y += 64;
	if (keysym == XK_a)
		vars->img.player.x -= 64;
	if (keysym == XK_d)
		vars->img.player.x += 64;
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.map.img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.player.img, vars->img.player.x, vars->img.player.y);
}

int	main(int argc, char *argv[])
{
	t_vars vars;

	int a = 64;
	int b = 64;
	int i = 0;
	int j = 0;
	size_t z = 0;
	size_t k = 0;
	char **mapp;

	mapp = checkmap("./map.ber");
	z = 0;
	k = 0;
	vars.img.player.x = 600;
	vars.img.player.y = 300;
	(vars.mlx = mlx_init());
	(vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!"));
	vars.img.map.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.img.player.img = mlx_xpm_file_to_image(vars.mlx, "pacman.xpm", &a , &b);
	vars.img.map.addr = mlx_get_data_addr(vars.img.map.img, &vars.img.map.bits_per_pixel, &vars.img.map.line_length, &vars.img.map.endian);
	vars.img.player.addr = mlx_get_data_addr(vars.img.player.img, &vars.img.player.bits_per_pixel, &vars.img.player.line_length, &vars.img.player.endian);
	while (k < 900)
	{
			while (z < 680)
			{
				my_mlx_pixel_put(&vars.img.map, k + 400, z + 150, create_trgb(0,230,24,46));
				z++;
			}
			k++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.map.img, 0, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.player.img, vars.img.player.x, vars.img.player.y);
	mlx_key_hook(vars.win, close1, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
