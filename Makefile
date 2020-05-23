NAME = libftprintf.a

CYAN_CLR = \x1b[36m
GRN_CLR  = \x1b[32m
NO_CLR	 = \x1b[00m
WRN_CLR	 = \x1b[31m
HDR_PR = NO

OBJ_DIR = obj/
INC_DIR = includes/

SRC_DIR = src/
SRC_FILES =	ft_printf.c \
			error.c \
            flags.c \
            flags_help.c \
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
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n$(GRN_CLR)SUCCESS!$(NO_CLR)\n"



$(OBJ_DIR):
	@mkdir obj

ALL_SRC_DIRS = $(SRC_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@if [ "$(HDR_PR)" = "NO" ]; then \
		printf "\n$(CYAN_CLR)BUILD STAUS:$(NO_CLR)\n\n"; \
		$(eval HDR_PR = YES) \
	fi
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@printf "$(NO_CLR)$(notdir $<) "
	@printf "$(GRN_CLR)✓$(NO_CLR)\n"

clean:
	@rm -rf $(OBJ_DIR)*
	@echo "Cleaning" [ $(OBJ_DIR) ] "..." "$(GRN_CLR)OK"
	@printf "$(NO_CLR)All object files have been $(WRN_CLR)Removed!\n"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(NO_CLR)Cleaning" [ $(NAME) ] "..." "$(GRN_CLR)OK"
	@printf "$(NO_CLR)$(NAME) have been $(WRN_CLR)Removed!\n"

re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)
