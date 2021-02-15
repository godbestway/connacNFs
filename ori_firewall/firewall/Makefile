GXX=/usr/bin/clang
GCC=/usr/bin/gcc
FLAGS=-lpcap -std=gnu99 -ggdb 
FILES=read.c packets.c rules.c handle_packets.c state.c
OUTPUT=firewall

make :
	${GCC} ${FILES} ${FLAGS} -o ${OUTPUT}
