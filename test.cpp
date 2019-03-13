#include <stdio.h>
#include <string.h>

int do_overflow(char* argv1)
{
	char error_msg[256];
	sprintf(error_msg, "test %s", argv1);
	printf(error_msg);
	return 0;
}

int main(int argc, char* argv[])
{
	do_overflow(argv[1]);
	return 0;
}

