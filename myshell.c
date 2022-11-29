#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// read the parametres and fills the line array
char *readPrm()
{
	char *line = (char *)malloc(sizeof(char) * 1024); //  Buffer Allocation
	char read;
	int pos = 0;
	int bufferSize = 1024;
	char end = EOF;
	char newLine = '\n';
	char nullChar = '\0';
	if (!line)
	{ // Fail
		printf("\n Buffer Could Not Allocated.");
		exit(1);
	}
	while (1)
	{
		read = getchar();
		// if char equals newline or end of line,changes with nullchar
		if (read == end || read == newLine)
		{
			line[pos] = nullChar;
			return line;
		}
		else
		{
			line[pos] = read;
		}
		pos++;
		// If the buffer exceeded
		if (pos >= bufferSize)
		{
			bufferSize += 1024;
			line = realloc(line, sizeof(char) * bufferSize);
			if (!line)
			{ // Fail
				printf("\nBuffer Could Not Allocated");
				exit(1);
			}
		}
	}
}

// Input Function , copy values to buf
int input(char *str)
{
	char *buf;
	buf = readPrm();
	if (strlen(buf) != 0)
	{
		strcpy(str, buf);
		return 0;
	}
	else
	{
		return 1;
	}
}
// Clears the myshell
void clear()
{
	printf("\033[H\033[J");
}

// cat Function ,just read the input
void cat(char *str)
{
	printf("\ncat : %s", str);
}
// Command Execution by  name
void executeWithPrm(char **parsed)
{
	// Child process
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("\nFailed to fork");
		return;
	}
	else if (pid == 0)
	{
		/*
		char *argument_list[] = {"ls", "-l", NULL}; // NULL terminated array of char* strings
		// Ok! Will execute the command "ls -l"
		execvp("ls", argument_list);
		*/

		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nInvalid command..");
		}
		exit(0);
	}
	else
	{
		// waiting for child to abort
		wait(NULL);
		return;
	}
}

// print the menu ( commands)
void menu()
{
	printf("\n\n Write an command to use : "
		   "\n--exit = Exit from myshell"
		   "\n--bash = Opens bash terminal"
		   "\n--execx = Execute execx (execx -t 5 writef -f isim)"
		   "\n--cat = Prints arguments"
		   "\n--clear = Clear Screen"
		   "\n--ls = Lists files\n");
	return;
}

// Function to execute builtin commands
int execute(char **parsed)
{
	int NumberOfCommands = 8;
	int i;
	int index = 0;
	char *Commands[NumberOfCommands];

	Commands[0] = "exit";
	Commands[1] = "bash";
	Commands[2] = "execx";
	Commands[3] = "cat";
	Commands[4] = "clear";
	Commands[5] = "ls";
	Commands[6] = "tekrar";
	Commands[7] = "islem";

	for (i = 0; i < NumberOfCommands; i++)
	{
		if (strcmp(parsed[0], Commands[i]) == 0)
		{
			index = i + 1;
			break;
		}
	}

	switch (index)
	{
	case 1:
		exit(0);
	case 2:
		executeWithPrm(parsed);
		return 1;
	case 3:
		executeWithPrm(parsed);
		return 1;
	case 4:
		cat(parsed[1]);
		return 1;
	case 5:
		clear();
		return 1;
	case 6:
		executeWithPrm(parsed);
		return 1;
	case 7:
		
		return 1;
	case 8:
		
		return 1;
	default:
		printf("Invalid Command");
		break;
	}

	return 0;
}

void processString(char *str, char **parsed)
{

	int i;
	for (i = 0; i < 100; i++)
	{
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}

int main()
{
	char inputStr[1000], *Args[100];

	while (1)
	{

		menu();
		printf("\nmyshell>>");
		if (input(inputStr))
			continue;
		processString(inputStr, Args);
		execute(Args);
	}
	return 0;
}
