#******************************************************************************#
#																			   #
#														  :::	   ::::::::	   #
#	 Makefile											:+:		 :+:	:+:	   #
#													  +:+ +:+		  +:+	   #
#	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		   #
#												  +#+#+#+#+#+	+#+			   #
#	 Created: 2019/03/30 17:28:04 by archid-		   #+#	  #+#			   #
#	 Updated: 2019/06/30 01:28:46 by archid-		  ###	########.fr		   #
#																			   #
#******************************************************************************#

NAME	= libft.a
RM		= rm -f

DEPS	= libft.h
SRCS	= $(shell find . -type f -name "*.c")
OBJS	= $(patsubst %.c, %.o, $(SRCS))

CC		= gcc
CFLAGS	= -Wall -Wextra -ggdb # -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
