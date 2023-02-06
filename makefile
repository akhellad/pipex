NAME	=	pipex


SRCDIR	=	./src
INCDIR	=	./includes
BINCDIR =	./bonus_includes
OBJDIR	=	./obj
BONDIR	=	./bonus
BONOBJDIR = ./bonus_obj

SRC		=	pipex.c \
			utils.c \
			ft_split.c \
			childs.c \
			w_error.c \
			free.c \

BONUSSRC = 	pipex_bonus.c \
			utils_bonus.c \
			ft_split_bonus.c \
			childs_bonus.c \
			w_error_bonus.c \
			free_bonus.c \
			get_next_line.c \
			get_next_line_utils.c \
			here_doc.c \

OBJ		= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))
BONUSOBJ =  $(addprefix $(BONOBJDIR)/,$(BONUSSRC:.c=.o))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3


all: obj ${NAME}

obj:
	@mkdir -p ${OBJDIR}

obj_bonus:
	mkdir -p ${BONOBJDIR}

${OBJDIR}/%.o:${SRCDIR}/%.c
	@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) ${CFLAGS} -I ${INCDIR} -o $@ -c $<

${BONOBJDIR}/%.o:${BONDIR}/%.c
	@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) ${CFLAGS} -I ${BINCDIR} -o $@ -c $<

$(NAME): $(OBJ)
	@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m:" $<
	@$(CC) $(OBJ) -o $(NAME) 

bonus: obj_bonus $(BONUSOBJ) 
	@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m:" $<
	@$(CC) $(BONUSOBJ) -o $(NAME)


clean:
	@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: $(OBJDIR)" $<
	@rm -rf $(OBJDIR)
	@rm -rf $(BONOBJDIR)
	@rm -rf .here_doc

fclean: clean
	@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${NAME}"
	@rm -rf $(NAME)

re: fclean all 