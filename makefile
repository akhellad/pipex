NAME	=	pipex


SRCDIR	=	./src
INCDIR	=	./includes
OBJDIR	=	./obj

SRC		=	pipex.c \
			utils.c \
			ft_split.c \
			childs.c \
			w_error.c \
			free.c

OBJ		= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror


all: obj ${NAME}

obj: 
	@mkdir ${OBJDIR}

${OBJDIR}/%.o:${SRCDIR}/%.c
	@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) ${CFLAGS} -I ${INCDIR} -o $@ -c $<

$(NAME): $(OBJ)
	@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m:" $<
	@$(CC) $(OBJ) -o $(NAME)

clean:
	@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: $(OBJDIR)" $<
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${NAME}"
	@rm -rf $(NAME)

re: fclean all 