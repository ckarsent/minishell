NAME = minishell

CC = cc -g3 -Wall -Werror -Wextra
CFLAGS = -Iinclude -Ilibft
LDFLAGS = -lreadline

LIBFT_DIR = libft
SRC_DIR = src
OBJ_DIR = obj

LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  $(SRC_DIR)/main.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/execution/branch.c \
		$(SRC_DIR)/parsing/errors.c \
		$(SRC_DIR)/parsing/expansion_len.c \
		$(SRC_DIR)/parsing/expansion.c \
		$(SRC_DIR)/parsing/init_list.c \
		$(SRC_DIR)/parsing/parsing_utils.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/tokenize.c \
		$(SRC_DIR)/parsing/type.c \
        $(SRC_DIR)/utils/debug.c \
        $(SRC_DIR)/utils/free.c \
        $(SRC_DIR)/utils/pingouin.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_SUBDIRS = $(sort $(dir $(OBJS)))

all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
