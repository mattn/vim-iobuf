all : iobuf.dll iobuf_inject.dll

iobuf.dll : iobuf.c
	gcc -m64 -static -shared -o iobuf.dll iobuf.c

iobuf_inject.dll : iobuf_inject.c
	gcc -m64 -static -shared -o iobuf_inject.dll iobuf_inject.c -lmsvcrt

clean:
	-rm iobuf_inject.dll iobuf.dll
