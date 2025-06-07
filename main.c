#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

// https://medium.com/@fahnissa/authentication-system-in-c-programming-masking-password-2bcdb121ed1f
// https://www.geeksforgeeks.org/print-in-place-of-characters-for-reading-passwords-in-c/

int getch_(void)
{
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}

int main() {
  char storedPass[] = "123";
  char pass[50];
  int attempts = 3;

  while (attempts > 0) {
    // Read password with masking
    printf("Input password: ");
    int i = 0;
    char ch;
    while (true) {
      ch = getch_();
      if (ch == 13 || ch == 10) // Enter key ~ Line Feed
        break;
      if (ch == 8 && i > 0) { // Backspace key
        printf("\b \b");
        --i;
      } else {
        pass[i++] = ch;
        printf("*");
      }
    }
    pass[i] = '\0'; // Null-terminate the password
    printf("\n");

    // Check credentials
    if (strcmp(pass, storedPass) == 0) {
      printf("You are logged in!\n");
      return 0;
    } else {
      --attempts;
      printf("Login failed. %d attempts remaining.\n", attempts);
    }
  }

  printf("Too many failed attempts. Access denied.\n");
  return 0;
}
