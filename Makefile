NAME = minishell

CC = cc -Wall -Werror -Wextra
CFLAGS = -Iinclude -Ilibft
LDFLAGS = -lreadline

LIBFT_DIR = libft
SRC_DIR = src
OBJ_DIR = obj

LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  $(SRC_DIR)/builtins/cd.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/builtins/env.c \
		$(SRC_DIR)/builtins/exit.c \
		$(SRC_DIR)/builtins/export_sort.c \
		$(SRC_DIR)/builtins/export.c \
		$(SRC_DIR)/builtins/pwd.c \
		$(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/execution/cmd.c \
		$(SRC_DIR)/execution/execution.c \
		$(SRC_DIR)/execution/execution2.c \
		$(SRC_DIR)/execution/execution3.c \
		$(SRC_DIR)/execution/execution4.c \
		$(SRC_DIR)/execution/execution5.c \
		$(SRC_DIR)/execution/heredoc.c \
		$(SRC_DIR)/execution/heredoc2.c \
		$(SRC_DIR)/expansion/expansion.c \
		$(SRC_DIR)/parsing/errors.c \
		$(SRC_DIR)/parsing/init_cmd.c \
		$(SRC_DIR)/parsing/init_env.c \
		$(SRC_DIR)/parsing/init_token.c \
		$(SRC_DIR)/parsing/parsing_utils.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/quote.c \
		$(SRC_DIR)/parsing/tokenize.c \
		$(SRC_DIR)/parsing/type.c \
        $(SRC_DIR)/utils/debug.c \
        $(SRC_DIR)/utils/free.c \
        $(SRC_DIR)/utils/pingouin.c \
		$(SRC_DIR)/env_utils.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/signaux.c \

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
