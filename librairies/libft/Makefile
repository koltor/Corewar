# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/02 13:36:56 by kgrosjea     #+#   ##    ##    #+#        #
#    Updated: 2019/11/15 16:45:54 by kgrosjea    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

MAKEFLAGS	+=	--silent

#__________CONFIG__________#

CC			= gcc
NAME		= libft.a

FLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I ./libft.h

SRCDIR		= ./
BINDIR		= ./

SRC			=	ft_putchar.c			\
				ft_putstr.c				\
				ft_tolower.c			\
				ft_isalnum.c			\
		        ft_isalpha.c			\
    		    ft_isascii.c			\
				ft_isdigit.c			\
				ft_isprint.c			\
				ft_toupper.c			\
				ft_atoi.c				\
				ft_strcpy.c				\
				ft_strncpy.c			\
				ft_strcat.c				\
				ft_strncat.c			\
				ft_strlcat.c			\
				ft_strcmp.c				\
				ft_strncmp.c			\
				ft_strstr.c				\
				ft_strnstr.c			\
				ft_strchr.c				\
				ft_strrchr.c			\
				ft_strlen.c				\
				ft_strdup.c				\
				ft_memset.c				\
				ft_bzero.c				\
				ft_memcpy.c				\
				ft_memccpy.c			\
				ft_memmove.c			\
				ft_memchr.c				\
				ft_memcmp.c				\
				ft_memalloc.c			\
				ft_memdel.c				\
				ft_strnew.c				\
				ft_strdel.c				\
				ft_strclr.c				\
				ft_strctn.c				\
				ft_striter.c			\
				ft_striteri.c			\
				ft_strmap.c				\
				ft_strmapi.c			\
				ft_strequ.c				\
				ft_strnequ.c			\
				ft_strsub.c 			\
				ft_strjoin.c			\
				ft_strtrim.c			\
				ft_strtrim_f.c			\
				ft_strsplit.c			\
				ft_itoa.c				\
				ft_putendl.c			\
				ft_putnbr.c				\
				ft_putchar_fd.c			\
				ft_putstr_fd.c			\
				ft_putendl_fd.c			\
				ft_putnbr_fd.c			\
				ft_lstnew.c				\
				ft_lstdelone.c			\
				ft_lstdel.c				\
				ft_lstadd.c				\
				ft_lstiter.c			\
				ft_lstmap.c				\
				ft_pow.c				\
				ft_sqrt.c				\
				ft_isupper.c			\
				ft_islower.c			\
				ft_isspace.c			\
				ft_factorial.c			\
				get_next_line.c			\
				ft_max.c				\
				ft_min.c				\
				ft_nblen.c				\
				ft_lltoa_base.c			\
				ft_ulltoa_base.c		\
				ft_strjoin_f.c			\
				ft_strcapitalize.c		\
				ft_parsing.c			\
				ft_manage_structs.c		\
				ft_get_format_parts.c	\
				ft_fill_format.c		\
				ft_convert_string.c		\
				ft_convert_character.c	\
				ft_convert_decimal.c	\
				ft_convert_octal.c		\
				ft_convert_hexa.c		\
				ft_convert_unsigned.c	\
				ft_convert_pointer.c	\
				ft_convert_float.c		\
				ft_printf.c				\
				ft_sprintf.c			\
				ft_ldtoa.c				\
				ft_abs.c				\
				rgb_to_int.c			\
				ft_unsigned_int_reverse_octet.c		\
				ft_unsigned_short_reverse_octet.c	\
				ft_atol.c				\
				ft_itoa_base.c			\
				ft_hexdump.c			\

BIN			= $(SRC:.c=.o)

SRCS		= $(addprefix $(SRCDIR), $(SRC))
BINS		= $(addprefix $(BINDIR), $(BIN))

COMPILE		= $(CC) $(FLAGS) $(INCLUDES)

.PHONY: all clean fclean re

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[0;32m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME)

$(NAME): $(BINS)

	@printf "\033[2K\r${G}>>Compiling DONE${N}"
	@ar rc $(NAME) $^
	@printf "\n\n${B}[LIBRARY \"$(NAME)\" COMPILED]${N}\n"
	@ranlib $(NAME)
	@printf "${B}[LIBRARY \"$(NAME)\" INDEXED]${N}\n\n"

$(BINDIR)%.o: $(SRCDIR)%.c libft.h

	@$(COMPILE) -o $@ -c $<
	@printf "\033[2K\r${G}>>Compiling ${N}$<"

clean:
	
	@printf "${R}[CLEANING $(NAME) BINARIES]${N}\n\n"
	@rm -f $(BINS)

fclean: clean
	
	@printf "${R}[REMOVING \"$(NAME)\"]${N}\n\n"
	@rm -f $(NAME)

re: fclean all
