##
## Makefile for test in /media/bigott_a/fcf68f6c-ae09-4a35-9a71-539d19cb9a04/home/bigott_a/Documents/Bomberman/Projet/test_lib
## 
## Made by bigott-a
## Login   <bigott_a@epitech.net>
## 
## Started on  Tue Apr 30 10:37:43 2013 bigott-a
## Last update Sun Jun  9 19:05:57 2013 bigott-a
##

CC=		g++

RM=		rm -f

SRC=		InterfaceGraphique.cpp\
		camera.cpp\
		Vector3f.cpp\
		Bombe.cpp\
		Player.cpp\
		Object.cpp\
		Text.cpp\
		Picture.cpp\
		Error.cpp\
		Map.cpp\
		Score.cpp\
		ABlock.cpp\
		Menu.cpp\
		main.cpp\
		Ia.cpp\
		Bonus.cpp\
		Introduction.cpp\
		Plan.cpp

OBJ=		$(SRC:.cpp=.o)

NAME=		bomberman

CPP_FLAGS=	-I ./lib/libgdl_gl-2012.4/include\
		-L ./lib/libgdl_gl-2012.4/lib\
		-Wl,--rpath=./lib/libgdl_gl-2012.4/lib\
		-lsfml-audio\
		-lgdl_gl -lGL -lGLU\
		-Wall -W -Werror

.cpp.o:
	$(CC) -c $< $(CPP_FLAGS)

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPP_FLAGS)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all