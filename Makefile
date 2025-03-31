NAME= so_long
CC=gcc
# CFLAGS= -Wall -Wextra -Werror
PRINTFPATH = ft_printf/
PRINTFLIB = ft_printf/libftprintf.a
LIBFTPATH = libft/
LIBFTLIB = libft/libft.a
SRC= game.c Get_next_line/get_next_line.c Get_next_line/get_next_line_utils.c
OBJ= ${SRC:%.c=%.o}

all: ${NAME}


$(NAME): $(OBJ) ${PRINTFLIB} ${LIBFTLIB}
	$(CC) $(OBJ) ${PRINTFLIB} ${LIBFTLIB} -L/home/ogi/Desktop/so_long/lib/minilibx -lmlx_Linux -L/home/ogi/Desktop/so_long/lib/minilibx -I/home/ogi/Desktop/so_long/lib/minilibx -lXext -lX11 -lm -lz -o $(NAME)

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
minilibx:
	@echo "...cloning minilibx..."
	@git clone https://github.com/42paris/minilibx-linux.git ./lib/minilibx > /dev/null 2>&1; 
	@make -C ./lib/minilibx > /dev/null 2>&1

re : fclean all clean minilibx