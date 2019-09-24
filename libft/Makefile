#******************************************************************************#
#																			   #
#														  :::	   ::::::::	   #
#	 Makefile											:+:		 :+:	:+:	   #
#													  +:+ +:+		  +:+	   #
#	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		   #
#												  +#+#+#+#+#+	+#+			   #
#	 Created: 2019/03/30 17:28:04 by archid-		   #+#	  #+#			   #
#    Updated: 2019/09/23 17:51:10 by archid-          ###   ########.fr        #
#																			   #
#******************************************************************************#

DEBUG	= 1

NAME	= libft.a
RM		= rm -f

DEPS	= libft.h
SRCS	= $(shell find . -type f -name "*.c")
OBJDIR	= obj
OBJS	= $(patsubst %.c, %.o, $(SRCS))

CC		= gcc
CFLAGS	= -Wall -Wextra

YLW		= \033[0;33m[o]\033[0m

ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb
else
	CFLAGS += -Werror
endif

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(YLW) archiving $(NAME)..\n"
	@rm -rf $(NAME)
	@ar rc $(NAME) $^

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(notdir $(OBJS))

fclean:
	@$(RM) $(notdir $(OBJS))
	@$(RM) $(NAME)

re: fclean all
