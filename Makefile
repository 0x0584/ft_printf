NAME	= ft_printf

SRCDIR	= src
DEPDIR	= include
OBJDIR	= objs

SRCS	:= $(shell find $(SRCDIR) -type f -name '*.c')
DEPS	:= $(shell find $(DEPDIR) -type f -name '*.h')
OBJS	:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CC		= gcc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -ggdb # -Werror
LDFLAGS = -I$(DEPDIR) -Ilibft -Llibft -lft

all: setup $(NAME)
	@echo -e "\ncompilation done."

$(NAME): $(OBJS) $(DEPS)
	@echo -e "\nlinking the executable.."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

setup:
	@echo "making libft.."
	@make -C ./libft/
	@echo -e "\ncompiling object files.."
	@mkdir -p $(OBJDIR)

test: all
	./$(NAME)

clean:
	@echo -e "cleaning.."
	@make -C ./libft/ clean
	$(RM) $(OBJS)
	@echo ""

fclean:
	@echo -e "cleaning.."
	@make -C ./libft/ fclean
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	$(RM) $(NAME)
	@echo ""

re: fclean all
