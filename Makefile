# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oouklich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/06 12:08:45 by oouklich          #+#    #+#              #
#    Updated: 2020/11/17 20:13:14 by oouklich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computor

SRC_DIR = src
SRCS = main.cpp\
       computor.cpp\
       solver.cpp\
       root.cpp\
       utils.cpp
SRC = $(add prefic src/, $(SRCS))

OBJ_DIR = obj
OBJ = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

INCLUDES = -I inc

CFLAGS = #-Werror -Wextra -Wall

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)

obj/%.o: src/%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)


re: fclean all

!PHONY: all, clean, fclean, re
