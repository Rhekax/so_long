/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:13:50 by mdursun           #+#    #+#             */
/*   Updated: 2025/04/15 06:58:22 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define BUFFERSIZE 1024


# include "./minilibx-linux/mlx_int.h"
# include "./minilibx-linux/mlx.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "math.h"
# include "X11/keysym.h"
# include <fcntl.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_data;
typedef struct	s_images {
	t_data	player;
	t_data	map;
	t_data	wall;
	t_data	exit;
	t_data	cc;
}				t_images;
typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_images	img;
	char		**map;
	char		**map2;
	char		*path;
}				t_vars;
typedef struct s_fill
{
	int	player_count;
	int	exit_count;
	int	collected_count;
}	t_fill;

char	**ft_mapdup(char **map);
void	count_coin(t_vars *vars, char *path);
void	path_check(char *path);
size_t	getcol(char *path);
void	err();
void	destroy(t_vars *vars);
void	check_flood_fill(t_vars *vars, int total_collectibles);
void	free_both_maps(t_vars *vars);
void	free_2d(char **map);
void	validate_map_walls(t_vars *vars);

#endif