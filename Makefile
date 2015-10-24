# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/27 01:03:36 by y0ja              #+#    #+#              #
#    Updated: 2014/12/29 21:46:50 by jripoute         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG=no
ifeq ($(DEBUG),no)
	FLAGS=-Wall -Wextra -Werror
else
	FLAGS= -g
endif
NAME=ft_ls
FLAGS= -g 
LDFLAGS= -I./includes/ -L./libft/ -lft
SRC=	get_data.c get_data2.c main.c \
		make_dlist_files.c misc.c set_params.c \
		long_listingf.c long_listingf2.c \
		colors.c colors2.c recurs_n_sort.c \
		error.c

OBJ=$(SRC:.c=.o)

INC=	colors.h error.h ft_ls.h libft.h
SRCDIR=./srcs/
OBJDIR=./objs/
INCDIR=./includes/
SRCS=$(addprefix $(SRCDIR), $(SRC))
OBJS=$(addprefix $(OBJDIR), $(OBJ))
INCS=$(addprefix $(INCDIR), $(INC))

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	make -C libft/
	@gcc $(FLAGS) -o $@ $^ $(LDFLAGS)
	@echo "\\033[1;32mSuccess."
$(OBJS): $(SRCS)
ifeq ($(DEBUG),yes)
		@echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
		@echo "\\033[1;31mCompilation with -Wall -Wextra -Werror...\\033[0;39m"
endif
	@echo "\\033[1;34mGenerating objects... Please wait."
	@gcc $(FLAGS) -c $(SRCS) $(LDFLAGS)
	@mv $(OBJ) $(OBJDIR)

.PHONY: clean fclean re

clean:
	@echo "\\033[1;34mDeleting objects..."
	@rm -f $(OBJS)

fclean: clean
	@echo "\\033[1;34mDeleting ft_ls..."
	@rm -f $(NAME)

re: fclean all
