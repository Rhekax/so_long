/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:34:03 by mdursun           #+#    #+#             */
/*   Updated: 2025/02/09 18:32:52 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


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
int	read_lines()
{
	char	buf[BUFFERSIZE];
	int		i;
	int		line;
	int		j;

	j = 0;
	line = 0;
	i = 1;
	while (i > 0)
	{
		i = read(3, buf, BUFFERSIZE);
		if (i == -1)
			exit (1);
		while (j < BUFFERSIZE)
		{
			if (buf[j] == '\n')
				line++;
			j++;
		}
		if (i == 0 && buf[0] != 0)
			line++;
	}
	return (line);
}
void checkmap(int x, int y, char *path)
{
	char	**map;
	int		line;
	int		colmn;

	line = read_lines();
	colmn = 0;
	if (open(path, O_RDONLY) == -1)
		exit (1);
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
	if (keysym = XK_w)
	{
		vars->img.player.y -= 30;
		mlx_clear_window(vars->mlx, vars->win);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.map.img, 0, 0);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.player.img, vars->img.player.x, vars->img.player.y);
	}
}

int	main(int argc, char *argv[])
{
	t_vars vars;

	int a = 64;
	int b = 64;
	vars.img.player.x = 600;
	vars.img.player.y = 300;
	(vars.mlx = mlx_init());
	(vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!"));
	vars.img.map.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.img.player.img = mlx_xpm_file_to_image(vars.mlx, "pacman.xpm", &a , &b);
	vars.img.map.addr = mlx_get_data_addr(vars.img.map.img, &vars.img.map.bits_per_pixel, &vars.img.map.line_length, &vars.img.map.endian);
	vars.img.player.addr = mlx_get_data_addr(vars.img.player.img, &vars.img.player.bits_per_pixel, &vars.img.player.line_length, &vars.img.player.endian);
	for (int y = 0 ; y < 860;y++)
	{
			for (int x = 0 ; x < 640;x++)
			{	
				my_mlx_pixel_put(&vars.img.map, y + 400, x + 150, create_trgb(0,230,24,46));
			}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.map.img, 0, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.player.img, vars.img.player.x, vars.img.player.y);
	mlx_key_hook(vars.win, close1, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
