tokenizer: tokenizer.c
	gcc -Wall -Werror -o tokenizer tokenizer.c

clean:
	rm -f tokenizer
