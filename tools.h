#define MAXROW 9
#define MAXCOLUNM 9
#define MAXCHESS 40
#define MAXDIE 38
#define MAXSTEP 100

bool bu(int,int,int,int);
bool gwae(int,int,int,int);
bool shun(int,int,int,int);
bool silver(int,int,int,int);
bool gold(int,int,int,int);
bool king(int,int,int,int);
bool gioaw(int,int,int,int);
bool fei(int,int,int,int);
bool gioaw_s(int,int,int,int);
bool fei_s(int,int,int,int);
bool rule_checking(int,int,int,int,int,int [3][MAXCHESS]);//checking if the move is correct for the chess
void initial(int [3][MAXCHESS]);//initializing the checkerboard
bool whose(int);//determining the chess is whose
void change_view(int [3][MAXCHESS]);//changing the view for another player
void show_checkerboard(bool,int [3][MAXCHESS]);//show the checkerboard
bool checkmate(int [3][MAXCHESS]);//determining if the player is ckeckmate
int level_up(int);
int level_down(int);