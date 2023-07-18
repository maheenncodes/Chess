#include "GameData.h"

void PromotePawn(GameData& Game,char P,chessMove Move) {
    // A special move that is allowed under special conditions
    int FR = 0, FC = 0, TR = 0, TC = 0;

    FR = Move.FromRow;
    FC = Move.FromColumn;
    TR = Move.ToRow;
    TC = Move.ToColumn;

  
    if (P == 'R')
    {
        Game.Board[TR][TC].Code = ROOK;
    }
    else if (P == 'B')
    {
        Game.Board[TR][TC].Code = BISHOP;
    }
    else if (P == 'Q')
    {
        Game.Board[TR][TC].Code = QUEEN;
    }
    else if (P == 'K')
    {
        Game.Board[TR][TC].Code = KNIGHT;
    }
}


bool isValidMove(GameData& Game, chessMove Move, Color Player)
{
    // this function will return true if the move specified by the Move parameter is a valid move
    // You might make more functions to breakdown the task of this function into subtasks
    int FR = 0, FC = 0, TR = 0, TC = 0;

    FR = Move.FromRow;
    FC = Move.FromColumn;
    TR = Move.ToRow;
    TC = Move.ToColumn;

    if (Game.Board[FR][FC].PieceColor == Player)
    {
        if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == WHITE)
        {
            if (Game.Board[TR][TC].Code == NONE && TR<FR)
            {
                if (FC == TC && FR == 6 && (TR == (FR - 1) || TR == (FR - 2)))
                {
                    return true;
                }
                else if (FC == TC && TR == (FR - 1))
                {
                    return true;
                }
                else if (TR == 2 && FR == 3 && Game.Board[3][TC].PieceColor == BLACK && Game.Board[3][TC].Code == PAWN && Game.Board[2][TC].MoveCount == 0 && ((FC - TC == 1) || (TC - FC == 1)))
                {
                    Game.en_passant =PAWN;
                    Game.Board[3][TC].Code = NONE;
                    return true;

                }
                else
                {
                    return false;
                }

            }
            else if (Game.Board[TR][TC].PieceColor == BLACK && TC != FC && TR < FR)
            {
                if (FR - TR == 1 && (FC - TC == 1 || TC - FC == 1))
                {
                    return true;
                }
                else
                    return false;
            }
            else
                return false;

        }

        else if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == BLACK)
        {
            if (Game.Board[TR][TC].Code == NONE && TR > FR)
            {
                if (FC == TC && FR == 1 && (TR == (FR + 1) || TR == (FR + 2)))
                {
                    return true;
                }
                else if (FC == TC && TR == (FR + 1))
                {
                    return true;
                }
                else if (TR == 5 && FR == 4  && Game.Board[4][TC].PieceColor == WHITE && Game.Board[4][TC].Code == PAWN && Game.Board[5][TC].MoveCount == 0 && ((FC - TC == 1)|| (TC - FC == 1)))
                {
                    Game.en_passant = PAWN;
                    Game.Board[4][TC].Code = NONE;
                    return true;

                }
                else
                    return false;

            }
            else if (Game.Board[TR][TC].PieceColor == WHITE && TC != FC && TR > FR)
            {
                if (TR - FR == 1 && ((FC - TC == 1) || (TC - FC == 1)))
                {
                    return true;
                }
                else
                    return false;
            }
            else
                return false;


        }

        else if (Game.Board[FR][FC].Code == ROOK)
        {
            if (Game.Board[TR][TC].Code == NONE || (Game.Board[FR][FC].PieceColor != Game.Board[TR][TC].PieceColor))
            {
                if (TR == FR && TC > FC)
                {
                    for (int i = FC + 1; i < TC; i++)
                    {
                        if (Game.Board[TR][i].Code != NONE)
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else if (TR == FR && TC < FC)
                {
                    for (int i = TC + 1; i < FC; i++)
                    {
                        if (Game.Board[TR][i].Code != NONE)
                        {
                            return false;
                        }
                    }
                    return true;


                }
                else if (TC == FC && TR > FR)
                {
                    for (int i = FR + 1; i < TR; i++)
                    {
                        if (Game.Board[i][TC].Code != NONE)
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else if (TC == FC && TR < FR)
                {

                    for (int i = TR + 1; i < FR; i++)
                    {
                        if (Game.Board[i][TC].Code != NONE)
                        {
                            return false;
                        }
                    }

                    return true;

                }

            }
            return false;

        }

        else if (Game.Board[FR][FC].Code == KING)
        {
            if (Game.Board[TR][TC].Code == NONE || Game.Board[FR][FC].PieceColor != Game.Board[TR][TC].PieceColor)
            {
                if (TR == FR && (TC == FC - 1 || TC == FC + 1))
                {
                    return true;
                   
                }
                else if (TC == FC && (TR == FR - 1 || TR == FR + 1))
                {
                   
                    return true; 
                    
                }
                else if (TR == FR + 1 && (TC == FC + 1 || TC == FC - 1))
                {
                    return true;
                }
                else if (TR == FR - 1 && (TC == FC + 1 || TC == FC - 1))
                {
                    return true;
                }
                else if (Game.Board[TR][TC].Code == NONE && Game.Board[FR][FC].PieceColor == WHITE &&( TC-FC==2||FC-TC==2))
                {
                    int C1 = 0, C2 = 0;
                    if (TR == 7 && TC == 2 && Game.Board[7][1].Code == Game.Board[7][2].Code == Game.Board[7][3].Code == NONE && Game.Board[7][0].Code == ROOK && Game.Board[7][0].PieceColor ==WHITE)
                    {
                        Game.Board[7][3].Code = KING;
                        Game.Board[7][3].PieceColor = WHITE;
                        Game.Board[7][4].Code = NONE;

                        C1 = isfacingCheck(Game, Move, Game.TurningPlayer);
                        if (Game.Check == 0)
                        {
                            Game.Board[7][3].Code = NONE;
                            Game.Board[7][2].Code = KING;
                            Game.Board[7][2].PieceColor = WHITE;

                            C2 = isfacingCheck(Game, Move, Game.TurningPlayer);
                            if (Game.Check == 0)
                            {
                                Game.Board[7][3].Code = ROOK;
                                Game.Board[7][3].PieceColor = WHITE;
                                Game.Board[7][4].Code = KING;
                                Game.Board[7][4].PieceColor = WHITE;
                                Game.Board[7][0].Code = Game.Board[7][1].Code  = Game.Board[7][2].Code = NONE;


                                return true;
                            }
                            else
                            {
                                Game.Board[7][4].Code = KING;
                                Game.Board[7][4].PieceColor = Game.Board[7][0].PieceColor = WHITE;
                                Game.Board[7][0].Code = ROOK;
                                Game.Board[7][1].Code = Game.Board[7][2].Code = Game.Board[7][3].Code = NONE;
                                return false;
                            }
                        }
                        else
                        {
                            Game.Board[7][4].Code = KING;
                            Game.Board[7][4].PieceColor = WHITE;
                            Game.Board[7][3].Code = NONE;
                            return false;
                        }

                    }
                    else if (TR == 7 && TC == 6 && Game.Board[7][5].Code == NONE && Game.Board[7][6].Code == NONE && Game.Board[7][7].Code == ROOK && Game.Board[7][7].PieceColor == WHITE)
                    {
                        Game.Board[7][5].Code = KING;
                        Game.Board[7][5].PieceColor = WHITE;
                        Game.Board[7][4].Code = NONE;

                        C1 = isfacingCheck(Game, Move, Game.TurningPlayer);
                        if (Game.Check == 0)
                        {
                            Game.Board[7][5].Code = NONE;
                            Game.Board[7][6].Code = KING;
                            Game.Board[7][6].PieceColor = WHITE;

                            C2 = isfacingCheck(Game, Move, Game.TurningPlayer);
                            if (Game.Check == 0)
                            {
  
                                Game.Board[7][5].Code = ROOK;
                                Game.Board[7][4].PieceColor = Game.Board[7][5].PieceColor = WHITE;
                                Game.Board[7][4].Code = KING;
                                Game.Board[7][6].Code = Game.Board[7][7].Code = NONE;
                                return true;
                            }
                            else
                            {
                                Game.Board[7][4].Code = KING;
                                Game.Board[7][4].PieceColor = Game.Board[7][7].PieceColor = WHITE;
                                Game.Board[7][7].Code = ROOK;
                                Game.Board[7][5].Code = Game.Board[7][6].Code = NONE;
                                return false;
                            }
                        }
                        else
                        {
                            Game.Board[7][4].Code = KING;
                            Game.Board[7][4].PieceColor = WHITE;
                            Game.Board[7][5].Code = NONE;
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else if (Game.Board[TR][TC].Code == NONE && Game.Board[FR][FC].PieceColor == BLACK && (TC - FC == 2 || FC - TC == 2))
                {
               
                if (TR == 0 && TC == 2 && Game.Board[0][1].Code == Game.Board[0][2].Code == Game.Board[0][3].Code == NONE && Game.Board[0][0].Code == ROOK && Game.Board[0][0].PieceColor == BLACK)
                {
                    Game.Board[0][3].Code = KING;
                    Game.Board[0][3].PieceColor =BLACK;
                    Game.Board[0][4].Code = NONE;

                    isfacingCheck(Game, Move, Game.TurningPlayer);
                    if (Game.Check == 0)
                    {
                        Game.Board[0][3].Code = NONE;
                        Game.Board[0][2].Code = KING;
                        Game.Board[0][2].PieceColor = BLACK;

                        isfacingCheck(Game, Move, Game.TurningPlayer);
                        if (Game.Check == 0)
                        {
                            Game.Board[0][0].Code = Game.Board[0][1].Code = Game.Board[0][2].Code = NONE;
                            Game.Board[0][3].Code = ROOK;
                            Game.Board[0][4].Code = KING;
                            Game.Board[0][3].PieceColor  = Game.Board[0][4].PieceColor = BLACK;
                            return true;
                        }
                        else
                        {
                            Game.Board[0][0].Code = ROOK;
                            Game.Board[0][1].Code = Game.Board[0][2].Code = Game.Board[0][3].Code = NONE;
                            Game.Board[0][4].Code = KING;
                            Game.Board[0][4].PieceColor = Game.Board[0][0].PieceColor = WHITE;
                           
                            return false;
                        }
                    }
                    else
                    {
                        Game.Board[0][4].Code = KING;
                        Game.Board[0][4].PieceColor = BLACK;
                        Game.Board[0][3].Code = NONE;
                        return false;
                    }

                }
                else if (TR == 0 && TC == 6 &&  Game.Board[0][6].Code == NONE && Game.Board[0][5].Code == NONE && Game.Board[0][7].Code == ROOK && Game.Board[0][7].PieceColor == BLACK)
                {
                    Game.Board[0][4].Code = NONE;
                    Game.Board[0][5].Code = KING;
                    Game.Board[0][5].PieceColor = BLACK;

                     isfacingCheck(Game, Move, Game.TurningPlayer);
                    if (Game.Check == 0)
                    {
                        Game.Board[0][5].Code = NONE;
                        Game.Board[0][6].Code = KING;
                        Game.Board[0][6].PieceColor = BLACK;

                        isfacingCheck(Game, Move, Game.TurningPlayer);
                        if (Game.Check == 0)
                        {
                            Game.Board[0][7].Code = NONE;
                            Game.Board[0][5].Code = ROOK;
                            Game.Board[0][4].Code = KING;
                            Game.Board[0][5].PieceColor = Game.Board[0][4].PieceColor = BLACK;
                            
                            return true;
                        }
                        else
                        {
                            Game.Board[0][4].Code = KING;
                            Game.Board[0][4].PieceColor = Game.Board[0][7].PieceColor = BLACK;
                            Game.Board[0][7].Code = ROOK;
                            Game.Board[0][5].Code = Game.Board[0][6].Code  = NONE;
                            return false;
                        }
                    }
                    else
                    {
                        Game.Board[0][4].Code = KING;
                        Game.Board[0][4].PieceColor = BLACK;
                        Game.Board[0][5].Code = NONE;
                        return false;
                    }
                }
                else
                    return false;
                }
               
            }
            return false;


        }

        else if (Game.Board[FR][FC].Code == KNIGHT)
        {
            if (Game.Board[TR][TC].Code == NONE || (Game.Board[FR][FC].PieceColor != Game.Board[TR][TC].PieceColor))
            {
                if (TR - FR == 2 && ((TC == FC + 1) || (FC == TC + 1)))
                {
                    return true;
                }
                else if (FR - TR == 2 && ((TC == FC + 1) || (FC == TC + 1)))
                {
                    return true;
                }
                else if (TC - FC == 2 && ((TR == FR + 1) || (FR == TR + 1)))
                {
                    return true;
                }
                else if (FC - TC == 2 && ((TR == FR + 1) || (FR == TR + 1)))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
                return false;
        }

        else if (Game.Board[FR][FC].Code == BISHOP)
        {
            if (Game.Board[TR][TC].Code == NONE || (Game.Board[FR][FC].PieceColor != Game.Board[TR][TC].PieceColor))
            {
                //1ST QUADRANT
                if (FR > TR && FC < TC && (FR - TR) == (TC - FC))
                {

                    if (TC - FC == 1)
                    {
                        return true;
                    }
                    else
                    {
                        for (FR = FR - 1, FC = FC + 1; TR < FR; FR--, FC++)
                        {
                            // Game.V.push_back(FR);
                            // Game.V.push_back(FC);
                            if (Game.Board[FR][FC].Code != NONE)
                            {
                                return false;
                            }


                        }
                        return true;

                    }
                  


                }
                //2ND QUADRANT
                else if (FR > TR && FC > TC && (FR - TR == FC - TC))
                {
                    if (FR - TR == 1)
                    {
                        return true;

                    }
                    else
                    {
                        for (FR = FR - 1, FC = FC - 1; TR < FR; FR--, FC--)
                        {

                            if (Game.Board[FR][FC].Code != NONE)
                            {
                                return false;
                            }

                        }
                        return true;
                    }
                  
                }
                //3RD QUADRANT
                else if (FR < TR && FC > TC && (TR - FR == FC - TC))
                {
                    if (TR - FR == 1)
                    {
                        return true;

                    }
                    else
                    {
                        for (FR = FR + 1, FC = TC - 1; FR < TR; FR++, FC--)
                        {

                            if (Game.Board[FR][FC].Code != NONE)
                            {
                                return false;
                            }

                        }
                        return true;
                    }

                   
                }
                //4TH QUADRANT
                else if (FR < TR && FC < TC && (TR - FR) == (TC - FC))
                {
                    if (TR - FR == 1)
                    {
                        return true;

                    }
                    else
                    {
                        for (FR = FR + 1, FC = FC + 1; FR < TR; FR++, FC++)
                        {

                            if (Game.Board[FR][FC].Code != NONE)
                            {
                                return false;
                            }

                        }
                        return true;
                    
                    }

                }

            }
            else
                return false;
          

        }
        else if (Game.Board[FR][FC].Code == QUEEN)
        {
            if (Game.Board[TR][TC].Code == NONE || (Game.Board[FR][FC].PieceColor != Game.Board[TR][TC].PieceColor))
            {
                if (TR == FR && TC > FC)
                {
                    for (int i = FC + 1; i < TC; i++)
                    {
                        if (Game.Board[TR][i].Code != NONE)
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else if (TR == FR && TC < FC)
                {
                    for (int i = TC + 1; i < FC; i++)
                    {
                        if (Game.Board[TR][i].Code != NONE)
                        {
                            return false;
                        }
                    }
                    return true;


                }
                else if (TC == FC && TR > FR)
                {
                    for (int i = FR + 1; i < TR; i++)
                    {
                        if (Game.Board[i][TC].Code != NONE)
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else if (TC == FC && TR < FR)
                {

                    for (int i = TR + 1; i < FR; i++)
                    {
                        if (Game.Board[i][TC].Code != NONE)
                        {
                            return false;
                        }
                    }

                    return true;

                }
                //1ST QUADRANT
                else if (FR > TR && FC < TC && (FR - TR) == (TC - FC))
                {

                    if (TC - FC == 1)
                    {
                        return true;
                    }
                    else
                    {
                        for (FR = FR - 1, FC = FC + 1; TR < FR; FR--, FC++)
                        {
                            // Game.V.push_back(FR);
                            // Game.V.push_back(FC);
                            if (Game.Board[FR][FC].Code != NONE)
                            {
                                return false;
                            }


                        }
                        return true;

                    }



                }
                //2ND QUADRANT
                else if (FR > TR && FC > TC && (FR - TR == FC - TC))
                {
                    if (FR - TR == 1)
                    {
                        return true;

                    }
                    else
                    {
                        for (FR = FR - 1, FC = FC - 1; TR < FR; FR--, FC--)
                        {

                            if (Game.Board[FR][FC].Code != NONE)
                            {
                                return false;
                            }

                        }
                        return true;
                    }

                }
                //3RD QUADRANT
                else if (FR < TR && FC > TC && (TR - FR == FC - TC))
                {
                    if (TR - FR == 1)
                    {
                        return true;

                    }
                    else
                    {
                        for (FR = FR + 1, FC = TC - 1; FR < TR; FR++, FC--)
                        {

                            if (Game.Board[FR][FC].Code != NONE)
                            {
                                return false;
                            }

                        }
                        return true;
                    }


                }
                //4TH QUADRANT
                else if (FR < TR && FC < TC && (TR - FR) == (TC - FC))
                {
                    if (TR - FR == 1)
                    {
                        return true;

                    }
                    else
                    {
                        for (FR = FR + 1, FC = FC + 1; FR < TR; FR++, FC++)
                        {

                            if (Game.Board[FR][FC].Code != NONE)
                            {
                                return false;
                            }

                        }
                        return true;

                    }

                }
              

            }
             else
                return false;


        }
        else
           return false;

    }
    else
       return false;
    
   return false;
}



int MakeMove(GameData& Game, chessMove Move){
    //Function to make a move on the board
    // It will return 0 if the move is valid and a code of error to specify why the move is not valid otherwise
    int FR = 0, FC = 0, TR = 0, TC = 0;
    
    FR = Move.FromRow ;
    FC = Move.FromColumn ;
    TR = Move.ToRow ;
    TC = Move.ToColumn ; 
 
   
    if (!isValidMove(Game, Move, Game.TurningPlayer))
    {
        return 1;
    }
    else
    {
        
        Game.Board[TR][TC].PieceColor = Game.Board[FR][FC].PieceColor;
        Game.Board[TR][TC].Code = Game.Board[FR][FC].Code;
        Game.Board[FR][FC].Code = NONE;
        Game.Board[FR][FC].PieceColor = BLACK;
       
        isfacingCheck(Game, Move, Game.TurningPlayer);
        
        if (Game.TurningPlayer == BLACK)
        {
            Game.TurningPlayer = WHITE;
            Game.notPlayer = BLACK;
        }
        else
        {
            Game.TurningPlayer = BLACK;
            Game.notPlayer = WHITE;
        }

        Game.Board[TR][TC].MoveCount++;
       
        return 0;

    }

    return -1;
}

void initGame(GameData& Game){

    for(int r = 0; r < 2; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].PieceColor = BLACK;

    for(int r = 2; r < 6; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].Code = NONE;

    for(int r = 6; r < 8; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].PieceColor = WHITE;


    Game.Board[0][0].Code = Game.Board[0][7].Code = ROOK;
    Game.Board[7][0].Code = Game.Board[7][7].Code = ROOK;

    Game.Board[0][1].Code = Game.Board[0][6].Code = KNIGHT;
    Game.Board[7][1].Code = Game.Board[7][6].Code = KNIGHT;

    Game.Board[0][2].Code = Game.Board[0][5].Code = BISHOP;
    Game.Board[7][2].Code = Game.Board[7][5].Code = BISHOP;

    Game.Board[0][3].Code = Game.Board[7][3].Code = QUEEN;
    Game.Board[0][4].Code = Game.Board[7][4].Code = KING;

    for(int c= 0; c < 8; c++ )
        Game.Board[1][c].Code = Game.Board[6][c].Code = PAWN;

    Game.TurningPlayer = WHITE;
   
    Game.MoveHistory = vector<chessMove>(1);
    return;
}


int isfacingCheck(GameData& Game, chessMove Move,Color Player)
{
    // This function must return true if player having Color Player is facing a check
    Color notPlayer;
    int FR = 0, FC = 0, TR = 0, TC = 0;

    FR = Move.FromRow;
    FC = Move.FromColumn;
    TR = Move.ToRow;
    TC = Move.ToColumn;
    if (Player == WHITE)
    {
        notPlayer = BLACK;
    }
    else
    {
        notPlayer = WHITE;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Game.Board[i][j].Code == KING && Game.Board[i][j].PieceColor == Player)
            {
                Move.ToRow = i;
                Move.ToColumn = j;

            }

        }

    }
    
    bool T = false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move.FromRow = i;
            Move.FromColumn = j;

            if (Game.Board[i][j].PieceColor == notPlayer)
            {
             

                T = isValidMove(Game, Move, notPlayer);

                if (T == true)
                {
                    Game.Check = 1;
                  
                    return 1;


                }
                else 
                {
                    Game.Check = 0;

                }
                

            }

        }

    }

    return 0;
}
bool isGameOver(bool Ans)
{
    return Ans;
}

bool isCheckmate(GameData& Game, Color Player, chessMove Move)
{
 int  F=0,M=0;
    bool V = false;
    PieceType present;


    for (int I = 0; I < 8; I++)
    {
        for (int J = 0; J < 8; J++)
        {
            Move.FromRow = I;
            Move.FromColumn = J;
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Move.ToRow = i;
                    Move.ToColumn = j;
                    V = isValidMove(Game, Move, Player);

                    if (Game.Board[I][J].PieceColor == Player)
                    {
                        Color presentcolor;
                        if (V == true)
                        {
                            present = Game.Board[i][j].Code;
                            presentcolor = Game.Board[i][j].PieceColor;

                            Game.Board[i][j].PieceColor = Game.Board[I][J].PieceColor;
                            Game.Board[i][j].Code = Game.Board[I][J].Code;
                            Game.Board[I][J].Code = NONE;

                            F = isfacingCheck(Game, Move, Player);

                            Game.Board[I][J].Code = Game.Board[i][j].Code;
                            Game.Board[i][j].Code = present;
                            Game.Board[i][j].PieceColor=presentcolor;

                            if (Game.Check == 0)
                            {
                                Game.ValidMoves.push_back(I);
                                Game.ValidMoves.push_back(J);
                                Game.ValidMoves.push_back(i);
                                Game.ValidMoves.push_back(j);
                            }


                        }
                    }


                }
            }


        }
    }
    
    if (Game.ValidMoves.size() < 4)
    {
        return true;
    }
    
    
    return false;

}

void UNDO(int MoveCount) {
    // A function to undo a number of moves
    return;
}

int SaveGame(string FileName) {
    //Function to save a game data into a file.
    return 0;

}

int LoadGame(string FileName) {
    // function to load games data from a file
    return 0;
}