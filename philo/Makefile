# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/29 17:16:49 by jhurpy            #+#    #+#              #
#    Updated: 2023/10/30 16:54:27 by jhurpy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = @gcc
C_FLAGS = -pthread -Wall -Wextra -Werror -g3 #-fsanitize=address
#S_FLAGS = -g -fsanitize=address,undefined,leak

# Commands
RM = @rm -f
AR = ar rc

# ---------------------------------------------------------------------------- #

# Target library name and directories
NAME = philo
INC = -I.
SRC =	philo.c \
		parser.c \
		init_data.c \
		routine.c \
		time.c \
		writer.c \
		utils_philo.c
OBJ = $(SRC:.c=.o)

# ---------------------------------------------------------------------------- #

# Default target, build the library
all: $(NAME)

# Object file build rule
%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

# Target library build rule
$(NAME): $(OBJ)
	$(CC) $(C_FLAGS) $(OBJ) -o $(NAME)

# ---------------------------------------------------------------------------- #

# Clean object files
clean:
	$(RM) $(OBJ)

# Clean object files and target library
fclean: clean
	$(RM) $(NAME)

# Clean and rebuild the target library
re: fclean all

# Check code style
norm:
	@norminette -R CheckForbiddenSourceHeader *.c ;
	@norminette -R CheckDefine *.h ;

# Phony targets
.PHONY: all clean fclean re norm
