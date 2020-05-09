NAME = libftprintf.a

CYAN_COLOR     := \x1b[36m
GRN_COLOR     := \x1b[32;01m

OBJ_DIR = obj/
INC_DIR = includes/

SRC_DIR = src/
SRC_FILES =	ft_printf.c \
            flags.c \
			flag_x.c\
			flag_f.c\
			flag_lf.c\
			flag_o.c\
			flag_di.c\
			flag_u.c\
			flag_s.c\
			flag_c.c\
			flag_size.c\
			flag_color.c\
			util.c \
			buffun.c \
			offpre.c \
			stringfun.c \
			memfun.c \
		ft_itoa.c \
		ft_isdigit.c \
		ft_atoi.c \
		calculator.c\


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
