INSTALL=/usr/bin/ginstall
bindir = /usr/bin

LIBS_1 = `gtk-config --cflags --libs`
OBJ_1 = szapgtk.cpp
NAME_1 = szapgtk


szapgtk: $(OBJ_1)
	g++ -o $(NAME_1) $(OBJ_1)  $(LIBS_1)

install: szapgtk
	install szapgtk /usr/bin
	chmod 755 /usr/bin/szapgtk
