#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

struct Player;
struct PlayerCoordinate;
void gmRenderMap();
void gmFindPlayer();
void gmPrintPlayerStats(Player player);
int Game();
void menuMain();

vector<vector<char>> gmLevel = {
{'#', '#', '#', '#', '#', '#', '#', '#'},
{'#', '.', '+', '.', '#', '.', '.', '#'},
{'#', '.', '.', '.', '#', '.', '.', '#'}, 
{'#', '.', '#', '#', '#', '.', '.', '#'}, 
{'#', '.', '.', '.', '.', '.', '.', '#'}, 
{'#', '.', '#', '#', '#', '.', '.', '#'}, 
{'#', '.', '.', '.', '#', '.', '.', '#'}, 
{'#', '#', '#', '#', '#', '#', '#', '#'} };

void gmRenderMap()
{
    for (int y = 0; y < gmLevel.size(); y++) {
        for (int x = 0; x < gmLevel[y].size(); x++) {
            cout << gmLevel[y][x] << ' ';
        }
        cout << endl;
    }
}
/*
struct Walls {
    int strength = 10;
};
*/
struct Player {
    char name[20] = "Влиидан";
    int heals = 5;
    string thoughts = "Что  ?";
    const static int inventorySize = 4;
    const static int equpedItemsSize = 2;
    string inventory[inventorySize] = { "Ничего" };
    string equpedItems[equpedItemsSize] = { "Ничего" };
    char gmSetterPlayerModel = '+';
};
Player P1;

struct PlayerCoordinate {
    int x;
    int y;
};
PlayerCoordinate P1Coords;

void gmFindPlayer()
{
    P1Coords.x = -1;
    P1Coords.y = -1;
    for (int y = 0; y < gmLevel.size(); y++) {
        for (int x = 0; x < gmLevel[y].size(); x++) {
            if (gmLevel[y][x] == '+') {
                P1Coords.x = x;
                P1Coords.y = y;
                return;
            }
        }
    }
}

void gmPrintPlayerStats(Player player)
{
    cout << "> Ваше имя - " << player.name << ".\n\n"
        << "> Ваши мысли - " << player.thoughts << "\n\n";
    switch (player.heals) {
    case 5:
        cout << "> Вашему здоровью ничего не угрожает.\n" << endl;
        break;
    case 4:
        cout << "!> Обнаружены небольшие повреждения эпителия.\n    Рекомендуется применить лечебные мази и/или бинты. \n" << endl;
        break;
    case 3:
        cout << "!> Обнаружены порезы средней глубины, стабильность организма и сознания под сомнением.\n"
            << "    Рекомендуется медицинская помощь с последующим наложением бинтов(при необходимости швов) и применения лекарственных препаратов.\n" << endl;
        break;
    case 2:
        cout << "!> ВНИМАНИЕ! Вашей жизни грозит опасность!\n   Обнаружены следы внутреннего и внешнего кровотечений, организм не стабилен!\n"
            << "    Требуется срочная медицинская помощь, а также применения обезболиващих, бинтов, шин, медицинских препаратов, крово-останавливающих препаратов!\n" << endl;
        break;
    case 1:
        cout << "!> КРИТИЧЕСКОЕ СОСТОЯНИЕ ОРГАНИЗМА!\n   Обнаружены следы сердечной недостаточности, закрытых переломов, кровотечений, помутнения рассудка, организм крайне не стабилен!\n"
            << "    Требуется немедленная медицинская помощь, высокие дозы: поддерживающих препаратов, обезболивающих, а также хирургическое вмешательство!\n" << endl;
        break;
    default:
        cout << "?!> Системе не удалось установить ваше состояние здоровья. \n" << endl;
        break;
    }
    cout << "> В вашем инвентаре находится:\n   ";
    for (int i = 0; i < sizeof(player.inventory) / sizeof(*player.inventory); i++) {
        cout << player.inventory[i];
    }
    cout << "\n\n";
    cout << "> На вас экиперовано:\n   ";
    for (int i = 0; i < sizeof(player.equpedItems) / sizeof(*player.equpedItems); i++) {
        cout << player.equpedItems[i];
    }
    cout << "\n\n";
}

int Game()
{
    char gmSetterBG = '.';
    signed int gmEvent = 0;
    bool gmPause = false;
    signed int gmTurnCounter = 0;

    gmFindPlayer();
    while (gmPause != true) {
        while (gmEvent == 0) {
            system("cls");
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Очистка input в cmd, работает странно.
            cout << "- Ход номер " << gmTurnCounter << "(\"w, a, s, d\" - для передвижения; 'h' - сканировать себя; 'b' - получить урон.)" << endl;
            gmRenderMap();
            char gmInput = _getch();
            if (gmInput == 'h') {
                gmPrintPlayerStats(P1); //Выводит описание игрока (struct P1).
                while (!_kbhit());
            }
            else if (gmInput == 'b') {
                cout << "~Каким-то образом вы получили раны~" << endl;
                P1.heals--;
                while (!_kbhit());
            }
            else if (gmInput == 'w' || gmInput == 'W') {
                if (gmLevel[P1Coords.y - 1][P1Coords.x] != '#') {
                    gmLevel[P1Coords.y][P1Coords.x] = gmSetterBG;
                    gmLevel[P1Coords.y - 1][P1Coords.x] = P1.gmSetterPlayerModel;
                    P1Coords.y--;
                }
            }
            else if (gmInput == 's' || gmInput == 'S') {
                if (gmLevel[P1Coords.y + 1][P1Coords.x] != '#') {
                    gmLevel[P1Coords.y][P1Coords.x] = gmSetterBG;
                    gmLevel[P1Coords.y + 1][P1Coords.x] = P1.gmSetterPlayerModel;
                    P1Coords.y++;
                }
            }
            else if (gmInput == 'a' || gmInput == 'A') {
                if (gmLevel[P1Coords.y][P1Coords.x - 1] != '#') {
                    gmLevel[P1Coords.y][P1Coords.x] = gmSetterBG;
                    gmLevel[P1Coords.y][P1Coords.x - 1] = P1.gmSetterPlayerModel;
                    P1Coords.x--;
                }
            }
            else if (gmInput == 'd' || gmInput == 'D') {
                if (gmLevel[P1Coords.y][P1Coords.x + 1] != '#') {
                    gmLevel[P1Coords.y][P1Coords.x] = gmSetterBG;
                    gmLevel[P1Coords.y][P1Coords.x + 1] = P1.gmSetterPlayerModel;
                    P1Coords.x++;
                }
            }
            else {
                continue; // Не делаем ход если нажатая кнопка не делает ничего и ждём input.
            }
            gmTurnCounter++;
            //bots func here
        }
        //Game event here; gmEvent for pause "
    }
    //menuMain here
    return 0;
}

// Меню, содержит в себе всё: центрирование текста, управление курсором и анимацию.
void menuMain()
{
    vector<string> menuArr = { "Начать", "Настройки", "Инфо", "Выход" };
    vector<int> menuArrLenghtOfDecor(menuArr.size());
    size_t menuArrCounter = 0;
    string menuIndent = "\n|\n";
    string menuDecorSimbols(7, '-');
    short int menuCursorPos = 0;
    int menuIntInput = 0;
    bool menuActionChecker = false;

    for (size_t j = 0; j < menuArr.size(); j++) {
        menuArrLenghtOfDecor[j] = menuArr[j].length();
    }

    while (true) {
        system("cls");
        for (size_t z = 0; z < menuDecorSimbols.length(); z++) {
            cout << "|----------Просто меню =S ('w'-Вверх; 's'-Вниз; 'e'-Принять)" << menuIndent;
            for (int x = 0; x < menuArr.size(); x++) {
                
                if (menuCursorPos == x) {
                    menuDecorSimbols[z] = '>';
                    if (z != 0) {
                        menuDecorSimbols[z - 1] = '-'; // Если это не первый кадр анимации то убираем стрелку оставшуюся с предыдушего кадра
                    }
                    if (menuActionChecker == true) { // Если была нажата клавиша 'e' то меняем положение правой стрелки
                        cout << "|" << menuDecorSimbols << menuArr[x] << "< " << menuIndent;
                    }
                    else {
                        cout << "|" << menuDecorSimbols << menuArr[x] << " <" << menuIndent;
                    }
                    menuDecorSimbols[z] = '-'; // Для того чтобы не выводить стрелку в коде ниже -> else {}
                }
                else {
                    cout << "|" << menuDecorSimbols << menuArr[x] << menuIndent;
                }
            }
            if (z + 1 != menuDecorSimbols.length()) {
                system("cls");
            }
            //Sleep(10);
        }
        cout << "\n\nВвод: ";

        if (menuActionChecker == true) {
            switch (menuCursorPos) {
            case 0:
                Game();
                break;
            case 1:
                cout << "\nНастроек пока нет, но вы держитесь.\n";
                while (!_kbhit());
                break;
            case 2:
                cout << "\nИнформации тоже пока нет.\n";
                while (!_kbhit());
                break;
            case 3:
                cout << "\n\nВы точно хотите выйти? (Y/N)\nВвод: ";
                while (true) {
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Очистка input в cmd, работает странно.
                    menuIntInput = _getch();
                    if (menuIntInput == 'Y' || menuIntInput == 'y') {
                        return;
                    }
                    else if (menuIntInput == 'N' || menuIntInput == 'n') {
                        break;
                    }
                }
                break;
            }
            menuActionChecker = false;
        }
        else {
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Очистка input в cmd, работает странно.
            menuIntInput = _getch();
            switch (menuIntInput) {
            case 'w':
            case 'W':
                menuCursorPos--;
                break;
            case 's':
            case 'S':
                menuCursorPos++;
                break;
            case 'e':
            case 'E':
                menuActionChecker = true;
                break;
            }
            // Модуль проверки Start.
            if (menuCursorPos < 0) {
                menuCursorPos = menuArr.size() - 1;
            }
            else if (menuCursorPos > menuArr.size() - 1) {
                menuCursorPos = 0;
            }
            // Модуль проверки End.
        }
    }
}

int main()
{
    SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода.
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода.

    menuMain();
    return 0;
}