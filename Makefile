# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 09:44:35 by araiteb           #+#    #+#              #
#    Updated: 2023/08/22 22:52:55 by araiteb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc 
CFLAGS := -Wall -Wextra -Werror -g 
INCLUDE := minishell.h
SRCS := main.c  execution2.c fonction_libft.c char_size.c ft_split.c list.c ft_strtrim.c \
		syntaxe.c free.c execution.c file.c list2.c fonction_here_doc.c
OBJS := $(SRCS:.c=.o)
EXEC := minishell
COMP = $(shell brew --prefix readline)/lib
LINK = $(shell brew --prefix readline)/include

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS)$^ -o $@ -lreadline -L $(COMP)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -I $(LINK) -c  $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re : fclean all
.PHONY: all clean fclean