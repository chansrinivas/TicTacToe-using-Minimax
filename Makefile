PROG = tictactoe

$(PROG): tictactoe.c
	gcc -g -o $@ $<

clean:
	rm -rf $(PROG) 
