# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirardi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:09:47 by agirardi          #+#    #+#              #
#    Updated: 2022/05/10 16:23:50 by agirardi         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

INC_PATH	:=	includes
SRC_PATH	:=	srcs
OBJ_PATH	:=	.objects

LST_INCS	:=	main.h

LST_SRCS	:=	main.c \
				parsing.c \
				initialization.c \
				threads.c \
				routine.c \
				utils.c \
				lib/ft_atoi.c \
				lib/ft_isdigit.c \
				lib/ft_strlen.c

LST_OBJS	:=	$(LST_SRCS:.c=.o)

INCS		:=	$(addprefix $(INC_PATH)/,$(LST_INCS))
SRCS		:=	$(addprefix $(SRC_PATH)/,$(LST_SRCS))
OBJS		:=	$(addprefix $(OBJ_PATH)/,$(LST_OBJS))

CC			:=	gcc

CFLAGS		:=	-Wall -Wextra -Werror -pthread

RM			:=	rm -rf

ERASE		:=	\033[2K\r
BOLD		:=	\033[1m
redir		:=	\033[31m
GREEN		:=	\033[32m
BLUE		:=	\033[34m
PINK		:=	\033[35m
BOLD		:=	\033[1m
END			:=	\033[0m

all : $(NAME)

.SILENT:

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS) Makefile | $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@
	printf "$(BLUE)> Compiling :$(END) $<\n"

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)/lib

$(NAME): $(OBJS)
	printf "$(GREEN)> All the .c files from so_long have been compiled successfully !$(END)\n"
	printf "$(BLUE)> Creating the executable file :$(END) $@\n"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	printf "$(GREEN)> Executable file has been created successfully !$(END)\n"
	
clean:
	${RM} ${OBJ_PATH}
	printf "$(GREEN)> All the .o files have been removed successfully !$(END)\n"

fclean: clean
	$(RM) $(NAME)
	printf "$(GREEN)> all executable files have been removed successfully !$(END)\n"

re: fclean all

.PHONY: all clean fclean re
