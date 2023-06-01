NAME	= pipex
NAME_B  = pipex_bonus

SRCS 	= srcs/pipex.c srcs/utils.c
OBJS 	= ${SRCS:.c=.o}

SRCS_B	= srcs/pipex_bonus.c srcs/utils.c srcs/utils_bonus.c
OBJS_B	= ${SRCS_B:.c=.o}

HEADER	= -Iincludes

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g

.c.o:		%.o : %.c
					@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: 		${NAME}

${NAME}:	${OBJS}
					@make re -C ./libft
					@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m: ${NAME}" 
					@$(CC) ${OBJS} -Llibft -lft -o ${NAME}
					


bonus:		${NAME_B}

${NAME_B}:	${OBJS_B}
					@make re -C ./libft
					@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m: ${NAME}" 
					@$(CC) ${OBJS_B} -Llibft -lft -o ${NAME_B}

clean:
					@make clean -C ./libft
					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${NAME}"
					@make fclean -C ./libft
					@rm -f $(NAME_B)
					@rm -f ${NAME}

re:			fclean all

re_bonus:	fclean bonus


.PHONY: all clean fclean re re_bonus bonus