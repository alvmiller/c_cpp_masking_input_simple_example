#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

// https://www.geeksforgeeks.org/taking-password-as-input-in-cpp/
// https://ryandeangraham.medium.com/masking-password-input-in-c-b007fa97b649

int password_prompt(std::string &password)
{
    struct termios tty;

    // Get current terminal settings
    if (tcgetattr(STDIN_FILENO, &tty) != 0)
        return -1;

    // Unset ECHO flag
    tty.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) != 0)
        return -1;

    // Prompt for password
    std::cout << "Password: ";
    std::cin >> password;

    // Set ECHO flag
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    return 0;
}

int main(void)
{
    std::string password = "";
    password_prompt(password);
    std::cout << std::endl;
    std::cout << password << std::endl;

    return 0;
}
