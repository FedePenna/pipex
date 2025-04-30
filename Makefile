SRCS_DIR	=	srcs/

SRC			=	main.c \
		init.c \
		opener.c \
		family.c \
		pipex.c \
		free.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRC))

OBJS_DIR	=	objs/

OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))

NAME		=	pipex

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -gdwarf-4

RM			=	rm -f

INCLUDES	=	-I/usr/include -Ilibft

LIBFT_FLAGS	=	-Llibft -lft

all:			$(NAME)

$(OBJS_DIR):
				mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c | $(OBJS_DIR)
				$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME):		$(OBJS_DIR) $(OBJS)
				@make -C ./libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)

clean:
				$(RM) $(OBJS)
				$(RM) -r $(OBJS_DIR)
				@make -C ./libft clean

fclean:			clean
				$(RM) $(NAME)
				@make -C ./libft fclean

re:				fclean all

all:			$(NAME)

norm:
				@norminette $(SRCS) $(SRCS_DIR)pipex.h

.PHONY:			all clean fclean re norm test