# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/15 14:47:40 by archid-           #+#    #+#              #
#    Updated: 2019/09/30 04:18:00 by archid-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG	:= 0

NAME	= libftprintf.a
FTDIR	= libft

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
YLW		= \033[0;33m[o]\033[0m

ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb
else
	CFLAGS += -Werror
endif

.PHONY: all setup clean fclean re

all: setup $(NAME)
	@rm -rf $(EXEC)

ifeq ($(DEBUG), 1)
	@printf  "$(GRN) linking test executable $(MAIN) > $(EXEC)..\n"
	@$(CC) $(CFLAGS) -o $(EXEC) $(MAIN) $(NAME) $(LDFLAGS)
endif

$(NAME): $(OBJS)
	@printf  "$(YLW) archiving $(NAME)..\n"
	@rm -rf $(NAME)
	@ar rc $(NAME) $(shell find $(FTDIR) -name '*.o') $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

setup:
	@printf  "$(GRN) making $(FTDIR)..\n"
	@make -C ./libft/

clean:
	@printf  "$(RED) cleaning..\n"
	@make -C ./libft/ clean
	@$(RM) $(shell find $(OBJDIR) -name '*.o' -type f)

fclean:
	@printf  "$(RED) cleaning everything..\n"
	@make -C ./libft/ fclean
	@$(RM) $(notdir $(OBJS))
	@$(RM) $(OBJDIR)
	@$(RM) $(NAME)

re: fclean
	@make
