# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 09:44:35 by araiteb           #+#    #+#              #
#    Updated: 2023/09/18 21:52:15 by nait-ali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc 
CFLAGS := -Wall -Wextra -Werror -g 
INCLUDE := minishell.h
SRCS := main.c  execution2.c fonction_libft.c char_size.c ft_split.c list.c ft_strtrim.c \
		syntaxe.c free.c execution.c file.c list2.c fonction_here_doc.c exit.c echo.c pwd.c \
		cd.c unset.c export.c les_outiles.c update_env.c env.c signals.c export2.c initialisation.c\
		ft_lstnew.c export3.c error_messaages.c get_cmd.c execution3.c execution4.c expand.c execchile.c
OBJS := $(SRCS:.c=.o)
EXEC := minishell
COMP = ~/.brew/opt/readline/lib
LINK = ~/.brew/opt/readline/include

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