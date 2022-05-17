SRC_DIR		=	.

SRCS		=	$(addprefix ${SRC_DIR}/,	\
				ft_printf.c					\
				ft_printf_cs.c				\
				ft_printf_pxx.c				\
				ft_printf_diu.c				\
				ft_printf_utils.c			\
				)

OBJS		=	${SRCS:.c=.o}

NAME		=	libftprintf.a

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

AR_RC		=	ar rcs

MAKE		=	make -C

RM			=	rm -f

all:			${NAME}

${NAME}:		${OBJS} 
				${AR_RC} ${NAME} ${OBJS}

.c.o:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:			
				${RM} ${OBJS}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re 
