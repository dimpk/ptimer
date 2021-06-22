#
#    Makefile for ptimer
#
#    Created by dimpk
#

CFLAGS = -g -Wall
PKGCONFIG = pkg-config --cflags -libs

src/notifications.o: src/notifications.c src/notifications.h
	$(CC) $(CFLAGS) -c $< `$(PKGCONFIG) glib-2.0 gdk-pixbuf-2.0` -o $@

ptimer: src/main.c src/notifications.o
	$(CC) $(CFLAGS) -lnotify $^ -o $@

clean:
	rm -f src/*.o ptimer
