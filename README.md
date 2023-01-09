# SHOUGI 

## Introduction
This is a program of a shougi game.  
You can do two things in this program:  
* open a new game and play it (for two real players)
* load the recorded game and watch the process of the game

## How to Compile
1. open the terminal
2. enter the instruction below in the terminal
```
g++ SHOUGI.c tools.c -o SHOUGI
```
## open a new game
1. After compiling , enter the instruction below:
```
./SHOUGI.exe -n -s new_game_file_name
```
2. during a game , there are 4 things players can do:
* moving a chess on the checkerboard and enhanced the ability of the chess if the player wants and has the right to do it. (enter 'a')
* put a chess that has been eaten.(enter 'd')
* undo the last step.(enter '0')
* save the process of the game.(enter 's').  
The saved data will be stored in the file that has the name which is "new_game_file_name".
## load the recorded game 
1. After compiling , enter the instruction below("old_game_file_name" is the name of the file of the game you want to replay.):
```
./SHOUGI.exe -l old_game_file_name
```
2. you can _enter 'f'_ to show the next step or _enter 'b'_ to show the last step of the the game.
## important funcitons used in this program
### show_checkerboard
this function shows the distribution of the chesses on the board. Players can determine the move of a chess by the row and column labels on the edge.   
```sh
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
```
### change_view
this function can changing the view of the checkboard for the different players,
another reason to use this function is to make the 
```sh
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
```
### rule_checking  
this function can judge the move of the chess, if the move of the chess is not correspond to the moving rules of the type of the chess , then it will return "false" to the main function and this move won't be implemented.
```sh
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
```
### checkmate
this function is checking that if one or both of the kings are checkmated , the way of checking of this function is to check every chess on the board if one of them pose threat to the kings. Once the "checkmate" situation occurs, this function will return ture to the main function and the sign of "checkmate" will be show to the players.
```sh
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
```
## the works in the main function
* _read the loaded file_  
If you enter "-l old_game_file_name", the program will load the information of every step in the old game and stored it into an stack.The stack I use calls "process".A "process" means a step in the game,it contains the information listed below :
1.  the sequence of the step
2.  the number of the moved chess in this step(I give every chess with a correspond number in the game, from 0 to 39)
3.  the type of the moved chess in this step
4. the position of the moved chess before moving 
5. the position of the moved chess after moving
6. the number of the eaten chess
7. the type of the eaten chess
8. if the moved chess is enhanced
9. the type of the action (move chess、eat chess or put back a chess)
```sh
int top_of_step_stack;
if(instr[0][1]=='l')
{
    char data[100];
    int count=0;
    FILE *file;
    file=fopen(instr[2],"r");
    for(int i=0;i<11;i++){fscanf(file,"%s",&data);}
    while(!feof(file))
    {
        count++;
        fscanf(file,"%d",&process[count].step);
        fscanf(file,"%d",&process[count].num);
        fscanf(file,"%d",&process[count].type);
        fscanf(file,"%d",&process[count].o_row);
        fscanf(file,"%d",&process[count].o_col);
        fscanf(file,"%d",&process[count].d_row);
        fscanf(file,"%d",&process[count].d_col);
        fscanf(file,"%d",&process[count].eat_num);
        fscanf(file,"%d",&process[count].eat_type);
        fscanf(file,"%s",&process[count].enhanced);
        fscanf(file,"%s",&process[count].act);
    }
    top_of_step_stack=count;
}
```
* _replay the load file_  
According to the information saved in the stack, you can see every step in the old game shows on the checkerboard. There is a variable calls "step", it means the sequence of the step is showing now. If you enter 'f',step will increase and you can see the next step. If you enter 'b',step will decrease and you can see the last step.
```sh
while(instr[0][1]=='l'){
    printf("enter \033[32mf\033[m for next step\n");
    printf("enter \033[32mb\033[m for last step\n");
    printf("enter \033[32mq\033[m if you want to quit\n");
    printf("->");
    scanf("%s",&act);
    if(act=='q'){break;}
    if(act=='b')
    {
        if(step==1)
        {
            printf("this is the first step!\n");
            show_checkerboard(player,board);
            continue;
        }
        step--;
        if(process[step].act=='a' || process[step].act=='e')
        {
            board[0][process[step].num]=process[step].o_row;
            board[1][process[step].num]=process[step].o_col;
            if(process[step].act=='e')
            {
                board[0][process[step].eat_num]=process[step].d_row;
                board[1][process[step].eat_num]=process[step].d_col;
                board[2][process[step].eat_num]=process[step].eat_type;                                       
            }
        }
        if(process[step].act=='d')
        {
            board[0][process[step].num]=0;
            board[1][process[step].num]=0;
        }
        if(process[step].enhanced=='y')
        {
            board[2][process[step].num]=level_down(board[2][process[step].num]);
        }
        }
    if(act=='f')
    {
        if(step==top_of_step_stack)
        {
            printf("no more step!\n");
            show_checkerboard(player,board);
            continue;
        }
        if(process[step].act=='a' || process[step].act=='e')
        {
            board[0][process[step].num]=process[step].d_row;
            board[1][process[step].num]=process[step].d_col;
            if(process[step].act=='e')
            {
                board[0][process[step].eat_num]=0;
                board[1][process[step].eat_num]=0;                                       
            }
        }
        if(process[step].act=='d')
        {
            board[0][process[step].num]=process[step].d_row;
            board[1][process[step].num]=process[step].d_col;
            board[2][process[step].num]=process[step].type;
        }
        if(process[step].enhanced=='y')
        {
            board[2][process[step].num]=level_up(board[2][process[step].num]);
        }
        step++;
    }  
    show_checkerboard(player,board);       
}
```
* _put the eaten chess_  
During a new game, if you wants to put the chess that you have eaten,
you can enter 'd',and choose the chess from a stack you want to put.
There is a stack calls 'die',it stores all the chesses that have been eaten. There is another stack calls "chess_for_put", it collects the eaten chess that can be put on the checkerboard by the correspond player, and the chess choosed to put by the player is from this stack instead of the "die" stack .(you can only put the chess eaten by you) 
```sh
        if(act=='d')
        {   
            int n=0;
            int chess_for_put[MAXDIE]={40};  
            n=0;
            for(int i=0;i<eat;i++)
            {
                if(player && whose(board[2][die[i]]))
                {
                    chess_for_put[n]=die[i];
                    n++;
                }
                if(!player && !whose(board[2][die[i]]))
                {
                    chess_for_put[n]=die[i];
                    n++;
                }
            }
            for(int i=0;i<n;i++)
            {
                int tmp;
                if(player)
                {
                    tmp=board[2][chess_for_put[i]];
                }
                if(!player)
                {
                    tmp=board[2][chess_for_put[i]]-10;
                }
                printf("%d",i);
                switch(tmp)
                {
                    setlocale(LC_CTYPE, "");
                    case 0:
                        wprintf(L"步 ");
                        break;
                    case 1:
                        wprintf(L"香 ");
                        break;
                    case 2:
                        wprintf(L"桂 ");
                        break;
                    case 3:
                        wprintf(L"銀 ");
                        break;
                    case 4:
                        wprintf(L"金 ");
                        break;
                    case 5:
                        wprintf(L"王 ");
                        break;
                    case 6:
                        wprintf(L"角 ");
                        break;
                    case 7:
                        wprintf(L"飛 ");
                        break;
                }
            }
            printf("\n");
            if(n>0)
            {
                printf("enter the number on the left of the chess you want put:");
                int put,put_row,put_col;
                scanf("%d",&put);
                printf("input the position you want to put to\n");
                wprintf(L"段:");
                scanf("%d",&put_row);
                wprintf(L"筋:");
                scanf("%d",&put_col);
                //checking if the desired position is out of the checkerboard
                if(put_col>9 || put_col<1 || put_row>9 || put_row<1)
                {
                    show_checkerboard(player,board);
                    printf("the position is out of the checkerboard!\n");
                    continue;
                }
                //checking if the desired position has any chess on it
                bool position_has_chess=false;
                for(int i=0;i<MAXCHESS;i++)
                {
                    if(board[0][i]==put_row && board[1][i]==put_col)
                    {
                        position_has_chess=true;
                        break;
                    }
                }
                if(position_has_chess)
                {
                    show_checkerboard(player,board);
                    printf("the position is already has chess!\n");
                    continue;
                }

                board[0][chess_for_put[put]]=put_row;
                board[1][chess_for_put[put]]=put_col;

                //checking if it's checkmate

                if(!player)
                {change_view(board);}
                if(checkmate(board))
                {
                    printf("!!!!!checkmate!!!!!\n");
                }
                if(!player)
                {change_view(board);}

                //after putting the chess, compact the "die" stack
                int gap;
                for(int i=0;i<eat;i++)       
                {
                    if(die[i]==chess_for_put[put])
                    {
                        gap=i;
                        break;
                    }
                } 
                for(int i=gap;i<eat;i++)
                {
                    die[i]=die[i+1];
                }
                eat--;

                //save the process
                process[step].step=step;
                process[step].num=chess_for_put[put];
                process[step].type=board[2][chess_for_put[put]];
                process[step].o_row=0;
                process[step].o_col=0;
                process[step].d_row=put_row;
                process[step].d_col=put_col;
                process[step].eat_type=40;
                process[step].eat_num=40;
                process[step].enhanced='n';
                process[step].act='d';
                step++;

                player=!player;
                change_view(board);
                show_checkerboard(player,board);
            }
            //if the player has not eaten any chess , then this action is meaningless

            if(n==0)
            {
                show_checkerboard(player,board);
                printf("no chess to put\n");
            }
            continue;
        }
```
* _undo the last step_  
There's a stack calls "process".It keeps storing information of each step all the time,even you don't enter 's'.  
When you enter '0' to undo the last step, the "process" stack will pop, and the program will get the information of the last step to restore the checkerboard to the last state.
```sh
if(act=='0')
        {
            if(step==1){
                show_checkerboard(player,board);
                printf("this is the first step!\n");
                continue;
            }
            step--;
            //back to last situation
            if(process[step].act=='a' || process[step].act=='e')
            {
                if(!player){
                    board[0][process[step].num]=10-process[step].o_row;
                    board[1][process[step].num]=10-process[step].o_col;
                }
                if(player){
                    board[0][process[step].num]=process[step].o_row;
                    board[1][process[step].num]=process[step].o_col;
                }
                //if the chess has enhanced, let it degenerates
                if(process[step].enhanced=='y')
                {
                    board[2][process[step].num]=level_down(board[2][process[step].num]);
                }
                //if a chess has eaten, let it comes back
                if(process[step].act=='e')
                {                     
                    if(!player){
                        board[0][process[step].eat_num]=10-process[step].d_row;
                        board[1][process[step].eat_num]=10-process[step].d_col;
                    }
                    if(player){
                        board[0][process[step].eat_num]=process[step].d_row;
                        board[1][process[step].eat_num]=process[step].d_col;
                    }
                    board[2][process[step].eat_num]=process[step].eat_type;
                    eat--;
                }
            }
            //if the chess has reborned, let it die
            if(process[step].act=='d')
            {
                board[0][process[step].num]=0;
                board[1][process[step].num]=0;
                die[eat]=process[step].num;
                eat++;
            }
            player=!player;
            change_view(board);
            show_checkerboard(player,board);
            continue;
        }
```
* _save the gaming process to the file_  
There's a stack calls "process",it keeps storing information of each step all the time. When you enter 's', the program will write the information in the "process" stack to a text file.The text file can be load to this program anytime to replay the gaming process.
```sh
        if(act=='s')
        {
            FILE *file;
            file=fopen(instr[2],"w+");
            fprintf(file,"step  chess_num  chess_type  src_row  src_col  next_row  next_col  eat_num  eat_type  enhanced?  act\n");
            for(int i=1;i<step;i++)
            {

                fprintf(file,"%d",process[i].step);
                for(int i=0;i<4;i++){fprintf(file," ");}
                if(process[i].step<10){fprintf(file," ");}

                fprintf(file,"%d",process[i].num);
                for(int i=0;i<9;i++){fprintf(file," ");}
                if(process[i].num<10){fprintf(file," ");}

                fprintf(file,"%d",process[i].type);
                for(int i=0;i<10;i++){fprintf(file," ");}
                if(process[i].type<10){fprintf(file," ");}

                fprintf(file,"%d",process[i].o_row);
                for(int i=0;i<7;i++){fprintf(file," ");}
                if(process[i].o_row<10){fprintf(file," ");}

                fprintf(file,"%d",process[i].o_col);
                for(int i=0;i<7;i++){fprintf(file," ");}
                if(process[i].o_col<10){fprintf(file," ");}

                fprintf(file,"%d",process[i].d_row);
                for(int i=0;i<8;i++){fprintf(file," ");}
                if(process[i].d_row<10){fprintf(file," ");}

                fprintf(file,"%d",process[i].d_col);
                for(int i=0;i<8;i++){fprintf(file," ");}
                if(process[i].d_col<10){fprintf(file," ");}
                
                fprintf(file,"%d",process[i].eat_num);
                for(int i=0;i<7;i++){fprintf(file," ");}
                if(process[i].eat_num<10){fprintf(file," ");}

                fprintf(file,"%d",process[i].eat_type);
                for(int i=0;i<8;i++){fprintf(file," ");}
                if(process[i].eat_type<10){fprintf(file," ");}

                fprintf(file,"%c",process[i].enhanced);
                for(int i=0;i<10;i++){fprintf(file," ");}

                fprintf(file,"%c\n",process[i].act);
            }
            fclose(file);
            show_checkerboard(player,board);
            continue;
        }
```
* _moving and eating chesses_  
When you enter 'a' and the position of the chess you want to move and the position you want to move to, this program will find out the chess with the entered postion.  
After the chess is found, the program will checking that if the move follows the rules.   
Next, the program will check if the moving destination has a chess on it.  
If the chess on it is yours, then the move won't be implemented, however, if the chess on it is not yours , the move will be implemented and the chess will be eaten and be stored to the "die" stack.
```sh
        for(int i=0;i<MAXCHESS;i++)
        {
            if(board[0][i]==ori_row && board[1][i]==ori_col)
            {
                has_chess=true;
                correct=rule_checking(des_col,des_row,ori_col,ori_row,board[2][i],board);
                
                if(correct){
                    for(int j=0;j<MAXCHESS;j++)
                    {
                        if(board[0][j]==des_row && board[1][j]==des_col)
                        {
                            if(player && whose(board[2][i])){
                                if(whose(board[2][j])){correct = false;}
                                else{
                                    board[0][j]=0;board[1][j]=0;

                                    process[step].eat_type=board[2][j];
                                    if(board[2][j]>=10 && board[2][j]<=17){board[2][j]=board[2][j]-10;}
                                    if(board[2][j]==GIOAW_S_2 || board[2][j]==FEI_S_2){board[2][j]=board[2][j]-12;}
                                    if(board[2][j]>=30 && board[2][j]<=33){board[2][j]=board[2][j]-30;}
                                    die[eat]=j;
                                    eat++;

                                    process[step].act='e';
                                    process[step].eat_num=j;

                                    if(board[2][j]==KING_2){win=1;}//if the eaten chess is king,the player1 wins
                                }
                            }
                            if(!player && !(whose(board[2][i]))){
                                if(!(whose(board[2][j]))){correct = false;}
                                else{
                                    board[0][j]=0;board[1][j]=0;

                                    process[step].eat_type=board[2][j];
                                    if(board[2][j]>=0 && board[2][j]<=7){board[2][j]=board[2][j]+10;}
                                    if(board[2][j]==GIOAW_S_1 || board[2][j]==FEI_S_1){board[2][j]=board[2][j]+8;}
                                    if(board[2][j]>=20 && board[2][j]<=23){board[2][j]=board[2][j]-10;}
                                    die[eat]=j;
                                    eat++;

                                    process[step].act='e';
                                    process[step].eat_num=j;

                                    if(board[2][j]==KING_1){win=2;}//if the eaten chess is king,the player2 wins
                                }
                            }
                            break; 
                        }
                    }
                }
                moved_chess=i;
                break;
            }
        }
        //check if the move is beyond the board
        if(des_col>9 || des_col<1 || des_row>9 || des_row<1){correct = false;}
        
        if(!has_chess){correct = false;}
        //check if the player is using his/her chess
        if(has_chess && player && !whose(board[2][moved_chess]))
        {
            correct = false;
            printf("that's not your chess,");
        }
        if(has_chess && !player && whose(board[2][moved_chess]))
        {
            correct = false;
            printf("that's not your chess,");
        }
        //if all the checking is passed, move the chess
        //enhance the chess if the player wants
        if(correct)
        {
            board[0][moved_chess]=des_row;board[1][moved_chess]=des_col;
            player=!player;
            change_view(board);           
        }
```
* _enhence the chess_  
After you moving a chess, this program will check if the moved chess can be enhanced. 
```sh
        if( board[0][moved_chess]>6 && 
            board[2][moved_chess]!=GOLD_1 && board[2][moved_chess]!=KING_1
         && board[2][moved_chess]!=GIOAW_S_1 &&board[2][moved_chess]!=FEI_S_1 &&  
            board[2][moved_chess]!=GOLD_2 && board[2][moved_chess]!=KING_2
         && board[2][moved_chess]!=GIOAW_S_2 &&board[2][moved_chess]!=FEI_S_2 &&
            board[2][moved_chess]<20 && 
            correct)
        {
            printf("enhanced the chess?(y/n)");
            scanf("%s",&en);
            if(en=='y' || en=='Y')
            {
                process[step].enhanced='y';
                board[2][moved_chess]=level_up(board[2][moved_chess]);
            }
        }
```




