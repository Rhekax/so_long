NAME= so_long
CC=gcc
# CFLAGS= -Wall -Wextra -Werror
PRINTFPATH = ft_printf/
PRINTFLIB = ft_printf/libftprintf.a
LIBFTPATH = libft/
LIBFTLIB = libft/libft.a
SRC= game.c
OBJ= ${SRC:%.c=%.o}

all: ${NAME}


$(NAME): $(OBJ) ${PRINTFLIB} ${LIBFTLIB}
	$(CC) $(OBJ) ${PRINTFLIB} ${LIBFTLIB} -L/home/mdursun/Desktop/mlx/minilibx_linux -lmlx_Linux -L/home/mdursun/Desktop/mlx/minilibx-linux -I/home/mdursun/Desktop/mlx/minilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

${PRINTFLIB} : 
	@make -C ${PRINTFPATH}

${LIBFTLIB} :
	@make -C ${LIBFTPATH}

clean :
	@make -C ${PRINTFPATH} clean
	@make -C ${LIBFTPATH} clean
	@rm -rf ${OBJ}

fclean :
	@make -C ${PRINTFPATH} fclean
	@make -C ${LIBFTPATH} fclean
	@rm -rf  ${OBJ} ${NAME}

re : fclean all clean