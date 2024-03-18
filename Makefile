_:
	@clear
	@fasm example.asm a.out
	@chmod +x a.out
	@./a.out

clean:
	rm -f a.out
