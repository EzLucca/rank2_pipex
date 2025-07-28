NAME = libft.a

DIR_SRC = .
DIR_OBJ = $(DIR_SRC)/objects
HEADERS = include/

LIBFT_FLAGS = -L $(DIR_LIB) -lft

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g -fPIE
AR = ar rcs
RM = rm -rf

# Submodules directory
GNL_DIR = ./gnl
FT_PRINTF_DIR = ./ft_printf

# Files
LIBFT_FILES = 	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_memset.c  \
				ft_bzero.c \
				ft_memcpy.c  \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \
				ft_free_array.c \
				ft_error_exit.c \
				ft_minmax.c

GNL_FILES = $(GNL_DIR)/get_next_line.c \
			$(GNL_DIR)/get_next_line_utils.c

FT_PRINTF_FILES = $(FT_PRINTF_DIR)/ft_printf.c \
				  $(FT_PRINTF_DIR)/ft_printf_chars.c \
				  $(FT_PRINTF_DIR)/ft_printf_hex.c 

# Objects
LIBFT_OBJECTS = $(patsubst %.c, $(DIR_OBJ)/%.o, $(LIBFT_FILES))
GNL_OBJECTS = $(patsubst $(GNL_DIR)/%.c, $(DIR_OBJ)/%.o, $(GNL_FILES))
FT_PRINTF_OBJECTS = $(patsubst $(FT_PRINTF_DIR)/%.c, $(DIR_OBJ)/%.o, $(FT_PRINTF_FILES))

# Targets
all: $(NAME)

$(NAME): $(LIBFT_OBJECTS) $(FT_PRINTF_OBJECTS) $(GNL_OBJECTS)
	@$(AR) $@ $^
	@echo "✅ Build $(GREEN)$(NAME) $(NC)successfully! 🎉"

$(DIR_OBJ)/%.o: %.c | $(DIR_OBJ)
	@$(COMPILER) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(DIR_OBJ)/%.o: $(GNL_DIR)/%.c | $(DIR_OBJ)
	@$(COMPILER) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(DIR_OBJ)/%.o: $(FT_PRINTF_DIR)/%.c | $(DIR_OBJ)
	@$(COMPILER) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

clean:
	@$(RM) $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
