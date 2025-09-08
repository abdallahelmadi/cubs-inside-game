CC = cc
RM = rm -rf
NAME = cub3D
LINKINGFLAGS = -lm -lmlx -lX11 -lXext
CFLAGS = -I./ -Wextra -Wall -Werror
OBJECTS = ./main.o \
		  ./tools/playerinit.o \
		  ./tools/gameinit.o \
		  ./tools/rerenderinit.o \
		  ./tools/pressinit.o \
		  ./tools/exitinit.o \
		  ./tools/rerenderinit_utils.o \
		  ./utils/helper_functions.o \
		  ./parsin/check_path.o \
		  ./parsin/check_map.o \
		  ./utils/get_next_line.o \
		  ./utils/get_next_line_utils.o \
		  ./utils/split.o parsin/assign_col_tex.o \
		  ./parsin/create_map.o \
		  ./parsin/check_walls.o \
		  ./parsin/check_walls_help.o \
		  ./parsin/check_colors.o \
		  ./parsin/assign_col.o \
		  ./parsin/create_map_helper.o \
		  ./utils/others.o

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