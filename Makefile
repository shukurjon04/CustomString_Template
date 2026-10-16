CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Asosiy dastur va test dasturi nomlari
TARGET = main
TEST_TARGET = test_runner

#1. Oddiy 'make' yozilganda main.c va StringM.c kompilyatsiya bo'ladi
all: $(TARGET)

$(TARGET): main.c StringM.c StringM.h
	$(CC) $(CFLAGS) main.c StringM.c -o $(TARGET)

#2. 'make test' yozilganda avtomatik testlar kompilyatsiya bo'lib, ishga tushadi
$(TEST_TARGET): test.c StringM.c StringM.h
	$(CC) $(CFLAGS) test.c StringM.c -o $(TEST_TARGET)


#3. 'make valgrind' yozilganda testlar xotira tekshiruvidan o'tkaziladi
valgrind: $(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(TEST_TARGET)

#4. 'make clean' yozilganda tayyor fayllar tozalanadi
clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test valgrind clean