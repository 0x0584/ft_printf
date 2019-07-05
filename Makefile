EXEC	= ft_printf
CFLAGS	= -Wall -Wextra -ggdb
LDFLAGS = -Llibft -lft -Ilibft

all:
	@echo "making libft.."
	make -C ./libft/
	gcc $(CFLAGS) -o $(EXEC) *.c $(LDFLAGS)
	@echo "compilation done.\n"

test: all
	./$(EXEC)

clean:
	make -C ./libft/ clean
	rm -fv *.o

fclean: clean
	make -C ./libft/ fclean
	rm	-fv fillit
