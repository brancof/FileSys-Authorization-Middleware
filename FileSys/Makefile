crFilesys: passthr.o verify.o getCode.o email.o
	gcc -o crFilesys passthr.o verify.o getCode.o email.o `pkg-config fuse3 --cflags --libs`  -lcurl 

passthr.o: passthr.c verify.h email.h
	gcc -o passthr.o  passthr.c  `pkg-config fuse3 --cflags --libs` -c -Wall

verify.o: verify.c verify.h getCode.h  config.h
	gcc -o verify.o verify.c -c -Wall -lcurl

getCode.o: getCode.c getCode.h
	gcc -o getCode.o getCode.c -c -Wall -lcurl

email.o: email.c email.h config.h
	gcc -o email.o email.c -c -Wall -lcurl

clean:
	rm -rf *.o *~ crFilesys


	