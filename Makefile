EXEC	= ft_printf

SRCDIR	= src
DEPDIR	= include
OBJDIR	= objs

CC		= gcc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -ggdb # -Werror
LDFLAGS = -I$(DEPDIR) -Ilibft -Llibft -lft

SRCS	:= $(shell find $(SRCDIR) -type f -name '*.c')
DEPS	:= $(shell find $(DEPDIR) -type f -name '*.h')
OBJS	:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: setup $(EXEC)
	@echo "compilation done."

$(EXEC): $(OBJS) $(DEPS)
	@echo "linking the executable.."
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

setup:
	@echo "making libft.."
	@make -C ./libft/
	@echo "making the objects.."
	@mkdir -p $(OBJDIR)

test: all
	./$(EXEC)

clean:
	@make -C ./libft/ clean
	$(RM) $(OBJS)

fclean:
	@make -C ./libft/ fclean
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	$(RM) $(EXEC)

re: fclean all
