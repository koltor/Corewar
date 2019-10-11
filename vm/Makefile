# nom de l'executable
NAME = corewar

# les routes
SRC_PATH		= src
SRC_INST_PATH	= instructions
OBJ_PATH		= bins
INC_PATH		= includes
LIB_PATH		= librairies

# nom des fichier code source (*.c)
NAME_SRC_COREWAR = corewar.c error.c debug.c process_arg.c \
					process_champ.c process_arg_sf.c process_champ_sf.c \
					generate_start_process.c browse_lst.c cycle.c op.c \
					move_process.c \
					$(SRC_INST_PATH)/live.c $(SRC_INST_PATH)/direct_load.c \
					$(SRC_INST_PATH)/direct_store.c $(SRC_INST_PATH)/aritmetical_addition.c \
					$(SRC_INST_PATH)/aritmetical_substraction.c $(SRC_INST_PATH)/logical_and.c \
					$(SRC_INST_PATH)/logical_or.c $(SRC_INST_PATH)/logical_xor.c \
					$(SRC_INST_PATH)/jump_if_zero.c $(SRC_INST_PATH)/indirect_load.c \
					$(SRC_INST_PATH)/indirect_store.c $(SRC_INST_PATH)/short_fork.c \
					$(SRC_INST_PATH)/long_direct_load.c $(SRC_INST_PATH)/long_indirect_load.c \
					$(SRC_INST_PATH)/long_fork.c $(SRC_INST_PATH)/aff.c

#nom des ficher objects (*.o)
NAME_OBJ_COREWAR = $(NAME_SRC_COREWAR:.c=.o)

#les sources
SRC_COREWAR	= $(addprefix $(SRC_PATH)/,$(NAME_SRC_COREWAR))

# les objects
OBJ_COREWAR	= $(addprefix $(OBJ_PATH)/,$(NAME_OBJ_COREWAR))

# les headers
HEADER_COREWAR = $(INC_PATH)/corewar.h

#compilateur + flags
CFLAGS	= -Wall -Wextra -Werror 
FDB		= -fsanitize=address -g3
CC		= gcc

#librairies
LIBFT				= $(LIB_PATH)/libft
PRINTF				= $(LIB_PATH)/my_printf
LIBFT_INCLUDE		= $(LIBFT)
PRINTF_INCLUDE		= $(PRINTF)
LIBFT.A				= $(LIBFT)/libft.a
PRINTF.A			= $(PRINTF)/libftprintf.a

all : libft $(NAME)

$(NAME) : $(OBJ_COREWAR) $(LIBFT.A) $(PRINTF.A)
	@$(CC) -I $(LIBFT) -L $(LIBFT_INCLUDE) -I $(PRINTF) -L $(PRINTF_INCLUDE) $^ -o $@
	@echo "\t\033[32m\033[0m"
	@echo "\033[31m \n┏(＾0＾)┛ COREWAR ┗(＾0＾)┓\n\033[0m"
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER_COREWAR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)/$(SRC_INST_PATH) 2> /dev/null || true
	@$(CC) -I $(LIBFT) -I $(PRINTF_INCLUDE) -I $(INC_PATH) -c $< -o $@
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"

libft :
	@make -C $(LIBFT)

clean :
	@rm -f $(OBJ_COREWAR)
	@make -C $(LIBFT) clean
	@rmdir $(OBJ_PATH)/$(SRC_INST_PATH) 2> /dev/null || true
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\t\033[32m\033[0m"
	@echo "\033[37m \n (✌ﾟ∀ﾟ)☞  delete bins \n\033[0m"

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@echo "\033[33m \n DELETE COREWAR ᕙ(⇀‸↼‶)ᕗ  \n\033[0m"

re: fclean all

n :
	@norminette src/*.c includes/*.h
