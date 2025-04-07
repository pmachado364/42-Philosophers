# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 10:36:24 by pmachado          #+#    #+#              #
#    Updated: 2025/04/07 17:49:14 by pmachado         ###   ########.fr        #
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
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g
SNTZ = -fsanitize=thread

#==============================================================================#
#                                    Paths                                     #
#==============================================================================#

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

#SRC = $(wildcard $(SRC_DIR)/*.c)
#OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
SRCS = $(SRC_DIR)/philo.c \
	   $(SRC_DIR)/actions.c \
	   $(SRC_DIR)/behaviour.c \
	   $(SRC_DIR)/clean.c \
	   $(SRC_DIR)/init.c \
	   $(SRC_DIR)/parsing.c \
	   $(SRC_DIR)/threads.c \
	   $(SRC_DIR)/utils.c \
	   $(SRC_DIR)/utils_2.c \
	   
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
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

san: $(OBJ)
	@echo "Linking $(NAME) with ThreadSanitizer..."
	@$(CC) $(CFLAGS) $(SNTZ) $(INC) -o $(NAME) $(OBJ)
	@echo "Sanitized binary built."

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(ERROR)$(RED)Executable and objects deleted.$(RESET)"

re: fclean all

.PHONY: all clean fclean re san