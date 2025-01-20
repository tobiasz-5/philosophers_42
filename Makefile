NAME = philo

SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror -O2 -pthread -Wno-unused-result

HEADER = ./src/philosophers.h

HEAD = \033[1;32m
BLUE = \033[1;34m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(HEAD)-------MANDATORY-------$(RESET)"
	@echo "$(BLUE)Compiling Philosophers Project$(RESET)"
	@echo "$(RED)...Setting the table$(RESET)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Table cleaned...$(RESET)"
	@rm -f $(OBJ)

fclean:
	@echo "$(GREEN)Table fcleaned...$(RESET)"
	@rm -f $(NAME) $(OBJ)

re: fclean all

val: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)
	@echo "$(GREEN)Valgrind Flags Used: $(RESET)$(YELLOW)--leak-check=full --show-leak-kinds=all --track-origins=yes$(RESET)"

hel: re
	@valgrind --tool=helgrind ./$(NAME) $(ARGS)
	@echo "$(GREEN)Valgrind Tool Used: $(RESET)$(RED)--tool=helgrind$(RESET)"

.PHONY: all clean fclean re val hel
