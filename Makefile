all:
	gcc -o hw7_test hw7.c hw7_test.o
	gcc -o hw7_main hw7.c hw7_main.c
clean:
	rm hw7_main hw7_test
submit:
	echo "To verify your submission went through"
	git add hw7.c
	git commit -m "submission"
	git push
verify:
	git ls-remote ~cs240/repos/${USER}/hw7
	git -C ~cs240/repos/${USER}/hw7.git log
