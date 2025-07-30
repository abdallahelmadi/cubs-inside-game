CC = cc
RM = rm -rf
NAME = cub3D
LINKINGFLAGS = -lm -lmlx -lX11 -lXext
CFLAGS = -I./ # -Wextra -Wall -Werror
OBJECTS = cub3d.o \
	      ./ray-casting/gameinit.o

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LINKINGFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	$(RM) $(OBJECTS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.SECONDARY : $(OBJECTS)