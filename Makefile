DEBUG	= 0

NAME	= libftprintf.a
LIBFT	= -Ilibft -Llibft -lft

RM		= rm -rf
MAIN	= main.c
EXEC	= ft_printf

SRCDIR	= src
DEPDIR	= include
OBJDIR	= obj

SRCS	:= $(shell find $(SRCDIR) -type f -name '*.c')
DEPS	:= $(shell find $(DEPDIR) -type f -name '*.h')
OBJS	:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CC		= gcc
CFLAGS	= -Wall -Wextra
LDFLAGS = -I$(DEPDIR) $(LIBFT)

ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb
else
	CFLAGS += -Werror
endif

all: $(NAME)
	@echo -e "\ncompilation done."

$(NAME): setup $(OBJS) $(DEPS)
	@echo -e "\nbuilding the library.."
	ar rc $(NAME) $(OBJS)

ifeq ($(DEBUG), 1)
	@echo -e "\ncreating the executable.."
	$(CC) $(CFLAGS) -o $(EXEC) $(MAIN) $(NAME) $(LDFLAGS)
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

setup:
	@echo -e "\nmaking libft.."
	@make -C ./libft/
	@echo -e "\ncompiling object files.."

test: all
	./$(NAME)

clean:
	@echo -e "cleaning.."
	@make -C ./libft/ clean
	@echo -e ""
	$(RM) $(OBJS)

fclean:
	@echo -e "cleaning.."
	@make -C ./libft/ fclean
	@echo -e ""
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	$(RM) $(NAME)

re: fclean all
