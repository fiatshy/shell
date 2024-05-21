TARGET = minishell
CC	= gcc
FLAGS = -Wall -Wextra -Werror
FLAG_BONUS = 0

H = $(addprefix -I, $(HEADER_DIR))
HEADER_DIR = ./includes/
HEADER = ./includes/minishell.h 

SRCS_DIR = ./srcs/

SRCS_ARGUMENTS = arguments/arg_dollar_check.c \
					arguments/arg_dollar_environ.c \
					arguments/arg_dollar_set.c \
					arguments/arg_dollar_utils.c \
					arguments/arg_question_set.c \
					arguments/arg_set.c \
					arguments/arg_wild_check.c \
					arguments/arg_wild_set.c \

SRCS_SPLIT = split/ft_split_first.c \
				split/ft_split_first_nested.c \
				split/ft_split_quote.c \
				split/ft_split_quote_nested.c \
				split/ft_split_string.c \
				split/ft_split_string_nested.c \

SRCS_INIT = init/init.c \
				init/init_env.c \
				init/init_fd_pipe.c \

SRCS_GNL = gnl/get_next_line.c \
			gnl/get_next_line_utils.c \

SRCS_BUILTIN = builtin/builtin.c \
				builtin/builtin_nested.c \
				builtin/builtin_utils.c \
				builtin/env.c \

SRCS_FORK = fork/fork.c \
			fork/fork_parents.c \
			fork/fork_prepare.c \
			fork/fork_redirect.c \
			fork/fork_redirect_nested.c \

SRCS_PATH = path/get_exec_path.c \
			path/relative_path.c \
			path/relative_utils.c \

SRCS_PIPE = pipe/pipe.c \
			pipe/set_tunnel.c \

SRCS_ANDOR = andor/grouping.c \
				andor/handle_parenthesis.c \

SRCS_UTILS = utils/free.c \
				utils/handle_signal.c \
				utils/misc.c \
				utils/util.c \
				utils/util_gets.c \

SRCS_LIST = minishell.c \
			$(SRCS_ARGUMENTS) \
			$(SRCS_ANDOR) \
			$(SRCS_BUILTIN) \
			$(SRCS_FORK) \
			$(SRCS_GNL) \
			$(SRCS_INIT) \
			$(SRCS_PATH) \
			$(SRCS_PIPE) \
			$(SRCS_SPLIT) \
			$(SRCS_UTILS) \

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	= ./objs/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

LIBFT_PATH = ./srcs/libft/

.PHONY: all clean fclean re bonus

all: $(TARGET)

$(TARGET): $(OBJS)
	@ make -C $(LIBFT_PATH)
	@ $(CC) $(FLAGS) $(H) $^ -D BONUS=$(FLAG_BONUS) -o $@ $(LIBFT_PATH)libft.a -lreadline

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(H) -c -o $@ $<

bonus:
	@ $(MAKE) all FLAG_BONUS=1

clean:
	@ rm -rf $(OBJS_DIR)
	@ make clean -C $(LIBFT_PATH)
	@ if [ -f "tmp" ]; then \
		rm "tmp"; \
	fi

fclean: clean
	@ rm -f $(TARGET)
	@ make fclean -C $(LIBFT_PATH)

re: fclean all
