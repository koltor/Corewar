# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/14 16:56:52 by matheme      #+#   ##    ##    #+#        #
#    Updated: 2019/10/01 13:48:03 by matheme     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

# nom de l'executable
NAME = corewar

# les routes
SRC_PATH	= src
OBJ_PATH	= obj
INC_PATH	= includes
LIB_PATH	= librairies

# nom des fichier code source (*.c)
NAME_SRC_COREWAR = corewar.c error.c debug.c hexdump.c process_arg.c \
					process_champ.c process_arg_sf.c process_champ_sf.c

#nom des ficher objects (*.o)
NAME_OBJ_COREWAR = $(NAME_SRC_COREWAR:.c=.o)

#les sources
SRC_COREWAR	= $(addprefix $(SRC_PATH)/,$(NAME_SRC_COREWAR))

# les objects
OBJ_COREWAR	= $(addprefix $(OBJ_PATH)/,$(NAME_OBJ_COREWAR))

# les headers
HEADER_COREWAR = $(INC_PATH)/corewar.h

#compilateur + flags
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

#librairies
LIBFT				= $(LIB_PATH)/libft
LIBFT_INCLUDE		= $(LIBFT)
LIBFT.A				= $(LIBFT)/libft.a

all : libft $(NAME)

$(NAME) : $(OBJ_COREWAR) $(LIBFT.A)
	@$(CC) -I $(LIBFT) -L $(LIBFT_INCLUDE)  $^ -o $@
	@echo "\t\033[32m\033[0m"
	@echo "\033[31m \n┏(＾0＾)┛ COREWAR ┗(＾0＾)┓\n\033[0m"
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER_COREWAR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(LIBFT) -I $(INC_PATH) -c $< -o $@
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"

libft :
	@make -C $(LIBFT)

clean :
	@rm -f $(OBJ_COREWAR)
	@make -C $(LIBFT) clean
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all

n :
	@norminette src/*.c includes/*.h
