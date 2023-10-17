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
	git ls-remote git@github.com:xxxattemtion/work.git
	git log





