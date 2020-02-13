NAME = libftprintf.a

CYAN_COLOR     := \x1b[36m
GRN_COLOR     := \x1b[32;01m
HEAD_COLOR   := \x1b[32;01m
SILENT_COLOR := \x1b[30;01m

OBJ_DIR = obj/
INC_DIR = includes/

SRC_DIR = src/
SRC_FILES =	ft_printf.c \
              flags.c \
		printf_string.c \
		ft_util.c \
		ft_itoa_o.c \
		ft_itoa.c \
		ft_isdigit.c \
		ft_atoi.c \
		ft_memalloc.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memset.c \
		ft_putstr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strncat.c \
		ft_strnew.c \
		flag_x.c\
		flag_o.c\
		flag_di.c\
		flag_u.c\


HEADERS = $(INC_DIR)ft_printf.h

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))


CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I $(INC_DIR)

all: $(NAME)

$(NAME): $(HEADERS) $(OBJ_DIR) $(OBJ)
	@printf "$(CYAN_COLOR) ZATSHIM!\n"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR):
	@mkdir obj

ALL_SRC_DIRS = $(SRC_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)*
	@printf "$(GRN_COLOR) CHISTO!\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(GRN_COLOR) SUPER CHISTO!\n"

re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)
