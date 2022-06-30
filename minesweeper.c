#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Global Vars
int rowSize=8;
int colSize=8;
char mineLayout[20][20];
char groundLayout[20][20];

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

void quesGen(int r,int c)
{
 int i,j;
 int rr,rc,minecnt;
 srand(time(NULL));
 minecnt = (15.65*(rowSize*colSize))/100;
 
 i=j=0;
 while(j<minecnt)
 {
  rr = rand()%rowSize;
  rc = rand()%colSize;
  if(mineLayout[rr][rc] == ' ' && !(rr == r && rc == c))
  {
   mineLayout[rr][rc] = '*';
   j++;
  }
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
 
void operateMine(char op,int r,int c)
{
 if(op == 'f')
 { 
  if(groundLayout[r][c] == ' ')
    groundLayout[r][c] = 'f';
  else if(groundLayout[r][c] == 'f')
    groundLayout[r][c] = ' ';
 }
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

int checkGameStatus()
{
 int i,j,mines,mc=0;
 mines = (15.65*rowSize*colSize)/100;
 for(i = 0; i < rowSize; i++)
 {
  for(j = 0; j < colSize; j++)
  {
   if(groundLayout[i][j] == '*')
   {
    printf("\n\n\t+-----------------+");
      printf("\n\t|    GAME OVER    |");
      printf("\n\t+-----------------+\n");
    return 0;
   }
   if(groundLayout[i][j] == 'f' && mineLayout[i][j] == '*')
   {
    mc++;
   }
  }
 }
 if(mc == mines)
 {
  printf("\n\n\t+--------------------------+");
    printf("\n\t|    YOU WON THE GAME !    |");
    printf("\n\t+--------------------------+\n");
  return 0;
 }
 else
  return 1;
}

int main()
{
start : 
 char ch,op;
 int i,j,r,c,flag=-1;
 printf("\tMinesweeper!\n");
 printf("Use Default Board Size(8x8)? [y/n] : ");
 scanf("%c",&ch);
 if(ch=='n')
 {
  printf("Enter Custom Board Size : ");
  scanf("%d%d",&rowSize,&colSize);
 }
 printf("Size : %dx%d\n",rowSize,colSize);

 for(i = 0; i < rowSize; i++)
 {
  for(j = 0; j < colSize; j++){
   mineLayout[i][j] = ' ';
   groundLayout[i][j] = ' ';
  }
 }
 //Game is Live
 do
 {
  displayBoard();
  printf("Enter the cell( [d/f] row col) : ");
  scanf(" %c%d%d",&op,&r,&c);
  if(flag==-1)
  {
   flag = 0;
   quesGen(r,c);
  }
  operateMine(op,r,c);
 }while(checkGameStatus());
 printf("\nPlay Again ? [y/n]: ");
 scanf(" %c",&ch);
 if(ch == 'y')
  goto start;
}
