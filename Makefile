# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaucher <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 14:23:30 by afaucher          #+#    #+#              #
#    Updated: 2014/01/03 19:01:55 by afaucher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = /usr/bin/gcc

SOURCES = wolf3d.c image.c tab.c point.c wall.c game.c player.c \

OBJS = $(SOURCES:.c=.o)

LINKS = -lmlx -lXext -lX11

FLAGS = -Wall -Werror -Wextra

LIBFT_DIR = libft/

LIBMLX = /usr/X11/lib

LIB = libft/libft.a

NAME = wolf3d

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) -o $(NAME) $(FLAGS) $(SOURCES:.c=.o) -L$(LIBMLX) $(LIB) $(LINKS)

%.o: %.c
	$(CC) -o $@ -c $^ $(FLAGS)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(SOURCES:.c=.o)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: $(LIBFT_DIR) clean fclean re all
