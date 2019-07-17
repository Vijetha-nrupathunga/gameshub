#include<stdio.h>
#include<iomanip>
#include<iostream>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<string.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void loading()
{

   char *a="GAME ZONE LOADING..." ;
   char b=178;

   for(int j=0;j<3;j++)
   {
       system("cls");
       system("color 0c");
       for(int j=0;j<20;j++)
        {
            cout<<"\n";
        }

         cout<<endl<<setw(100);
       for(int i=0;i<strlen(a);i++)
   {
       delay(120);
       cout<<a[i];
   }
   cout<<endl<<setw(100);
      for(int i=0;i<strlen(a);i++)
   {
       delay(120);
       cout<<b;
   }
   cout<<endl;
   }

}

using namespace std;
class MINES//the class is used for forming the basic structure of CENTRAL_UNIT
{
    protected:
    char user_table[10][10];//this to indicate the positions selected by the user
    char set_mine[10][10];//this is the original array with mines located
    public:
        void NO_OF_MINES_AROUND(int i,int j)//function is used to check how many mines are present around
        {
            if(i>=0&&i<10&&j>=0&&j<10&&set_mine[i][j]!='X')
            set_mine[i][j]++;
        }
        void MINE_POSITIONS()//function is for assigning mines at a random positions
        {
            int counter=0;
            srand(time(NULL));
            for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                set_mine[i][j]='0';
            while(counter<10)
            {
                int i=rand()%10;
                int j=rand()%10;
                //cout<<i<<j<<endl;delay(1000);
                if(set_mine[i][j]=='0')
                {
                    set_mine[i][j]='X';
                    NO_OF_MINES_AROUND(i-1,j);
                    NO_OF_MINES_AROUND(i+1,j);
                    NO_OF_MINES_AROUND(i,j-1);
                    NO_OF_MINES_AROUND(i,j+1);
                    NO_OF_MINES_AROUND(i-1,j-1);
                    NO_OF_MINES_AROUND(i-1,j+1);
                    NO_OF_MINES_AROUND(i+1,j-1);
                    NO_OF_MINES_AROUND(i+1,j+1);
                    counter++;
                }
            }system("cls");
        }
        void GET_TABLE()
        {
            for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                user_table[i][j]=' ';
        }
        void DISPLAY_TABLE(char arr[10][10])
        {
            cout<<setw(70)<<"   ";
            for(int i=0;i<10;i++)
                cout<<"|"<<setw(2)<<i;
            cout<<"|";
            cout<<endl<<setw(70)<<"  ";
            for(int i=0;i<32;i++)
                cout<<"_";
                cout<<endl<<setw(70);
            for(int i=0;i<10;i++)
            {
                cout<<setw(3)<<setw(70)<<i<<"|";
                for(int j=0;j<10;j++)
                cout<<setw(2)<<arr[i][j]<<"|";
                cout<<endl<<" "<<setw(70);
                for(int i=0;i<33;i++)
                cout<<"_";
                cout<<endl;
            }
        }
        void MINE_FINDERS(int i,int j)
        {
            if (user_table[i][j]==' '&&set_mine[i][j]!='X'&&i>=0&&i<10&&j>=0&&j<10)
            {
                user_table[i][j]=set_mine[i][j];
                if(set_mine[i][j]=='0')
                {
                    MINE_FINDERS(i,j-1);
                    MINE_FINDERS(i,j+1);
                    MINE_FINDERS(i-1,j-1);
                    MINE_FINDERS(i+1,j-1);
                    MINE_FINDERS(i+1,j+1);
                    MINE_FINDERS(i-1,j+1);
                    MINE_FINDERS(i-1,j);
                    MINE_FINDERS(i+1,j);
                }
            }
        }
};
class mine_inputs:public MINES
{
    protected:
    char symbol; //the input symbol, it can be 'o' or f'
    int FLAG_COUNTER=0;
    int mines_flagged_counter=0;
    bool GAME_OVER=false;
    public:
    void SELECT_BLOCK()//function to user inputs of selecting positions
    {
        int i,j;
        do
            cin>>i>>j;
        while(i<0||i>9||j<0||j>9);
        if(set_mine[i][j]=='X')//used to check whether mine is present at that position or not
        {
            user_table[i][j]='X';
            GAME_OVER=true;//true if present
            for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                if(set_mine[i][j]=='X')//this will be helpful while displaying so the user can know the positions of mines
                    user_table[i][j]='X';
        }
        else
            MINE_FINDERS(i,j);//display board after input
    }
    void FLAG_OPERATIONS()//function for user to place or remove flags of identifications
    {
        int i,j;
        do
            cin>>i>>j;
        while(i<0||i>9||j<0||j>9);
        if (user_table[i][j]==' ')
        {
            user_table[i][j]='F';
            FLAG_COUNTER++;
            if(set_mine[i][j]=='X')//this indicates users assumption is right
                mines_flagged_counter++;
        }
        else if (user_table[i][j]=='F')//if he already marked it will remove it
        {
            user_table[i][j]=' ';
            FLAG_COUNTER--;
            if(set_mine[i][j]=='X')
                mines_flagged_counter--;
        }
    }
};
void printline(int range=130,char c='_')
{
    for(int i=0;i<range;i++)
        cout<<c;
    cout<<endl;
}
class checker_n_inputs:public mine_inputs//this class contains functions which have basic inputs
{
    public:
        bool WIN_GAME()
        {
            if(FLAG_COUNTER==10&&mines_flagged_counter==10)//this indicates that user have found every mines properly
                return 1;
            else
                return 0;
        }
        void CENTRAL_UNIT()//this is the central function for all the functions
        {
            int x=1;
            GET_TABLE();//function to create the structure of user_table before CENTRAL_UNIT starts
            MINE_POSITIONS();//function to create mines
            while(!GAME_OVER&&!WIN_GAME())
            {
                x=1;system("cls");
                for(int e=0;e<15;e++)
                        cout<<endl;
                DISPLAY_TABLE(user_table);
                while(x)
                {

                    cout<<setw(100)<<"1.ENTER FOR NEW GAME"<<endl<<setw(100)<<"2.SELECT BLOCK"<<endl<<setw(100)<<"3.PLACE OR REMOVE FLAG"<<endl<<setw(100)<<"4.MENU"<<endl;
                    cin>>symbol;
                    //printline(120,'_');
                    cout<<endl;
                   // printline(120,'_');
                    switch (symbol)
                    {
                        case '1' :CENTRAL_UNIT();
                                    x=0;break;
                        case '2' :cout<<endl<<setw(100)<<"ENTER ROW AND COLUMN NUMBERS"<<endl;
                                    SELECT_BLOCK();
                                    x=0; break;//to select a block
                        case '3' :cout<<endl<<setw(100)<<"ENTER ROW AND COLUMN NUMBERS"<<endl;
                                    FLAG_OPERATIONS();
                                    cout<<endl<<setw(100)<<"NUMBER OF FLAGS SELECTED:"<<FLAG_COUNTER<<endl;
                                    x=0; break;//to place a flag
                        case '4' :return;break;
                        default  : x=1;//if invalid input is entered repeat again
                    }
                }
            }
            if(GAME_OVER)
            {
                system("cls");
                for(int e=0;e<15;e++)
                        cout<<endl;
                DISPLAY_TABLE(user_table);
                cout<<setw(100)<<endl<<"GAME OVER"<<endl;delay(3000);
                cin.get();
            }
            if(WIN_GAME())
            {
                system("cls");
                for(int e=0;e<15;e++)
                        cout<<endl;
                DISPLAY_TABLE(user_table);
                cout<<setw(100)<<endl<<"WINNER!"<<endl; cin.get();delay(3000);
            }
        }
};
class WORD
{
    int wrong_guesses=0;
    static int max_guess;
    char guess;
    public:static int fs,ls;
            int letterFill(char,string,string &);
            string word;
            WORD(){};
            void rules()
            {
                system("cls");
               printline(120,'_');
                cout<<endl;
                printline(120,'_');
                cout.setf(ios::left);
                cout <<endl<<"INSTRUCTIONS:"<<endl<<endl;
                cout<<endl<<"1.YOU HAVE TO GUESS A WORD.";
                cout<<endl<<"2.EACH LETTERS ENTERED MUST BE IN LOWER CASE.";
                cout<<endl<<"3.NUMBER OF TRIES DECREASES ON WRONG GUESS.";
                cout<<endl<<"4.NO CHANGE IN NUMBER OF TRIES UPON CORRECT GUESS OF A LETTER.";
                cout<<endl<<"5.NO SPECIAL CHARACTERS MUST BE USED (except \'_\'). USE _(underscore) FOR SPACE";
                cout <<endl<<"6.YOU HAVE " << max_guess << " TRIES TO TRY AND GUESS THE WORD."<<endl;
                printline(120,'_');
                cout<<endl;
                printline(120,'_');
                cout.setf(ios::right);system("pause");
                cout<<endl<<"GET READY......ALL THE BEST.....";
            }
            int game_start();
            void settings();
};
int WORD::ls=1;
int WORD::fs=1;
class programmers_word:public WORD
{
    string words[10] =
    {
        "mark_zuckerberg",//invented facebook
        "dennis_ritchie",//founder of c
        "bill_gates",//founder of microsoft
        "steve_jobs",//founder of apple
        "larry_page",//invented google
        "binny_bansal"//founder of flipkart
        "brian_kernighan",//computer scientist, worked for development of unix
        "ken_thompson",//designed and implemented unix
        "ada_lovelace",//world's first programmer
        "bjarne_stroustrup"//developer of c++

    };
    public:
    programmers_word(int x)
    {
        //choose and copy a word from array of words randomly
        srand(time(NULL));
        if(x==1)//selecting levels
        {   int n=rand()%4;
            word=words[n];
        }
        if(x==2)
        {   int n=(rand()%4)+3;
            word=words[n];
        }
         if(x==3)
        {   int n=(rand()%4)+6;
            word=words[n];
        }
    }
};
class app_word:public WORD
{
    string words[10] =
    {"twitter","facebook","whatsapp","yahoo","gmail",
    "youtube","amazon","pinterest","linkedin","tumbler"};
    public:
    app_word(){}
    app_word(int ch)
    {
          //choose and copy a word from array of words randomly
        srand(time(NULL));
        if(ch==1)//selecting levels
        {   int n=rand()%4;
            word=words[n];
        }
        if(ch==2)
        {   int n=(rand()%4)+3;
            word=words[n];
        }
         if(ch==3)
        {   int n=(rand()%4)+6;
            word=words[n];
        }
    }
};
class lang_word:public WORD
{
    string words[10] =
    {"php","java","shell","python","pascal",
    "ruby","perl","scala","javascript","typescript"};
    public:
    lang_word(int ch)
    {
          //choose and copy a word from array of words randomly
        srand(time(NULL));
        if(ch==1)//selecting levels
        {   int n=rand()%4;
            word=words[n];
        }
        if(ch==2)
        {   int n=(rand()%4)+3;
            word=words[n];
        }
         if(ch==3)
        {   int n=(rand()%4)+6;
            word=words[n];
        }
    }
};
void WORD::settings()
{
    system("cls");
    int choice;
    do{
            system("cls");
        for(int f=0;f<20;f++)
            cout<<endl;
        cout<<setw(100)<<"1.FIELDS"<<endl;
        cout<<setw(100)<<"2.LEVELS"<<endl;
        cout<<setw(100)<<"3.BACK"<<endl;
        int count=0;
        cout<<endl<<"ENTER YOUR WISH"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1:system("cls");
                for(int f=0;f<20;f++)
                    cout<<endl;
                cout<<endl<<setw(100)<<"1.PERSONALITIES"<<endl<<setw(100)<<"2.APPLICATIONS"<<endl<<setw(100)<<"3. PROGRAMMING LANGUAGE"<<endl;
                cout<<endl<<"ENTER YOUR WISH"<<endl;
                cin>>fs;//field select
                //printline(120,'_');
                cout<<endl;
               // printline(120,'_');
                break;
            case 2:system("cls");//printline(120,'_');
                cout<<endl;
                for(int f=0;f<20;f++)
                        cout<<endl;
                //printline(120,'_');
                cout<<endl<<setw(100)<<"1.EASY"<<endl<<setw(100)<<"2.MEDIUM"<<endl<<setw(100)<<"3.HARD"<<endl<<setw(100)<<"Which level you choose?"<<endl;
                cin>>ls;//level select
                //printline(120,'_');
                cout<<endl;
                //printline(120,'_');
                break;
            case 3:count++;
                break;
            default:cout<<setw(100)<<"INVALID CHOICE.....(enter the given choices)";
        }
    if(count!=0)
        break;
    }while(1);
}
int WORD::game_start()
{
     system("cls");
    char letter;
    cout<<endl<<setw(100)<<"YOUR WORD TO GUESS IS "<<endl<<setw(100);
    string unknown(word.length(),'*');
    while (wrong_guesses < max_guess)
    {
        for(int f=0;f<25;f++)
        cout<<endl;



        cout <<endl<<endl <<setw(100)<< unknown;
        cout << endl<<endl<<setw(100)<<"GUESS A LETTER:";
        cin >> letter;
        letter=tolower(letter);cout.setf(ios::left);
        // Fill secret word with letter if the guess is correct,
        // otherwise increment the number of wrong guesses.
        if (letterFill(letter, word,unknown)==0)
        {
            cout << endl <<"WHOOPS! WRONG GUESS. THAT LETTER ISN'T THERE!" << endl;
            wrong_guesses++;
        }
        else
        {
            cout << endl << "YOU FOUND A LETTER!! GOOD MOVE.....!" << endl;
        }
        // Tell user how many guesses has left.
        cout<<"YOU HAVE " << max_guess-wrong_guesses;
        cout <<" GUESSES LEFT." << endl;
        // Check if user guessed the word.
        if (word==unknown)
        {
            system("cls");
            for(int f=0;f<25;f++)
        cout<<endl;
           // printline(120,'_');
            cout<<endl;
           // printline(120,'_');
            cout <<endl<<setw(100)<< word << endl;
            cout <<setw(100)<< "YEAH! YOU GOT IT!.....CONGRATS!!!!!!";
           // printline(120,'_');
            cout<<endl;
            //printline(120,'_');
            cin.get();
            return (1);
            break;
        }
        if(wrong_guesses == max_guess)
        {
            system("cls");
            for(int f=0;f<25;f++)
        cout<<endl;
           // printline(120,'_');
            cout<<endl;
           // printline(120,'_');
            cout <<endl<<setw(100)<< "SORRY, YOU LOSE...."<<endl;
            cout<<endl<<setw(100)<<"BETTER LUCK NEXT TIME." << endl;
            cout <<setw(100)<< "THE WORD WAS : " << word << endl;
            //printline(120,'_');
            cout<<endl;
            //printline(120,'_');
            cin.get();
            return (0);
        }delay(2000);
        cin.get();
        system("cls");cout.setf(ios::right);
    }
}
int WORD::max_guess=7;
int WORD::letterFill (char guess, string secretword,string &guessword)
{
    int i;
    int matches=0;
    int len;
    len=secretword.size();
    for (i = 0; i< len; i++)
    {
        // Did we already match this letter in a previous guess?
        if (guess == guessword[i])
        return 0;
        // Is the guess in the secret word?
        if (guess == secretword[i])
        {
            guessword[i] = guess;
            matches++;
        }
    }
    return matches;
}
void result(int res,int ch)
{
    //cout.setf(ios::left);
    //printline(120,'_');
    cout<<endl;
    printline(120,'_');
    if(res==1)
    {
        if(ch==1)
            cout<<endl<<setw(100)<<"YOU SCORED 100 POINTS....."<<endl;
        if(ch==2)
            cout<<endl<<setw(100)<<"YOU SCORED 200 POINTS....."<<endl;
        if(ch==3)
            cout<<endl<<setw(100)<<"YOU SCORED 500 POINTS....."<<endl;
    }
    if(res==0)
        cout<<endl<<"YOU HAVE NOT SCORED ANY POINTS.."<<endl;
    //printline(120,'_');
    cout<<endl;
    //printline(120,'_');
    //cout.setf(ios::right);
}
void centre()
{
    WORD w;
    int a,ch;
    int choice,i;
    cout<<setw(100)<<"1.NEW GAME"<<endl<<setw(100)<<"2.RULES"<<endl<<setw(100)<<"3.SETTINGS"<<endl<<setw(100)<<"4.MAIN MENU"<<endl;
    cout<<"ENTER CHOICE"<<endl;
    cin>>choice;
   // printline(120,'_');
    cout<<endl;
    //printline(120,'_');
    //programmers_word ch(1);
    switch(choice)
    {
        case 1://programmers_word ch();
                a=w.fs;
                ch=w.ls;
                switch(a)
                {
                    case 1:{
                                int res;
                                programmers_word c1(ch);
                                res=c1.game_start();
                                result(res,ch);
                                break;
                            }
                    case 2: {
                                int res;
                                app_word c1(ch);
                                res=c1.game_start();
                                result(res,ch);
                                break;
                            }
                    case 3:{
                                int res;
                                lang_word c1(ch);
                                res=c1.game_start();
                                result(res,ch);
                                break;
                            }
                default:cout<<endl<<"INVALID CHOICE....(enter the given choice)"<<endl;
            }
        case 2:w.rules();break;
        case 3:w.settings();break;
        default:centre();
    }
}

void FUNCTION()
{

    system("color f9");
    WORD w;
    int a,ch;
    int choicew,i;
     checker_n_inputs c;
    int choice,select;
    for(int f=0;f<20;f++)
        cout<<endl;
      //  printline(120,'_');
      char b=178;
      delay(250);
   cout<<setw(100)<<b<<b<<b<<b<<" "<<"   "<<b<<b<<b<<"   "<<b<<"   "<<b<<"   "<<b<<b<<b<<endl;delay(250);
   cout<<setw(100)<<b<<"   "<<"    "<<b<<" "<<b<<"   "<<b<<b<<" "<<b<<b<<"   "<<b<<"  "<<endl;delay(250);
   cout<<setw(100)<<b<<b<<b<<b<<"    "<<b<<b<<b<<"   "<<b<<" "<<b<<" "<<b<<"   "<<b<<b<<b<<endl;delay(250);
   cout<<setw(100)<<b<<"  "<<b<<"    "<<b<<" "<<b<<"   "<<b<<"   "<<b<<"   "<<b<<"  "<<endl;delay(250);
   cout<<setw(100)<<b<<b<<" "<<b<<" "<<"   "<<b<<" "<<b<<"   "<<b<<"   "<<b<<"   "<<b<<b<<b<<endl;delay(250);
   cout<<setw(102)<<"  "<<b<<" "<<b<<"    "<<b<<"   "<<b<<"   "<<b<<"  "<<endl;delay(250);
   cout<<setw(102)<<"  "<<b<<" "<<b<<"    "<<b<<"   "<<b<<"   "<<b<<"  "<<endl;delay(250);
   cout<<setw(102)<<"  "<<b<<b<<b<<"    "<<b<<"   "<<b<<"   "<<b<<b<<b<<endl;delay(250);
   cout<<setw(102)<<"  "<<b<<" "<<b<<"    "<<b<<"   "<<b<<"   "<<b<<" "<<b<<endl;delay(250);
   cout<<setw(102)<<"  "<<b<<" "<<b<<"    "<<b<<b<<b<<b<<b<<"   "<<b<<b<<b<<endl;delay(250); system("color fC");delay(500);
   cout<<setw(120)<<"TIME TO WIN"<<endl; delay(500);system("color f2");delay(500);system("color f9");

   //  printline(120,'_');
    cout<<endl;
   // printline(120,'_');
  cin.get();
   system("cls");
     for(int e=0;e<20;e++)
        cout<<endl;
    cout<<setw(100)<<"---MAIN MENU---"<<endl<<endl<<setw(100)<<"1.MINESWEEPER"<<endl<<setw(100)<<"2.WORD GUESS"<<endl<<setw(100)<<"3.EXIT"<<endl<<endl<<setw(100)<<"ENTER CHOICE"<<endl;
    cin>>choice;
   // printline(120,'_');
    cout<<endl;
   // printline(120,'_');
    do{
    switch(choice)
    {
        case 1:loading();system("cls");
                do
                {system("color 0c");
                    checker_n_inputs c;system("cls");//system("color 0c");
                    for(int e=0;e<20;e++)
                        cout<<endl;
                    cout<<setw(100)<<"---WELCOME TO MINESWEEPER---"<<endl<<endl<<setw(100)<<"1.NEW GAME"<<endl<<setw(100)<<"2.INSTRUCTIONS"<<endl<<setw(100)<<"3.MAIN MENU"<<endl<<setw(100)<<"ENTER CHOICE"<<endl;
                    cin>>select;
                    //printline(120,'_');
                    cout<<endl;
                    //printline(120,'_');
                    switch(select)
                    {
                        case 1:for(int e=0;e<20;e++)
                                cout<<endl;
                                c.CENTRAL_UNIT();delay(1000);break;
                        case 2:system("cls");
                                for(int e=0;e<20;e++)
                                cout<<endl;
                                cout.setf(ios::left);
                                 printline(120,'_');
                                cout<<endl;
                                printline(120,'_');
                                cout<<"INSTRUCTIONS:"<<endl<<setw(100)<<"1.Don't worry about your first click. The first square that you click will never have a mine"<<endl;
                                cout<<endl<<"2.Know what the numbers mean. A number on a square refers to the number of "<<endl;
                                cout<<"mines that are currently adjacent to that square."<<endl;
                                cout<<endl<<"3.Right-click any squares that you think contain mines. This will put a flag on the" <<endl;
                                cout<<"square. It's best to start with squares that absolutely have to contain mines"<<endl<<endl;
                                cout<<"4.Clear the board. To win a round of Minesweeper, you must click on the board every"<<endl;
                                cout<<"square that doesn't have a mine under it. Once you've done so, the game will be over.If "<<endl;
                                cout<<"you accidentally click a square that has a mine beneath it, the game will be over. You'll"<<endl;
                                cout<<"have the option of starting a new game or redoing the one you just played."<<endl;
                                printline(120,'_');
                                cout<<endl;
                                printline(120,'_');cout.setf(ios::right);system("pause");
                                break;
                        case 3:for(int e=0;e<20;e++)
                                cout<<endl;
                                system("cls");system("cls");FUNCTION();//default
                                break;
                    }
                }while(!(select==1||select==2||select==3));break;
        case 2:loading();
                {system("cls");system("color f0");
                cin.get();
                system("cls");
                 for(int f=0;f<20;f++)
                cout<<endl;
                cout<<endl<<setw(100)<<"---WELCOME TO WORD GUESS---"<<endl<<endl<<setw(100)<<"1.NEW GAME"<<endl<<setw(100)<<"2.INSTRUCTIONS"<<endl<<setw(100)<<"3.SETTINGS"<<endl<<setw(100)<<"4.MAIN MENU"<<endl;
                cout<<endl<<setw(100)<<"ENTER CHOICE"<<endl;
                cin>>choicew;
                //printline(120,'_');
                cout<<endl;
                //printline(120,'_');
                switch(choicew)
                {
                    case 1://programmers_word ch();
                        system("cls");
                        system("color 0c");
                            a=w.fs;
                            ch=w.ls;
                            switch(a)
                            {
                                case 1:{
                                             for(int f=0;f<20;f++)
                                            cout<<endl;
                                            int res;
                                            programmers_word c1(ch);
                                            res=c1.game_start();
                                            result(res,ch);
                                            break;
                                        }
                                case 2:{
                                             for(int f=0;f<20;f++)
                                            cout<<endl;
                                            int res;
                                            app_word c1(ch);
                                            res=c1.game_start();
                                            result(res,ch);
                                            break;
                                        }
                                case 3:{
                                             for(int f=0;f<20;f++)
                                            cout<<endl;
                                            int res;
                                            lang_word c1(ch);
                                            res=c1.game_start();
                                            result(res,ch);
                                            break;
                                        }
                                default:cout<<endl<<setw(100)<<"INVALID CHOICE.....(Enter the given choices) "<<endl;
                        }
                        break;
                        case 2:w.rules();break;
                        case 3:w.settings();break;
                        case 4:system("cls");FUNCTION();
                        default:FUNCTION();
                }
            }break;
            case 3:exit(1);
            default:FUNCTION();
        }
    }while(1);
}
int main()
{
    FUNCTION();
    return (0);
}

