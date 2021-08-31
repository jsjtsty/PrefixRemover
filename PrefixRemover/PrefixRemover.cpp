#include <iostream>
#include <string>
#include <clocale>

void ShowWelcome();
void SelectBoldMode();
int ShowMenu();
void ShowAbout();
void ShowPrefixRemover();

int main()
{
    std::setlocale(LC_ALL, "");
    ShowWelcome();
    SelectBoldMode();
    bool exitFlag = false;
    while (true) {
        int selection = ShowMenu();
        switch (selection) {
        case 1:
            ShowPrefixRemover();
            break;
        case 2:
            ShowAbout();
            break;
        case 3:
            exitFlag = true;
            break;
        }

        if (exitFlag) {
            break;
        }
    }
    return 0;
}
