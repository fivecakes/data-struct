
# 所有的.c文件列表，然后把.c换成.o
objects := $(patsubst %.c,%.o,$(wildcard */*.c *.c))

main:$(objects)
	gcc -o $@ $^ 

# %.c是对所有的.c文件逐个执行命令，*.c是对所有的*.c执行一次命令
%.o:%.c
	gcc -Wall -c -o $@ $^

clean:
	rm -f $(objects) main

