# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 10:36:24 by pmachado          #+#    #+#              #
#    Updated: 2025/02/07 11:23:33 by pmachado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color codes
RED    = \033[1;31m
ORANGE = \033[1;33m
RESET  = \033[0m
GREEN  = \033[1;32m
WHITE  = \033[1;37m

# SYMBOLS
SUCCESS = $(WHITE)[$(GREEN)✅$(WHITE)] $(GREEN)
ERROR = $(WHITE)[$(RED)❌$(WHITE)] $(RED)

#==============================================================================#
#                           Compiler and flags                                 #
#==============================================================================#

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

#==============================================================================#
#                                    Paths                                     #
#==============================================================================#

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
INC = -I$(INC_DIR) -I.

#==============================================================================#
#                                    Rules                                     #
#==============================================================================#

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Building $(NAME)..."
	@$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ)
	@echo "$(SUCCESS)$(NAME)$(GREEN) compiled successfully.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(ERROR)$(RED)Executable and objects deleted.$(RESET)"

re: fclean all

.PHONY: all clean fclean re