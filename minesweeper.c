#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Global Vars
int rowSize=8;
int colSize=8;
int gameStat=1;
char mineLayout[20][20];
char groundLayout[20][20];

void quesGen()
{
 int i,j;
 int rr,rc,minecnt;

 srand(time(NULL));
 minecnt = (15.65*(rowSize*colSize))/100;

 for(i = 0; i < minecnt; i++)
 {
  rr = rand()%rowSize;
  rc = rand()%colSize;
  mineLayout[rr][rc] = '*';
 }

 for(i = 0; i < rowSize; i++)
 {
  for(j = 0; j < colSize; j++)
  {
   mineLayout[i][j] = (mineLayout[i][j] == '*') ? '*' : ' ';
   if(mineLayout[i][j] == ' ')
   {
    int rmx,rmy,cmx,cmy,x,y,mineCount=0;
    rmx = (i == 0) ? i : i-1;
    rmy = (i == (rowSize-1)) ? (rowSize-1) : i+1;
    cmx = (j == 0) ? j : j-1;
    cmy = (j == (colSize-1)) ? (colSize-1) : j+1;
    for(x = rmx; x <= rmy; x++)
    {
    for(y = cmx; y <= cmy; y++)
     {
      if(mineLayout[x][y] == '*' &&  !(x==i && y==j))
      {
       mineCount++;
      }
     }
    }
    mineLayout[i][j] = (mineCount != 0) ? 48+mineCount : '~';
   }
   groundLayout[i][j] = ' ';
  }
 }
}

void displayBoard()
{
 int i,j;
 system("clear");
 printf("\n      ");
 for(i = 0; i < colSize; i++)
 	printf("%2d  ",i);
 printf("\n");

 for(i = 0; i <= rowSize*2; i++)
 {
  int ival = (i-1)/2;
  if(i%2 == 1)
   printf(" %2d  |",ival);
  else
   printf("     +");

  for(j = 0; j < colSize; j++)
  {
   if(i%2 == 0)
    printf("---+");
   else
    printf("%2c |",groundLayout[ival][j]);
  }

  printf("\n");
 }
}

void operateMine(char op,int r,int c)
{
 if(op == 'f' && groundLayout[r][c] == ' ')
  groundLayout[r][c] = 'f';
 else if(op == 'd' && groundLayout[r][c] == ' ')
 {
  if(mineLayout[r][c] == '~')
  {
   openEmptySpots(r,c);
  }
  else
  {
   groundLayout[r][c] = mineLayout[r][c];
  }
 }
 displayBoard(); 
}

void openEmptySpots(int r, int c)
{
 if(!(mineLayout[r][c] == '~' || mineLayout[r][c] == '-'))
 {
  return;
 }
 else
 {
  int rmx,rmy,cmx,cmy,x,y,mineCount=0;
  rmx = (r == 0) ? r : r-1;
  rmy = (r == (rowSize-1)) ? (rowSize-1) : r+1;
  cmx = (c == 0) ? c : c-1;
  cmy = (c == (colSize-1)) ? (colSize-1) : c+1;
  mineLayout[r][c] = '-';
  groundLayout[r][c] = '-';
  for(x = rmx; x <= rmy; x++)
  {
   for(y = cmx; y <= cmy; y++)
   {
    if(mineLayout[x][y] == '~' &&  !(x==r && y==c))
    {
     openEmptySpots(x,y);
    }
    else
    {
     groundLayout[x][y] = mineLayout[x][y];
    }
   }
  }
 }
}
 
int main()
{
 char ch;
 printf("\tMinesweeper!\n");
 printf("Use Default Board Size(8x8)? [y/n] : ");
 scanf("%c",&ch);
 if(ch=='n')
 {
  printf("Enter Custom Board Size : ");
  scanf("%d%d",&rowSize,&colSize);
 }
 printf("Size : %dx%d\n",rowSize,colSize);

 //Generate Question
 quesGen();
 
 //Game is Live

 do
 {
  char op;
  int r,c;
  displayBoard();
  /*for(int i =0; i < rowSize; i++){
   for(int j =0; j < colSize; j++){
     printf("|%2c ",mineLayout[i][j]);
    }
     printf("|\n");
    }*/
  printf("Enter the cell([d/f] row col) : ");
  fflush(stdin);
  scanf("%c%d%d",&op,&r,&c);
  operateMine(op,r,c);
 }while(gameStat);
}
