CC       := cc
CFLAGS   := -g -Wall -Wextra -Werror

NAME     := pipex 

SRC_DIR     := src
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/src
INCLUDES    := -I include -I lib/libft/include

LIBFT_DIR   := lib/libft
LIBFT_A     := $(LIBFT_DIR)/libft.a

SRC      := $(SRC_DIR)/*.c \

OBJ      := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT_A) -o $@
	@clear
	@echo "✅ Build $(NAME) successfully! 🎉"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	# rm -rf $(BUILD_DIR)
	rm -rf $(OBJ_DIR) $(BUILD_DIR)/src
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME) $(BUILD_DIR)
	@make --no-print-directory fclean -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re
