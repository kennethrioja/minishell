NAME		=	minishell

SRC_DIR 	= 	src/
SRCS		=	main.c					\
				get_line.c				\
				ms_split.c				\
				ms_split_utils.c		\
				ms_split_redir_utils.c	\
				ms_split_pa_utils.c		\
				signal.c				\
				free_all.c				\

FT_DIR		=	ft/
LIBFT_DIR	=	$(SRC_DIR)$(FT_DIR)libft
INC_LIBFT	=	-I $(LIBFT_DIR) -L $(LIBFT_DIR) -lft
PRINTF_DIR	=	$(SRC_DIR)$(FT_DIR)ft_printf
INC_PRINTF	=	-I $(PRINTF_DIR) -L $(PRINTF_DIR) -lftprintf

ifeq ($(shell hostname | cut -b -6), c1r6s3)
	READLINE_DIR	=	~/goinfre/homebrew/Cellar/readline/8.1.2/
else ifeq ($(shell hostname | cut -b -6), c3r4s1)
	READLINE_DIR	=	~/goinfre/.brew/Cellar/readline/8.1.2/
else ifeq ($(shell env | grep USER= | cut -b 6-), tpinto-m)
	READLINE_DIR	=	~/.brew/Cellar/readline/8.1.2/
endif
READLINE_LIB=	$(READLINE_DIR)lib
READLINE_INC=	$(READLINE_DIR)include
INC_READLINE=	-I $(READLINE_INC) -L $(READLINE_LIB) -lreadline

OBJ_DIR		= 	obj/
OBJS		=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o) $(SRCS_GNL:.c=.o))

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror
LEAKS		=	-fsanitize=address
MAKE		=	make -C
RM			=	rm -rf

all:			$(NAME)

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				$(CC) -c $(CFLAGS) -Iinc -I $(READLINE_INC) $< -o $@

$(OBJ_DIR)%.o :	$(GNL_DIR)%.c
				$(CC) -c $(CFLAGS) -I inc/ $< -o $@

$(NAME):		$(OBJS)
				$(MAKE) $(LIBFT_DIR)
				$(MAKE) $(PRINTF_DIR)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC_READLINE) $(INC_PRINTF) $(INC_LIBFT) 

l:				$(OBJS)
				source ~/goinfre/.zshrc
				which clang
				$(MAKE) $(LIBFT_DIR)
				$(MAKE) $(PRINTF_DIR)
				clang $(LEAKS) $(OBJS) -o $(NAME) $(INC_READLINE) $(INC_PRINTF) $(INC_LIBFT)

clean:
				$(RM) $(OBJ_DIR)
				$(RM) $(OBJS)
				$(MAKE) $(PRINTF_DIR) clean
				$(MAKE) $(LIBFT_DIR) clean

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
