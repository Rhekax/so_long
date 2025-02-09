/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:34:03 by mdursun           #+#    #+#             */
/*   Updated: 2025/02/09 18:11:31 by mdursun          ###   ########.fr       */
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
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars -> mlx, vars -> win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit (0);
	}
}

int	main(int argc, char *argv[])
{
	t_vars vars;

	(vars.mlx = mlx_init());
	(vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!"));
	vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	for (int y = 0 ; y < 860;y++)
	{
			for (int x = 0 ; x < 640;x++)
			{	
				my_mlx_pixel_put(&vars.img, y + 400, x + 150, create_trgb(0,230,24,46));
			}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_key_hook(vars.win, close1, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
