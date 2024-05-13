# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 12:01:59 by wonhseo           #+#    #+#              #
#    Updated: 2024/05/14 06:50:29 by wonhseo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
CDEBUG			=	-fsanitize=address -g
RM				=	rm -f
LIB_NAME		=	readline
LIB_HEADER		=	/usr/local/opt/readline/include/
LIB_FOLDER		=	/usr/local/opt/readline/lib/
NAME			=	minishell
HEADER			=	./includes/
FOLDER			=	./srcs/
D_AS			=	astree/
D_BUILT			=	builtin/
D_EXEC			=	exec/
D_LIBFT			=	libft/
D_PARSE			=	parse/
D_RB			=	rbtree/
D_RUN			=	runtime/
SRC_LIST		=	main.c						\
					$(D_AS)check.c				\
					$(D_AS)exec.c				\
					$(D_AS)frag_1.c				\
					$(D_AS)frag_2.c				\
					$(D_AS)print.c				\
					$(D_BUILT)cd.c				\
					$(D_BUILT)echo.c			\
					$(D_BUILT)env.c				\
					$(D_BUILT)exit.c			\
					$(D_BUILT)export.c			\
					$(D_BUILT)pwd.c				\
					$(D_BUILT)unset.c			\
					$(D_EXEC)command_1.c		\
					$(D_EXEC)command_2.c		\
					$(D_EXEC)command_3.c		\
					$(D_EXEC)command_4.c		\
					$(D_EXEC)pipe.c				\
					$(D_EXEC)rdr_1.c			\
					$(D_EXEC)rdr_2.c			\
					$(D_LIBFT)ft_abs.c			\
					$(D_LIBFT)ft_atoi.c			\
					$(D_LIBFT)ft_calloc.c			\
					$(D_LIBFT)ft_free.c			\
					$(D_LIBFT)ft_gnl.c			\
					$(D_LIBFT)ft_isalnum.c		\
					$(D_LIBFT)ft_isalpha.c		\
					$(D_LIBFT)ft_isascii.c		\
					$(D_LIBFT)ft_isdigit.c		\
					$(D_LIBFT)ft_isprint.c		\
					$(D_LIBFT)ft_isspace.c		\
					$(D_LIBFT)ft_itoa.c			\
					$(D_LIBFT)ft_lstadd_back.c	\
					$(D_LIBFT)ft_lstadd_front.c	\
					$(D_LIBFT)ft_lstclear.c		\
					$(D_LIBFT)ft_lstdelone.c		\
					$(D_LIBFT)ft_lstiter.c		\
					$(D_LIBFT)ft_lstlast.c		\
					$(D_LIBFT)ft_lstmap.c			\
					$(D_LIBFT)ft_lstnew.c			\
					$(D_LIBFT)ft_lstshow.c		\
					$(D_LIBFT)ft_lstsize.c		\
					$(D_LIBFT)ft_memset.c			\
					$(D_LIBFT)ft_numlen.c			\
					$(D_LIBFT)ft_putchar.c		\
					$(D_LIBFT)ft_putendl.c		\
					$(D_LIBFT)ft_putnbr.c			\
					$(D_LIBFT)ft_putstr.c			\
					$(D_LIBFT)ft_split.c			\
					$(D_LIBFT)ft_strappend.c		\
					$(D_LIBFT)ft_strchr.c			\
					$(D_LIBFT)ft_strdup.c			\
					$(D_LIBFT)ft_strjoin.c		\
					$(D_LIBFT)ft_strlcpy.c		\
					$(D_LIBFT)ft_strlen.c			\
					$(D_LIBFT)ft_strncmp.c		\
					$(D_LIBFT)ft_strrchr.c		\
					$(D_LIBFT)ft_strtrim.c		\
					$(D_LIBFT)ft_substr.c			\
					$(D_LIBFT)ft_tolower.c		\
					$(D_LIBFT)ft_toupper.c		\
					$(D_LIBFT)ft_wordlen.c		\
					$(D_PARSE)expand_1.c		\
					$(D_PARSE)expand_2.c		\
					$(D_PARSE)pair.c			\
					$(D_PARSE)tokenize.c		\
					$(D_RB)check.c				\
					$(D_RB)delete_1.c			\
					$(D_RB)delete_2.c			\
					$(D_RB)insert_1.c			\
					$(D_RB)insert_2.c			\
					$(D_RB)print.c				\
					$(D_RB)search.c				\
					$(D_RB)util_1.c				\
					$(D_RB)util_2.c				\
					$(D_RB)util_3.c				\
					$(D_RUN)check.c				\
					$(D_RUN)loop.c				\
					$(D_RUN)signal.c			\
					$(D_RUN)termios.c
SRC				=	$(addprefix $(FOLDER), $(SRC_LIST))
OBJ				=	$(SRC:.c=.o)
%.o				:	%.c
					@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $< -I $(LIB_HEADER)
$(NAME)			:	$(OBJ)
					@$(CC) $(CFLAGS) -I $(HEADER) -o $(NAME) $(OBJ) -I $(LIB_HEADER) -l $(LIB_NAME) -L $(LIB_FOLDER)
all				:	$(NAME)
clean			:
					@$(RM) $(OBJ)
fclean			:	clean
					@$(RM) -r readline
					@$(RM) .heredoc
					@$(RM) $(NAME)
re				:	fclean all
bonus			:	all
.PHONY			:	all clean fclean re bonus