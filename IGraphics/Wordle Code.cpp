# include "iGraphics.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NUM_OF_WORDS 500

int number_letter;
char str[100];
char strout0[5], strout1[5],strout2[5],strout3[5],strout4[5],strout5[5],strout6[5];
char button[100][100]= { "asset/Newgame.bmp", "asset/Settings.bmp", "asset/Instructions.bmp"};
char clue[20][20]= {"00000","00000","00000","00000","00000","00000"};
char reset[100];
char counteroutput[5];
char highestoutput[5];
char wordle[50] = "asset/wordle.bmp";
char homemenu[50] = "asset/menu.bmp";
char instructions[30]= "asset/instruction_page.bmp";
char settings[30]= "asset/settings_page.bmp";
char gamecomplete[100][100]= {"asset/end.bmp", "asset/1st.bmp", "asset/2nd.bmp", "asset/3rd.bmp", "asset/4th.bmp", "asset/5th.bmp", "asset/6th.bmp"};
char answer[6];
bool musicOn = true;
bool music2 = false;
bool answerflags[5]= {false,false,false,false,false};
char guess[6][5];
int IndexNumber =0;
int first_box = 200;
int value= 0;
int num_of_guesses=0;
int n;
int line = 600;
int first_letter = 215;
int endgame = 0;
float gamestate = -3;
int flag=0;
struct button_coordinate
{
    int x;
    int y;
} bcoordinate[5];
int i,j,k;

char* answercall()
{
    FILE* wordsFile;
    char** wordsList = (char**)calloc(MAX_NUM_OF_WORDS, sizeof(char*));
    int wordCount = 0;
    char* LetterWord = (char*)malloc((number_letter)*sizeof(char));
    if(number_letter==3)
    {
        wordsFile = fopen("words3.txt", "r");
    }
    if(number_letter==4)
    {
        wordsFile = fopen("words4.txt", "r");
    }
    if(number_letter==5)
    {
        wordsFile = fopen("words5.txt", "r");
    }
    while (fscanf(wordsFile, "%s", LetterWord) != EOF && wordCount < MAX_NUM_OF_WORDS)
    {
        wordsList[wordCount] = LetterWord;
        wordCount++;
        LetterWord = (char*)malloc((number_letter+1)*sizeof(char));
    }
    fclose(wordsFile);


    srand(time(NULL));
    char *answerpath = wordsList[rand()%wordCount];
    strcpy(answer, answerpath);
    printf("%s", answer);
    return answer;
}


int read_file(char *filename)
{
    FILE *fp;
    int count_from_file;
    fp = fopen(filename, "r");
    //while (!feof (fp))
        fscanf(fp, "%d", &count_from_file);
    return count_from_file;
}

int counter ;
//= read_file("score.txt");
int highest_streak = read_file("high score.txt");

void write_file(char *filename, int counter)
{
    FILE *fp;
    fp = fopen(filename, "w");
    fprintf(fp, "%d", counter);
}

void iDraw()
{
    //place your drawing codes here
    iClear();

    char ch[number_letter+1];
    for(int i=0; i<number_letter; i++)
    {
        ch[i]='1';
    }
    ch[number_letter]='\0';

    if(gamestate == -3)
    {
        iShowBMP(0,0, "asset/insert.bmp");
        iText(250,150, "PRESS ENTER TO CONTINUE....", GLUT_BITMAP_TIMES_ROMAN_10);
    }

    if(gamestate==-2)
    {
        iRectangle(50, 600, 130, 65);
        iShowBMP(0,0,homemenu);
        iShowBMP2(50, 600, "asset/wordle.bmp", 255);

        for(int i=0; i<3; i++)
        {
            iShowBMP2(bcoordinate[i].x,bcoordinate[i].y,button[i],255);
            iRectangle(bcoordinate[i].x-2,bcoordinate[i].y-3, 230,65);
        }
        iShowBMP(520,8,"asset/quit.bmp");
        iRectangle(518, 5, 130, 65);
    }

    if(gamestate == -1)
    {
        iShowBMP(0,0,"asset/selection.bmp");
    }

    if(gamestate == 0)
    {
        int x=number_letter;
        iSetColor(255,255,255);
        iShowBMP(275,665, "asset/1.bmp");
        iShowBMP(100, 20, "asset/2.bmp");
        iShowBMP(50, 665, "asset/Untitled(63 � 44 px).bmp");
        iShowBMP(585,665, "asset/question.bmp");
        iRectangle(48,662,63,44);
        iRectangle(583,662,44,44);
        iLine(0, 655, 672, 655);

        for(i=0; i<number_letter; i++)
        {
            for(j=0; j<6; j++)
            {
                iSetColor(100,100,100);
                iRectangle(first_box+(57*i),580-60*j,50,50);
            }

        }
        iSetColor(255,255,255);

        if(num_of_guesses==0)
        {
            for(j=0 ; j<number_letter; j++)
            {
                guess[0][j]=str[j];
                strout0[0]= guess[0][j];
                iText(first_letter+ (57* j),line,strout0,GLUT_BITMAP_TIMES_ROMAN_24);
            }
        }
        char modify[number_letter+1];
        if( num_of_guesses==1)
        {
            strcpy(modify,answer);
            for(j=0; j<number_letter; j++)
            {
                if(guess[0][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),580,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }


                //yellow color
                else if(guess[0][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[0][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),580,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }


            if( strcmp(answer, ch )==0)
            {
                counter++;
                write_file("score.txt",counter);

                if(highest_streak<= counter)
                {
                    highest_streak = counter;
                    write_file("high score.txt", highest_streak);
                }
                gamestate = 4;
            }
            strcpy(answer,modify);
            //letter print
            for(j=0 ; j<number_letter; j++)
            {
                guess[0][j]=str[j];
                strout0[0]= guess[0][j];
                iText(first_letter+ 57* j,line,strout0,GLUT_BITMAP_TIMES_ROMAN_24);
            }

            for(j=0 ; j<number_letter; j++)
            {
                guess[1][j]=str[j+x];
                strout2[0]= guess[1][j];
                iText(first_letter+ 57 * j,line-60,strout2,GLUT_BITMAP_TIMES_ROMAN_24);

            }
        }

        if(num_of_guesses==2)
        {
            //1st comparison
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[0][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),580,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[0][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[0][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),580,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //2nd comparison start
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[1][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),520,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[1][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[1][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),520,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }
                if(strcmp(answer, ch )==0)
                {
                    counter++;
                    write_file("score.txt",counter);

                    if(highest_streak<= counter)
                    {
                        highest_streak = counter;
                        write_file("high score.txt", highest_streak);
                    }
                    gamestate = 5;
                }
            }
            strcpy(answer,modify);

            for(j=0 ; j<number_letter; j++)
            {
                guess[0][j]=str[j];
                strout1[0]= guess[0][j];
                iText(first_letter+ 57* j,line,strout1,GLUT_BITMAP_TIMES_ROMAN_24);
            }

            for(j=0 ; j<number_letter; j++)
            {
                guess[1][j]=str[j+x];
                strout2[0]= guess[1][j];
                iText(first_letter+ 57 * j,line-60,strout2,GLUT_BITMAP_TIMES_ROMAN_24);
            }

            for(j=0 ; j<number_letter; j++)
            {

                guess[2][j]=str[j+2*x];
                strout3[0]= guess[2][j];
                iText(first_letter+ 57 * j,line-120,strout3,GLUT_BITMAP_TIMES_ROMAN_24);
            }
        }

        if(num_of_guesses==3)
        {
            //1st comparison
            strcpy(modify,answer);
            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[0][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),580,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[0][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[0][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),580,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //2nd comparison start
            strcpy(modify,answer);


            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[1][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),520,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[1][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[1][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),520,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //3rd comparison
            strcpy(modify,answer);


            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[2][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),460,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[2][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[2][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),460,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }
                if(strcmp(answer, ch )==0)
                {
                    counter++;
                    write_file("score.txt",counter);
                    if(highest_streak<= counter)
                    {
                        highest_streak = counter;
                        write_file("high score.txt", highest_streak);
                    }
                    gamestate = 6;
                }

            }
            strcpy(answer,modify);

            //letter print

            for(j=0 ; j<number_letter; j++)
            {
                guess[0][j]=str[j];
                strout1[0]= guess[0][j];
                iText(first_letter+ 57* j,line,strout1,GLUT_BITMAP_TIMES_ROMAN_24);


            }

            for(j=0 ; j<number_letter; j++)
            {
                guess[1][j]=str[j+x];
                strout2[0]= guess[1][j];
                iText(first_letter+ 57 * j,line-60,strout2,GLUT_BITMAP_TIMES_ROMAN_24);
            }

            for(j=0 ; j<number_letter; j++)
            {
                guess[2][j]=str[j+2*x];
                strout3[0]= guess[2][j];
                iText(first_letter+ 57 * j,line-120,strout3,GLUT_BITMAP_TIMES_ROMAN_24);
            }

            for(j=0 ; j<number_letter; j++)
            {

                guess[3][j]=str[j+3*x];
                strout4[0]= guess[3][j];
                iText(first_letter+57 *j,line-180,strout4,GLUT_BITMAP_TIMES_ROMAN_24);
            }
        }

        if(num_of_guesses==4)
        {

            //1st comparison
            strcpy(modify,answer);


            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[0][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),580,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[0][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[0][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),580,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //2nd comparison
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[1][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),520,50,50);
                    iSetColor(255,255,255);
                    answerflags[j] = true;
                    answer[j]='1';
                }
                //yellow color
                else if(guess[1][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[1][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),520,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //3rd comparison
            strcpy(modify,answer);


            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[2][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),460,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[2][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[2][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),460,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //4th comparison
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[3][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),400,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[3][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[3][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),400,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

                if(strcmp(answer, ch )==0)
                {
                    counter++;

                    write_file("score.txt",counter);
                    if(highest_streak<= counter)
                    {
                        highest_streak = counter;
                        write_file("high score.txt", highest_streak);
                    }
                    gamestate = 7;
                }
            }
            strcpy(answer,modify);

            //letter print
            for(j=0 ; j<number_letter; j++)
            {
                guess[0][j]=str[j];
                strout0[0] = guess[0][j];
                iText(first_letter+ 57* j,line,strout0,GLUT_BITMAP_TIMES_ROMAN_24);

            }
            for(j=0 ; j<number_letter; j++)
            {
                guess[1][j]=str[j+x];
                strout1[0]= guess[1][j];
                iText(first_letter+ 57 * j,line-60,strout1,GLUT_BITMAP_TIMES_ROMAN_24);

            }
            for(j=0 ; j<number_letter; j++)
            {

                guess[2][j]=str[j+2*x];
                strout2[0]= guess[2][j];
                iText(first_letter+ 57 * j,line-120,strout2,GLUT_BITMAP_TIMES_ROMAN_24);

            }
            for(j=0 ; j<number_letter; j++)
            {

                guess[3][j]=str[j+3*x];
                strout3[0]= guess[3][j];
                iText(first_letter+57 *j,line-180,strout3,GLUT_BITMAP_TIMES_ROMAN_24);
            }
            for(j=0 ; j<number_letter; j++)
            {
                guess[4][j]=str[j+4*x];
                strout4[0]= guess[4][j];
                iText(first_letter+ 57 * j,line-240,strout4,GLUT_BITMAP_TIMES_ROMAN_24);

            }
        }

        if(num_of_guesses==5)
        {
            //1st
            strcpy(modify,answer);
            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[0][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),580,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[0][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[0][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),580,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //2nd
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[1][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),520,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[1][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[1][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),520,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //3rd
            strcpy(modify,answer);
            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[2][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),460,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[2][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[2][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),460,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //4th
            strcpy(modify,answer);


            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[3][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),400,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[3][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[3][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),400,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //5th
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[4][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),340,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[4][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[4][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),340,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }
                //compare
                if(strcmp(answer, ch )==0)
                {
                    counter++;

                    write_file("score.txt",counter);
                    if(highest_streak<= counter)
                    {
                        highest_streak = counter;
                        write_file("high score.txt", highest_streak);
                    }
                    gamestate = 8;
                }

            }
            strcpy(answer,modify);

            //print letter
            for(j=0 ; j<number_letter; j++)
            {
                guess[0][j]=str[j];
                strout0[0]=guess[0][j];
                iText(first_letter+ 57* j,line,strout0,GLUT_BITMAP_TIMES_ROMAN_24);


            }
            for(j=0 ; j<number_letter; j++)
            {
                guess[1][j]=str[j+x];
                strout1[0]= guess[1][j];
                iText(first_letter+ 57 * j,line-60,strout1,GLUT_BITMAP_TIMES_ROMAN_24);


            }
            for(j=0 ; j<number_letter; j++)
            {

                guess[2][j]=str[j+2*x];
                strout2[0]= guess[2][j];
                iText(first_letter+ 57 * j,line-120,strout2,GLUT_BITMAP_TIMES_ROMAN_24);


            }
            for(j=0 ; j<number_letter; j++)
            {

                guess[3][j]=str[j+3*x];
                strout3[0]= guess[3][j];
                iText(first_letter+57 *j,line-180,strout3,GLUT_BITMAP_TIMES_ROMAN_24);
            }


            for(j=0 ; j<number_letter; j++)
            {
                guess[4][j]=str[j+4*x];
                strout4[0]= guess[4][j];
                iText(first_letter+ 57 * j,line-240,strout4,GLUT_BITMAP_TIMES_ROMAN_24);

            }
            for(j=0 ; j<number_letter; j++)
            {
                guess[5][j]=str[j+5*x];
                strout5[0]= guess[5][j];
                iText(first_letter+ 57 * j,line-300,strout5,GLUT_BITMAP_TIMES_ROMAN_24);

            }
        }

        if(num_of_guesses>=6)
        {
            //1st row comparison start
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[0][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),580,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';

                }
                //yellow color
                else if(guess[0][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[0][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),580,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }



            }
            strcpy(answer,modify);
            //2nd row comparison start
            strcpy(modify,answer);
            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[1][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),520,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[1][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[1][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),520,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //3rd row comparision start
            strcpy(modify,answer);


            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[2][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),460,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[2][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[2][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),460,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //4th row comparison start
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[3][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),400,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[3][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[3][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),400,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //5th row comparison start
            strcpy(modify,answer);

            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[4][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),340,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[4][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[4][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),340,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }

            }
            strcpy(answer,modify);
            //6th row comparison start
            strcpy(modify,answer);


            //green colour
            for(j=0; j<number_letter; j++)
            {
                if(guess[5][j]==answer[j] )
                {
                    iSetColor(83,140,78);
                    iFilledRectangle(first_box+(57*j),280,50,50);
                    iSetColor(255,255,255);
                    answer[j]='1';
                }
                //yellow color
                else if(guess[5][j]!=answer[j])
                {
                    for(k=0; k<number_letter; k++)
                    {
                        if((guess[5][j]==answer[k]))
                        {
                            iSetColor(180, 158, 59);
                            iFilledRectangle(first_box+(57*j),280,50,50);
                            iSetColor(255,255,255);
                            break;
                        }
                    }
                }
                if(strcmp(answer, ch )==0)
                {
                    counter++;
                    write_file("score.txt",counter);
                    if(highest_streak<= counter)
                    {
                        highest_streak = counter;
                        write_file("high score.txt", highest_streak);
                    }
                    gamestate = 9;
                }
                else
                {
                    gamestate = 3;
                    counter = 0;
                }
            }
            strcpy(answer,modify);

            for(j=0 ; j<number_letter; j++)
            {
                guess[0][j]=str[j];
                strout0[0]=guess[0][j];
                iText(first_letter+ 57* j,line,strout0,GLUT_BITMAP_TIMES_ROMAN_24);


            }

            for(j=0 ; j<number_letter; j++)
            {
                guess[1][j]=str[j+x];
                strout1[0]= guess[1][j];
                iText(first_letter+ 57 * j,line-60,strout1,GLUT_BITMAP_TIMES_ROMAN_24);


            }
            for(j=0 ; j<number_letter; j++)
            {

                guess[2][j]=str[j+2*x];
                strout2[0]= guess[2][j];
                iText(first_letter+ 57 * j,line-120,strout2,GLUT_BITMAP_TIMES_ROMAN_24);


            }
            for(j=0 ; j<number_letter; j++)
            {

                guess[3][j]=str[j+3*x];
                strout3[0]= guess[3][j];
                iText(first_letter+57 *j,line-180,strout3,GLUT_BITMAP_TIMES_ROMAN_24);
            }


            for(j=0 ; j<number_letter; j++)
            {
                guess[4][j]=str[j+4*x];
                strout4[0]= guess[4][j];
                iText(first_letter+ 57 * j,line-240,strout4,GLUT_BITMAP_TIMES_ROMAN_24);

            }
            for(j=0 ; j<number_letter; j++)
            {
                guess[5][j]=str[j+5*x];
                strout5[0]= guess[5][j];
                iText(first_letter+ 57 * j,line-300,strout5,GLUT_BITMAP_TIMES_ROMAN_24);

            }

        }
    }
    if(gamestate==1)
    {

        iShowBMP(0,0,settings);
        if (musicOn)
        {
            iRectangle(475,390,140, 65)  ;
        }

    }
    if(gamestate==2)
    {

        iShowBMP(0,0,instructions);
    }
    if(gamestate == 3)
    {
        iShowBMP(0, 0, "asset/end.bmp");
        iText(490,242, answer,GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if( gamestate== 4)
    {
        iShowBMP(0, 0,  "asset/1st.bmp");

    }
    if(gamestate == 5)
    {
        iShowBMP(0, 0,"asset/2nd.bmp");
    }
    if(gamestate == 6)
    {
        iShowBMP(0, 0,"asset/3rd.bmp");
    }
    if(gamestate == 7)
    {
        iShowBMP(0, 0,"asset/4th.bmp");
    }
    if(gamestate == 8)
    {
        iShowBMP(0, 0,"asset/5th.bmp");
    }
    if(gamestate == 9)
    {
        iShowBMP(0, 0, "asset/6th.bmp");
    }

    if (gamestate >= 1 && gamestate <= 10)
    {
        iRectangle(50,87, 128,86);
    }
    if(gamestate>=3 && gamestate <= 9)
    {


        sprintf(counteroutput,"%d", counter);
        iSetColor(0,255,0);

        iText(320, 501,counteroutput, GLUT_BITMAP_TIMES_ROMAN_24 );
        iSetColor(255,0,0);
        iText(580, 501,highestoutput, GLUT_BITMAP_TIMES_ROMAN_24 );
        iSetColor(255,255,255);
        iText(90,501,"CURRENT STREAK: ", GLUT_BITMAP_TIMES_ROMAN_24);
        sprintf(highestoutput, "%d", highest_streak);
        iText(350,501,"MAX STREAK: ", GLUT_BITMAP_TIMES_ROMAN_24);
    }

}

void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (gamestate ==-1)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                //place your codes here

                //new game
                if(mx>=110 && mx<=195 && my>=208 && my<=248 )
                {


                    number_letter=3;
                    for(i=0; i<100; i++)
                    {
                        str[i]=' ';
                    }
                    strcpy(answer,answercall());
                    num_of_guesses = 0;
                    IndexNumber= 0;
                    gamestate = 0;
                    for(i = 0; i<20; i++)
                        for (j=0; j< 20; j++)
                            clue[i][j]= '0';


                }
                if(mx>=274 && mx<=370 && my>=208 && my<=248 )
                {


                    number_letter=4;
                    for(i=0; i<100; i++)
                    {
                        str[i]=' ';
                    }
                    strcpy(answer,answercall());
                    num_of_guesses = 0;
                    IndexNumber= 0;
                    gamestate = 0;
                    for(i = 0; i<20; i++)
                        for (j=0; j< 20; j++)
                            clue[i][j]= '0';


                }
                if(mx>=457 && mx<=565 && my>=208 && my<=248 )
                {


                    number_letter=5;
                    for(i=0; i<100; i++)
                    {
                        str[i]=' ';
                    }
                    strcpy(answer,answercall());
                    num_of_guesses = 0;
                    IndexNumber= 0;
                    gamestate = 0;
                    for(i = 0; i<20; i++)
                        for (j=0; j< 20; j++)
                            clue[i][j]= '0';


                }
                if(mx>=52 && mx<=146 && my>=63 && my<=98 )
                {
                    gamestate=-2;
                }

            }
        }

        if (gamestate ==-2)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                //place your codes here
                //new game
                if(mx>= bcoordinate[0].x && mx<=bcoordinate[0].x+230 && my>=bcoordinate[0].y && my<= bcoordinate[0].y+65)
                {
                    gamestate = -1;
                }
                if(mx>=  bcoordinate[1].x&& mx<=  bcoordinate[1].x+230 && my>= bcoordinate[1].y && my<= bcoordinate[1].y+65)
                {
                    gamestate = 1;
                }
                //credits
                if(mx>= bcoordinate[2].x && mx<=  bcoordinate[2].x+230 && my>= bcoordinate[2].y && my<=  bcoordinate[2].y+65)
                {
                    gamestate = 2;
                }
                //instructions
                if(mx>=  bcoordinate[3].x && mx<=  bcoordinate[3].x+230 && my>= bcoordinate[3].y && my<= bcoordinate[3].y+65)
                {
                    gamestate = 10;
                }
                //instructions

                //exit
                if(mx>=518  && mx<=518+130 && my>=5  && my<=65  )
                {
                    exit(0);
                }
            }
        }

        if(gamestate == 1)
        {
            //settings music on\off
            if(mx>= 480 && mx<= 610 && my>=400 && my<= 465)
            {
                if(musicOn)
                {
                    musicOn = false;
                    PlaySound(0,0,0);
                }
                else
                {
                    musicOn = true;
                    PlaySound("asset/sound/bg.wav",NULL, SND_LOOP | SND_ASYNC);

                }

            }

        }
        if (gamestate == 0)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                if(mx>= 48 && mx<= 48+63 && my>=663 && my<= 663+63)
                {
                    gamestate = -1;
                }
                //go to instructions
                if(mx>= 583 && mx<= 583+44 && my>=662 && my<= 662+44)
                {
                    gamestate = 2;
                }
            }
        }
        if (gamestate>=1 && gamestate <= 11)
        {

            // the back button for each page
            if(mx>= 63 && mx<= 128+63 && my>=63 && my<= 86+63)
            {
                gamestate = -2;
            }
        }

    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }

    //place your codes here
    //back to main menu
}

void iKeyboard(unsigned char key)
{


    if (key =='\r')
    {
        if(gamestate ==-2)
        {
            gamestate = -1;
        }
        if (gamestate == 0)
        {
            num_of_guesses+=1;
        }
    }

    if (gamestate == 0)
    {
        if(num_of_guesses == 0)
        {
            if (key != '\b' && key != ' '&& key >= 'a' && key <= 'z' && IndexNumber<number_letter)
            {
                str[IndexNumber] = key-32;
                str[IndexNumber + 1] = '\0';
                IndexNumber++;
            }
            else if (key == '\b' && key != ' ' )
            {
                if (IndexNumber <= 0) IndexNumber = 0;
                else IndexNumber--;
                str[IndexNumber] = '\0';

            }
        }

        if(num_of_guesses == 1)
        {
            if (key != '\b' && key != ' '&& key >= 'a' && key <= 'z'&& IndexNumber<2*number_letter && IndexNumber>number_letter-1 )
            {

                str[IndexNumber] = key-32;
                str[IndexNumber + 1] = '\0';
                IndexNumber++;
            }
            else if (key == '\b' && key != ' ' )
            {
                if (IndexNumber <= number_letter) IndexNumber = number_letter;
                else IndexNumber--;
                str[IndexNumber] = '\0';

            }


        }

        if(num_of_guesses == 2)
        {
            if (key != '\b' && key != ' '&& key >= 'a' && key <= 'z'&& IndexNumber<3*number_letter && IndexNumber>(2*number_letter)-1 )
            {
                str[IndexNumber] = key-32;
                str[IndexNumber + 1] = '\0';
                IndexNumber++;
            }
            else if (key == '\b' && key != ' ' )
            {
                if (IndexNumber <= 2*number_letter) IndexNumber = 2*number_letter;
                else IndexNumber--;
                str[IndexNumber] = '\0';

            }
        }
        if(num_of_guesses == 3)
        {
            if (key != '\b' && key != ' '&& key >= 'a' && key <= 'z'&& IndexNumber<4*number_letter && IndexNumber>(3*number_letter)-1 )
            {
                str[IndexNumber] = key-32;
                str[IndexNumber + 1] = '\0';
                IndexNumber++;
            }
            else if (key == '\b' && key != ' ' )
            {
                if (IndexNumber <= 3*number_letter) IndexNumber = 3*number_letter;
                else IndexNumber--;
                str[IndexNumber] = '\0';

            }
        }
        if(num_of_guesses == 4)
        {
            if (key != '\b' && key != ' '&& key >= 'a' && key <= 'z'&& IndexNumber<5*number_letter && IndexNumber>(4*number_letter)-1 )
            {
                str[IndexNumber] = key-32;
                str[IndexNumber + 1] = '\0';
                IndexNumber++;
            }
            else if (key == '\b' && key != ' ' )
            {
                if (IndexNumber <= 4*number_letter) IndexNumber = 4*number_letter;
                else IndexNumber--;
                str[IndexNumber] = '\0';

            }
        }
        if(num_of_guesses == 5)
        {
            if (key != '\b' && key != ' '&& key >= 'a' && key <= 'z'&& IndexNumber<6*number_letter && IndexNumber>(5*number_letter)-1 )
            {
                str[IndexNumber] = key-32;
                str[IndexNumber + 1] = '\0';
                IndexNumber++;
            }
            else if (key == '\b' && key != ' ' )
            {
                if (IndexNumber <= 5*number_letter) IndexNumber = 5*number_letter;
                else IndexNumber--;
                str[IndexNumber] = '\0';

            }
        }

    }

}
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_HOME)
    {
        gamestate = -2;
    }
    //place your codes for other keys here

    if (key == GLUT_KEY_UP)
    {
        if(musicOn)
        {
            musicOn = false;
            PlaySound(0,0,0);
        }
        else
        {
            musicOn = true;
            PlaySound("asset/sound/bg.wav",NULL, SND_LOOP | SND_ASYNC);

        }

    }
    else if(key == GLUT_KEY_DOWN)
    {
        musicOn = true;
        PlaySound("asset/sound/bg.wav",NULL, SND_ASYNC | SND_LOOP);
    }

}

void musics()
{

        PlaySound("asset/sound/bg.wav",NULL, SND_LOOP | SND_ASYNC);

}

void change()
{
    if (gamestate ==-3)
    {
        gamestate += 1;
    }
}
int main()
{
//place your own initialization codes here.
    FILE *fp;
    int c=0;
    fp = fopen("score.txt", "w");
    fprintf(fp, "%d", c);
    iSetTimer(3000, change);
    //iSetTimer(10000, loadend);
    printf("%d", counter);


    int deviate_y=40;
    for(int i=4; i>=0; i--)
    {
        bcoordinate[i].x=50;
        bcoordinate[i].y=deviate_y;
        deviate_y+=90;

    }
    if(gamestate >= -2)
    {
        if(musicOn) musics();
    }

    iInitialize(672, 728, "Wordle project");

    return 0;
}
