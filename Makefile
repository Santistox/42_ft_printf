NAME = libftprintf.a

NO_COLOR     := \x1B[31m
OK_COLOR     := \x1b[32;01m
HEAD_COLOR   := \x1b[32;01m
SILENT_COLOR := \x1b[30;01m

OBJ_DIR = obj/
INC_DIR = includes/

SRC_DIR = src/
SRC_FILES =		ft_printf.c \
				printf_digits.c \
				printf_string.c \
				ft_util.c \
				ft_itoa_o.c \

LIBFT_DIR = libft/
LIBFT_FILES = ft_memset.c\
              ft_bzero.c\
              ft_memcpy.c\
              ft_memccpy.c\
              ft_memmove.c\
              ft_memchr.c\
              ft_memcmp.c\
              ft_strlen.c\
              ft_strdup.c\
              ft_strcpy.c\
              ft_strncpy.c\
              ft_strcat.c\
              ft_strncat.c\
              ft_strlcat.c\
              ft_strchr.c\
              ft_strrchr.c\
              ft_strstr.c\
              ft_strnstr.c\
              ft_strcmp.c\
              ft_strncmp.c\
              ft_atoi.c\
              ft_isalpha.c\
              ft_isdigit.c\
              ft_isalnum.c\
              ft_isascii.c\
              ft_isprint.c\
              ft_toupper.c\
              ft_tolower.c\
              ft_memalloc.c\
              ft_memdel.c\
              ft_strnew.c\
              ft_strdel.c\
              ft_strclr.c\
              ft_striter.c\
              ft_striteri.c\
              ft_strmap.c\
              ft_strmapi.c\
              ft_strequ.c\
              ft_strnequ.c\
              ft_strsub.c\
              ft_strjoin.c\
              ft_strtrim.c\
              ft_strsplit.c\
              ft_itoa.c\
              ft_putchar.c\
              ft_putstr.c\
              ft_putendl.c\
              ft_putnbr.c\
              ft_putchar_fd.c\
              ft_putstr_fd.c\
              ft_putendl_fd.c\
              ft_putnbr_fd.c


HEADERS = $(INC_DIR)ft_printf.h $(LIBFT_DIR)libft.h

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))


CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I $(INC_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(HEADERS) $(OBJ_DIR) $(OBJ)
	@printf "$(NO_COLOR) HAM PIZDA\n"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR):
	@mkdir obj

ALL_SRC_DIRS = $(SRC_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)*
	@printf "$(OK_COLOR) CHISTO!\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(OK_COLOR) SUPER CHISTO!\n"

re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)