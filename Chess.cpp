#include<iostream>
#include<string>
#include<conio.h>

#include "GameData.cpp"
//#include "Player.cpp"
#include<windows.h>
#include<iostream>
#include<fstream>

using namespace std;


void setcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return;
}
int Fcolor(int f, int b)
{
    int  finalcolor = 7;

    finalcolor = (16 * b) + f;
    return finalcolor;
}

struct Chess {
    GameData GameState;
    string PlayerNames[2];
    bool GameActive = false;
} Game;

string getPlayerinfo() {
    string Name = "";
    cout << "\nEnter Player Name\n";
    do {
        cin.clear();
        fflush(stdin);
        getline(cin, Name);
    } while (Name.length() == 0);
    return Name;
}

int SaveGame()
{
    // If we have an active game then save it for future along with player names
    // The function will ask the user to specify a file name and save the entire game into it
    string File;


    if (!Game.GameActive)
    {
        cout << "\n\n\t\tNo Active Game available!\nGame cannot be saved!\n\n";
        return -1;
    }
   /* while (File.length() == 0)
    {

        cin.clear();
        fflush(stdin);

    }*/
    cout << "Enter the Name of Saving File : ";
    cin >> File;
    ofstream F(File);
    if (!F)
    {
        cout << "nUnable to open file \n" << endl;
        return -2;
    }
    F << Game.PlayerNames[0] << endl << Game.PlayerNames[1] << endl;
    F << Game.GameState.TurningPlayer << endl;
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            F << Game.GameState.Board[r][c].PieceColor << "   " << Game.GameState.Board[r][c].Code<<"   " <<Game.GameState.Board[r][c].MoveCount<<"        ";

        }
        F << endl;

    }

    F.close();

    return 0;
}

bool LoadGame() {
    // The function will ask the user to specify a file name and save the entire game into it
    string File;

    /*while (File.length() == 0)
    {
        cin.clear();
        fflush(stdin);

    }*/
    cout << "Enter the Name of Loading File : ";
    cin >> File;
    ifstream F(File.c_str());

    if (F.is_open())
    {

        int turn;
        F >> Game.PlayerNames[0] >> Game.PlayerNames[1];
        F >> turn;
        switch (turn)
        {
        case 0:
            Game.GameState.TurningPlayer = BLACK;
            break;
        case 1:
            Game.GameState.TurningPlayer  = WHITE;
            break;
        }

        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
            {
                 int piece;
                 int  code;

                 F >> piece;
                 switch (piece)
                 {
                 case 0:
                     Game.GameState.Board[r][c].PieceColor = BLACK;
                     break;
                 case 1:
                     Game.GameState.Board[r][c].PieceColor = WHITE;
                     break;
                 }

                 F >>code;
                 switch (code)
                 {
                 case 0:
                     Game.GameState.Board[r][c].Code = NONE;
                     break;
                 case 1:
                     Game.GameState.Board[r][c].Code =PAWN;
                     break;

                 case 2:
                     Game.GameState.Board[r][c].Code =ROOK;
                     break;

                 case 3:
                     Game.GameState.Board[r][c].Code = BISHOP;
                     break;

                 case 4:
                     Game.GameState.Board[r][c].Code =KNIGHT;
                     break;

                 case 5:
                     Game.GameState.Board[r][c].Code= QUEEN ;
                     break;

                 case 6:
                     Game.GameState.Board[r][c].Code = KING ;
                     break;
                 }
                 F >> Game.GameState.Board[r][c].MoveCount;


            }

        F.close();
        return true;

    }
    else if(!F)
    {
        cout << "\n\n\t\t\tCan't open file!\n\n";
        return false;
    }

    return true;
}

void ShowGame()
 {
    int foregroundcolor = 0;
    int backgroundcolor = 15;
    int finalcolor;

    finalcolor = Fcolor(foregroundcolor, backgroundcolor);


    cout << Game.PlayerNames[1] << "\tvs\t" << Game.PlayerNames[0] << endl;

    for (int r = 0; r < 8; r++)
    {
        cout << "\t";
        if (r == 0 || r % 2 == 0)
        {

            for (int i = 0; i < 1; i++)
            {
                cout << endl;
                cout << "\t";
                for (int j = 0; j < 8; j++)
                {
                    if (j % 2 != 0 || j == 1)
                    {
                        setcolor(7);
                        cout << "          ";

                    }
                    else
                    {
                        setcolor(finalcolor);
                        cout << "          ";
                    }

                }

            }
        }
        else
        {
            for (int i = 0; i < 1; i++)
            {
                cout << endl;
                cout << "\t";
                for (int j = 0; j < 8; j++)
                {
                    if (j % 2 == 0)
                    {
                        setcolor(7);
                        cout << "          ";

                    }
                    else
                    {
                        setcolor(finalcolor);
                        cout << "          ";
                    }

                }
                setcolor(7);

            }
            setcolor(7);
        }
        cout << endl << r<<"\t";
        for (int c = 0; c < 8; c++)
        {

            if (r == 0 || r % 2 == 0)
            {
                if (c % 2 != 0||c==1)
                {
                    setcolor(7);

                }
                else
                {
                    setcolor(finalcolor);
                }
            }
            else if (r % 2 != 0 && r )
            {
                if (c % 2 == 0 )
                {
                    setcolor(7);
                }
                else
                {
                    setcolor(finalcolor);
                }


            }
            switch (Game.GameState.Board[r][c].Code) {
            case NONE:
                cout <<"    "<< "..    ";
                break;
            default:
                cout << "    " ;
                if (Game.GameState.Board[r][c].PieceColor == BLACK)
                {
                    cout << "B";
                }
                else
                {

                    cout << "W";

                }

                switch (Game.GameState.Board[r][c].Code) {
                case PAWN:
                    cout << "P    ";
                    break;

                case ROOK:
                    cout << "R    ";
                    break;

                case KNIGHT:
                    cout << "kN   ";
                    break;

                case BISHOP:
                    cout << "B    ";
                    break;

                case QUEEN:
                    cout << "Q    ";
                    break;

                case KING:
                    cout << "K    ";
                    break;
                }
                break;
            }
        }
        setcolor(7);

        cout << "\t";
        if (r == 0 || r % 2 == 0)
        {

            for (int i = 0; i < 1; i++)
            {
                cout << endl;
                cout << "\t";
                for (int j = 0; j < 8; j++)
                {
                    if (j % 2 != 0 || j == 1)
                    {
                        setcolor(7);
                        cout << "          ";

                    }
                    else
                    {
                        setcolor(finalcolor);
                        cout << "          ";
                    }

                }

            }
        }
        else
        {
            for (int i = 0; i < 1; i++)
            {
                cout << endl;
                cout << "\t";
                for (int j = 0; j < 8; j++)
                {
                    if (j % 2 == 0)
                    {
                        setcolor(7);
                        cout << "          ";

                    }
                    else
                    {
                        setcolor(finalcolor);
                        cout << "          ";
                    }

                }
                setcolor(7);

            }


            setcolor(7);

        }


    }
    cout << endl;
    cout << "\t    ";
    for (int c = 0; c < 8; c++)
        cout << c << "         ";
    cout << "\n";
}

void initNewGame() {
    cout << "Enter First(WHITE) Player's Info" << endl;
    Game.PlayerNames[1] = getPlayerinfo();
    cout << "\n\nEnter Second(BLACK) Player's Info" << endl;
    Game.PlayerNames[0] = getPlayerinfo();
    initGame(Game.GameState);
}

int PlayGame() {
    string Player[2] = { "BLACK","WHITE" };
    chessMove Move;
    ShowGame();
    bool Ans=false;

    while (!isGameOver(Ans))
    {

        cout << Game.PlayerNames[Game.GameState.TurningPlayer];
        if (Game.GameState.TurningPlayer == WHITE)
        {
            cout << " (WHITE) To Move";
        }
        else
        {

            cout << " (BLACK) To Move";

        }

        cout << "\n\n" << "Please enter your move  (use format FROM (Row# Column#) TO (Row# Column#) ) {Negative Value to move to the main menu}" << endl;
        int R = 0;

        cin >> Move.FromRow >> Move.FromColumn;
        cin >> Move.ToRow >> Move.ToColumn;


        if (Move.FromRow < 0 || Move.FromColumn < 0 || Move.ToColumn < 0 || Move.ToRow < 0) {
            Game.GameActive = true;
            cout << "Moving to main menu \n";
            return 0;
        }
        int M;

        M = Game.GameState.Board[Move.ToRow][Move.ToColumn].Code;

        R =MakeMove(Game.GameState, Move);
        char Piece;
        if (Move.ToRow == 0 && Game.GameState.Board[Move.ToRow][Move.ToColumn].Code == PAWN && Game.GameState.Board[Move.ToRow][Move.ToColumn].PieceColor == WHITE)
        {
            cout << "Your Pawn is getting \n" << "\t\t (R)ook\t(Q)ueen\t(B)ishop\t (K)night \n";
            cin >> Piece;

            PromotePawn(Game.GameState, Piece, Move);

        }
        else  if (Move.ToRow == 7 && Game.GameState.Board[Move.ToRow][Move.ToColumn].Code == PAWN && Game.GameState.Board[Move.ToRow][Move.ToColumn].PieceColor == BLACK)
        {
            cout << "Your Pawn is getting \n" << "\t\t\t(R)ook<<"    "<<(Q)ueen<<"    "<<(B)ishop<<"    "<<(K)night \n";
            cin >> Piece;

            PromotePawn(Game.GameState, Piece, Move);

        }

        if (Game.GameState.Check == 1 && R==0)
        {

            Game.GameState.TurningPlayer = Game.GameState.notPlayer;
            Game.GameState.Board[Move.FromRow][Move.FromColumn].Code = Game.GameState.Board[Move.ToRow][Move.ToColumn].Code;
            Game.GameState.Board[Move.ToRow][Move.ToColumn].Code = NONE;
            Game.GameState.Board[Move.FromRow][Move.FromColumn].PieceColor = Game.GameState.TurningPlayer;
        }


        ShowGame();


        isfacingCheck(Game.GameState, Move, Game.GameState.TurningPlayer);

        if (Game.GameState.Check == 1)
        {
            cout << "\nALERT ! YOU ARE FACING CHECK !\n";
            Ans = isCheckmate(Game.GameState, Game.GameState.TurningPlayer, Move);
            if (Ans == true)
            {
                isGameOver(Ans);
            }
            else
            {
                int size = 0;
                size = Game.GameState.ValidMoves.size();

                cout << "\t\t\tSUGGESTED MOVES\n";
                cout << "\t\t";
                for (int i = 1; i <= size; i++)
                {
                    cout << Game.GameState.ValidMoves[i - 1] << "\t";
                    if (i % 4 == 0)
                    {
                        cout << endl;
                        cout << "\t\t";
                    }
                }

                for (int i = Game.GameState.ValidMoves.size(); i > 0; i--)
                {
                    Game.GameState.ValidMoves.pop_back();
                }

            }

        }

        if (R == 0 )
        {
            if (Game.GameState.en_passant == PAWN)
            {
                cout << "PAWN of " << Player[Game.GameState.TurningPlayer] << " is captured by 'en passant' rule !\n";
                Game.GameState.en_passant = NONE;
            }

            switch (M)
            {
            case 1:
                cout << "PAWN of " << Player[Game.GameState.TurningPlayer] << " is captured !\n";
                break;

            case 2:
                cout << "ROOK of " << Player[Game.GameState.TurningPlayer] << " is captured !\n";
                break;

            case 3:
                cout << "BISHOP of " << Player[Game.GameState.TurningPlayer] << " is captured !\n";
                break;

            case 4:
                cout << "KNIGHT of " << Player[Game.GameState.TurningPlayer] << " is captured !\n";
                break;

            case 5:
                cout << "QUEEN of " << Player[Game.GameState.TurningPlayer] << " is captured !\n";
                break;

            case 6:
                cout << "KING of " << Player[Game.GameState.TurningPlayer] << " is captured ! \n Game has ended !";
                break;
            }

        }



    }
    Game.GameActive = false;
    cout << "\n\nGAME OVER CHECKMATE !!!\n" << Player[Game.GameState.notPlayer] << "  wins the game !\n\n";

    return 0;

}


int main()
{

    int choice = 0;
    do {
        do {


            cout<<"                                      ****   *     *   ****    ****   ****                                              ";
            cout<<"                                     *       *     *   *      *      *                                                  ";
            cout<<"                                     *       *******   ****     *       *                                               ";
            cout<<"                                     *       *     *   *          *       *                                             ";
            cout<<"                                      ****   *     *   ****   ****    ****                                              ";
            cout<<"-----------------------------------------------------------------------------------------------------------------------";
            cout<<"                                               |MADE BY CODEXOWLS|                                                       ";
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl<<endl<<endl;


            cout << "\t\t\t\t\t\t1. New Game\n\t\t\t\t\t\t2. Restart Game\n\t\t\t\t\t\t3. Save Game\n\t\t\t\t\t\t4. Load Game\n\t\t\t\t\t\t5. Exit\n\n Enter Your Choice(1-5) ";
            cin >> choice;
        } while (choice < 1 || choice > 5);

        switch (choice) {
        case 1:
            initNewGame();
            PlayGame();
            break;
        case 2:
            PlayGame();
            break;
        case 3:
            SaveGame();
            break;
        case 4:

            if (LoadGame())
            {
                PlayGame();
            }
            break;

        case 5:
            return 0;
            break;
        }
    } while (1);

    return 0;
}
