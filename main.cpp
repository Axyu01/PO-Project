#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
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
public:
    int xPos;
    int yPos;
    int xSize;
    int ySize;
    int color;
    std::string* textTab;
    void* activateButton();
private:
    int tabSize;

public:
    Button(int xPosB,int yPosB,int xSizeB,int ySizeB,int colorB)
    {
        xPos=xPosB;
        yPos=yPosB;
        xSize=xSizeB;
        ySize=ySizeB;
        color=colorB%256;
        tabSize=0;
    }
    Button()
    {
        xPos=0;
        yPos=0;
        xSize=10;
        ySize=4;
        color=74;
        tabSize=0;
    }
    void addText(std::string text)
    {
        std::string* temp;
        std::string* oldTab;
        temp = new std::string[tabSize + 1];
        for (int i = 0; i < tabSize + 1; i++)
        {
            if (i == tabSize)
            {
                temp[i] = text;
            }
            else
            {
                temp[i] = textTab[i];
            }
        }
        textTab = temp;
        delete oldTab;

        tabSize++;
    }

    std::string returnTabText(int arrayNum)
    {
        return textTab[arrayNum];
    }

    void editTabText(int arrayNum, std::string text)
    {
        textTab[arrayNum]=text;
    }

    void viewButton()
    {
        changeColor(color);
        for(int i=0;i<ySize;i++)
        {
            setCursor(xPos,yPos+i);
            for(int j=0;j<xSize;j++)
            {

                if(i<tabSize&&(int)textTab[i][j]!=0)
                {
                    std::cout<<textTab[i][j];
                }
                else
                {
                    for(int k=j;k<xSize;k++)
                        {
                            std::cout<<" ";
                        }
                        j=xSize;
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
            color=kolor%256;
            return true;
    }
};
class Interface//:Button
{
    private:
        int cursorPosX;
        int cursorPosY;
        int currentButton;
        int tabSize;

        static bool ifBigger(int a,int b)
        {
            if(a>b)
                return true;
            else
                return false;
        }
        static bool ifSmaller(int a,int b)
        {
            if(a<b)
                return true;
            else
                return false;
        }
    void lookForClosest(bool (*statement)(int,int),bool inAxisX)
    {
        int closeX;
        int closeY;
        int button=-1;//-1 tells if button was found
        if(inAxisX)
        {
            for(int i=0; i<tabSize; i++)
            {
                if((*statement)(cursorPosX,buttonsTab[i].xPos)/**sprawdza kierunek**/
                        &&(((cursorPosX-buttonsTab[i].xPos)*(cursorPosX-buttonsTab[i].xPos)+(cursorPosY-buttonsTab[i].yPos)*(cursorPosY-buttonsTab[i].yPos))<((cursorPosX-closeX)*(cursorPosX-closeX)+(cursorPosY-closeY)*(cursorPosY-closeY)))
                        /**sprawdza najblizszy button**/
                       )
                {
                    closeX=buttonsTab[i].xPos;
                    closeY=buttonsTab[i].yPos;
                    button=i;
                }
            }

            if((*statement)(cursorPosX,closeX)&&button>=0)
            {
                cursorPosX=closeX;
                cursorPosY=closeY;
                buttonsTab[currentButton].changeButtonColor(buttonsTab[currentButton].color-buttonsTab[currentButton].color%16+(buttonsTab[currentButton].color+8)%16+128);//shows which button is now selected
                buttonsTab[currentButton].viewButton();
                buttonsTab[button].changeButtonColor(buttonsTab[button].color-buttonsTab[button].color%16+(buttonsTab[button].color+8)%16+128);//shows which button is now selected
                buttonsTab[button].viewButton();
                currentButton=button;
            }
        }
        else
        {
            for(int i=0; i<tabSize; i++)
            {
                if((*statement)(cursorPosY,buttonsTab[i].yPos)/**sprawdza kierunek**/
                        &&(((cursorPosX-buttonsTab[i].xPos)*(cursorPosX-buttonsTab[i].xPos)+(cursorPosY-buttonsTab[i].yPos)*(cursorPosY-buttonsTab[i].yPos))<((cursorPosX-closeX)*(cursorPosX-closeX)+(cursorPosY-closeY)*(cursorPosY-closeY)))
                        /**sprawdza najblizszy button**/
                       )
                {
                    closeX=buttonsTab[i].xPos;
                    closeY=buttonsTab[i].yPos;
                    button=i;
                }
            }

            if((*statement)(cursorPosY,closeY)&&button>=0)
            {
                cursorPosX=closeX;
                cursorPosY=closeY;
                buttonsTab[currentButton].changeButtonColor(buttonsTab[currentButton].color-buttonsTab[currentButton].color%16+(buttonsTab[currentButton].color+8)%16+128);//shows which button is now selected
                buttonsTab[currentButton].viewButton();
                buttonsTab[button].changeButtonColor(buttonsTab[button].color-buttonsTab[button].color%16+(buttonsTab[button].color+8)%16+128);//shows which button is now selected
                buttonsTab[button].viewButton();
                currentButton=button;
            }
        }
    }
    public:
        Button* buttonsTab;
        Interface()
        {
            tabSize=0;
            cursorPosX=0;
            cursorPosY=0;
            currentButton=0;
        }
        void moveCursor(char ch)
        {
            switch(ch)
            {
                case 'w':case 'W':
                {
                   lookForClosest(ifBigger,false);
                }
                break;

                case 's':case 'S':
                {
                   lookForClosest(ifSmaller,false);
                }
                break;

                case 'a':case 'A':
                {
                   lookForClosest(ifBigger,true);
                }
                break;

                case 'd':case 'D':
                {
                   lookForClosest(ifSmaller,true);
                }
                break;
            }
        }
        void addButton(Button* button)
        {
            Button* temp;
            Button* oldTab=buttonsTab;
            temp = new Button[tabSize + 1];

            if(tabSize==0)
            {
              currentButton=0;
              cursorPosX=(*button).xPos;
              cursorPosY=(*button).yPos;
              (*button).changeButtonColor((*button).color-(*button).color%16+((*button).color+8)%16+128);//highlights current button
            }

            for (int i = 0; i < tabSize + 1; i++)
            {
                if (i == tabSize)
                {
                    temp[i] = *button;
                }
                else
                {
                    temp[i] = buttonsTab[i];
                }
            }
            buttonsTab = temp;
            delete oldTab;

            tabSize++;
        }
        void removeButton(int tabPos)
        {
            if(tabSize>0)
            {
                Button* temp;
            Button* oldTab=buttonsTab;
            temp = new Button[tabSize - 1];

            for (int i = 0; i < tabSize - 1; i++)
            {
                if (i >= tabPos)
                {
                    temp[i] =  buttonsTab[i+1];
                }
                else
                {
                    temp[i] = buttonsTab[i];
                }
            }
            buttonsTab = temp;
            delete oldTab;

            tabSize--;
            }
        }
        void viewInterface()
        {
            for(int i=0;i<tabSize;i++)
            {
                buttonsTab[i].viewButton();
            }
        }

};
int main()
{
    /**std::cout << "Hello World!\n";
    Button Test;
    Test.addText("abc");
    Test.addText("abc");
    Test.addText("abc");
    Test.addText("abc");
    Test.viewButton();
    std::cout << Test.returnTabText(0);
    std::cout << Test.returnTabText(1);
    std::cout << Test.returnTabText(2);
    std::cout << Test.returnTabText(3);*/
    /*Interface Interfejs;
    char ch;
    Button* temp;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            temp=new Button(j*10,i*4,10,4,58);
            Interfejs.addButton(temp);
            delete temp;
            Interfejs.buttonsTab[10*i+j].addText("Zajecia");
            Interfejs.buttonsTab[10*i+j].addText("parzysty");
            Interfejs.buttonsTab[10*i+j].addText("8:00");
        }
    }
    Interfejs.viewInterface();
    while(true)
    {
        ch=getch();
        Interfejs.moveCursor(ch);
    }*/
    Interface Wybor;
    Interface Poczta;
    Interface Ramka;
    Ramka.addButton(new Button(9,1,111,3,50));
    Ramka.addButton(new Button(0,0,120,1,30));
    Ramka.addButton(new Button(0,4,120,1,30));
    Ramka.addButton(new Button(0,8,120,1,30));
    Ramka.addButton(new Button(0,12,120,1,30));
    Ramka.addButton(new Button(0,16,120,1,30));
    Ramka.addButton(new Button(0,20,120,1,30));
    Ramka.addButton(new Button(0,24,120,1,30));
    Ramka.addButton(new Button(0,28,120,1,30));
    Ramka.addButton(new Button(0,0,1,29,30));
    Ramka.addButton(new Button(8,0,1,29,30));
    Ramka.addButton(new Button(1,5,7,3,50));
    Ramka.addButton(new Button(1,9,7,3,50));
    Ramka.addButton(new Button(1,13,7,3,50));
    Ramka.addButton(new Button(1,17,7,3,50));
    Ramka.addButton(new Button(1,21,7,3,50));
    Ramka.addButton(new Button(1,25,7,3,50));
    Ramka.viewInterface();

    Poczta.addButton(new Button(1,1,7,3,40));
    Poczta.buttonsTab[0].addText("");
    Poczta.buttonsTab[0].addText("Wstecz");

    Poczta.addButton(new Button(9,5,111,3,40));
    Poczta.addButton(new Button(9,9,111,3,40));
    Poczta.addButton(new Button(9,13,111,3,40));
    Poczta.addButton(new Button(9,17,111,3,40));
    Poczta.addButton(new Button(9,21,111,3,40));
    Poczta.addButton(new Button(9,25,111,3,40));
    Poczta.viewInterface();

    Wybor.addButton(new Button(5,10,8,3,50));
    //Wybor.addButton(new Button(13,10,8,3,50));
    //Wybor.viewInterface();

    char ch;

    while(true)
    {
        ch=getch();
        Poczta.moveCursor(ch);
    }
    return 0;

}
