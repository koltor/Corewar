# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/17 11:23:06 by kgrosjea     #+#   ##    ##    #+#        #
#    Updated: 2019/11/15 16:46:00 by kgrosjea    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#__________CONFIG__________#

NAME		=	asm
MAKEFLAGS	+= --silent

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

LIB_FLAGS	=	-L$(LIB_PATH) $(LIB_FLAG)
INC_PREF	=	-I

SRC_PATH	=	./srcs/
BIN_PATH	=	./bins/
INC_PATH	=	./includes/
LIB_PATH	=	../librairies/libft/

INC			=	$(INC_PATH) \
				$(LIB_PATH)

SRC			=	main.c				\
				command_list.c		\
				parse_command.c		\
				parse_line.c		\
				compute_champ.c		\
				compute_param.c		\
				write_to_cor.c		\
				op_infos.c			\
				new_struct.c		\
				op.c				\
				utils.c				\
				str_multisplit.c	\
				label_utils.c		\
				free_structs.c		\
				fix.c				\

BIN			=	$(SRC:.c=.o)

HEADERS		=	$(INC_PATH)asm.h $(INC_PATH)op.h

LIB_FLAG	=	-lft
LIB			=	libft.a

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BINS		=	$(addprefix $(BIN_PATH), $(BIN))
LIBS		=	$(addprefix $(LIB_PATH), $(LIB))
INCS		=	$(addprefix $(INC_PREF), $(INC))

.PHONY: all clean fclean re norm list

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[0;32m
B			=	\033[0;34m
N			=	\33[0;0m

#__________RULES__________#

all: $(LIBS) $(NAME)

$(NAME): $(LIBS) $(BINS)

	@printf "\033[2K\r${G}>>Compiling DONE${N}"
	@$(CC) $(CFLAGS) $(INCS) $(LIB_FLAGS) $^ -o $@ && printf "\n\n${B}[EXECUTABLE \"$(NAME)\" COMPILED]${N}\n\n"

$(LIBS):

	@make -C $(LIB_PATH) 2> /dev/null || TRUE

$(BIN_PATH)%.o: $(SRC_PATH)%.c $(HEADERS)

	@mkdir -p $(BIN_PATH) 2> /dev/null || TRUE
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@printf "\033[2K\r${G}>>Compiling ${N}$<\033[36m \033[0m"

clean:

	@printf "${R}[CLEANING $(NAME) BINARIES]${N}\n\n"
	@rm -f $(BINS)
	@rmdir $(BIN_PATH) 2> /dev/null || TRUE

fclean: clean

	@printf "${R}[REMOVING \"$(NAME)\"]${N}\n\n"
	@rm -f $(NAME)

re: fclean all

norm:

	@norminette ./srcs/*.c ./includes/*.h
