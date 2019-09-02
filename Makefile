NAME	= ft_printf
LIBFT	= -Ilibft -Llibft -lft

SRCDIR	= src
DEPDIR	= include
OBJDIR	= obj

SRCS	:= $(shell find $(SRCDIR) -type f -name '*.c')
DEPS	:= $(shell find $(DEPDIR) -type f -name '*.h')
OBJS	:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CC		= gcc
CFLAGS	= -Wall -Wextra -ggdb # -Werror
LDFLAGS = -I$(DEPDIR) $(LIBFT)

RM		= rm -rf

all: $(NAME)
	@echo -e "\ncompilation done."

$(NAME): setup $(OBJS) $(DEPS)
	@echo -e "\nlinking the executable.."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

setup:
	@echo "making libft.."
	@make -C ./libft/
	@echo -e "\ncompiling object files.."

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
