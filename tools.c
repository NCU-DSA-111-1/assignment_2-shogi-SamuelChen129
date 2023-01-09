#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include <wchar.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include"tools.h"

bool bu(int x1,int y1,int x0,int y0)
{
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(move_x==0 && move_y==-1){return true;}//move forward 1
    else{return false;}
}
bool gwae(int x1,int y1,int x0,int y0)
{
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(move_x==1 && move_y==-2){return true;}//move forward 2 and left 1
    else if(move_x==-1 && move_y==-2){return true;}//move forward 2 and right 1
    else{return false;}
}
bool shun(int x1,int y1,int x0,int y0)
{
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(move_x==0 && move_y<0){return true;}//move forward, can't move back
    else{return false;}
}
bool silver(int x1,int y1,int x0,int y0)
{
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(move_x==1 && move_y==-1){return true;}//move forward 1 and left 1
    else if(move_x==0 && move_y==-1){return true;}//move forward 1
    else if(move_x==-1 && move_y==-1){return true;}//move forward 1 and right 1
    else if(move_x==1 && move_y==1){return true;}//move back 1 and left 1
    else if(move_x==-1 && move_y==1){return true;}//move back 1 and right 1
    else{return false;}
}
bool gold(int x1,int y1,int x0,int y0)
{
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(move_x==1 && move_y==-1){return true;}//move forward 1 and left 1
    else if(move_x==0 && move_y==-1){return true;}//move forward 1
    else if(move_x==-1 && move_y==-1){return true;}//move forward 1 and right 1
    else if(move_x==1 && move_y==0){return true;}//move left 1
    else if(move_x==-1 && move_y==0){return true;}//move right 1
    else if(move_x==0 && move_y==1){return true;}//move back 1
    else{return false;}
}
bool king(int x1,int y1,int x0,int y0)
{
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(move_x<2 && move_x>-2 && move_y<2 && move_y>-2){return true;}//move no more than 1 in x and y
    else{return false;}
}
bool gioaw(int x1,int y1,int x0,int y0)
{
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(abs(move_x)==abs(move_y)){return true;}//move diagnally
    else{return false;}
}
bool fei(int x1,int y1,int x0,int y0)
{
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(move_x==0 || move_y==0){return true;}//move straightly
    else{return false;}
}
bool gioaw_s(int x1,int y1,int x0,int y0)
{
    bool correct=false;
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(abs(move_x)==abs(move_y)){correct=true;}//move diagnally
    if(move_x<2 && move_x>-2 && move_y<2 && move_y>-2){correct=true;}//move no more than 1 in x and y
    return correct;
}
bool fei_s(int x1,int y1,int x0,int y0)
{
    bool correct=false;
    int move_x,move_y;
    move_x = x1-x0;
    move_y = y1-y0;
    if(move_x==0 || move_y==0){correct=true;}//move straightly
    if(move_x<2 && move_x>-2 && move_y<2 && move_y>-2){correct=true;}//move no more than 1 in x and y
    return correct;
}
//initializing the checkerboard
void initial(int board[3][MAXCHESS])
{
    int row,col,type;
    //put "bu" chesses
    row=7,col=9,type=0;
    for(int i=0;i<9;i++){        
        board[0][i]=row;
        board[1][i]=col;
        board[2][i]=type;
        col--;
    }
    row=3;col=9;type=10;
    for(int i=9;i<18;i++){        
        board[0][i]=row;
        board[1][i]=col;
        board[2][i]=type;
        col--;
    }
    //put "shun" chesses
    row=9;col=9;type=1;
    board[0][18]=row;
    board[1][18]=col;
    board[2][18]=type;
    row=9;col=1;type=1;
    board[0][19]=row;
    board[1][19]=col;
    board[2][19]=type;
    row=1;col=9;type=11;
    board[0][20]=row;
    board[1][20]=col;
    board[2][20]=type;
    row=1;col=1;type=11;
    board[0][21]=row;
    board[1][21]=col;
    board[2][21]=type;
    //put "gwae" chesses
    row=9;col=8;type=2;
    board[0][22]=row;
    board[1][22]=col;
    board[2][22]=type;
    row=9;col=2;type=2;
    board[0][23]=row;
    board[1][23]=col;
    board[2][23]=type;
    row=1;col=8;type=12;
    board[0][24]=row;
    board[1][24]=col;
    board[2][24]=type;
    row=1;col=2;type=12;
    board[0][25]=row;
    board[1][25]=col;
    board[2][25]=type;
    //put "silver" chesses
    row=9;col=7;type=3;
    board[0][26]=row;
    board[1][26]=col;
    board[2][26]=type;
    row=9;col=3;type=3;
    board[0][27]=row;
    board[1][27]=col;
    board[2][27]=type;
    row=1;col=7;type=13;
    board[0][28]=row;
    board[1][28]=col;
    board[2][28]=type;
    row=1;col=3;type=13;
    board[0][29]=row;
    board[1][29]=col;
    board[2][29]=type;
    //put "gold" chesses
    row=9;col=6;type=4;
    board[0][30]=row;
    board[1][30]=col;
    board[2][30]=type;
    row=9;col=4;type=4;
    board[0][31]=row;
    board[1][31]=col;
    board[2][31]=type;
    row=1;col=6;type=14;
    board[0][32]=row;
    board[1][32]=col;
    board[2][32]=type;
    row=1;col=4;type=14;
    board[0][33]=row;
    board[1][33]=col;
    board[2][33]=type;
    //put "king" chesses
    row=9;col=5;type=5;
    board[0][34]=row;
    board[1][34]=col;
    board[2][34]=type;
    row=1;col=5;type=15;
    board[0][35]=row;
    board[1][35]=col;
    board[2][35]=type;
    //put "gioaw" chesses
    row=8;col=8;type=6;
    board[0][36]=row;
    board[1][36]=col;
    board[2][36]=type;
    row=2;col=2;type=16;
    board[0][37]=row;
    board[1][37]=col;
    board[2][37]=type;
    //put "fei" chesses
    row=8;col=2;type=7;
    board[0][38]=row;
    board[1][38]=col;
    board[2][38]=type;
    row=2;col=8;type=17;
    board[0][39]=row;
    board[1][39]=col;
    board[2][39]=type;
}
//determining the chess is whose
bool whose(int type)
{
    if(type<10)
    {return true;}
    if(type>=20 && type<24)
    {return true;}
    if(type>=10 && type<20)
    {return false;}
    if(type>=30 && type<34)
    {return false;}
}
//rule checking
bool rule_checking(int next_x,int next_y,int now_x,int now_y,int type,int (*board)[MAXCHESS])
{
    int chess;
    bool step_correct;
    enum chess_type {BU=0,SHUN=1,GWAE=2,SILVER=3,GOLD=4,KING=5,GIOAW=6,FEI=7,GIOAW_S=8,FEI_S=9};
    //checking if the step is correct
    //step_correct==true -> the move is legal
    //step_correct==false -> the move is illegal
    if(type>=10 && type<20){chess=type-10;}
    if(type<10){chess=type;}
    if(type>=20 && type<24){chess=4;}
    if(type>=30 && type<34){chess=4;}
    switch(chess)
    {
        case BU:
            step_correct = bu(next_x,next_y,now_x,now_y);
            break;
        case SHUN:
            step_correct = shun(next_x,next_y,now_x,now_y);
            //checking if there's an obstacle on shun's moving route
            for(int i=0;i<MAXCHESS;i++)
            {
                if(board[0][i]>next_y && board[0][i]<now_y && board[1][i]==now_x)
                {
                    step_correct = false;
                    break;
                }
            }
            break;
        case GWAE:
            step_correct = gwae(next_x,next_y,now_x,now_y);
            break;
        case SILVER:
            step_correct = silver(next_x,next_y,now_x,now_y);
            break;
        case GOLD:
            step_correct = gold(next_x,next_y,now_x,now_y);
            break;
        case KING:
            step_correct = king(next_x,next_y,now_x,now_y);
            break;
        case GIOAW:
            step_correct = gioaw(next_x,next_y,now_x,now_y);
            //checking if there's an obstacle on gioaw's moving route
            int dx_1,dy_1,dx_2,dy_2;
            dx_1=next_x-now_x;
            dy_1=next_y-now_y;
            for(int i=0;i<MAXCHESS;i++)
            {               
                dx_2=board[1][i]-now_x;
                dy_2=board[0][i]-now_y;
                if(abs(dx_2)==abs(dy_2) && dx_1*dx_2>0 && dy_1*dy_2>0 && abs(dx_2)<abs(dx_1))
                {
                    step_correct = false;
                    break;
                }
            }
            break;
        case FEI:
            step_correct = fei(next_x,next_y,now_x,now_y);
            //checking if there's an obstacle on fei's moving route
            int dx_3,dy_3,dx_4,dy_4;
            dx_3=next_x-now_x;
            dy_3=next_y-now_y;
            for(int i=0;i<MAXCHESS;i++)
            {
                dx_4=board[1][i]-now_x;
                dy_4=board[0][i]-now_y;
                if(next_x==now_x && board[1][i]==now_x)
                {
                    if(abs(dy_3)>abs(dy_4) && dy_3*dy_4>0 && dy_4!=0)
                    {
                        step_correct = false;
                        printf("dy_3=%d\n",dy_3);
                        printf("dy_4=%d\n",dy_4);
                        printf("correct=%d\n",step_correct);
                        break;
                    }
                }
                if(next_y==now_y && board[0][i]==now_y)
                {
                    if(abs(dx_3)>abs(dx_4) && dx_3*dx_4>0 && dx_4!=0)
                    {
                        step_correct = false;
                        break;
                    }
                }
            }
            break;
        case GIOAW_S:
            step_correct = gioaw_s(next_x,next_y,now_x,now_y);
            //checking if there's an obstacle on gioaw_s's moving route
            int dx_5,dy_5,dx_6,dy_6;
            dx_5=next_x-now_x;
            dy_5=next_y-now_y;
            if(abs(dx_5)==abs(dy_5))
            {
                for(int i=0;i<MAXCHESS;i++)
                {               
                    dx_6=board[1][i]-now_x;
                    dy_6=board[0][i]-now_y;
                    if(abs(dx_6)==abs(dy_6) && dx_5*dx_6>0 && dy_5*dy_6>0 && abs(dx_6)<abs(dx_5))
                    {
                        step_correct = false;
                        break;
                    }
                }
            }
            break;
        case FEI_S:
            step_correct = fei_s(next_x,next_y,now_x,now_y);
            //checking if there's an obstacle on fei_s's moving route
            int dx_7,dy_7,dx_8,dy_8;
            dx_7=next_x-now_x;
            dy_7=next_y-now_y;
            if(dx_7==0 || dy_7==0)
            {
                for(int i=0;i<MAXCHESS;i++)
                {
                    dx_8=board[1][i]-now_x;
                    dy_8=board[0][i]-now_y;
                    if(next_x==now_x && board[1][i]==now_x)
                    {
                        if(abs(dy_7)>abs(dy_8) && dy_7*dy_8>0 && dy_8!=0)
                        {
                            step_correct = false;
                            break;
                        }
                    }
                    if(next_y==now_y && board[0][i]==now_y)
                    {
                        if(abs(dx_7)>abs(dx_8) && dx_7*dx_8>0 && dx_8!=0)
                        {
                            step_correct = false;
                            break;
                        }
                    }
                }
            }
            break;
    }
    return step_correct;
}
//changing view for another player
void change_view(int board[3][MAXCHESS])
{
    int tmp[3][MAXCHESS];
    for(int i=0;i<MAXCHESS;i++)
    {
        tmp[0][i]=MAXROW+1-board[0][i];
        tmp[1][i]=MAXCOLUNM+1-board[1][i];

        board[0][i]=tmp[0][i];
        board[1][i]=tmp[1][i];
    }
}
//show the checkerboard
void show_checkerboard(bool player,int board[3][MAXCHESS])
{
    bool have_chess=0;
    setlocale(LC_ALL, "chs");
    if(player){wprintf(L" _9 _ _8 _ _7 _ _6 _ _5 _ _4 _ _3 _ _2 _ _1 _\n");}
    if(!player){wprintf(L" _1 _ _2 _ _3 _ _4 _ _5 _ _6 _ _7 _ _8 _ _9 _\n");}
    for(int j=1;j<MAXROW+1;j++)
    {
        for(int k=1;k<MAXCOLUNM+1;k++)
        {
            printf("|");
            for(int i=0;i<MAXCHESS;i++)
            {
                if(board[0][i]==j && board[1][i]==10-k)
                {
                    if(whose(board[2][i])){
                        switch(board[2][i])
                        {
                            case 0:
                                wprintf(L"\033[34m_步_\033[m");
                                break;
                            case 1:
                                wprintf(L"\033[34m_香_\033[m");
                                break;
                            case 2:
                                wprintf(L"\033[34m_桂_\033[m");
                                break;
                            case 3:
                                wprintf(L"\033[34m_銀_\033[m");
                                break;
                            case 4:
                                wprintf(L"\033[34m_金_\033[m");
                                break;
                            case 5:
                                wprintf(L"\033[34m_王_\033[m");
                                break;
                            case 6:
                                wprintf(L"\033[34m_角_\033[m");
                                break;
                            case 7:
                                wprintf(L"\033[34m_飛_\033[m");
                                break;
                            case 8:
                                wprintf(L"\033[34m_馬_\033[m");
                                break;
                            case 9:
                                wprintf(L"\033[34m_龍_\033[m");
                                break;
                            case 20:
                                wprintf(L"\033[34m_金_\033[m");
                                break;
                            case 21:
                                wprintf(L"\033[34m_金_\033[m");
                                break;
                            case 22:
                                wprintf(L"\033[34m_金_\033[m");
                                break;
                            case 23:
                                wprintf(L"\033[34m_金_\033[m");
                                break;
                        }  
                    }//blue word
                    if(!whose(board[2][i])){
                        switch(board[2][i]-10)
                        {
                            case 0:
                                wprintf(L"\033[31m_步_\033[m");
                                break;
                            case 1:
                                wprintf(L"\033[31m_香_\033[m");
                                break;
                            case 2:
                                wprintf(L"\033[31m_桂_\033[m");
                                break;
                            case 3:
                                wprintf(L"\033[31m_銀_\033[m");
                                break;
                            case 4:
                                wprintf(L"\033[31m_金_\033[m");
                                break;
                            case 5:
                                wprintf(L"\033[31m_王_\033[m");
                                break;
                            case 6:
                                wprintf(L"\033[31m_角_\033[m");
                                break;
                            case 7:
                                wprintf(L"\033[31m_飛_\033[m");
                                break;
                            case 8:
                                wprintf(L"\033[31m_馬_\033[m");
                                break;
                            case 9:
                                wprintf(L"\033[31m_龍_\033[m");
                                break;
                            case 20:
                                wprintf(L"\033[31m_金_\033[m");
                                break;
                            case 21:
                                wprintf(L"\033[31m_金_\033[m");
                                break;
                            case 22:
                                wprintf(L"\033[31m_金_\033[m");
                                break;
                            case 23:
                                wprintf(L"\033[31m_金_\033[m");
                                break;
                        }
                    }//red word
                    have_chess=1;
                }
            }
            if(!have_chess)
            {
                printf("_  _");
            }
            have_chess=0;
        }
        printf("|");
        switch(j)
        {
            case 1:
                if(player)
                {wprintf(L"一");}
                if(!player)
                {wprintf(L"九");}
                break;
            case 2:
                if(player)
                {wprintf(L"二");}
                if(!player)
                {wprintf(L"八");}
                break;
            case 3:
                if(player)
                {wprintf(L"三");}
                if(!player)
                {wprintf(L"七");}
                break;
            case 4:
                if(player)
                {wprintf(L"四");}
                if(!player)
                {wprintf(L"六");}
                break;
            case 5:
                wprintf(L"五");
                break;
            case 6:
                if(player)
                {wprintf(L"六");}
                if(!player)
                {wprintf(L"四");}
                break;
            case 7:
                if(player)
                {wprintf(L"七");}
                if(!player)
                {wprintf(L"三");}
                break;
            case 8:
                if(player)
                {wprintf(L"八");}
                if(!player)
                {wprintf(L"二");}
                break;
            case 9:
                if(player)
                {wprintf(L"九");}
                if(!player)
                {wprintf(L"一");}
                break;
        }
        printf("\n");
    }
}
bool checkmate(int board[3][MAXCHESS])
{
    int king1_row,king1_col;
    int king2_row,king2_col;
    bool re=false;
    //find the position of kings
    for(int i=0;i<MAXCHESS;i++)
    {
        if(board[2][i]==5)
        {
            king1_row=board[0][i];
            king1_col=board[1][i];
        }
        if(board[2][i]==15)
        {
            king2_row=board[0][i];
            king2_col=board[1][i];
        }
    }
    //checking if it's checkmate
    for(int j=0;j<MAXCHESS;j++)
    {
        if(whose(board[2][j]))
        {
            re=rule_checking(king2_col,king2_row,board[1][j],board[0][j],board[2][j],board);
            if(re)
            {
                break;
            }
        }
        if(!whose(board[2][j]))
        {
            re=rule_checking(king1_col,king1_row,board[1][j],board[0][j],board[2][j],board);
            if(re)
            {
                break;
            }
        }
    }
    return re;
}
int level_up(int type)
{
    int result;
    if(type>=0 && type<=3) 
    {
        result=type+20;
    }
    if(type>=10 && type<=13) 
    {
        result=type+20;
    }
    if(type==6)
    {
        result=8;
    }
    if(type==7)
    {
        result=9;
    }
    if(type==16)
    {
        result=18;
    }
    if(type==17)
    {
        result=19;
    }
    return result;
}
int level_down(int type)
{
    int result;
    if(type>=20 && type<=23) 
    {
        result=type-20;
    }
    if(type>=30 && type<=33) 
    {
        result=type-20;
    }
    if(type==8)
    {
        result=6;
    }
    if(type==9)
    {
        result=7;
    }
    if(type==18)
    {
        result=16;
    }
    if(type==19)
    {
        result=17;
    }
    return result;
}