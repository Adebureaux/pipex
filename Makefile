# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/12 13:49:29 by adeburea          #+#    #+#              #
#    Updated: 2021/08/28 01:13:40 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
.PHONY: all clean fclean re

CC		=	gcc
NAME	=	pipex
FLAGS	=	-Wall -Wextra -Werror
INC		=	pipex.h
OBJ		=	objs
OBJS	=	$(addprefix $(OBJ)/, $(SRCS:.c=.o))
SRCS 	=	main.c \
			ft_strings.c \
			ft_split.c \
			ft_utils.c

$(NAME): $(LIBFT) $(OBJ) $(OBJS)
	$(CC) $(FLAGS) -I$(INC) -o $(NAME) $(OBJS)

$(OBJ):
	@mkdir -p $(OBJ)

$(OBJ)/%.o: ./%.c
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
