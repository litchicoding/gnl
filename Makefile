##### Executable program's name ###############################################
NAME = get_next_line.a

##### Define path and variables ###############################################
###############################################################################
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g

##### Define source files and objects #########################################
###############################################################################
SRC = get_next_line.c get_next_line_utils.c
HEADER =  get_next_line.h
OBJ = $(SRC:.c=.o)

##### Rule by default #########################################################
###############################################################################
all: $(NAME)

##### Create objectc (.o) from source fils (.c )###############################
###############################################################################
%.o: %.c
	@$(CC) -c $(CFLAGS) -I$(HEADER) $< -o $@

##### Linking objects in executable ###########################################
###############################################################################
$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

##### Clean objects ###########################################################
###############################################################################
clean:
	@$(RM) -r *.o

##### Clean executable ########################################################
###############################################################################
fclean: clean
	@$(RM) $(NAME)

re: fclean all 

.PHONY: all clean fclean re