all: ex-compile word_count

ex-compile: ex_compile.c
	gcc -Wall ex_compile.c -o ex-compile -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0

word_count: word_count.c
	gcc -Wall word_count.c -o word_count -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0