# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/11/15 11:32:20 by kgrosjea     #+#   ##    ##    #+#        #
#    Updated: 2019/11/15 16:46:10 by kgrosjea    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

MAKEFLAGS	+= --silent

VM_FOLDER = ./vm/
ASM_FOLDER = ./asm/
LIBFT_FOLDER = ./librairies/libft

all : libft vm asm

libft:
	@make -C $(LIBFT_FOLDER)
	
vm:
	@make -C $(VM_FOLDER)

asm:
	@make -C $(ASM_FOLDER)

clean:
	@make clean -C $(VM_FOLDER)
	@make clean -C $(ASM_FOLDER)
	@make clean -C $(LIBFT_FOLDER)

fclean:
	@make fclean -C $(VM_FOLDER)
	@make fclean -C $(ASM_FOLDER)
	@make fclean -C $(LIBFT_FOLDER)

re: fclean all

norm:
	@norminette $(VM_FOLDER)/srcs/*.c
	@norminette $(VM_FOLDER)/includes/*.h
	@norminette $(ASM_FOLDER)/srcs/*.c
	@norminette $(ASM_FOLDER)/includes/*.h
	@norminette $(LIBFT_FOLDER)/*.c
	@norminette $(LIBFT_FOLDER)/*.h

.PHONY: vm asm libft clean fclean re norm