#include <iostream>
#include "Data.h"
#include <string>
#include <conio.h>

// FrontEnd.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <windows.h>
#include <conio.h>
#include <functional>

//using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
void changeColor(int color)
{
    SetConsoleTextAttribute(hOut, color);
}

void setCursor(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class Button
{
private:
    const static int BACKSPACE = 8;
    const static int ESC = 27;
private:

    int tabSize;
public:

    int xPos;
    int yPos;

    int xSize;
    int ySize;

    int color;

    std::string* textTab;

    std::function<void(void)> activateButton;

    //void (*activateButton)();

    void setButtonFunction(std::function<void(void)> function) { activateButton = function; }
    //void callThem() { _callback(); }
    void realTimeInput()
    {
        char ch;
        bool ifContinue = true;
        while (ifContinue)
        {
            ch = _getch();
            if (ch == BACKSPACE)
            {
                for (int i = 0; i < tabSize; i++)
                {
                    if (textTab[i].size() > 0 && i < tabSize - 1)
                    {
                        if (textTab[i + 1].size() == 0)
                        {
                            textTab[i].erase(textTab[i].end()-1);
                        }
                    }
                    else if (textTab[i].size() > 0)
                    {
                        textTab[i].erase(textTab[i].end());
                    }
                }
            }
            else if (ch == ESC)
            {
                ifContinue = false;
            }
            else if (ch == 14 || ch == 15)
            {
            }
            else
            {
                for (int i = 0; i < xSize; i++)
                {
                    if (textTab[i].size() < xSize)
                    {
                        textTab[i] += ch;
                        i = xSize;
                    }
                }
            }
            viewButton();
        }
    }

    static void nothing()
    {}

public:

    Button(int xPosB, int yPosB, int xSizeB, int ySizeB, int colorB)
    {
        xPos = xPosB;
        yPos = yPosB;
        xSize = xSizeB;
        ySize = ySizeB;
        color = colorB % 256;
        tabSize = 0;
        textTab = new std::string[0];
        activateButton = nothing;
    }

    Button()
    {
        xPos = 0;
        yPos = 0;
        xSize = 10;
        ySize = 4;
        color = 74;
        tabSize = 0;
        textTab = new std::string[0];
        activateButton = nothing;
    }

    void addText(std::string text)
    {
        std::string* temp = new std::string[tabSize + 1];;
        std::string* oldTab = textTab;

        for (int i = 0; i < tabSize; i++)
        {
            temp[i] = textTab[i];
        }

        temp[tabSize] = text;

        textTab = temp;
        delete[] oldTab;

        tabSize++;
    }

    std::string returnTabText(int arrayNum)
    {
        return textTab[arrayNum];
    }

    void editTabText(int arrayNum, std::string text)
    {
        textTab[arrayNum] = text;
    }

    void viewButton()
    {
        changeColor(color);
        for (int i = 0; i < ySize; i++)
        {
            setCursor(xPos, yPos + i);
            for (int j = 0; j < xSize; j++)
            {

                if (i < tabSize && (int)textTab[i][j] != 0)
                {
                    std::cout << textTab[i][j];
                }
                else
                {
                    for (int k = j; k < xSize; k++)
                    {
                        std::cout << " ";
                    }
                    j = xSize;
                }
            }
        }
        changeColor(7);
        /**std::cout<<xPos<<" =xPos|";
        std::cout<<yPos<<" =yPos|";
        std::cout<<xSize<<" =xSize|";
        std::cout<<ySize<<" =ySize|";
        std::cout<<color<<" =color|";*/
    }

    bool changeButtonColor(int kolor)
    {
        color = kolor % 256;
        return true;
    }
};

class Interface//Button Agregation
{
private:
    int cursorPosX;
    int cursorPosY;
    int currentButton;
    int tabSize;

public:
    Button* buttonsTab;

    static bool ifBigger(int a, int b)
    {
        if (a > b)
            return true;
        else
            return false;
    }

    static bool ifSmaller(int a, int b)
    {
        if (a < b)
            return true;
        else
            return false;
    }

    void lookForClosest(bool (*statement)(int, int), bool inAxisX)
    {
        int closeX;
        int closeY;
        int button = -1;//-1 tells if button was found
        if (inAxisX)
        {
            for (int i = 0; i < tabSize; i++)
            {
                if ((*statement)(cursorPosX, buttonsTab[i].xPos))/**sprawdza kierunek**/
                {
                    if (button == -1) /**sprawdza znalezienie buttona**/
                    {
                        closeX = buttonsTab[i].xPos;
                        closeY = buttonsTab[i].yPos;
                        button = i;
                    }
                    else
                    {
                        if (((cursorPosX - buttonsTab[i].xPos) * (cursorPosX - buttonsTab[i].xPos) + (cursorPosY - buttonsTab[i].yPos) * (cursorPosY - buttonsTab[i].yPos))
                            < ((cursorPosX - closeX) * (cursorPosX - closeX) + (cursorPosY - closeY) * (cursorPosY - closeY)))/**sprawdza najblizszy button**/
                        {
                            closeX = buttonsTab[i].xPos;
                            closeY = buttonsTab[i].yPos;
                            button = i;
                        }
                    }
                }
            }
            if (button >= 0)
            {
                if ((*statement)(cursorPosX, closeX))
                {
                    cursorPosX = closeX;
                    cursorPosY = closeY;
                    buttonsTab[currentButton].changeButtonColor(buttonsTab[currentButton].color - buttonsTab[currentButton].color % 16 + (buttonsTab[currentButton].color + 8) % 16 + 128);//shows which button is now selected
                    buttonsTab[currentButton].viewButton();
                    buttonsTab[button].changeButtonColor(buttonsTab[button].color - buttonsTab[button].color % 16 + (buttonsTab[button].color + 8) % 16 + 128);//shows which button is now selected
                    buttonsTab[button].viewButton();
                    currentButton = button;
                }
            }
        }
        else
        {
            for (int i = 0; i < tabSize; i++)
            {
                if ((*statement)(cursorPosY, buttonsTab[i].yPos))/**sprawdza kierunek**/
                {
                    if (button == -1) /**sprawdza znalezienie buttona**/
                    {
                        closeX = buttonsTab[i].xPos;
                        closeY = buttonsTab[i].yPos;
                        button = i;
                    }
                    else
                    {
                        if (((cursorPosX - buttonsTab[i].xPos) * (cursorPosX - buttonsTab[i].xPos) + (cursorPosY - buttonsTab[i].yPos) * (cursorPosY - buttonsTab[i].yPos))
                            < ((cursorPosX - closeX) * (cursorPosX - closeX) + (cursorPosY - closeY) * (cursorPosY - closeY)))/**sprawdza najblizszy button**/
                        {
                            closeX = buttonsTab[i].xPos;
                            closeY = buttonsTab[i].yPos;
                            button = i;
                        }
                    }
                }
            }
            if (button >= 0)
            {
                if ((*statement)(cursorPosY, closeY))
                {
                    cursorPosX = closeX;
                    cursorPosY = closeY;
                    buttonsTab[currentButton].changeButtonColor(buttonsTab[currentButton].color - buttonsTab[currentButton].color % 16 + (buttonsTab[currentButton].color + 8) % 16 + 128);//shows which button is now selected
                    buttonsTab[currentButton].viewButton();
                    buttonsTab[button].changeButtonColor(buttonsTab[button].color - buttonsTab[button].color % 16 + (buttonsTab[button].color + 8) % 16 + 128);//shows which button is now selected
                    buttonsTab[button].viewButton();
                    currentButton = button;
                }
            }
        }
    }

public:
    Interface()
    {
        tabSize = 0;
        cursorPosX = 0;
        cursorPosY = 0;
        currentButton = 0;
        buttonsTab = new Button[0];
    }

    void moveCursor(char ch)
    {
        switch (ch)
        {
        case 'w':case 'W':
        {
            lookForClosest(ifBigger, false);
        }
        break;

        case 's':case 'S':
        {
            lookForClosest(ifSmaller, false);
        }
        break;

        case 'a':case 'A':
        {
            lookForClosest(ifBigger, true);
        }
        break;

        case 'd':case 'D':
        {
            lookForClosest(ifSmaller, true);
        }
        break;

        case ' ':
        {
            buttonsTab[currentButton].activateButton();
        }
        break;
        }
    }

    void addButton(Button* button)
    {
        Button* temp;
        Button* oldTab = buttonsTab;
        temp = new Button[tabSize + 1];

        if (tabSize == 0)
        {
            currentButton = 0;
            cursorPosX = (*button).xPos;
            cursorPosY = (*button).yPos;
            (*button).changeButtonColor((*button).color - (*button).color % 16 + ((*button).color + 8) % 16 + 128);//highlights current button
        }

        for (int i = 0; i < tabSize; i++)
        {
            temp[i] = buttonsTab[i];
        }

        temp[tabSize] = *button;

        buttonsTab = temp;
        delete[] oldTab;

        tabSize++;
    }

    void removeButton(int tabPos)
    {
        if (tabSize > 0)
        {
            Button* temp;
            Button* oldTab = buttonsTab;
            temp = new Button[tabSize - 1];

            for (int i = 0; i < tabSize - 1; i++)
            {
                if (i >= tabPos)
                {
                    temp[i] = buttonsTab[i + 1];
                }
                else
                {
                    temp[i] = buttonsTab[i];
                }
            }
            buttonsTab = temp;
            delete[] oldTab;

            tabSize--;
        }
    }

    void viewInterface()
    {
        for (int i = 0; i < tabSize; i++)
        {
            buttonsTab[i].viewButton();
        }
    }

    int getCurrentButtonInt()
    {
        return currentButton;
    }

};

class MenuA
{
private:

    Interface Wybor;
    Interface Poczta;
    Interface Ramka;

public:
    void menuFunction()
    {
        system("cls");
        Wybor.viewInterface();

        char ch;

        while (true)
        {
            ch = _getch();
            Wybor.moveCursor(ch);
        }
    };
    void pocztaFunction()
    {
        system("cls");
        Poczta.viewInterface();
        Ramka.viewInterface();

        char ch;

        while (true)
        {
            ch = _getch();
            Poczta.moveCursor(ch);
        }

    }
    MenuA()
    {
        Ramka.addButton(new Button(9, 1, 111, 3, 50));
        Ramka.addButton(new Button(0, 0, 120, 1, 30));
        Ramka.addButton(new Button(0, 4, 120, 1, 30));
        Ramka.addButton(new Button(0, 8, 120, 1, 30));
        Ramka.addButton(new Button(0, 12, 120, 1, 30));
        Ramka.addButton(new Button(0, 16, 120, 1, 30));
        Ramka.addButton(new Button(0, 20, 120, 1, 30));
        Ramka.addButton(new Button(0, 24, 120, 1, 30));
        Ramka.addButton(new Button(0, 28, 120, 1, 30));
        Ramka.addButton(new Button(0, 0, 1, 29, 30));
        Ramka.addButton(new Button(8, 0, 1, 29, 30));
        Ramka.addButton(new Button(1, 5, 7, 3, 50));
        Ramka.addButton(new Button(1, 9, 7, 3, 50));
        Ramka.addButton(new Button(1, 13, 7, 3, 50));
        Ramka.addButton(new Button(1, 17, 7, 3, 50));
        Ramka.addButton(new Button(1, 21, 7, 3, 50));
        Ramka.addButton(new Button(1, 25, 7, 3, 50));
        //Ramka.viewInterface();

        Poczta.addButton(new Button(1, 1, 7, 3, 40));
        Poczta.buttonsTab[0].addText("");
        Poczta.buttonsTab[0].addText("Wstecz");
        Poczta.buttonsTab[0].setButtonFunction([&]() {menuFunction(); });//!!!!!!!

        Poczta.addButton(new Button(9, 5, 111, 3, 40));
        Poczta.addButton(new Button(9, 9, 111, 3, 40));
        Poczta.addButton(new Button(9, 13, 111, 3, 40));
        Poczta.addButton(new Button(9, 17, 111, 3, 40));
        Poczta.addButton(new Button(9, 21, 111, 3, 40));
        Poczta.addButton(new Button(9, 25, 111, 3, 40));
        //Poczta.viewInterface();

        Wybor.addButton(new Button(5, 10, 8, 3, 40));
        Wybor.addButton(new Button(13, 10, 8, 3, 40));
        Wybor.buttonsTab[0].addText("Poczta");
        Wybor.buttonsTab[0].addText("Poczta");
        Wybor.buttonsTab[0].addText("Poczta");
        Wybor.buttonsTab[0].setButtonFunction([&]() {pocztaFunction(); });//!!!!!!!
        Wybor.viewInterface();
    }
};

class Menu;

class RegisterSystem
{
    friend Menu;

private:

    User* currentUser = nullptr;
    int which_spec=0;
    int which_course = 0;
    int which_group = 0;
    int which_lecture = 0;

public:

    RegisterSystem(){}

    void viewRegisterSystem()
    {
        system("cls");
        Interface background;
        Interface optList;


        background.addButton(new Button(0, 0, 30 + currentUser->login.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==WITAJ W SYSTEMIE ZAPISOW " + currentUser->login + "==");
        background.buttonsTab[0].addText("");

        if (!currentUser->isRegistered()) {
            optList.addButton(new Button(0, 3, 28, 3, 62));
            optList.buttonsTab[0].addText("");
            optList.buttonsTab[0].addText("Wybierz kierunek");
            optList.buttonsTab[0].setButtonFunction([&]() { selectSpec(); });

            while (currentUser->spec==nullptr)
            {
                system("cls");
                background.viewInterface();
                optList.viewInterface();

                char ch = _getch();

                optList.moveCursor(ch);

                which_spec = optList.getCurrentButtonInt();

                if (ch == 27)
                {
                    break;
                }
            }
        }
        else
        {
            optList.addButton(new Button(0, 3, 28, 3, 62));
            optList.buttonsTab[0].addText("");
            optList.buttonsTab[0].addText("Zapisy na zajecia");
            optList.buttonsTab[0].setButtonFunction([&]() {selectCourse(); });

            optList.addButton(new Button(0, 6, 28, 3, 62));
            optList.buttonsTab[1].addText("");
            optList.buttonsTab[1].addText("Wypisz sie z kierunku " + currentUser->spec->name);
            optList.buttonsTab[1].setButtonFunction([&]() {leaveSpec(); });

            while (currentUser->spec != nullptr)
            {
                system("cls");
                background.viewInterface();
                optList.viewInterface();

                char ch = _getch();

                optList.getCurrentButtonInt();

                optList.moveCursor(ch);

                if (ch == 27)
                {
                    break;
                }
            }
        }

     }

    void selectSpec()
    {
        system("cls");
        Interface background;
        Interface optList;


        background.addButton(new Button(0, 0, 30 + currentUser->login.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==KIERUNKI DOSTEPNE DLA " + currentUser->login + "==");
        background.buttonsTab[0].addText("");

        for (int i=0;i<RegisterData::specs.size();i++)
        {
            optList.addButton(new Button(0, 3 + (i * 3), 20, 3, 62));
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].addText("Zapisz na " + RegisterData::specs[i]->name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {joiningSpec(); });
        }



        while (currentUser->spec==nullptr)
        {
            system("cls");
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            which_spec = optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                break;
            }
        }

    }

    void joiningSpec()
    {
        system("cls");
        Interface background;
        Interface optList;


        background.addButton(new Button(0, 0, 40 + RegisterData::specs[which_spec]->name.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==CZY NAPEWNO ZAPISAC NA KIERUNEK " + RegisterData::specs[which_spec]->name + "?==");
        background.buttonsTab[0].addText("");

        optList.addButton(new Button(0, 3, 5, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText(" TAK");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {currentUser->joinSpec(RegisterData::specs[which_spec]); });

        optList.addButton(new Button(6, 3, 5, 3, 62));
        optList.buttonsTab[1].addText("");
        optList.buttonsTab[1].addText(" NIE");
        optList.buttonsTab[1].addText("");
        optList.buttonsTab[1].setButtonFunction([&]() {});

        while (true)
        {
            system("cls");
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();
            
            optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                break;
            }
            if (ch == ' ')
            {
                break;
            }
        }


    }

    void leaveSpec()
    {
        system("cls");
        Interface background;
        Interface optList;


        background.addButton(new Button(0, 0, 40 + RegisterData::specs[which_spec]->name.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==CZY NAPEWNO WYPISAC Z KIERUNKU " + RegisterData::specs[which_spec]->name + "?==");
        background.buttonsTab[0].addText("");

        optList.addButton(new Button(0, 3, 5, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText(" TAK");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {currentUser->leaveSpec(); });

        optList.addButton(new Button(6, 3, 5, 3, 62));
        optList.buttonsTab[1].addText("");
        optList.buttonsTab[1].addText(" NIE");
        optList.buttonsTab[1].addText("");
        optList.buttonsTab[1].setButtonFunction([&]() {});

        while (true)
        {
            system("cls");
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                break;
            }
            if (ch == ' ')
            {
                break;
            }
        }



    }

    void selectCourse()
    {
        system("cls");
        Interface background;
        Interface optList;


        background.addButton(new Button(0, 0, 23 + currentUser->spec->name.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==KURSY DOSTEPNE DLA " + currentUser->spec->name + "==");
        background.buttonsTab[0].addText("");

        for (int i = 0; i < currentUser->spec->courses.size(); i++)
        {
            optList.addButton(new Button(0, 3 + (i * 3), 25, 3, 62));
            optList.buttonsTab[i].addText("");
            std::string name = currentUser->spec->courses[i]->name;

            if(name.size()>25)
              std::string name = name.substr(0, 21) + "...";

            optList.buttonsTab[i].addText(name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {selectGroup(); });
        }



        while (true)
        {
            system("cls");
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            which_course=optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                break;
            }
        }


    }

    void selectGroup()
    {
        system("cls");
        Interface background;
        Interface optList;


        background.addButton(new Button(0, 0, 16 + currentUser->spec->courses[which_course]->name.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==GRUPY KURSU " + currentUser->spec->courses[which_course]->name + "==");
        background.buttonsTab[0].addText("");

        for (int i = 0; i < currentUser->spec->courses[which_course]->groups.size(); i++)
        {
            optList.addButton(new Button(0, 3+(i*3), 25, 3, 62));
            optList.buttonsTab[i].addText("");
            std::string name = currentUser->spec->courses[which_course]->groups[i]->name;

            if (name.size() > 25)
                std::string name = name.substr(0, 21) + "...";

            optList.buttonsTab[i].addText(name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {selectLecture(); });
        }



        while (true)
        {
            system("cls");
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            which_group = optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                break;
            }
        }
    }

    void selectLecture()
    {
        system("cls");
        Interface background;
        Interface optList;


        background.addButton(new Button(0, 0, 30 + currentUser->spec->courses[which_course]->groups[which_group]->name.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==DOSTEPNE ZAJECIA W GRUPIE " + currentUser->spec->courses[which_course]->groups[which_group]->name + "==");
        background.buttonsTab[0].addText("");

        for (int i = 0; i < currentUser->spec->courses[which_course]->groups[which_group]->lectures.size(); i++)
        {
            optList.addButton(new Button(0, 3 + (i * 3), 25, 3, 62));
            optList.buttonsTab[i].addText("");
            std::string name = currentUser->spec->courses[which_course]->groups[which_group]->lectures[i]->name;

            if (name.size() > 25)
            {
                std::string temp = name.substr(0, 22) + "...";
                    name = temp;
            }

            optList.buttonsTab[i].addText(name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {joinLecture(); });
        }

        for (int i = 0; i < currentUser->spec->courses[which_course]->groups[which_group]->lectures.size(); i++)
        {
            background.addButton(new Button(26, 3 + (i * 3), 10, 3, 62));
            background.buttonsTab[1 + i].addText("");
            background.buttonsTab[1 + i].addText("");
            background.buttonsTab[1 + i].addText("");
        }



        while (true)
        {
            system("cls");

            for (int i = 0; i < currentUser->spec->courses[which_course]->groups[which_group]->lectures.size(); i++)
            {
                if(currentUser->isRegistered(currentUser->spec->courses[which_course]->groups[which_group]->lectures[i]))
                  background.buttonsTab[1 + i].editTabText(1,">ZAPISANY<");
                else
                  background.buttonsTab[1 + i].editTabText(1, "");
            }

            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            which_lecture = optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                break;
            }
        }


    }

    void joinLecture()
    {
        Interface prompt;

        prompt.addButton(new Button(0, 0, 35 + currentUser->spec->courses[which_course]->groups[which_group]->lectures.size(), 3, 62));
        prompt.buttonsTab[0].addText("");
        prompt.buttonsTab[0].addText("==JESTES JUZ ZAPISANY W TEJ GRUPIE!==");


        if (currentUser->isRegistered(currentUser->spec->courses[which_course]->groups[which_group]->lectures[which_lecture]))
        {
            currentUser->leaveLecture(currentUser->spec->courses[which_course]->groups[which_group]->lectures[which_lecture]);
        }
        else if (!currentUser->spec->courses[which_course]->groups[which_group]->userRegisteredInGroup(currentUser))
        {
            currentUser->joinLecture(currentUser->spec->courses[which_course]->groups[which_group]->lectures[which_lecture]);
        }
        else
        {
            prompt.viewInterface();
            _getch();
        }

    }
};
class ChatSystem
{
    //////////////////////////////////////////////
    //                                          //
    //                FINISHED                  //
    //                                          //
    //////////////////////////////////////////////

    friend Menu;

private:

    User* currentUser = nullptr;
    int selectedChatIt = 0;

public:

    ChatSystem() {}

    void viewChat()
    {
        system("cls");
        Interface background;
        Interface chat;

        background.addButton(new Button(0, 0, 30+currentUser->login.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==LISTA CHATOW UZYTKOWNIKA " + currentUser->login + "==");

        for (int i = 0; i < currentUser->userLectures.size(); i++)
        {
            chat.addButton(new Button(1, 1+2*(i+1), 30, 2, 62));
            chat.buttonsTab[i].addText(currentUser->userLectures[i]->name);
            chat.buttonsTab[i].setButtonFunction([&]() {showChatWindow(); });
        }

        while (true)
        {
            system("cls");
            background.viewInterface();
            chat.viewInterface();

            char ch = _getch();

            selectedChatIt = chat.getCurrentButtonInt();

            chat.moveCursor(ch);

            if (ch == 27)
            {
                break;
            }
        }

    }

    void showChatWindow()
    {
        system("cls");
        Interface chatWindowBckgrnd;
        Interface chatWindowInteractable;

        chatWindowBckgrnd.addButton(new Button(0, 0, 30 + currentUser->userLectures[selectedChatIt]->lectureChat.chatName.size(), 3, 62));

        chatWindowBckgrnd.buttonsTab[0].addText("");
        chatWindowBckgrnd.buttonsTab[0].addText("==CHAT ZAJEC " + currentUser->userLectures[selectedChatIt]->name + "==");

        chatWindowBckgrnd.addButton(new Button(0, 3, 40, 16, 62));
        chatWindowBckgrnd.addButton(new Button(0, 19, 40, 1, 60));
        chatWindowBckgrnd.buttonsTab[2].addText("=Tu wpisz wiadomosc====================");
        for (int i = 0; i < 16; i++)
        {
            chatWindowBckgrnd.buttonsTab[1].addText("");
        }



        chatWindowInteractable.addButton(new Button(0, 20, 40, 3, 62));
        chatWindowInteractable.buttonsTab[0].addText("");
        chatWindowInteractable.buttonsTab[0].addText("");
        chatWindowInteractable.buttonsTab[0].addText("");
        chatWindowInteractable.buttonsTab[0].setButtonFunction([&]() {chatWindowInteractable.buttonsTab[0].realTimeInput(); });



        while (true)
        {
            //int i;
            //if (currentUser->userLectures[selectedChatIt]->lectureChat.chatArchive.size() < 8)
            //    i = currentUser->userLectures[selectedChatIt]->lectureChat.chatArchive.size();
            //else i = 8;
            int curChatSize = currentUser->userLectures[selectedChatIt]->lectureChat.chatArchive.size()-1;

            //for (int j = 0; j < 16; j++)
            //{
            //    chatWindowBckgrnd.buttonsTab[1].textTab[j] = "";
            //}

            int which_line = 15;
            for (int i= 0; i < curChatSize; i++)
            {
                std::string chatm = currentUser->userLectures[selectedChatIt]->lectureChat.chatArchive[curChatSize - i];
                std::string prefix = chatm.substr(0, chatm.find(':') + 14);
                std::string msg = chatm.substr(chatm.find(':') + 15, chatm.npos);


                if (which_line > -1)
                {

                    if (msg.size() > 40)
                    {
                        std::string first = msg.substr(0, 40);
                        std::string second = msg.substr(40,msg.npos);

                        if (second.size() > 40)
                        {
                            std::string third = msg.substr(80, msg.npos);
                            chatWindowBckgrnd.buttonsTab[1].editTabText(which_line--, third);
                        }
                        chatWindowBckgrnd.buttonsTab[1].editTabText(which_line--, second);
                        chatWindowBckgrnd.buttonsTab[1].editTabText(which_line--, first);
                    }
                    else if (msg.size())
                        chatWindowBckgrnd.buttonsTab[1].editTabText(which_line--, msg);

                    if(which_line>-1)
                        chatWindowBckgrnd.buttonsTab[1].editTabText(which_line--, prefix);
                }
            }

            system("cls");
            chatWindowBckgrnd.viewInterface();
            chatWindowInteractable.viewInterface();

            char ch = _getch();

            chatWindowInteractable.moveCursor(ch);

            std::string message = chatWindowInteractable.buttonsTab[0].textTab[0] + chatWindowInteractable.buttonsTab[0].textTab[1] + chatWindowInteractable.buttonsTab[0].textTab[2];

            switch (ch)
            {
            case 13:
            {
                if (message.size())
                {
                    currentUser->userLectures[selectedChatIt]->lectureChat.sendMessage(currentUser,message);
                    chatWindowInteractable.buttonsTab[0].editTabText(0,"");
                    chatWindowInteractable.buttonsTab[0].editTabText(0,"");
                    chatWindowInteractable.buttonsTab[0].editTabText(0,"");
                }
            }
            break;
            }
            if (ch == 27)
            {
                break;
            }
        }

    }

};
class MailSystem
{
    friend Menu;
private:
    User* currentUser;
    MailData* mailData;
    RegisterData* regData;

};
class CallendarSystem
{
    friend Menu;
private:
    User* currentUser;

public:
    CallendarSystem()
    {
    }
    void viewCallendar()
    {
        system("cls");
        Interface callendar;
        
        for (int y = 0; y < 7; y++)
        {
            for (int x = 0; x < 7; x++)
            {
                callendar.addButton(new Button(x*4,y*3,4,3,62));
                callendar.buttonsTab[x + y * 7].addText("");
                callendar.buttonsTab[x + y * 7].addText("xd");
            }
        }//potrzebna pomoc

        char ch;

        while (true)
        {
            system("cls");
            callendar.viewInterface();

            ch = _getch();

            callendar.moveCursor(ch);

            switch (ch)
            {
            case ' '://do zrobienia//Wybieranie eventu
                {
                    callendar.getCurrentButtonInt();
                    //eventList(new Event("xd", *(new Date), "opis");
                    eventList();//(new Event("xd", *(new Date), "opis"),1);//potrzebna pomoc
                }
                break;
            }
            if (ch == 27)
            {
                break;
            }
        }

    }
    void eventList()//(Event* eventTab,int tabSize)//potrzebna pomoc
    {
        system("cls");
        //callendar.getCurrentButtonInt();
        Interface list;

        int listPage = 0;

        for (int i = 0; i < 10; i++)//Button(int xPosB, int yPosB, int xSizeB, int ySizeB, int colorB)
        {
            list.addButton(new Button(4, i * 2 + 2, 30, 2, 48));
            list.buttonsTab[i].addText("");
            list.buttonsTab[i].addText("Event");

        }


        list.addButton(new Button(4, 22, 15, 3, 32));//prev Events
        list.buttonsTab[10].addText("");
        list.buttonsTab[10].addText("prev");


        list.addButton(new Button(4, 25, 15, 3, 32));//next Events
        list.buttonsTab[11].addText("");
        list.buttonsTab[11].addText("next");

        list.addButton(new Button(4, 28, 15, 3, 32));//add Event
        list.buttonsTab[12].addText("");
        list.buttonsTab[12].addText(" + Ingridient");

        char ch;
        while (true)
        {
            system("cls");
            list.viewInterface();
            ch = _getch();

            list.moveCursor(ch);

            switch (ch)
            {
            case ' '://do zrobienia//Wybieranie eventu
            {
                list.getCurrentButtonInt();
                viewEvent();
            }
            break;
            }
            if(ch==27)
            {
                break;
            }
        }

        //refresh();

    }

    void eventPrev()
    {

    }
    void viewEvent()
    {
        system("cls");
        Interface list;

            list.addButton(new Button(4, 0 + 2, 30, 2, 48));
            list.buttonsTab[0].addText("");
            list.buttonsTab[0].addText("tytul");

            list.addButton(new Button(4, 1 * 2 + 2, 30, 2, 48));
            list.buttonsTab[1].addText("");
            list.buttonsTab[1].addText("data");

            list.addButton(new Button(4, 2 * 2 + 2, 30, 10, 48));
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("tresc");

            list.addButton(new Button(4, 2 * 2 + 2+10, 30, 3, 48));
            list.buttonsTab[3].addText("");
            list.buttonsTab[3].addText("usun");

            char ch;

            while (true)
            {
                system("cls");
                list.viewInterface();
                ch = _getch();

                list.moveCursor(ch);

                if (ch==27)
                {
                        break;
                }
            }

    }
    void addEvent()
    {

    }
    void deleteEvent()
    {

    }


};
class NotificationSystem
{
    friend Menu;

};
/*
class IngridientData
{
private:
    Interface list;
    int listPage;
    Data* data;

public:
    IngridientData()
    {
        listPage = 0;
    }

    IngridientData(Data* dataVar)
    {
        listPage = 0;
        data = dataVar;

        for (int i = 0; i < 10; i++)//Button(int xPosB, int yPosB, int xSizeB, int ySizeB, int colorB)
        {
            list.addButton(new Button(4, i * 2 + 2, 30, 2, 48));
            list.buttonsTab[i].addText("");
            list.buttonsTab[i].addText("");

        }


        list.addButton(new Button(4, 22, 15, 3, 32));//prev Ingridients
        list.buttonsTab[10].addText("");
        list.buttonsTab[10].addText("prev");
        list.buttonsTab[10].setButtonFunction([&]() {prev(); });


        list.addButton(new Button(19, 22, 15, 3, 32));//next Ingridients
        list.buttonsTab[11].addText("");
        list.buttonsTab[11].addText("next");
        list.buttonsTab[11].setButtonFunction([&]() {next(); });

        list.addButton(new Button(4, 25, 15, 3, 32));//add Ingridients
        list.buttonsTab[12].addText("");
        list.buttonsTab[12].addText(" + Ingridient");
        list.buttonsTab[12].setButtonFunction([&]() {addIngridient(); });

        list.addButton(new Button(19, 25, 15, 3, 32));//delete Ingridients
        list.buttonsTab[13].addText("");
        list.buttonsTab[13].addText(" - Ingridient");
        list.buttonsTab[13].setButtonFunction([&]() {deleteIngridient(); });

        refresh();
    }

    void loop()
    {
        viewList();
        char ch;
        while (true)
        {
            ch = _getch();
            list.moveCursor(ch);
            if (ch == 'b')
                break;
        }
    }

    void viewList()
    {
        list.viewInterface();
        std::cout << listPage;
    }

    void next()
    {
        listPage++;

        refresh();
    }

    void prev()
    {
        if (listPage > 0)
        {
            listPage--;

            refresh();
        }
    }

    void refresh()
    {
        int howMany = 0;

        if (data->tabSize[0] >= listPage * 10 + 10)
        {
            howMany = 10;
        }
        else
        {
            howMany = data->tabSize[0] - listPage * 10;
        }

        for (int i = 0; i < howMany; i++)//Button(int xPosB, int yPosB, int xSizeB, int ySizeB, int colorB)
        {

            list.buttonsTab[i].editTabText(1, data->ingridientTab[listPage * 10 + i]->name);

        }

        for (int i = howMany; i < 10; i++)//Button(int xPosB, int yPosB, int xSizeB, int ySizeB, int colorB)
        {
            list.buttonsTab[i].editTabText(1, " ");

        }

    }

    void addIngridient()
    {
        std::string name;
        int kcal;
        system("cls");

        std::cout << "Write down Ingridient Name:\n";
        std::cin >> name;
        std::cout << "Write down how many colaries it has:\n";
        std::cin >> kcal;
        data->addIngridient(new Ingridient(name, kcal));

        refresh();

        system("cls");

        viewList();

    }

    void deleteIngridient()
    {
        int which;
        system("cls");

        std::cout << "Which ingridient would you like to delete?:\n";
        std::cin >> which;
        data->deleteIngridient(which);

        refresh();

        system("cls");

        viewList();
    }
};
*/
class Menu
{
private:
    User* currentUser;

    ChatSystem* chat;
    RegisterSystem* registerSys;
    MailSystem* mail;
    CallendarSystem* callendar;
    NotificationSystem* notifications;
    std::string login;
    std::string password;
public:
    Menu()
    {
        //currentUser = new User;
        chat = new ChatSystem;
        registerSys = new RegisterSystem;
        mail = new MailSystem;
        callendar = new CallendarSystem;
        notifications = new NotificationSystem;
    }
    void loginScreen()
    {
        Interface loginScr;
        //Button(xPos,yPos,xSize,ySize,color)
        loginScr.addButton(new Button(7, 3, 23, 3, 62));//login
        loginScr.buttonsTab[0].addText("");
        loginScr.buttonsTab[0].addText("");
        loginScr.buttonsTab[0].addText("");
        loginScr.buttonsTab[0].setButtonFunction([&]() {loginScr.buttonsTab[0].realTimeInput(); });

        loginScr.addButton(new Button(7, 6, 23, 3, 62));//haslo
        loginScr.buttonsTab[1].addText("");
        loginScr.buttonsTab[1].addText("");
        loginScr.buttonsTab[1].addText("");
        loginScr.buttonsTab[1].setButtonFunction([&]() {loginScr.buttonsTab[1].realTimeInput(); });

        loginScr.addButton(new Button(0, 9, 30, 3, 62));//zaloguj
        loginScr.buttonsTab[2].addText("");
        loginScr.buttonsTab[2].addText("ZALOGUJ");
        loginScr.buttonsTab[2].setButtonFunction([&]() {drawMenu(); });

        Interface background;

        background.addButton(new Button(0, 0, 30, 3, 62));

        background.addButton(new Button(0, 3, 7, 3, 62));
        background.buttonsTab[1].addText("");
        background.buttonsTab[1].addText("Login:");

        background.addButton(new Button(0, 6, 7, 3, 62));
        background.buttonsTab[2].addText("");
        background.buttonsTab[2].addText("Haslo:");

        /*background.addButton(new Button(0, 0, 20, 3, 62));
        background.buttonsTab[3].addText("");
        background.buttonsTab[3].addText("Niepoprawne Dane!");

        background.addButton(new Button(0, 0, 20, 3, 62));
        background.buttonsTab[4].addText("");
        background.buttonsTab[4].addText("Zalogowano:");*/

        char ch;

        while (true)
        {
            loginScr.viewInterface();
            background.viewInterface();

            login = loginScr.buttonsTab[0].textTab[0] + loginScr.buttonsTab[0].textTab[1] + loginScr.buttonsTab[0].textTab[2];
            password = loginScr.buttonsTab[1].textTab[0] + loginScr.buttonsTab[1].textTab[1] + loginScr.buttonsTab[1].textTab[2];


            ch = _getch();
            loginScr.moveCursor(ch);
        }

    }
    void drawMenu()
    {
        system("cls");
        if (UsersData::verifyUser(login, password) != nullptr)
        {
            currentUser = UsersData::verifyUser(login, password);
            Interface menu;

            menu.addButton(new Button(0, 0, 30, 5, 62));//
            menu.buttonsTab[0].addText("");
            menu.buttonsTab[0].addText("");
            menu.buttonsTab[0].addText("");
            menu.buttonsTab[0].addText("");

            if (currentUser->userType == "admin")
            {
                menu.addButton(new Button(0, 5, 30, 3, 62));//
                menu.buttonsTab[1].addText("");
                menu.buttonsTab[1].addText("Users");
                menu.buttonsTab[1].setButtonFunction([&]() {Users(); });

                menu.addButton(new Button(0, 8, 30, 3, 62));//
                menu.buttonsTab[2].addText("");
                menu.buttonsTab[2].addText("Kierunki/Wektory");
                menu.buttonsTab[2].setButtonFunction([&]() {selectRegister(); });
            }
            else
            {
                menu.addButton(new Button(0, 5, 30, 3, 62));//
                menu.buttonsTab[1].addText("");
                menu.buttonsTab[1].addText("Kalendarz");
                menu.buttonsTab[1].setButtonFunction([&]() {selectCallendar(); });

                menu.addButton(new Button(0, 8, 30, 3, 62));//
                menu.buttonsTab[2].addText("");
                menu.buttonsTab[2].addText("Powiadomienia");
                menu.buttonsTab[2].setButtonFunction([&]() {selectNotifications(); });
            }

            menu.addButton(new Button(0, 11, 30, 3, 62));//
            menu.buttonsTab[3].addText("");
            menu.buttonsTab[3].addText("Mail");
            menu.buttonsTab[3].setButtonFunction([&]() {selectMail(); });

            if (currentUser->userType == "student")
            {
                menu.addButton(new Button(0, 14, 30, 3, 62));//
                menu.buttonsTab[4].addText("");
                menu.buttonsTab[4].addText("Chat");
                menu.buttonsTab[4].setButtonFunction([&]() {selectChat(); });

                menu.addButton(new Button(0, 17, 30, 3, 62));//
                menu.buttonsTab[5].addText("");
                menu.buttonsTab[5].addText("Rejestracja");
                menu.buttonsTab[5].setButtonFunction([&]() {selectRegister(); });
            }
            menu.viewInterface();

            char ch;

            while(true)
            {
                menu.viewInterface();
                ch = _getch();
                menu.moveCursor(ch);
            }
        }
    }

    void Users()
    {

    }
    void selectNotifications()
    {

    }
    void selectRegister()
    {
        registerSys->currentUser = currentUser;
        registerSys->viewRegisterSystem();
    }
    void selectChat()
    {
        chat->currentUser = currentUser;
        chat->viewChat();
    }
    void selectMail()
    {

    }
    void selectCallendar()
    {
        callendar->currentUser = currentUser;
        callendar->viewCallendar();
    }
};

int main()
{
    RegisterData regd;
    UsersData usersd;
    MailData maild;
    ChatData chatd;

    Data* data[4] = { &usersd ,&regd, &chatd ,&maild };

    data[0]->readFromFile();
    data[1]->readFromFile();
    data[2]->readFromFile();

    Menu menu;

    menu.loginScreen();
    return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln



/*
int main()
{

	RegisterData regd;
	UsersData usersd;
	MailData maild;
	ChatData chatd;

	Data* data[4] = { &usersd ,&regd, &chatd ,&maild };

	Menu men;

	data[0]->readFromFile();
	data[1]->readFromFile();
	data[2]->readFromFile();

	//regd.addSpec("ITE");
	//regd.specs[0]->addCourse("Analiza Matematyczna 2");
	//regd.specs[0]->courses[0]->addGroup("Wyklad");
	//regd.specs[0]->courses[0]->groups[0]->addLecture("Wyklad - M.Wodecki", true, 5, Date(2021, 10, 1), 200, 0);
	//regd.specs[0]->courses[0]->groups[1]->addLecture("Cwiczenia - Joanna Welyczko", true, 3, Date(2021, 10, 1, 14,15), 200, 0, 0);
	//regd.addSpec("CBE");
	//regd.addSpec("EKA");
	//regd.addSpec("TEL");
	//regd.addSpec("TIN");
	//regd.addSpec("AIR");


	//User uone("Pierwszy@pwr.edu.pl","Pierwszy","password1", "student",&maild, &usersd);
	//User utwo("Drugi@pwr.edu.pl", "Drugi", "password2", "student", &maild, &usersd);
	//User uthree("Trzeci@pwr.edu.pl", "Trzeci", "password3", "student", &maild, &usersd);

	//MailBox one("one@pwr.edu.pl", &maild), two("two@pwr.edu.pl", &maild), three("three@pwr.edu.pl", &maild);

	//uone.mbox.sendEmail(&utwo.mbox);
	//uone.mbox.sendEmail(&uthree.mbox, "Gorace mamuski w twojej okolicy.\n\n Kliknij w mail, aby poznac je wszystkie!\n");
	//uone.mbox.sendEmail(&utwo.mbox, "Mamo, potrzebuje klej i bibule na jutro.\n\n No ale pani naprawde powiedziala dopiero teraz!\n");
	//uthree.mbox.sendEmail(&utwo.mbox, "Gorace mamuski w twojej okolicy.\n\n Kliknij w mail, aby poznac je wszystkie!\n");
	//uthree.mbox.sendEmail(&utwo.mbox, "SEKS SKESKEKSKEKSEKK\n\n");

	/*regd.addSpec("ITE");
	regd.specs[0]->addCourse("Analiza 2.3");
	regd.specs[0]->courses[0]->addGroup("Wyklad");
	regd.specs[0]->courses[0]->groups[0]->addLecture("Wyklad Analiza 2.3", true, 3, Date(2021, 10, 2), 15, 200);
	regd.specs[0]->courses[0]->addGroup("Cwiczenia");
	regd.specs[0]->courses[0]->groups[1]->addLecture("Cwiczenia grupa 1", true, 3, Date(2021, 10, 2, 15), 15, 20);
	regd.specs[0]->courses[0]->groups[1]->addLecture("Cwiczenia grupa 2", true, 3, Date(2021, 10, 2, 15), 15, 20);

	
		for (auto s : regd.specs)
		{
			s->listCourse();
			for (auto c : s->courses)
			{
				std::cout << "  "; 
				c->listGroup();

				for (auto g : c->groups)
				{
					std::cout << "    ";
					g->listLecture();
				}
			}
		}

		return 0;



	saver = &usersd;

		saver->readFromFile();
	
		Chat test("TEST CHAT");

		UsersData::currentUser = UsersData::userList[0];

		while (true)
		{
			test.viewChat();
			test.sendMessage(UsersData::currentUser);
		}


	int i = 1;
	while (true)
	{
		usersd.userList[1]->mbox.listMail();
		int it = (_getch() - 48);
		usersd.userList[1]->mbox.readMail(it);
	}

	saver->saveToFile();
	saver = &maild;
	saver->saveToFile();*/

