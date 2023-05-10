project:main.o code.o pass1.o pass2.o print.o allocation.o data.o label.o
	gcc -ansi -pedantic -Wall -g main.o code.o pass1.o pass2.o print.o allocation.o data.o label.o -o project
main.o:main.c project.h
	gcc -c -ansi -pedantic -Wall main.c -o main.o
code.o:code.c project.h
	gcc -c -ansi -pedantic -Wall code.c -o code.o
pass1.o:pass1.c project.h
	gcc -c -ansi -pedantic -Wall pass1.c -o pass1.o
pass2.o:pass2.c project.h
	gcc -c -ansi -pedantic -Wall pass2.c -o pass2.o
print.o:print.c project.h
	gcc -c -ansi -pedantic -Wall print.c -o print.o
allocation.o:allocation.c project.h
	gcc -c -ansi -pedantic -Wall allocation.c -o allocation.o
data.o: data.c project.h
	gcc -c -ansi -pedantic -Wall data.c -o data.o
label.o: label.c project.h
	gcc -c -ansi -pedantic -Wall label.c -o label.o	

