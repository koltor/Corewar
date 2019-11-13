# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/03 11:06:26 by yalabidi     #+#   ##    ##    #+#        #
#    Updated: 2019/11/07 14:10:25 by matheme     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME=libft.a
MAKEFLAGS += --silent


HEADER=libft.h

OBJ= 	ft_memcpy.o\
		ft_strncat.o\
		ft_memmove.o\
		ft_memset.o\
		ft_strcpy.o\
		ft_strncpy.o\
		ft_bzero.o\
		ft_memccpy.o\
		ft_strdup.o\
		ft_memchr.o\
		ft_strlcat.o\
		ft_memcmp.o\
		ft_strcat.o\
		ft_strlen.o\
		ft_strchr.o\
		ft_strrchr.o\
		ft_strstr.o\
		ft_strnstr.o\
		ft_strcmp.o\
		ft_strncmp.o\
		ft_atoi.o\
		ft_atol.o\
		ft_isalpha.o\
		ft_isalnum.o\
		ft_isascii.o\
		ft_isdigit.o\
		ft_isprint.o\
		ft_toupper.o\
		ft_tolower.o\
		ft_putchar.o\
		ft_putstr.o\
		ft_putendl.o\
		ft_putnbr.o\
		ft_putchar_fd.o\
		ft_putstr_fd.o\
		ft_putendl_fd.o\
		ft_putnbr_fd.o\
		ft_memalloc.o\
		ft_memdel.o\
		ft_strnew.o\
		ft_strdel.o\
		ft_strclr.o\
		ft_striter.o\
		ft_striteri.o\
		ft_strmap.o\
		ft_strmapi.o\
		ft_strequ.o\
		ft_strnequ.o\
		ft_strsub.o\
		ft_strjoin.o\
		ft_strtrim.o\
		ft_strsplit.o\
		ft_itoa.o\
		ft_power.o\
		ft_putadresse.o\
		ft_puttab.o\
		ft_tabsub.o\
		get_next_line.o\
		ft_lstadd.o\
		ft_lstnew.o\
		ft_hexdump.o\
		ft_lstdelone.o\
		ft_lstdel.o \
		ft_unsigned_int_reverse_octet.o \
		ft_int_reverse_octet.o \
		ft_short_reverse_octet.o \
		ft_unsigned_short_reverse_octet.o \
		ft_count_signed_number_size.o \
		ft_itoa_base.o \
		ft_nblen.o


CC=-Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@echo "\t\033[32m\033[0m"
	@echo "\033[35m\n(✌ﾟ∀ﾟ)☞  libft Compiler\n\033[0m"

%.o : %.c
	@gcc -I$(HEADER) $(CC) -c $^ -o $@
	@ar rs $(NAME) $@
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"

clean :
	@rm -f $(OBJ)
fclean : clean
	@rm -f $(NAME)

re : fclean all

