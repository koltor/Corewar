# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/11/15 11:32:51 by kgrosjea     #+#   ##    ##    #+#        #
#    Updated: 2019/11/15 17:13:41 by matheme     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

# nom de l'executable
NAME			=	corewar
MAKEFLAGS	+= --silent

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror 
SDL_FLAGS		=	-I /usr/includes/SDL2 $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer

LIB_FLAGS	=	-L$(LIB_PATH) $(LIB_FLAG)
INC_PREF	=	-I

# les routes
SRC_PATH		=	srcs/
SRC_AUX_PATH	=	auxiliary_function/
SRC_VISU_PATH	=	visualizer/
SRC_INST_PATH	=	instructions/
BIN_PATH		=	bins/
INC_PATH		=	includes/
LIB_PATH		=	../librairies/libft/

INC				=	$(INC_PATH) \
					$(LIB_PATH) \
					../librairies/SDL2/

# nom des fichier code source (*.c)
SRC_VISU		=	init_visu.c \
					g_env.c \
					intro.c \
					quit_visu.c \
					sdl_loop.c \
					interface.c \
					corewar_loop.c \
					print_arena.c \
					print.c \
					highlight_process.c \
					info_process.c \
					footprint.c \
					live.c \
					get_path.c \
					pause_loop.c \
					info_process_sf.c \
					music.c \
					my_rand.c \
					winner.c \
					check_resource_visu.c

SRC_INST		=	live.c \
					direct_load.c \
					direct_store.c \
					aritmetical_addition.c \
					aritmetical_substraction.c \
					logical_and.c logical_or.c \
					logical_xor.c \
					jump_if_zero.c \
					indirect_load.c \
					indirect_store.c \
					short_fork.c \
					long_direct_load.c \
					long_indirect_load.c \
					long_fork.c \
					aff.c \

SRC_AUX			=	error.c \
					op.c \
					ft_memcpy_memsize.c \
					print_memory.c \
					print_memory2.c \
					print_space.c \
					compute_params.c \
					get_params.c \
					get_param_type.c \

SRC				=	corewar.c \
					process_arg.c \
					process_arg_sf.c \
					bin_transfer.c \
					process_champ.c \
					process_champ_sf.c \
					generate_start_process.c \
					cycle.c \
					browse_process.c \
					move_process.c \
					clean_process.c \
					affect_new_ocp.c \
					affect_new_opc.c \
					read_ocp.c \
					$(addprefix $(SRC_INST_PATH), $(SRC_INST)) \
					$(addprefix $(SRC_VISU_PATH), $(SRC_VISU)) \
					$(addprefix $(SRC_AUX_PATH), $(SRC_AUX))

#nom des ficher objects (*.o)
BIN				=	$(SRC:.c=.o)

# les headers
HEADERS			=	$(INC_PATH)corewar.h $(INC_PATH)visu_corewar.h $(INC_PATH)op.h

#librairies
LIB_FLAG			=	-lft
LIB					=	libft.a

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

all : $(LIBS) $(NAME)

$(NAME) : $(LIBS) $(BINS)

	@printf "\033[2K\r${G}>>Compiling DONE${N}"
	@$(CC) $(CFLAGS) $(INCS) $(LIB_FLAGS) $(SDL_FLAGS) $^ -o $@ && printf "\n\n${B}[EXECUTABLE \"$(NAME)\" COMPILED]${N}\n\n"

$(LIBS):

	@make -C $(LIB_PATH) 2> /dev/null || TRUE
	
$(BIN_PATH)%.o : $(SRC_PATH)%.c $(HEADERS)

	@mkdir -p $(BIN_PATH) 2> /dev/null || TRUE
	@mkdir -p $(BIN_PATH)/$(SRC_INST_PATH) 2> /dev/null || TRUE
	@mkdir -p $(BIN_PATH)/$(SRC_AUX_PATH) 2> /dev/null || TRUE
	@mkdir -p $(BIN_PATH)/$(SRC_VISU_PATH) 2> /dev/null || TRUE
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@printf "\033[2K\r${G}>>Compiling ${N}$<\033[36m \033[0m"

clean :

	@printf "${R}[CLEANING $(NAME) BINARIES]${N}\n\n"
	@rm -f $(BINS)
	@rmdir $(BIN_PATH)/$(SRC_INST_PATH) 2> /dev/null || TRUE
	@rmdir $(BIN_PATH)/$(SRC_AUX_PATH) 2> /dev/null || TRUE
	@rmdir $(BIN_PATH)/$(SRC_VISU_PATH) 2> /dev/null || TRUE
	@rmdir $(BIN_PATH) 2> /dev/null || TRUE

fclean: clean

	@printf "${R}[REMOVING \"$(NAME)\"]${N}\n\n"
	@rm -f $(NAME)

re: fclean all

norm :
	@norminette src/*.c includes/*.h
