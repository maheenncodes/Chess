#include<string>
#include<vector>
using namespace std;
#ifndef GAME_DATA
#define GAME_DATA

	// Following enum have been defined to represent some of the commonly used vocabulary used in Chess
    enum PieceType {NONE, PAWN, ROOK, BISHOP, KNIGHT, QUEEN, KING};
    enum Color {BLACK, WHITE};

    struct chessPiece{
        PieceType Code = NONE;
        Color PieceColor = BLACK;
		int MoveCount = 0;  // How Many moves have this piece made needed for castling, En Passant, and first move of pawn
    };

    // The following struct is being used for multiple purposes i.e. to represent a single move, to specify pawn promotion if applicable and to save information of piece being captured for keeping a history of moves for undo option

	struct chessMove {
        short FromRow = 0, FromColumn = 0, ToRow = 0, ToColumn = 0; // Variables to specify the move
		PieceType PawnPromotedTo = PAWN; // A variable being kept to indicate the promotion of pawn into a higher piece
    };

    struct GameData{
        int Check = 0;
        chessPiece Board[8][8]; // INITIALLY WHITE ON HIGHER ROWS AND BLACK ON LOWER ROWS {In this implementation this is a hard coded rule}
        Color TurningPlayer = WHITE; // START WITH WHITE PLAYER
        Color notPlayer = BLACK;
		vector<chessMove> MoveHistory;  // Needed to give an undo option and saving a game for future use
       
        vector<int> ValidMoves ;
        PieceType en_passant;// A variable to indicate the piece being captured in en passant move

    };
 
    void PromotePawn(GameData& Game, char P, chessMove Move);
    int isfacingCheck(GameData& Game, chessMove Move, Color Player);

    bool isValidMove(GameData& Game, chessMove Move, Color Player);

    int MakeMove(GameData& Game, chessMove Move);

    bool isCheckmate(GameData& Game, Color Player, chessMove Move);

    void initGame(GameData& Game);

	void UNDO(int MoveCount); // A function to undo a number of moves specified by the MoveCount parameter
   // void checking(GameData& Game, Color Player, chessMove Move);
	// Following functions will be used to save an unfinished game onto into a file and load a previously stored game from a file
	int SaveGame(string FileName);
	int LoadGame (string FileName);

#endif
