NAME		=	minishell

SRC_DIR 	= 	src/
SRCS		=	signal.c\
				prompt.c\
				print.c\
				main.c

#FT_DIR		=	ft_functions/
#LIBFT_DIR	=	$(FT_DIR)libft
#INC_LIBFT	=	-I $(LIBFT_DIR) -L $(LIBFT_DIR) -lft
#PRINTF_DIR	=	$(FT_DIR)ft_printf
#INC_PRINTF	=	-I $(PRINTF_DIR) -L $(PRINTF_DIR) -lftprintf
#GNL_DIR	=	$(FT_DIR)get_next_line/
#SRCS_GNL	=	get_next_line.c							\
#				get_next_line_utils.c

READLINE_DIR=	~/.brew/Cellar/readline/8.1.2/
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
				#$(MAKE) $(LIBFT_DIR)
				#$(MAKE) $(PRINTF_DIR)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC_READLINE) #$(INC_LIBFT) $(INC_PRINTF)

l:				$(OBJS)
				source ~/goinfre/.zshrc
				which clang
				clang $(LEAKS) $(OBJS) -o $(NAME) #$(INC_LIBFT) $(INC_PRINTF)

clean:
				$(RM) $(OBJ_DIR)
				$(RM) $(OBJS)
				#$(MAKE) $(LIBFT_DIR) clean
				#$(MAKE) $(PRINTF_DIR) clean

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
