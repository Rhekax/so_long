/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:34:03 by mdursun           #+#    #+#             */
/*   Updated: 2025/04/13 20:11:04 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "Get_next_line/get_next_line.h"


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
		ft_strncpy (map[i], line, ft_strlen(line));
		*((map[i]) + ft_strlen(line)) = 0;
		map[i] = ft_strtrim(map[i]," \n\t");
		line = get_next_line(fd);
		i++;
	}
	return (map);
}
void	put_player(t_vars *vars , int x, int y, int keysym)
{
	if (y > vars->img.player.y + 64 && keysym == XK_s)
{		vars->map[x / 64][y / 64] = '0';
		vars->img.player.y += 64;}
	else if (-1  < vars->img.player.y - 64 && keysym == XK_w)
{		vars->map[x / 64][y / 64] = '0';
		vars->img.player.y -= 64;}
	else if (x > vars->img.player.x + 64 && keysym == XK_d)
{		vars->map[x / 64][y / 64] = '0';
		vars->img.player.x += 64;}
	else if (-1 < vars->img.player.x - 64 && keysym == XK_a)
{		vars->map[x / 64][y / 64] = '0';
		vars->img.player.x -= 64;}
	if (vars->map[vars->img.player.y / 64][vars->img.player.x / 64] == 'C')
	{
		vars->img.cc.x -= 1;
		vars->map[vars->img.player.y / 64][vars->img.player.x / 64] = '0';
	}
}

void	render_img (t_vars *vars, int keysym)
{
	int	i = strlen(*(vars -> map));
	int j = getcol("map.ber");
	int	a = j;
	int b = i;
	int cc = 0;
	put_player(vars, b * 64, a * 64, keysym); 
	while (i--)
	{
		j = a;
		while (j--)
		{
			if ((vars->map)[j][i] == 'C')
			{
				vars->img.cc.x += 1;
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.cc.img, (i * 64), (64 * j));
			}
			if ((vars->map)[j][i] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.exit.img, (i * 64), (64 * j));
			if ((vars->map)[j][i] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.wall.img, (i * 64), (64 * j));
			if ((vars->map)[j][i] == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.map.img, (i * 64), (64 * j));
		}
	}
	if (vars->map[vars->img.player.y / 64][vars->img.player.x / 64] == 'E' && vars->img.cc.x == 0)
		close1(XK_Escape, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.player.img, vars->img.player.x, vars->img.player.y);
}

int	close1(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
	{
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
	mlx_clear_window(vars->mlx, vars->win);
	render_img(vars, keysym);
}


int	main(int argc, char *argv[])
{
	t_vars vars;

	int a = 1;
	int b = 1;
	int z = 1;
	int k = 1;
	int i = 0;

	vars.map = checkmap("./map.ber");
	i = strlen(*(vars.map));
	int j = getcol("map.ber");
	(vars.mlx = mlx_init());
	(vars.win = mlx_new_window(vars.mlx, i * 64, j * 64, "Hello world!"));
	vars.img.map.img = mlx_xpm_file_to_image(vars.mlx, "wall.xpm", &k,&z);
	vars.img.wall.img = mlx_xpm_file_to_image(vars.mlx, "bw.xpm", &k,&z);
	vars.img.cc.img = mlx_xpm_file_to_image(vars.mlx, "rs.xpm", &k,&z);
	vars.img.exit.img = mlx_xpm_file_to_image(vars.mlx, "exi.xpm", &k,&z);
	vars.img.player.img = mlx_xpm_file_to_image(vars.mlx, "pacman.xpm", &k , &z);
	vars.img.map.addr = mlx_get_data_addr(vars.img.map.img, &vars.img.map.bits_per_pixel, &vars.img.map.line_length, &vars.img.map.endian);
	vars.img.player.addr = mlx_get_data_addr(vars.img.player.img, &vars.img.player.bits_per_pixel, &vars.img.player.line_length, &vars.img.player.endian);
	vars.img.player.x = 0;
	vars.img.player.y = 0;
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.player.img, vars.img.player.x, vars.img.player.y);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.map.img, vars.img.map.x, vars.img.map.y);
	mlx_key_hook(vars.win, close1, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
