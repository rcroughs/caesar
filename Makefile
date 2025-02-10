FLAGS = -Wall -Wextra -Werror

all: encode decode

encode: encode.c
	gcc -o encode encode.c $(FLAGS)

decode: decode.c
	gcc -o decode decode.c $(FLAGS)

clean: 
	rm -f encode decode
