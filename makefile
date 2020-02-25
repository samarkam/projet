prog : obj/main.o obj/init.o obj/event.o obj/map.o obj/load.o obj/interface.o obj/editeur.o obj/jeu.o
	gcc obj/main.o obj/init.o obj/event.o obj/map.o obj/load.o obj/interface.o obj/editeur.o obj/jeu.o -o bin/prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
obj/main.o : main.c
	gcc -c main.c -o obj/main.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer  -g
obj/init.o : init.c
	gcc -c init.c -o obj/init.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer  -g
obj/event.o : event.c
	gcc -c event.c -o obj/event.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer  -g
obj/map.o : map.c
	gcc -c map.c -o obj/map.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer  -g
obj/interface.o : interface.c
	gcc -c interface.c -o obj/interface.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer  -g
obj/editeur.o : editeur.c
	gcc -c editeur.c -o obj/editeur.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer  -g
obj/jeu.o : jeu.c
	gcc -c jeu.c -o obj/jeu.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer  -g
obj/joueur.o : joueur.c
	gcc -c joueur.c -o obj/joueur.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer  -g
