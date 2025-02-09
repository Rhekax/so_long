/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:13:50 by mdursun           #+#    #+#             */
/*   Updated: 2025/02/09 18:28:08 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define BUFFERSIZE 1024



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
}				t_images;
typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_images	img;
}				t_vars;
# include "./minilibx-linux/mlx_int.h"
# include "./minilibx-linux/mlx.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "math.h"
# include "X11/keysym.h"
# include <fcntl.h>

#endif