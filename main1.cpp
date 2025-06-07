#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

// https://www.geeksforgeeks.org/taking-password-as-input-in-cpp/
// https://ryandeangraham.medium.com/masking-password-input-in-c-b007fa97b649

using namespace std;

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

// Enumerator
enum IN {

    // 13 is ASCII for carriage
    // return
    IN_BACK = 8,
    IN_LF = 10,
    IN_RET = 13

};

// Function that accepts the password
std::string takePasswdFromUser(char sp = '*')
{
    // Stores the password
    string passwd = "";
    char ch_ipt;

    // Until condition is true
    while (true) {
        ch_ipt = getch_();

        // if the ch_ipt
        if (ch_ipt == IN::IN_RET || ch_ipt == IN_LF) {
            cout << endl;
            return passwd;
        }
        else if (ch_ipt == IN::IN_BACK && passwd.length() != 0) {
            passwd.pop_back();

            // Cout statement is very
            // important as it will erase
            // previously printed character
            cout << "\b \b";

            continue;
        }

        // Without using this, program
        // will crash as \b can't be
        // print in beginning of line
        else if (ch_ipt == IN::IN_BACK && passwd.length() == 0) {
            continue;
        }

        passwd.push_back(ch_ipt);
        cout << sp;
    }
}

// Driver Code
int main()
{
    string input;
    cout << "user: ";
    input = takePasswdFromUser();
    cout << input << endl;
}
