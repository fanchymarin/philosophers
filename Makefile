# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 19:28:34 by fmarin-p          #+#    #+#              #
#    Updated: 2022/08/03 17:19:04 by fmarin-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CFLAGS = -g -Wall -Wextra -Werror -I$(INCDIR)

SRCFILES = *.c 
OBJFILES = $(SRCFILES:.c=.o)

SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

SRCDIR = src/
INCDIR = include/
OBJDIR = obj/

all: $(NAME)

$(NAME): $(SRCOBJ)
	gcc -o $@ $^

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc -c $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
