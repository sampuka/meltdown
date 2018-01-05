meltdown: meltdown.c victim.c
	gcc -o meltdown -O0 -Wall -Wextra -std=gnu99 -pedantic meltdown.c
	gcc -o -g victim -O0 -Wall -Wextra -std=gnu99 -pedantic victim.c

clean: 	
	rm meltdown victim
