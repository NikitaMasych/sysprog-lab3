
lexer: helpers.h helpers.c main.c number_lexem_parser.c number_lexem_parser.h operator_lexem_parser.h operator_lexem_parser.c letter_lexem_parser.c letter_lexem_parser.h types.h types.c
	gcc -g main.c types.c vector.c helpers.c letter_lexem_parser.c number_lexem_parser.c operator_lexem_parser.c -o lexer

tests: lexer tests/test_helpers.c tests/test_helpers.h tests/number_lexem_test/main.c tests/operator_lexem_test/main.c tests/letter_lexem_test/main.c
	gcc -g tests/number_lexem_test/main.c tests/test_helpers.c number_lexem_parser.c helpers.c types.c -o number_lexem_test
	gcc -g tests/operator_lexem_test/main.c tests/test_helpers.c operator_lexem_parser.c helpers.c types.c -o operator_lexem_test
	gcc -g tests/letter_lexem_test/main.c tests/test_helpers.c letter_lexem_parser.c helpers.c types.c -o letter_lexem_test

run_tests: tests
	cd tests/number_lexem_test && ../../number_lexem_test
	cd tests/operator_lexem_test && ../../operator_lexem_test
	cd tests/letter_lexem_test && ../../letter_lexem_test