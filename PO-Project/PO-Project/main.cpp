#include <iostream>
#include "Data.h"
#include <string>
#include <conio.h>
#include <stdexcept>

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

    int size()
    {
        return tabSize;
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

    bool deleted = false;

public:

    RegisterSystem(){}

    void viewRegisterSystem()
    {
        system("cls");
        Interface background;
        Interface optList;

        if (currentUser->userType == "student")
        {
            background.addButton(new Button(0, 0, 30 + currentUser->login.size(), 3, 62));
            background.buttonsTab[0].addText("");
            background.buttonsTab[0].addText("==WITAJ W SYSTEMIE ZAPISOW " + currentUser->login + "==");
            background.buttonsTab[0].addText("");

            if (!currentUser->isRegistered()) {
                optList.addButton(new Button(0, 3, 28, 3, 62));
                optList.buttonsTab[0].addText("");
                optList.buttonsTab[0].addText("Wybierz kierunek");
                optList.buttonsTab[0].setButtonFunction([&]() { selectSpec(); });

                while (currentUser->spec == nullptr)
                {
                    background.viewInterface();
                    optList.viewInterface();

                    char ch = _getch();

                    which_spec = optList.getCurrentButtonInt();
                    optList.moveCursor(ch);

                    if (ch == 27)
                    {
                        system("cls");
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
                    background.viewInterface();
                    optList.viewInterface();

                    char ch = _getch();

                    optList.getCurrentButtonInt();

                    optList.moveCursor(ch);

                    if (ch == 27)
                    {
                        system("cls");
                        break;
                    }
                }
            }
        }
        else if (currentUser->userType == "admin")
        {
            background.addButton(new Button(0, 0, 30, 3, 62));
            background.buttonsTab[0].addText("");
            background.buttonsTab[0].addText("==WYBIERZ KIERUNEK DO EDYCJI==");
            background.buttonsTab[0].addText("");

            int size = RegisterData::specs.size();


            for (int i = 0; i < RegisterData::specs.size(); i++)
            {
                optList.addButton(new Button(0, 3 + (i * 3), 20, 3, 62));
                optList.buttonsTab[i].addText("");
                optList.buttonsTab[i].addText(RegisterData::specs[i]->name);
                optList.buttonsTab[i].addText("");
                optList.buttonsTab[i].setButtonFunction([&]() {selectEditSpec(); });
            }

            for (int i = 0; i < RegisterData::specs.size(); i++)
            {
                optList.addButton(new Button(26, 3 + (i * 3), 6, 3, 62));
                optList.buttonsTab[i + size].addText("");
                optList.buttonsTab[i + size].addText(" USUN ");
                optList.buttonsTab[i + size].addText("");
                optList.buttonsTab[i + size].setButtonFunction([&]() {specDelPrompt(); });
            }


            optList.addButton(new Button(0, 4 + (size * 3), 25, 3, 62));
            optList.buttonsTab[size * 2].addText("");
            optList.buttonsTab[size * 2].addText(" +Dodaj nowy+ ");
            optList.buttonsTab[size * 2].addText("");
            optList.buttonsTab[size * 2].setButtonFunction([&]() {addNewSpec(); });

            deleted = false;
            while (!deleted)
            {
                background.viewInterface();
                optList.viewInterface();

                char ch = _getch();

                which_spec = optList.getCurrentButtonInt();
                optList.moveCursor(ch);


                if (ch == 27)
                {
                    system("cls");
                    break;
                }
            }
        }
     }

    void selectEditSpec()
    {
        system("cls");
        Interface background;
        Interface optList;

        background.addButton(new Button(0, 0, 22 + RegisterData::specs[which_spec]->name.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==KURSY NA KIERUNKU " + RegisterData::specs[which_spec]->name +"==");
        background.buttonsTab[0].addText("");

        int size = RegisterData::specs[which_spec]->courses.size();



        for (int i = 0; i < RegisterData::specs[which_spec]->courses.size(); i++)
        {
            optList.addButton(new Button(0, 3 + (i * 3), 25, 3, 62));
            optList.buttonsTab[i].addText("");
            std::string name = RegisterData::specs[which_spec]->courses[i]->name;

            if (name.size() > 25)
                name = name.substr(0, 21) + "...";

            optList.buttonsTab[i].addText(name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {selectEditCourse(); });
        }

        for (int i = 0; i < RegisterData::specs[which_spec]->courses.size(); i++)
        {
            optList.addButton(new Button(26, 3 + (i * 3), 6, 3, 62));
            optList.buttonsTab[i + size].addText("");
            optList.buttonsTab[i + size].addText(" USUN ");
            optList.buttonsTab[i + size].addText("");
            optList.buttonsTab[i + size].setButtonFunction([&]() {courseDelPrompt(); });
        }

        optList.addButton(new Button(0, 4 + (size * 3), 25, 3, 62));
        optList.buttonsTab[size * 2].addText("");
        optList.buttonsTab[size * 2].addText(" +Dodaj nowy+ ");
        optList.buttonsTab[size * 2].addText("");
        optList.buttonsTab[size * 2].setButtonFunction([&]() {addNewCourse(); });

        deleted = false;
        while (!deleted)
        {

            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            which_course = optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void selectEditCourse()
    {
        system("cls");
        Interface background;
        Interface optList;

        background.addButton(new Button(0, 0, 16 + RegisterData::specs[which_spec]->courses[which_course]->name.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==GRUPY KURSU " + RegisterData::specs[which_spec]->courses[which_course]->name + "==");
        background.buttonsTab[0].addText("");

        int size = RegisterData::specs[which_spec]->courses[which_course]->groups.size();



        for (int i = 0; i < RegisterData::specs[which_spec]->courses[which_course]->groups.size(); i++)
        {
            optList.addButton(new Button(0, 3 + (i * 3), 25, 3, 62));
            optList.buttonsTab[i].addText("");
            std::string name = RegisterData::specs[which_spec]->courses[which_course]->groups[i]->name;

            if (name.size() > 25)
                name = name.substr(0, 21) + "...";

            optList.buttonsTab[i].addText(name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {selectEditGroup(); });
        }

        for (int i = 0; i < RegisterData::specs[which_spec]->courses[which_course]->groups.size(); i++)
        {
            optList.addButton(new Button(26, 3 + (i * 3), 6, 3, 62));
            optList.buttonsTab[i + size].addText("");
            optList.buttonsTab[i + size].addText(" USUN ");
            optList.buttonsTab[i + size].addText("");
            optList.buttonsTab[i + size].setButtonFunction([&]() {groupDelPrompt(); });
        }

        optList.addButton(new Button(0, 4 + (size * 3), 25, 3, 62));
        optList.buttonsTab[size * 2].addText("");
        optList.buttonsTab[size * 2].addText(" +Dodaj nowy+ ");
        optList.buttonsTab[size * 2].addText("");
        optList.buttonsTab[size * 2].setButtonFunction([&]() {addNewGroup(); });


        deleted = false;
        while (!deleted)
        {

            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            which_group = optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }
    
    void selectEditGroup()
    {
        system("cls");
        Interface background;
        Interface optList;

        background.addButton(new Button(0, 0, 21 + RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->name.size(), 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==ZAJECIA W GRUPIE " + RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->name + "==");
        background.buttonsTab[0].addText("");

        int size = RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->lectures.size();



        for (int i = 0; i < RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->lectures.size(); i++)
        {
            optList.addButton(new Button(0, 3 + (i * 3), 25, 3, 62));
            optList.buttonsTab[i].addText("");

            std::string name = RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->lectures[i]->name;

            if (name.size() > 25)
                name = name.substr(0, 21) + "...";

            optList.buttonsTab[i].addText(name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {});
        }

        for (int i = 0; i < RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->lectures.size(); i++)
        {
            optList.addButton(new Button(26, 3 + (i * 3), 6, 3, 62));
            optList.buttonsTab[i + size].addText("");
            optList.buttonsTab[i + size].addText(" USUN ");
            optList.buttonsTab[i + size].addText("");
            optList.buttonsTab[i + size].setButtonFunction([&]() {lecDelPrompt(); });
        }

        optList.addButton(new Button(0, 4 + (size * 3), 25, 3, 62));
        optList.buttonsTab[size * 2].addText("");
        optList.buttonsTab[size * 2].addText(" +Dodaj nowy+ ");
        optList.buttonsTab[size * 2].addText("");
        optList.buttonsTab[size * 2].setButtonFunction([&]() {addNewLecture(); });

        deleted = false;
        while (!deleted)
        {
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            which_lecture = optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                system("cls");
                break;
            }
        }
    }

    void lecDelPrompt()
    {
        Interface background;
        Interface optList;

        int size = RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->lectures.size();

        std::string lec_name = RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->lectures[which_lecture-size]->name;
        optList.addButton(new Button(33, 3 + ((which_lecture-size) * 3), 11, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText(" NA PEWNO? ");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->delLecture(lec_name);
                                                       deleted = true; });

        while (true)
        {

            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);
            
            if (ch == ' ')
            {
                system("cls");
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void groupDelPrompt()
    {
        Interface background;
        Interface optList;

        int size = RegisterData::specs[which_spec]->courses[which_course]->groups.size();

        std::string grp_name = RegisterData::specs[which_spec]->courses[which_course]->groups[which_group-size]->name;
        optList.addButton(new Button(33, 3 + ((which_group - size) * 3), 11, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText(" NA PEWNO? ");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {RegisterData::specs[which_spec]->courses[which_course]->delGroup(grp_name);
        deleted = true; });

        while (true)
        {

            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);

            if (ch == ' ')
            {
                system("cls");
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void courseDelPrompt()
    {
        Interface background;
        Interface optList;

        int size = RegisterData::specs[which_spec]->courses.size();

        std::string crs_name = RegisterData::specs[which_spec]->courses[which_course-size]->name;
        optList.addButton(new Button(33, 3 + ((which_course - size) * 3), 11, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText(" NA PEWNO? ");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {RegisterData::specs[which_spec]->delCourse(crs_name);
        deleted = true; });

        while (true)
        {

            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);

            if (ch == ' ')
            {
                system("cls");
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void specDelPrompt()
    {
        Interface background;
        Interface optList;

        int size = RegisterData::specs.size();

        std::string spc_name = RegisterData::specs[which_spec - size]->name;
        optList.addButton(new Button(33, 3 + ((which_spec - size) * 3), 11, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText(" NA PEWNO? ");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {RegisterData::delSpec(spc_name);
                                                         deleted = true; });

        while (true)
        {

            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);

            if (ch == ' ')
            {
                system("cls");
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
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

            if (optList.size()) {
                which_spec = optList.getCurrentButtonInt();

                optList.moveCursor(ch);
            }
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
              name = name.substr(0, 21) + "...";

            optList.buttonsTab[i].addText(name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {selectGroup(); });
        }



        while (true)
        {
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();
            if (optList.size()) {
                which_course = optList.getCurrentButtonInt();

                optList.moveCursor(ch);
            }

            if (ch == 27)
            {
                system("cls");
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
                name = name.substr(0, 21) + "...";

            optList.buttonsTab[i].addText(name);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {selectLecture(); });
        }



        while (true)
        {
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();
            if (optList.size()) 
            {
                which_group = optList.getCurrentButtonInt();

                optList.moveCursor(ch);
            }
            if (ch == 27)
            {
                system("cls");
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

            for (int i = 0; i < currentUser->spec->courses[which_course]->groups[which_group]->lectures.size(); i++)
            {
                if(currentUser->isRegistered(currentUser->spec->courses[which_course]->groups[which_group]->lectures[i]))
                  background.buttonsTab[1 + i].editTabText(1,">ZAPISANY<");
                else
                  background.buttonsTab[1 + i].editTabText(1,"          ");
            }

            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            if (optList.size()) {
                which_lecture = optList.getCurrentButtonInt();

                optList.moveCursor(ch);
            }
            if (ch == 27)
            {
                system("cls");
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

    void addNewSpec()
    {
        system("cls");
        Interface background;
        Interface optList;

        background.addButton(new Button(0, 0, 38, 4, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==WPROWADZ NAZWE DLA NOWEGO KIERUNKU==");
        background.buttonsTab[0].addText("   ESC ABY WROCIC || ENTER ABY ZATW.  ");

        optList.addButton(new Button(0, 5, 30, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {optList.buttonsTab[0].realTimeInput(); });


        while (true)
        {
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);

            std::string name = optList.buttonsTab[0].textTab[0] + optList.buttonsTab[0].textTab[1] + optList.buttonsTab[0].textTab[2];

            if(ch==13)
            {
                system("cls");
                RegisterData::addSpec(name);
                deleted = true;
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void addNewCourse()
    {
        system("cls");
        Interface background;
        Interface optList;

        background.addButton(new Button(0, 0, 38, 4, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("  ==WPROWADZ NAZWE DLA NOWEGO KURSU== ");
        background.buttonsTab[0].addText("   ESC ABY WROCIC || ENTER ABY ZATW.  ");

        optList.addButton(new Button(0, 5, 30, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {optList.buttonsTab[0].realTimeInput(); });


        while (true)
        {
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);

            std::string name = optList.buttonsTab[0].textTab[0] + optList.buttonsTab[0].textTab[1] + optList.buttonsTab[0].textTab[2];

            if (ch == 13)
            {
                system("cls");
                RegisterData::specs[which_spec]->addCourse(name);
                deleted = true;
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void addNewGroup()
    {
        system("cls");
        Interface background;
        Interface optList;

        background.addButton(new Button(0, 0, 38, 4, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("  ==WPROWADZ NAZWE DLA NOWEJ GRUPY==  ");
        background.buttonsTab[0].addText("   ESC ABY WROCIC || ENTER ABY ZATW.  ");

        optList.addButton(new Button(0, 5, 30, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {optList.buttonsTab[0].realTimeInput(); });


        while (true)
        {
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);

            std::string name = optList.buttonsTab[0].textTab[0] + optList.buttonsTab[0].textTab[1] + optList.buttonsTab[0].textTab[2];

            if (ch == 13)
            {
                system("cls");
                RegisterData::specs[which_spec]->courses[which_course]->addGroup(name);
                deleted = true;
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }
    }

    void addNewLecture()
        {
            system("cls");
            Interface background;
            Interface optList;

            bool ev;

            background.addButton(new Button(0, 0, 37, 4, 62));
            background.buttonsTab[0].addText("");
            background.buttonsTab[0].addText(" ==WPROWADZ DANE DOT. NOWYCH ZAJEC== ");
            background.buttonsTab[0].addText("           ESC ABY WROCIC            ");

            background.addButton(new Button(0, 4, 10, 3, 62));
            background.buttonsTab[1].addText("");
            background.buttonsTab[1].addText("NAZWA >>");
            background.buttonsTab[1].addText("ZAJ.");

            background.addButton(new Button(0, 7, 10, 3, 62));
            background.buttonsTab[2].addText("");
            background.buttonsTab[2].addText("CYKL? >>");
            background.buttonsTab[2].addText("");

            background.addButton(new Button(0, 10, 37, 1, 62));
            background.buttonsTab[3].addText("FORMAT DATY TO <dd-mm-yyyy hh:min>");

            background.addButton(new Button(0, 11, 10, 3, 62));
            background.buttonsTab[4].addText("");
            background.buttonsTab[4].addText("DATA  >>");
            background.buttonsTab[4].addText("POCZ.");

            background.addButton(new Button(0, 14, 10, 3, 62));
            background.buttonsTab[5].addText("");
            background.buttonsTab[5].addText("IL.ZAJ>>");
            background.buttonsTab[5].addText("");

            background.addButton(new Button(0, 17, 10, 3, 62));
            background.buttonsTab[6].addText("");
            background.buttonsTab[6].addText("LIMIT >>");
            background.buttonsTab[6].addText("STUD.");


            optList.addButton(new Button(10, 4, 27, 3, 62));
            optList.buttonsTab[0].addText("");
            optList.buttonsTab[0].addText("");
            optList.buttonsTab[0].addText("");
            optList.buttonsTab[0].setButtonFunction([&]() {optList.buttonsTab[0].realTimeInput(); });

            optList.addButton(new Button(10, 7, 7, 3, 62));
            optList.buttonsTab[1].addText("");
            optList.buttonsTab[1].addText("  TAK  ");
            optList.buttonsTab[1].addText("");
            optList.buttonsTab[1].setButtonFunction([&]() { if (optList.buttonsTab[1].textTab[1] == "  TAK  ") {
                                                                 optList.buttonsTab[1].editTabText(1, "  NIE  ");
                                                                    ev = false;}
                                                            else
                                                            {
                                                                    optList.buttonsTab[1].editTabText(1, "  TAK  ");
                                                                    ev = true;
                                                            }});

            optList.addButton(new Button(10, 11, 27, 3, 62));
            optList.buttonsTab[2].addText("");
            optList.buttonsTab[2].addText("");
            optList.buttonsTab[2].addText("");
            optList.buttonsTab[2].setButtonFunction([&]() {optList.buttonsTab[2].realTimeInput(); });

            optList.addButton(new Button(10, 14, 27, 3, 62));
            optList.buttonsTab[3].addText("");
            optList.buttonsTab[3].addText("");
            optList.buttonsTab[3].addText("");
            optList.buttonsTab[3].setButtonFunction([&]() {optList.buttonsTab[3].realTimeInput(); });

            optList.addButton(new Button(10, 17, 27, 3, 62));
            optList.buttonsTab[4].addText("");
            optList.buttonsTab[4].addText("");
            optList.buttonsTab[4].addText("");
            optList.buttonsTab[4].setButtonFunction([&]() {optList.buttonsTab[4].realTimeInput(); });

            optList.addButton(new Button(10, 20, 27, 3, 62));
            optList.buttonsTab[5].addText("");
            optList.buttonsTab[5].addText("        >>UWTWORZ<<        ");
            optList.buttonsTab[5].addText("");
            optList.buttonsTab[5].setButtonFunction([&]() { 
                

                    system("cls");
                    try
                    {
                        std::string name;
                        std::string date = optList.buttonsTab[2].textTab[0].substr(0,16);
                        std::string lc_s = optList.buttonsTab[3].textTab[0];
                        std::string ul_s = optList.buttonsTab[4].textTab[0];;

                        std::string yy, mm, dd, hh, min;
                        name = optList.buttonsTab[0].textTab[0] + optList.buttonsTab[0].textTab[1] + optList.buttonsTab[0].textTab[2];

                        Date temp;


                        int lc = std::stoi(lc_s);
                        int ul = std::stoi(ul_s);


                        if (date.size() == 16)
                        {

                            dd = date.substr(0, 2);
                            mm = date.substr(3, 2);
                            yy = date.substr(6, 4);

                            hh = date.substr(11, 2);
                            min = date.substr(14, 2);

                            temp.changeDate(std::stoi(min), std::stoi(hh), std::stoi(dd), std::stoi(mm), std::stoi(yy));
                        }
                        else
                            throw std::invalid_argument("Zle wartosci");

                        RegisterData::specs[which_spec]->courses[which_course]->groups[which_group]->addLecture(name,ev,0,temp,lc,ul,0);
                        deleted = true;
                    }
                    catch (const std::invalid_argument& ia)
                    {

                        background.buttonsTab[0].editTabText(1, " ==WPROWADZONO ZLY FORMAT DANYCH!!== ");
                        background.buttonsTab[0].editTabText(2, "       POPRAW WPROAWDZONE DANE       ");
                        background.viewInterface();
                        optList.viewInterface();
                        _getch();
                        background.buttonsTab[0].editTabText(1, " ==WPROWADZ DANE DOT. NOWYCH ZAJEC== ");
                        background.buttonsTab[0].editTabText(2, "           ESC ABY WROCIC            ");
                    }

                });


            while (!deleted)
            {







                background.viewInterface();
                optList.viewInterface();

                char ch = _getch();

                optList.moveCursor(ch);




                if (ch == 27)
                {
                    system("cls");
                    break;
                }
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
    User* currentUser;//wyciągam maile currentUser.mbox.sendEmail(adres skrzynki pocztowej,tresc)
    //potrzebuje ludzi z lecutre lecture.participants dla wykladowcy
    //potrzebuje wszystkie emaile dla admina MailData wypisanie;//MailBox usuwanie
public:
    MailSystem()
    {

    }
    void viewMailBox()
    {
        //std::cout << "xd";
        system("cls");
        //callendar.getCurrentButtonInt();
        Interface list;

        int listPage = 0;

        for (int i = 0; i < 10; i++)//Button(int xPosB, int yPosB, int xSizeB, int ySizeB, int colorB)
        {
            list.addButton(new Button(4, i * 2 + 2, 30, 2, 48));
            list.buttonsTab[i].addText("");
            list.buttonsTab[i].addText("");
            if (currentUser->mbox.mail.size() > i + 10 * listPage)
                list.buttonsTab[i].textTab[1] = currentUser->mbox.mail[i + 10 * listPage]->date.toString() + currentUser->mbox.mail[i + 10 * listPage]->sender;

        }


        list.addButton(new Button(4, 22, 15, 3, 32));//prev mail
        list.buttonsTab[10].addText("");
        list.buttonsTab[10].addText("prev");


        list.addButton(new Button(4, 25, 15, 3, 32));//next mail
        list.buttonsTab[11].addText("");
        list.buttonsTab[11].addText("next");

        list.addButton(new Button(4, 28, 15, 3, 32));//send mail
        list.buttonsTab[12].addText("");
        list.buttonsTab[12].addText(" SEND MAIL");

        char ch;
        while (true)
        {
            for (int i = 0; i < 10; i++)
            {
                list.buttonsTab[i].textTab[1] = "";
            }

            for (int i = 0; i < 10; i++)
            {
                if (currentUser->mbox.mail.size() > i + 10 * listPage)
                    list.buttonsTab[i].textTab[1] = currentUser->mbox.mail[i + 10 * listPage]->date.toString() + currentUser->mbox.mail[i + 10 * listPage]->sender;
            }


            list.viewInterface();
            ch = _getch();

            list.moveCursor(ch);

            switch (ch)
            {
            case ' '://do zrobienia//Wybieranie eventu
            {
                int intVar = list.getCurrentButtonInt();
                if (intVar < currentUser->mbox.mail.size()) {
                   
                    if (intVar < 10)
                    {
                        viewMailContents(intVar + 10 * listPage);
                    }
                    else if (intVar == 10)
                    {
                        if (listPage > 0)
                            listPage--;


                    }
                }
                else if (intVar == 11)
                {
                    if (currentUser->mbox.mail.size()>(listPage+1)*10)
                     listPage++;


                }
                else if (intVar == 12)
                {
                    viewSendMail();
                }
            }
            break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }
    void viewMailContents(int var)
    {
        Interface mail;
        mail.addButton(new Button(0, 0, 50, 3, 62));
        mail.buttonsTab[0].addText("");
        mail.buttonsTab[0].addText(currentUser->mbox.mail[var]->date.toString());

        mail.addButton(new Button(0, 3, 50, 3, 62));
        mail.buttonsTab[1].addText("from:");
        mail.buttonsTab[1].addText(currentUser->mbox.mail[var]->sender);

        mail.addButton(new Button(0, 6, 50, 3, 62));
        mail.buttonsTab[2].addText("to:");
        mail.buttonsTab[2].addText(currentUser->mbox.mail[var]->reciever);

        mail.addButton(new Button(0, 9, 50, 10, 62));
        
        std::string stringVar;
        for (int i=0;i< currentUser->mbox.mail[var]->text.size();i++)
        {
            stringVar += currentUser->mbox.mail[var]->text[i];
            if ((i + 1)% 50 == 0)
            {
                mail.buttonsTab[3].addText(stringVar);
                stringVar = "";
            }
            if (i == 499)
            {
                i = currentUser->mbox.mail[var]->text.size();
            }
        }
        if (stringVar.size()>0)
        {
            mail.buttonsTab[3].addText(stringVar);
        }
        if (currentUser->userType == "admin")
        {
            mail.addButton(new Button(0, 19, 50, 3, 62));
            mail.buttonsTab[4].addText("");
            mail.buttonsTab[4].addText("DeleteMail");
        }

        mail.viewInterface();

        char ch;

        while (true)
        {
            ch=_getch();
            mail.moveCursor(ch);
            if (ch == ' ' && mail.getCurrentButtonInt() == 4 && currentUser->userType == "admin" && currentUser->mbox.mail.size())
            {
                currentUser->mbox.deleteEmail(var+1);
                system("cls");
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

        //currentUser->mbox.mail[var]->date.toString() + currentUser->mbox.mail[var]->sender;
    }
    void viewSendMail()
    {
        Interface mail;
        Interface background;

        background.addButton(new Button(0, 0, 50, 1, 62));
        background.buttonsTab[0].addText("from:");

        mail.addButton(new Button(0, 1, 50, 2, 62));
        if (currentUser->userType != "admin")
        {
            mail.buttonsTab[0].addText(currentUser->email);
            mail.buttonsTab[0].addText("");
        }
        else
        {
            mail.buttonsTab[0].setButtonFunction([&]() {mail.buttonsTab[0].realTimeInput(); });
            mail.buttonsTab[0].addText("");
            mail.buttonsTab[0].addText("");
        }

        background.addButton(new Button(0, 3, 50, 1, 62));
        background.buttonsTab[1].addText("to:");

        mail.addButton(new Button(0, 4, 50, 2, 62));
        mail.buttonsTab[1].setButtonFunction([&]() {mail.buttonsTab[1].realTimeInput(); });
        mail.buttonsTab[1].addText("");
        mail.buttonsTab[1].addText("");


        mail.addButton(new Button(0, 6, 50, 10, 62));
        mail.buttonsTab[2].setButtonFunction([&]() {mail.buttonsTab[2].realTimeInput(); });
        for(int i=0;i<10;i++)
            mail.buttonsTab[2].addText("");

        mail.addButton(new Button(0, 16, 50, 3, 62));
        mail.buttonsTab[3].addText("");
        mail.buttonsTab[3].addText("Send");

        if (currentUser->userType == "lecturer")
        {
            mail.addButton(new Button(0, 19, 50, 3, 62));
            mail.buttonsTab[4].addText("");
            mail.buttonsTab[4].addText("Send to group");
        }

        char ch;

        while (true)
        {
            background.viewInterface();
            mail.viewInterface();

            ch = _getch();

            mail.moveCursor(ch);
            if (ch == ' ' && mail.getCurrentButtonInt() == 4 && currentUser->userType == "lecturer")
            {
                Lecture* lecture;

                std::string receiver = "";
                for (int i = 0; i < 2; i++)
                    receiver += mail.buttonsTab[1].textTab[i];

                std::string text = "";
                for (int i = 0; i < 10; i++)
                    text += mail.buttonsTab[4].textTab[i];
                for (int i = 0; i < currentUser->userLectures.size(); i++)
                    if (currentUser->userLectures[i]->name == receiver)
                        lecture = currentUser->userLectures[i];

                system("cls");
                break;


                sendMailToLecture(lecture, text);
            }
            if (ch == ' ' && mail.getCurrentButtonInt() == 3 && currentUser->userType != "admin")
            {

                std::string receiver = "";
                for (int i = 0; i < 2; i++)
                    receiver += mail.buttonsTab[1].textTab[i];

                std::string text = "";
                for (int i = 0; i < 10; i++)
                    text += mail.buttonsTab[4].textTab[i];

                sendMail(receiver, text);

                system("cls");
                break;
            }
            else if (ch == ' ' && mail.getCurrentButtonInt() == 3 && currentUser->userType == "admin")
            {
                User* user = currentUser;


                std::string sender = "";
                for (int i = 0; i < 2; i++)
                    sender += mail.buttonsTab[0].textTab[i];

                currentUser = UsersData::findUser(sender);///PYTANIE ?????????????????????????????????????????????/

                std::string receiver = "";
                for (int i = 0; i < 2; i++)
                    receiver += mail.buttonsTab[1].textTab[i];

                std::string text = "";
                for (int i = 0; i < 10; i++)
                    text += mail.buttonsTab[4].textTab[i];

                sendMail(receiver, text);

                currentUser = user;

                system("cls");
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }

        }
    }
    void sendMail(std::string eAdress, std::string text)
    {
        currentUser->mbox.sendEmail(eAdress,text);
    }
    void sendMailToLecture(Lecture* lecture, std::string text)
    {
        for(int i= 0 ;i< lecture->participants.size();i++)
        currentUser->mbox.sendEmail(&(lecture->participants[i]->mbox),text);
    }
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

        Date* temp=new Date();
        int monthFirstDay = (temp->returnFirstDay() + 6)%7+1;//(0,6)(niedziela,sobota)--->(1,7)(pon,niedz)
        int daysInMonth = temp->returnDaysInMonth();
        for (int y = 0; y < 6; y++)
        {
            for (int x = 0; x < 7; x++)
            {

                callendar.addButton(new Button(x*4,y*3,4,3,62));
                callendar.buttonsTab[x + y * 7].addText("");
                callendar.buttonsTab[x + y * 7].addText(" ");

            }
        }

        CallendarData::returnUserEvents(currentUser, *(new Date(2021, 10, 8, 0, 0)));//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for (int i = monthFirstDay-1; i < daysInMonth + monthFirstDay - 1; i++)
        {
            callendar.buttonsTab[i].textTab[1] += std::to_string(i - monthFirstDay + 2);
        }

        char ch;

        while (true)
        {
            callendar.viewInterface();

            ch = _getch();

            callendar.moveCursor(ch);

            switch (ch)
            {
            case ' '://do zrobienia//Wybieranie eventu
                {
                    //eventList(new Event("xd", *(new Date), "opis");
                temp->day = callendar.getCurrentButtonInt()-monthFirstDay+1;
                temp->roundDate();
                    eventList(CallendarData::returnUserEvents(currentUser, *temp));//(new Event("xd", *(new Date), "opis"),1);//potrzebna pomoc
                }
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }
    void eventList(std::vector<Event*> eventList)//(Event* eventTab,int tabSize)//potrzebna pomoc
    {
        system("cls");
        //callendar.getCurrentButtonInt();
        Interface list;

        int listPage = 0;

        for (int i = 0; i < 10; i++)//Button(int xPosB, int yPosB, int xSizeB, int ySizeB, int colorB)
        {
            list.addButton(new Button(4, i * 2 + 2, 30, 2, 48));
            list.buttonsTab[i].addText("");
            list.buttonsTab[i].addText("");

        }


        list.addButton(new Button(4, 22, 15, 3, 32));//prev Events
        list.buttonsTab[10].addText("");
        list.buttonsTab[10].addText("prev");


        list.addButton(new Button(4, 25, 15, 3, 32));//next Events
        list.buttonsTab[11].addText("");
        list.buttonsTab[11].addText("next");

        list.addButton(new Button(4, 28, 15, 3, 32));//add Event
        list.buttonsTab[12].addText("");
        list.buttonsTab[12].addText(" + Event");

        char ch;
        while (true)
        {
            list.viewInterface();
            ch = _getch();

            list.moveCursor(ch);

            switch (ch)
            {
            case ' '://do zrobienia//Wybieranie eventu
            {
                int intVar = list.getCurrentButtonInt();
                if (intVar < 10)
                {
                    viewEvent(eventList,intVar + 10 * listPage);
                }
                else if (intVar == 10)
                {
                    listPage--;

                    for (int i = 0; i < 10; i++)
                    {
                        if (eventList.size() > i + 10 * listPage)
                            list.buttonsTab[i].textTab[1] = eventList[i + 10 * listPage]->eventDate.toString() + eventList[i + 10 * listPage]->eventName;

                    }
                }
                else if (intVar == 11)
                {
                    listPage++;

                    for (int i = 0; i < 10; i++)
                    {
                        if (eventList.size() > i + 10 * listPage)
                            list.buttonsTab[i].textTab[1] = eventList[i + 10 * listPage]->eventDate.toString() + eventList[i + 10 * listPage]->eventName;

                    }
                }
                else if (intVar == 12)
                {
                    addEvent(eventList);
                }
            }
            break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

        //refresh();

    }
    void viewEvent(std::vector<Event*> eventList,int intVar)
    {
        system("cls");
        Interface list;

            list.addButton(new Button(4, 0 + 2, 30, 2, 48));
            list.buttonsTab[0].addText("");
            list.buttonsTab[0].addText("");

            list.addButton(new Button(4, 1 * 2 + 2, 30, 2, 48));
            list.buttonsTab[1].addText("");
            list.buttonsTab[1].addText("");

            list.addButton(new Button(4, 2 * 2 + 2, 30, 10, 48));
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");
            list.buttonsTab[2].addText("");

            list.addButton(new Button(4, 2 * 2 + 2+10, 30, 3, 48));
            list.buttonsTab[3].addText("");
            list.buttonsTab[3].addText("usun Event");

            char ch;

            while (true)
            {
                system("cls");
                list.viewInterface();
                ch = _getch();

                list.moveCursor(ch);

                if (ch==27)
                {
                    system("cls");
                    break;
                }
                if (ch == 3 && list.getCurrentButtonInt()==3)
                {
                    Event* event=eventList[intVar];
                    eventList.erase(eventList.begin()+intVar);
                    currentUser->delCusomEvent(event);
                    system("cls");
                    break;
                }
            }

    }
    void addEvent(std::vector<Event*> eventList)
    {
        system("cls");
        Interface list;
        Interface background;
        for (int i=0; i < 6; i++)
        {
            list.addButton(new Button(4, i * 1, 30, 1, 48));
            list.buttonsTab[i].addText("");
            list.buttonsTab[i].setButtonFunction([&]() {list.buttonsTab[i].realTimeInput(); });
            background.addButton(new Button(0, i * 1, 4, 1, 48));
            background.buttonsTab[i].addText("");
        }
        background.buttonsTab[0].textTab[0] = "name";
        background.buttonsTab[1].textTab[0] = "yr: ";
        background.buttonsTab[2].textTab[0] = "mth:";
        background.buttonsTab[3].textTab[0] = "day:";
        background.buttonsTab[4].textTab[0] = "hr: ";
        background.buttonsTab[5].textTab[0] = "min:";


        list.addButton(new Button(4, 6, 30, 10, 48));
        list.buttonsTab[5].addText("tu wpisz opis");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].addText("");
        list.buttonsTab[5].setButtonFunction([&]() {list.buttonsTab[5].realTimeInput(); });


        list.addButton(new Button(4, 6 + 10, 30, 3, 48));
        list.buttonsTab[6].addText("");
        list.buttonsTab[6].addText("add Event");

        char ch;

        while (true)
        {
            system("cls");
            list.viewInterface();
            background.viewInterface();
            ch = _getch();

            list.moveCursor(ch);
            if (ch == ' ' && list.getCurrentButtonInt()==6)
            {
                std::string name= list.buttonsTab[0].textTab[0];

                std::string year= list.buttonsTab[1].textTab[0];
                std::string month= list.buttonsTab[2].textTab[0];
                std::string day= list.buttonsTab[3].textTab[0];
                std::string hour= list.buttonsTab[4].textTab[0];
                std::string minute= list.buttonsTab[5].textTab[0];

                std::string description="";
                for (int i = 0; i < 10; i++)
                    description += list.buttonsTab[6].textTab[i];

                Event* event = new Event(name, *(new Date(std::stoi(year), std::stoi(month), std::stoi(day), std::stoi(hour), std::stoi(minute))), description);
                eventList.push_back(event);
                currentUser->addCustomEvent(event);
                //eventList.push_back(new Event(name,new Date(),description);
                system("cls");
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }
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

    int which_user;
    bool running = true;

    ChatSystem* chat;
    RegisterSystem* registerSys;
    MailSystem* mail;
    CallendarSystem* callendar;
    NotificationSystem* notifications;

    RegisterData regd;
    UsersData usersd;
    MailData maild;
    ChatData chatd;

    Data* data[4] = { &usersd ,&regd, &chatd ,&maild };




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
        readData(data);

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

                menu.addButton(new Button(0, 11, 30, 3, 62));//
                menu.buttonsTab[3].addText("");
                menu.buttonsTab[3].addText("Skrzynki Mailowe");
                menu.buttonsTab[3].setButtonFunction([&]() {editMailBoxes(); });
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

                menu.addButton(new Button(0, 11, 30, 3, 62));//
                menu.buttonsTab[3].addText("");
                menu.buttonsTab[3].addText("Mail");
                menu.buttonsTab[3].setButtonFunction([&]() {selectMail(); });
            }
            std::cout << "xd";
            _getch();


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

            int pos;

            if (currentUser->userType == "student")
                pos = 20;
            else if (currentUser->userType == "lecturer" || currentUser->userType == "admin")
                pos = 14;


            menu.addButton(new Button(0,pos,30,3,62));
            menu.buttonsTab[menu.size()-1].addText("");
            menu.buttonsTab[menu.size()-1].addText(">>WYLOGUJ<<");
            menu.buttonsTab[menu.size()-1].setButtonFunction([&]() {currentUser=nullptr; system("cls");});
            char ch;

            while(currentUser!=nullptr)
            {
                menu.viewInterface();
                ch = _getch();
                menu.moveCursor(ch);
            }
        }
    }

    void editMailBoxes()
    {

        int which_mbox;
        User* temp = currentUser;
        system("cls");

        Interface background;
        Interface optList;

        background.addButton(new Button(0, 0, 22, 3, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==LISTA SKRZYNEK MAILOWYCH==");
        background.buttonsTab[0].addText("");

        for (int i = 0; i < MailData::mailBoxList.size(); i++)
        {
            optList.addButton(new Button(0, 3 + (i * 3), 20, 3, 62));
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].addText(MailData::mailBoxList[i]->address);
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {
                                                            std::string name = MailData::mailBoxList[which_mbox]->address;
                                                            name.erase(name.find('@'),name.npos);
                                                            currentUser = UsersData::findUser( name );
                                                            std::string prevtp = currentUser->userType;
                                                            currentUser->userType = "admin";
                                                            selectMail();
                                                            currentUser->userType = prevtp;
                });
        }

        while (true)
        {
            currentUser = temp;
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            which_mbox = optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                system("cls");
                break;
            }

        }

    }

    void Users()
    {
        system("cls");

        Interface background;
        Interface optList;
        Interface list;

        background.addButton(new Button(0, 0, 27, 3,62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText("==LISA UZYTKOWNIKOW==");
        background.buttonsTab[0].addText("");

        int size = UsersData::userList.size();

        for (int i=0;i<UsersData::userList.size();i++)
        {
            list.addButton(new Button(0, 3 + (i * 3), 25, 3, 62));
            list.buttonsTab[i].addText("");
            std::string name = UsersData::userList[i]->login;

            if (name.size() > 25)
                name = name.substr(0, 21) + "...";

            list.buttonsTab[i].addText(name);
            list.buttonsTab[i].addText("");
            list.buttonsTab[i].setButtonFunction([&]() {});
        }

        for (int i = 0; i < UsersData::userList.size(); i++)
        {
            optList.addButton(new Button(26, 3 + (i * 3), 6, 3, 62));
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].addText(" USUN ");
            optList.buttonsTab[i].addText("");
            optList.buttonsTab[i].setButtonFunction([&]() {if (UsersData::userList[which_user] != currentUser) { userDelPrompt(); }});
        }

        optList.addButton(new Button(0, 4 + (size * 3), 25, 3, 62));
        optList.buttonsTab[size].addText("");
        optList.buttonsTab[size].addText(" +Dodaj nowego+ ");
        optList.buttonsTab[size].addText("");
        optList.buttonsTab[size].setButtonFunction([&]() {addUser(); });

        running = true;
        while (running)
        {

            background.viewInterface();
            optList.viewInterface();
            list.viewInterface();

            char ch = _getch();

            which_user=optList.getCurrentButtonInt();

            optList.moveCursor(ch);

            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void userDelPrompt()
    {
        Interface background;
        Interface optList;

        int size = RegisterData::specs.size();

        User* which = UsersData::userList[which_user];
        optList.addButton(new Button(33, 3 + ((which_user) * 3), 11, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText(" NA PEWNO? ");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() { 
                                                            UsersData::delUser(which);
                                                            running = false;
                                                                                                          });

        running = true;
        while (running)
        {

            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);

            if (ch == ' ')
            {
                system("cls");
                break;
            }
            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void addUser()
    {
        system("cls");
        Interface background;
        Interface optList;

        background.addButton(new Button(0, 0, 38, 4, 62));
        background.buttonsTab[0].addText("");
        background.buttonsTab[0].addText(" ==WPROWADZ DANE NOWEGO UZYTKOWNIKA== ");
        background.buttonsTab[0].addText("            ESC ABY WROCIC            ");

        background.addButton(new Button(0, 4, 10, 3, 62));
        background.buttonsTab[1].addText("");
        background.buttonsTab[1].addText("LOGIN >>");
        background.buttonsTab[1].addText("");

        background.addButton(new Button(0, 7, 10, 3, 62));
        background.buttonsTab[2].addText("");
        background.buttonsTab[2].addText("HASLO >>");
        background.buttonsTab[2].addText("");

        background.addButton(new Button(0, 10, 10, 3, 62));
        background.buttonsTab[3].addText("");
        background.buttonsTab[3].addText("TYP >>");
        background.buttonsTab[3].addText("");



        optList.addButton(new Button(10, 4, 27, 3, 62));
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].addText("");
        optList.buttonsTab[0].setButtonFunction([&]() {optList.buttonsTab[0].realTimeInput(); });

        optList.addButton(new Button(10, 7, 27, 3, 62));
        optList.buttonsTab[1].addText("");
        optList.buttonsTab[1].addText("");
        optList.buttonsTab[1].addText("");
        optList.buttonsTab[1].setButtonFunction([&]() {optList.buttonsTab[1].realTimeInput(); });

        optList.addButton(new Button(10, 10, 27, 3, 62));
        optList.buttonsTab[2].addText("");
        optList.buttonsTab[2].addText("student");
        optList.buttonsTab[2].addText("");
        optList.buttonsTab[2].setButtonFunction([&]() {
            if (optList.buttonsTab[2].textTab[1] == "student")
                optList.buttonsTab[2].editTabText(1, "lecturer");
            else if(optList.buttonsTab[2].textTab[1] == "lecturer")
                optList.buttonsTab[2].editTabText(1, "admin");
            else if (optList.buttonsTab[2].textTab[1] == "admin")
                optList.buttonsTab[2].editTabText(1, "student");
            });

        optList.addButton(new Button(10, 13, 27, 3, 62));
        optList.buttonsTab[3].addText("");
        optList.buttonsTab[3].addText("  >>UTWORZ NOWEGO<<");
        optList.buttonsTab[3].addText("");
        optList.buttonsTab[3].setButtonFunction([&]() {
            
            std::string lg = optList.buttonsTab[0].textTab[0] + optList.buttonsTab[0].textTab[1] + optList.buttonsTab[0].textTab[2];
            std::string ps = optList.buttonsTab[1].textTab[0] + optList.buttonsTab[1].textTab[1] + optList.buttonsTab[1].textTab[2];
            std::string tp = optList.buttonsTab[2].textTab[0] + optList.buttonsTab[2].textTab[1] + optList.buttonsTab[2].textTab[2];
            
           
                UsersData::addUser(lg,ps,tp);
                running = false;
                system("cls");

            });



        running = true;
        while (running)
        {
            background.viewInterface();
            optList.viewInterface();

            char ch = _getch();

            optList.moveCursor(ch);


            if (ch == 27)
            {
                system("cls");
                break;
            }
        }

    }

    void selectNotifications()
    {
        std::cout << "pucim pwaanie";
        system("cls");
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
        std::cout << "pucim12312313e";
        mail->currentUser = currentUser;
        mail->viewMailBox();
        system("cls");
    }
    void selectCallendar()
    {
        callendar->currentUser = currentUser;
        callendar->viewCallendar();
        system("cls");
    }

    void saveData(Data* dt[4])
    {
        for (int i=0;i<4;i++)
        {
            dt[i]->saveToFile();
        }
    }

    void readData(Data* dt[4])
    {
        for (int i = 0; i < 4; i++)
        {
            dt[i]->readFromFile();
        }
    }
};

int main()
{
    //RegisterData regd;
    //UsersData usersd;
    //MailData maild;
    //ChatData chatd;

    //Data* data[4] = { &usersd ,&regd, &chatd ,&maild };

    //data[0]->readFromFile();
    //data[1]->readFromFile();
    //data[2]->readFromFile();

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

