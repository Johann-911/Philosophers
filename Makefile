# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 11:58:55 by jtoumani          #+#    #+#              #
#    Updated: 2025/07/25 15:19:54 by jtoumani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# philo/Makefile
NAME		= philo

# Compiler and Flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Iincludes -g 
LDFLAGS		= -lpthread 

# Directory Structure
SRCDIR		= src
OBJDIR		= build

# Source Files
SRC			= $(wildcard $(SRCDIR)/*.c)
OBJ			= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Linking $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "$(GREEN)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "$(RED)Cleaning object files$(NC)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)$(NC)"
	@rm -f $(NAME)

re: fclean all

# Phony targets
.PHONY: all clean fclean re