# nom de l'executable
NAME = corewar

# les routes
SRC_PATH		= srcs
SRC_AUX_PATH	= auxiliary_function
SRC_VISU_PATH	= visualizer
SRC_INST_PATH	= instructions
OBJ_PATH		= bins
INC_PATH		= includes
LIB_PATH		= librairies

# nom des fichier code source (*.c)
NAME_SRC_VISU	 =	init_visu.c g_env.c intro.c quit_visu.c sdl_loop.c interface.c \
					corewar_loop.c print_arena.c print.c highlight_process.c \
					info_process.c footprint.c live.c get_path.c pause_loop.c \
					info_process_sf.c music.c

NAME_SRC_INST	 =	live.c direct_load.c direct_store.c aritmetical_addition.c \
					aritmetical_substraction.c logical_and.c logical_or.c logical_xor.c \
					jump_if_zero.c indirect_load.c indirect_store.c short_fork.c \
					long_direct_load.c long_indirect_load.c long_fork.c aff.c

NAME_SRC_AUX	= error.c op.c ft_memcpy_memsize.c print_memory.c print_memory2.c \
					print_space.c compute_params.c get_params.c get_param_type.c

NAME_SRC_COREWAR =	corewar.c process_arg.c process_arg_sf.c bin_transfer.c\
					process_champ.c process_champ_sf.c generate_start_process.c \
					cycle.c browse_process.c move_process.c clean_process.c \
					affect_new_ocp.c affect_new_opc.c read_ocp.c \
					$(addprefix $(SRC_INST_PATH)/, $(NAME_SRC_INST)) \
					$(addprefix $(SRC_VISU_PATH)/, $(NAME_SRC_VISU)) \
					$(addprefix $(SRC_AUX_PATH)/, $(NAME_SRC_AUX))

#nom des ficher objects (*.o)
NAME_OBJ_COREWAR = $(NAME_SRC_COREWAR:.c=.o)

#les sources
SRC_COREWAR	= $(addprefix $(SRC_PATH)/,$(NAME_SRC_COREWAR))

# les objects
OBJ_COREWAR	= $(addprefix $(OBJ_PATH)/,$(NAME_OBJ_COREWAR))

# les headers
HEADER_COREWAR = $(INC_PATH)/corewar.h $(INC_PATH)/visu_corewar.h

#compilateur + flags
CFLAGS		= -Wall -Wextra -Werror 
SDLFLAGS	= -I /usr/includes/SDL2 $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer -O3
FDB			= -fsanitize=address -g3
CC			= gcc

#librairies
LIBFT				= $(LIB_PATH)/libft
PRINTF				= $(LIB_PATH)/my_printf
LIBFT_INCLUDE		= $(LIBFT)
PRINTF_INCLUDE		= $(PRINTF)
SDL_INCLUDE			= $(LIB_PATH)/SDL2
LIBFT.A				= $(LIBFT)/libft.a
PRINTF.A			= $(PRINTF)/libftprintf.a

all : libft $(NAME)

$(NAME) : $(OBJ_COREWAR) $(LIBFT.A) $(PRINTF.A)
	@$(CC) -I $(LIBFT) -L $(LIBFT_INCLUDE) -I $(PRINTF) -L $(PRINTF_INCLUDE) $(SDLFLAGS) $^ -o $@
	@echo "\t\033[32m\033[0m"
	@echo "\033[31m \n┏(＾0＾)┛ COREWAR ┗(＾0＾)┓\n\033[0m"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER_COREWAR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)/$(SRC_INST_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)/$(SRC_AUX_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)/$(SRC_VISU_PATH) 2> /dev/null || true
	@$(CC) -g3 -I $(LIBFT) -I $(PRINTF_INCLUDE) -I $(INC_PATH) -I $(SDL_INCLUDE) -c $< -o $@
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"

libft :
	@make -C $(LIBFT)

clean :
	@rm -f $(OBJ_COREWAR)
	@make -C $(LIBFT) clean
	@rmdir $(OBJ_PATH)/$(SRC_INST_PATH) 2> /dev/null || true
	@rmdir $(OBJ_PATH)/$(SRC_AUX_PATH) 2> /dev/null || true
	@rmdir $(OBJ_PATH)/$(SRC_VISU_PATH) 2> /dev/null || true
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
