# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/30 16:29:20 by ssar              #+#    #+#              #
#    Updated: 2021/04/09 22:24:19 by ssar             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX = -Lmlx_linux -lmlx -lXext -lX11 -lm
CC = clang -Wall -Werror -Wextra
NAME = cub3d
SRCS = parse_map/main.c \
       parse_map/check_close_map.c \
       parse_map/check_map.c \
       parse_map/cub_utils_b.c \
       parse_map/cub_utils.c \
       parse_map/ft_atoi.c \
       parse_map/get_info_perso.c \
       parse_map/get_map.c \
       parse_map/get_next_line.c \
       parse_map/get_next_line_utils.c \
       parse_map/get_path.c \
       parse_map/get_res_colors.c \
       parse_map/get_info.c \
       raycast/bitmap.c \
       raycast/collision.c \
       raycast/deplacement_2d.c \
       raycast/distance.c \
       raycast/print.c \
       raycast/print_utils.c \
       raycast/which_texture.c \
       raycast/check_distance.c \
       raycast/sprite_bis.c \
       raycast/sprite.c \
       raycast/sprite_print.c \
       raycast/spr_utils.c \
       raycast/stock_spr.c \
       raycast/utils.c \
       close/close.c \
       close/erreur.c

OBJS = $(SRCS:.c=.o)
$(NAME) : $(OBJS)
	$(MAKE) -C ./mlx_linux
	$(CC) $(OBJS) -I./includes -I./usr/include $(MLX) -o $(NAME)
all : $(NAME)
clean :
	rm -rf $(OBJS)
fclean : clean
	$(MAKE) clean -C ./mlx_linux
	rm -rf $(NAME)
	rm -rf save_image.bmp
re : fclean all
