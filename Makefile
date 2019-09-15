# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/15 14:47:40 by archid-           #+#    #+#              #
#    Updated: 2019/09/15 17:49:56 by archid-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG	:= 1

NAME	= libftprintf.a
FTDIR	= libft 
LIBFT	= -L$(FTDIR) -lft

EXEC	= ft_printf
MAIN	= main.c
RM		= rm -rf

SRCDIR	= src
DEPDIR	= include
OBJDIR	= obj

SRCS	:= $(shell find $(SRCDIR) -type f -name '*.c')
DEPS	:= $(shell find $(DEPDIR) -type f -name '*.h')
OBJS	:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CC		= gcc
CFLAGS	= -Wall -Wextra
LDFLAGS = -I$(DEPDIR) -I$(FTDIR)

GRN		= \033[0;32m[+]\033[0m
RED		= \033[0;31m[-]\033[0m
YLW		= \033[0;33m[*]\033[0m

ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb
else
	CFLAGS += -Werror
endif

.PHONY: all setup clean fclean re

all: setup $(NAME)

$(NAME): $(OBJS)
	@printf  "$(YLW) acrhiving $(NAME)..\n"
	@rm -rf $(NAME)
	ar rc $(NAME) $^ libft/libft.a
ifeq ($(DEBUG), 1)
	@printf  "$(GRN) creating the executable..\n"
	$(CC) $(CFLAGS) -o $(EXEC) $(MAIN) $(NAME) $(LDFLAGS) $(LIBFT)
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

setup:
	@printf  "$(GRN) making libft..\n"
	@make -C ./libft/
	@printf  "$(GRN) compiling object files..\n"

test: all
	./$(NAME)

clean: 
	@printf  "$(RED) cleaning..\n"
	@make -C ./libft/ clean
	$(RM) $(notdir $(OBJS))

fclean: 
	@printf  "$(RED) cleaning everything..\n"
	@make -C ./libft/ fclean
	$(RM) $(notdir $(OBJS))
	$(RM) $(OBJDIR)
	$(RM) $(NAME)

re: fclean all
