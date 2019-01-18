/****************************************************************************
*****************************************************************************
***************** D.A.V. BOYS SENIOR SECONDARY SCHOOL GPM *******************
**************** CLASS XII ANNUAL COMPUTER SCIENCE PROJECT ******************
******************************* 2017-2018 ***********************************
***************** ####### #      # ####### ####### ####### ******************
***************** #       #      # #       #       #       ******************
***************** #       ######## #####   ####### ####### ******************
***************** #       #      # #             #       # ******************
***************** ####### #      # ####### ####### ####### ******************
************ BY V.ASHWIN | B.ASHWATH | S.LOKESH | B.SUDARSHAN ***************
*****************************************************************************
****************************************************************************/
#include<fstream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int ch[8][8]={2,3,4,5,6,4,3,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,7,8,9,10,11,12,10,9,8};
int pmoves[30][2],i,j,c=0,cm=0,kpmoves[8][2],x,y,ctr[2],jij,fl=0,l,m,flg1=2;
int flg2=2,cpmoves[30][2],cp=0,enpassant1[4][2],enpassant2[4][2],ep1=0,ep2=0;
int p1p[5][9]={0,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1};
int p2p[5][9]={0,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1};
int p1mf[250][2],p1mt[250][2],p2mf[250][2],p2mt[250][2],nomoves1=0,nomoves2=0;
int stat=4,prevstat[250],prevstatctr=0,gamenumber=0,p1changed[8][2],n1=8,n2=8;
int bcount=0,flu,white,black,pcmoves[100][3],pc=0,castle[8][2],bd[8][8],p1ctr[5]={1,1,1,1,1};
int bdcount=0,nm=0,bd1[8][8],bdcount1=0,nm1=0,neww=0,p2changed[8][2],p2ctr[5]={1,1,1,1,1};
int castlecheck1[3]={0,0,0},castlecheck2[3]={0,0,0},revenp1[8][2],revenp2[8][2],move50=0,statue=0;
char name1[12]="Player 1",name2[12]="Player 2",gamefile[6];

union REGS in,out;

class buton
 {
  char Button_Name[100];
  int X0,Y0,X1,Y1,DEPTH,TOP_FLAG,COLOUR,size,flag,flag1,ROW,COLUMN,DESIGN;
  public :
  int ax,ay,PIECE;
  void createbutton(char name[],int x0,int y0,int x1,int y1,int depth,int tf,int col,int SIZE,int design);
  void button(int x0,int y0,int piece,int row=-1,int column=-1)
   {
    X0=x0;
    Y0=y0;
    X1=x0+50;
    Y1=y0+50;
    ax=x0;
    ay=y0;
    if(row==-1)
     flag1=0;
    else
     flag1=1;
    PIECE=piece;
    ROW=row;
    COLUMN=column;
    flag=0;
   }
  int Getresponce(int h=0);
  void Display(int);
  void Showpmoves();
  int Showresponce();
  int Getfocus();
 }p[25];

 void buton::createbutton(char name[],int x0,int y0,int x1,int y1,int depth,int tf,int col,int SIZE=-1,int design=0)
   {
    strcpy(Button_Name,name);
    X0=x0;
    X1=x1;
    Y0=y0;
    Y1=y1;
    DEPTH=depth;
    TOP_FLAG=tf;
    COLOUR=col;
    size=SIZE;
    DESIGN=design;
    flag=0;
    flag1=0;
    setcolor(col);
    bar3d(x0,y0,x1,y1,depth,tf);
    for(int id=x0+1;id<=x1-1;id++)
     line(id,y0+1,id,y1-1);
    Display(DESIGN);
   }

 void buton::Display(int mod)
  {
   if(mod==0)
   {
   int pos;
   if(size==-1)
   {
   if(Y1-Y0>74)
    size=9;
   else if(Y1-Y0>66)
    size=8;
   else if(Y1-Y0>58)
    size=7;
   else if(Y1-Y0>=50)
    size=6;
   else if(Y1-Y0>=42)
    size=5;
   else if(Y1-Y0>=34)
    size=4;
   else if(Y1-Y0>=26)
    size=3;
   else if(Y1-Y0>=18)
    size=2;
   else
    size=1;
   }
   setcolor(COLOUR+8);
   settextstyle(1,HORIZ_DIR,size);
   if (size<6)
    pos=-2*size;
   else
    pos=size-2;
   outtextxy(X0+10,Y0-10-pos,Button_Name);
   setcolor(15);
   settextstyle(1,HORIZ_DIR,size);
   outtextxy(X0+5,Y0-6-pos,Button_Name);
   }
   else if(mod==1)
    {
     setcolor(15);
     for(int xq=X0+20;xq<=X0+40;xq++)
      line(xq,(Y0+Y1)/2-5,xq,(Y0+Y1)/2+5);
     for(xq=(Y0+Y1)/2-10;xq<=(Y0+Y1)/2+10;xq++)
      line(X0+10,(Y0+Y1)/2,X0+20,xq);
    }
   else if(mod==2)
    {
     setcolor(15);
     for(int xq=0;xq<5;xq++)
      arc((X0+X1)/2,(Y0+Y1)/2,270,180,10+xq);
     for(xq=(X0+X1)/2-17;xq<=(X0+X1)/2-7;xq++)
      line(xq,(Y0+Y1)/2,(X0+X1)/2-12,(Y0+Y1)/2+7);
    }
   else if(mod==3)
    {
     setcolor(15);
     for(int xq=0;xq<=Y1-Y0-3;xq++)
      line(X0+1+xq,Y0+2+xq,X0+2+xq,Y0+1+xq);
     for(xq=0;xq<=Y1-Y0-3;xq++)
      line(X1-1-xq,Y0+2+xq,X1-2-xq,Y0+1+xq);
    }
   else if(mod==4)
    {
     setcolor(15);
     for(int xq=X0+4;xq<=X1-2;xq++)
      line(xq,(Y0+Y1)/2-1,xq,(Y0+Y1)/2+1);
     for(xq=Y0+2;xq<=Y1-2;xq++)
      line(X0+2,(Y0+Y1)/2,(X0+X1)/2-2,xq);
    }
   else if(mod==5)
    {
     setcolor(15);
     settextstyle(1,HORIZ_DIR,1);
     outtextxy(X0+8,Y0+5,"NEW");
     outtextxy(X0+2,Y0+20,"GAME");
    }
  }

struct BMP
 {
  char Type[2];
  unsigned long Size;
  unsigned long Reserved;
  unsigned long OffSet;
  unsigned long headsize;
  unsigned long Width;
  unsigned long Height;
  unsigned int Planes;
  unsigned int BitsPerPixel;
  unsigned long Compression;
  unsigned long SizeImage;
  unsigned long XPixelsPreMeter;
  unsigned long YPixelsPreMeter;
  unsigned long ColorsUsed;
  unsigned long ColorsImportant;
 };

void pawn(int,int);
void rook(int,int);
void knight(int,int);
void bishop(int,int);
void queen(int,int);
void king(int,int);
void showboard();
void check(int,int,int);

class Game
 {
  int p1movesfrom[250][2],p1movesto[250][2],p2movesfrom[250][2];
  int noofmoves1,noofmoves2,undoep1[8][2],undoep2[8][2],p2movesto[250][2];
  int finalboard[8][8],p1c[8][2],p2c[8][2],cc1[3],cc2[3],p1pieces[5][9];
  int previousstatus[250],psc,move_50,p1cnt[5],p2cnt[5],p2pieces[5][9];
  public :
  int gameno,status;
  char p1name[25],p2name[25];
  Game();
  void getname(int);
  void record();
  void display();
  void startit();
  void resume();
 }g,r[3];

Game::Game()
 {
  int i,j;
  gamenumber=1;
  gameno=gamenumber;
  strcpy(p1name,"Player 1");
  strcpy(p2name,"Player 2");
  for(i=0;i<3;i++)
   {
    cc1[i]=0;
    cc2[i]=0;
   }
  for(i=0;i<5;i++)
   for(j=0;j<9;j++)
   {
    p1cnt[i]=p1ctr[i];
    p2cnt[i]=p1ctr[i];
    p1pieces[i][j]=p1p[i][j];
    p2pieces[i][j]=p2p[i][j];
   }
  for(i=0;i<250;i++)
   for(j=0;j<2;j++)
    {
     p1mf[i][j]=0;
     p1mt[i][j]=0;
     p2mf[i][j]=0;
     p2mt[i][j]=0;
     p1movesfrom[i][j]=p1mf[i][j];
     p1movesto[i][j]=p1mt[i][j];
     p2movesfrom[i][j]=p2mf[i][j];
     p2movesto[i][j]=p2mt[i][j];
    }
  for(i=0;i<8;i++)
   for(j=0;j<8;j++)
    finalboard[i][j]=ch[i][j];
  status=stat;
  for(i=0;i<250;i++)
   {
    prevstat[i]=0;
    previousstatus[i]=prevstat[i];
   }
  for(i=0;i<8;i++)
   for(j=0;j<8;j++)
    {
     undoep1[i][j]=0;
     undoep2[i][j]=0;
     p1c[i][j]=0;
     p2c[i][j]=0;
    }
  psc=prevstatctr;
  noofmoves1=nomoves1;
  noofmoves2=nomoves2;
  move_50=move50;
 }

void Game::getname(int v)
 {
  int che;
  if(v==0)
   {
    buton X,OK;
    setcolor(0);
    rectangle(getmaxx()/2-201,getmaxy()/2-51,getmaxx()/2+200,getmaxy()/2+51);
    rectangle(getmaxx()/2-202,getmaxy()/2-52,getmaxx()/2+201,getmaxy()/2+52);
    setcolor(9);
    for(int k=0;k<400;k++)
     line(getmaxx()/2-200+k,getmaxy()/2-50,getmaxx()/2-200+k,getmaxy()/2+50);
    X.createbutton("",getmaxx()/2+185,getmaxy()/2-47,getmaxx()/2+195,getmaxy()/2-37,3,1,4,1,3);
    OK.createbutton("OK",464,234,504,264,3,1,1,3);
    setcolor(15);
    settextstyle(1,HORIZ_DIR,3);
    outtextxy(getmaxx()/2-190,getmaxy()/2-50,"ENTER YOUR NAMES");
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(130,220,"PLAYER 1 : ");
    outtextxy(130,248,"PLAYER 2 : ");
    setcolor(0);
    for(i=280;i<=450;i++)
     {
      line(i,223,i,240);
     }
    gotoxy(37,15);cout<<name1;
    for(i=280;i<=450;i++)
     {
      line(i,255,i,272);
     }
    gotoxy(37,17);cout<<name2;
    while(!kbhit()||getch()!=27)
     {
      in.x.ax=3;
      x=in.x.cx;
      y=in.x.dx;
      int86(0x33,&in,&in);
      if(X.Getfocus()==1)
       return;
      if(OK.Getfocus()==1)
       {
	strcpy(g.p1name,name1);
	strcpy(g.p2name,name2);
	return;
       }
      if(x>280&&x<450&&y<243&&y>223&&in.x.bx==0)
       {
	setcolor(1);
	rectangle(278,221,452,242);
       }
      else
       {
	setcolor(3);
	rectangle(278,221,452,242);
       }
      if(x>280&&x<450&&y<240&&y>223&&in.x.bx==1)
       {
	che=0;
	setcolor(0);
	for(i=280;i<=450;i++)
	 line(i,223,i,240);
	setcolor(4);
	rectangle(278,221,452,242);
	gotoxy(37,15);
	for(i=0;i<10;i++)
	 name1[i]=' ';
	name1[i]='\0';
	n1=0;
	while(che==0)
	 {
	  if(n1<=9)
	   {
	    setcolor(9);
	    for(i=130;i<=270;i++)
	     line(i,243,i,249);
	   }
	  name1[n1]=getch();
	  n1++;
	  if(name1[n1-1]=='\n'||name1[n1-1]=='\r'||name1[n1-1]=='\t')
	   {
	    che=1;
	    n1--;
	    name1[n1]='\0';
	   }
	  else if(name1[n1-1]=='\b')
	   {
	    n1--;
	    name1[n1]=' ';
	    if(n1!=0)
	     {
	      cout<<"\b \b";
	      n1--;
	     }
	   }
	  else if(n1>10)
	   {
	    n1--;
	    name1[n1]=' ';
	    setcolor(4);
	    settextstyle(0,HORIZ_DIR,1);
	    outtextxy(130,243,"MAX 10 CHARACTERS");
	   }
	  else
	   {
	    cout<<name1[n1-1];
	   }
	 }
	setcolor(3);
	rectangle(278,221,452,242);
       }
      if(x>280&&x<450&&y<272&&y>255&&in.x.bx==0)
       {
	setcolor(1);
	rectangle(278,253,452,274);
       }
      else
       {
	setcolor(3);
	rectangle(278,253,452,274);
       }
      if(x>280&&x<450&&y<272&&y>255&&in.x.bx==1||che==1)
       {
	che=0;
	setcolor(0);
	for(i=280;i<=450;i++)
	 {
	  line(i,255,i,272);
	 }
	setcolor(4);
	rectangle(278,253,452,274);
	gotoxy(37,17);
	for(i=0;i<10;i++)
	 name2[i]=' ';
	name2[0]='\0';
	n2=0;
	while(che==0)
	 {
	  if(n2<=9)
	   {
	    setcolor(9);
	    for(i=130;i<=270;i++)
	     line(i,271,i,277);
	   }
	  name2[n2]=getch();
	  n2++;
	  if(name2[n2-1]=='\n'||name2[n2-1]=='\r'||name2[n2-1]=='\t')
	   {
	    che=2;
	    n2--;
	    name2[n2]='\0';
	   }
	  else if(name2[n2-1]=='\b')
	   {
	    n2--;
	    name2[n2]=' ';
	    if(n2!=0)
	     {
	      cout<<"\b \b";
	      n2--;
	     }
	   }
	  else if(n2>10)
	   {
	    n2--;
	    name2[n2]=' ';
	    setcolor(4);
	    settextstyle(0,HORIZ_DIR,1);
	    outtextxy(130,271,"MAX 10 CHARACTERS");
	   }
	  else
	   {
	    cout<<name2[n2-1];
	   }
	 }
	setcolor(3);
	rectangle(278,253,452,274);
       }
     }
   }
 }

void Game::record()
 {
  gameno=gamenumber;
  strcpy(p1name,name1);
  strcpy(p2name,name2);
  for(i=0;i<3;i++)
  {
   cc1[i]=castlecheck1[i];
   cc2[i]=castlecheck2[i];
  }
  for(i=0;i<5;i++)
   for(j=0;j<9;j++)
   {
    p1cnt[i]=p1ctr[i];
    p2cnt[i]=p2ctr[i];
    p1pieces[i][j]=p1p[i][j];
    p2pieces[i][j]=p2p[i][j];
   }
  for(i=0;i<250;i++)
   for(j=0;j<2;j++)
    {
     p1movesfrom[i][j]=p1mf[i][j];
     p1movesto[i][j]=p1mt[i][j];
     p2movesfrom[i][j]=p2mf[i][j];
     p2movesto[i][j]=p2mt[i][j];
    }
  for(i=0;i<8;i++)
   {
   for(j=0;j<2;j++)
    {
     undoep1[i][j]=revenp1[i][j];
     undoep2[i][j]=revenp2[i][j];
     p1c[i][j]=p1changed[i][j];
     p2c[i][j]=p2changed[i][j];
    }
   }
  for(i=0;i<8;i++)
   {
    for(j=0;j<8;j++)
     {
      finalboard[i][j]=ch[i][j];
     }
   }
  status=stat;
  for(i=0;i<prevstatctr;i++)
   {
    previousstatus[i]=prevstat[i];
   }
  psc=prevstatctr;
  noofmoves1=nomoves1;
  noofmoves2=nomoves2;
  move_50=move50;
  itoa(gameno,gamefile,10);
  strcat(gamefile,"MP.dat");
  ofstream f(gamefile,ios::out|ios::binary);
  f.write((char*)&g,sizeof(g));
  f.close();
 }

void Game::display()
 {
  char m[5];
  itoa(gameno,gamefile,10);
  strcat(gamefile,"MP.dat");
  ifstream f(gamefile,ios::in|ios::binary);
  f.read((char*)&g,sizeof(g));
  setcolor(0);
  rectangle(6,100,188,278);
  rectangle(7,101,187,277);
  rectangle(9,103,185,275);
  settextstyle(1,HORIZ_DIR,1);
  outtextxy(15,110,g.p1name);
  settextstyle(0,HORIZ_DIR,2);
  if(move_50>0&&move_50<51)
   {
    itoa(move_50,m,10);
    settextstyle(0,HORIZ_DIR,1);
    outtextxy(17,130,"stalemate count : ");
    outtextxy(162,130,m);
   }
  else if(move_50>50&&move_50<101)
   {
    itoa(move_50-50,m,10);
    setcolor(15);
    settextstyle(0,HORIZ_DIR,1);
    outtextxy(17,315,"stalemate count : ");
    outtextxy(162,315,m);
   }
  setcolor(0);
  settextstyle(0,HORIZ_DIR,2);
  if(status==3)
   outtextxy(25,140,"Your Move");
  else if(status==5)
   {
    settextstyle(0,HORIZ_DIR,8);
    outtextxy(260,190,"CHECK");
    delay(500);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(60,140,"CHECK");
   }
  x=17;y=160;
  for(i=0;i<5;i++)
   {
    for(j=0;j<p1pieces[i][0];j++)
     {
      if(i==0)
       pawn(x,y);
      else if(i==1)
       rook(x,y);
      else if(i==2)
       knight(x,y);
      else if(i==3)
       bishop(x,y);
      else if(i==4)
       queen(x,y);
      x+=30;
      if(x==167)
       {
	x-=150;
	y+=38;
       }
     }
   }
  setcolor(15);
  rectangle(6,284,188,460);
  rectangle(7,285,187,459);
  rectangle(9,287,185,457);
  settextstyle(1,HORIZ_DIR,1);
  outtextxy(15,294,g.p2name);
  settextstyle(0,HORIZ_DIR,2);
  if(status==4)
   {
    outtextxy(25,324,"Your Move");
   }
  else if(status==6)
   {
    settextstyle(0,HORIZ_DIR,8);
    outtextxy(260,190,"CHECK");
    delay(500);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(60,324,"CHECK");
   }
  setcolor(7);
  x=17;y=344;
  for(i=0;i<5;i++)
   {
    for(j=0;j<p2pieces[i][0];j++)
     {
      if(i==0)
       {
	pawn(x,y);
       }
      else if(i==1)
       {
	rook(x,y);
       }
      else if(i==2)
       {
	knight(x,y);
       }
      else if(i==3)
       {
	bishop(x,y);
       }
      else if(i==4)
       {
	queen(x,y);
       }
      x+=30;
      if(x==167)
       {
	x-=150;
	y+=38;
       }
     }
   }
  if(status==0)
   {
    setcolor(0);
    rectangle(6,100,188,460);
    rectangle(7,101,187,459);
    rectangle(9,103,185,457);
    for(i=0;i<15;i++)
     {
      setcolor(i);
      for(j=0;j<=174;j++)
       {
	line(10+j,104,10+j,456);
       }
      delay(100);
     }
    setcolor(14);
    for(j=0;j<=174;j++)
     {
      line(10+j,104,10+j,456);
     }
    setcolor(4);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(75,140,"OOPS");
    outtextxy(40,200,"WELL PLAYED");
    outtextxy(40,230,p1name);
    outtextxy(86,260,"&");
    outtextxy(40,290,p2name);
    outtextxy(40,320,"WELL PLAYED");
    outtextxy(50,350,"ENDS IN A");
    outtextxy(50,380,"STALEMATE");
   }
  if(status==1)
   {
    for(i=0;i<15;i++)
     {
      setcolor(i);
      for(j=0;j<=174;j++)
       line(10+j,104,10+j,274);
      delay(100);
     }
    setcolor(14);
    for(j=0;j<=174;j++)
     {
      line(10+j,104,10+j,274);
     }
    setcolor(4);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(65,130,"OOPS");
    outtextxy(50,160,p2name);
    outtextxy(65,190,"SAYS");
    outtextxy(40,220,"CHECKMATE");
   }
  if(status==2)
   {
    for(i=0;i<15;i++)
     {
      setcolor(i);
      for(j=0;j<=174;j++)
       {
	line(10+j,288,10+j,456);
       }
      delay(100);
     }
    setcolor(14);
    for(j=0;j<=174;j++)
     {
      line(10+j,284,10+j,456);
     }
    setcolor(4);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(65,290,"OOPS");
    outtextxy(50,320,p1name);
    outtextxy(65,350,"SAYS");
    outtextxy(40,380,"CHECKMATE");
   }
  f.close();
 }

void Game::startit()
 {
  gameno=gamenumber;
  for(i=0;i<3;i++)
   {
    cc1[i]=castlecheck1[i];
    cc2[i]=castlecheck2[i];
   }
  strcpy(p1name,name1);
  strcpy(p2name,name2);
  for(i=0;i<5;i++)
   {
    p1pieces[i][0]=p1p[i][0];
    p1pieces[i][1]=p1p[i][1];
    p2pieces[i][0]=p2p[i][0];
    p2pieces[i][1]=p2p[i][1];
   }
  for(i=0;i<250;i++)
   for(j=0;j<2;j++)
    {
     p1movesfrom[i][j]=p1mf[i][j];
     p1movesto[i][j]=p1mt[i][j];
     p2movesfrom[i][j]=p2mf[i][j];
     p2movesto[i][j]=p2mt[i][j];
    }
  for(i=0;i<8;i++)
   for(j=0;j<8;j++)
    {
     finalboard[i][j]=ch[i][j];
    }
  status=stat;
  for(i=0;i<8;i++)
   for(j=0;j<2;j++)
    {
     undoep1[i][j]=revenp1[i][j];
     undoep2[i][j]=revenp2[i][j];
     p1c[i][j]=p1changed[i][j];
     p2c[i][j]=p2changed[i][j];
    }
  for(i=0;i<250;i++)
   {
    prevstat[i]=0;
    previousstatus[i]=prevstat[i];
   }
  psc=prevstatctr;
  noofmoves1=nomoves1;
  noofmoves2=nomoves2;
  move_50=move50;
 }

void Game::resume()
 {
  for(i=0;i<250;i++)
   {
   for(j=0;j<2;j++)
    {
     p1mf[i][j]=p1movesfrom[i][j];
     p2mf[i][j]=p2movesfrom[i][j];
     p1mt[i][j]=p1movesto[i][j];
     p2mt[i][j]=p2movesto[i][j];
    }
   }
  nomoves1=noofmoves1;
  nomoves2=noofmoves2;
  for(i=0;i<3;i++)
   {
    castlecheck1[i]=cc1[i];
    castlecheck2[i]=cc2[i];
   }
  for(i=0;i<8;i++)
   {
   for(j=0;j<2;j++)
    {
     revenp1[i][j]=undoep1[i][j];
     revenp2[i][j]=undoep2[i][j];
     p1changed[i][j]=p1c[i][j];
     p2changed[i][j]=p2c[i][j];
    }
   }
  move50=move_50;
  for(i=0;i<8;i++)
   {
    for(j=0;j<8;j++)
     {
      ch[i][j]=finalboard[i][j];
     }
   }
  for(i=0;i<250;i++)
   {
    prevstat[i]=previousstatus[i];
   }
  prevstatctr=psc;
  gamenumber=gameno;
  stat=status;
  strcpy(name1,p1name);
  strcpy(name2,p2name);
  for(i=0;i<5;i++)
   for(j=0;j<9;j++)
   {
    p1ctr[i]=p1cnt[i];
    p2ctr[i]=p2ctr[i];
    p1p[i][j]=p1pieces[i][j];
    p2p[i][j]=p2pieces[i][j];
   }
 }

int recentgames(int kl=0)
 {
  buton X,LEFT,RIGHT,G[3];
  char numb[5];
  int nos=0,pgno=0,fg[3],pages=0,pole=3,zerocheck=0;
  int notfound=1;
  while(notfound!=-1)
   {
    itoa(notfound,gamefile,10);
    strcat(gamefile,"MP.dat");
    ifstream f(gamefile,ios::nocreate|ios::binary);
    if(f)
     {
      notfound++;
      zerocheck=1;
      f.read((char*)&g,sizeof(g));
      f.close();
     }
    else
     notfound=-1;
   }
  nos=g.gameno;
  if(kl==1)
   {
    if(zerocheck==0)
     return nos;
    else
     return nos+1;
   }
  pgno=nos;
  pages=nos/3;
  if(nos%3!=0)
   {
    pages++;
   }
  move:
  cleardevice();
  setbkcolor(9);
  setcolor(3);
  rectangle(0,0,getmaxx(),getmaxy());
  setcolor(5);
  rectangle(4,4,getmaxx()-4,18);
  setfillstyle(1,5);
  floodfill(5,5,5);
  setcolor(15);
  settextstyle(0,HORIZ_DIR,1);
  outtextxy(10,8,"chess.exe");
  X.createbutton("",getmaxx()-30,7,getmaxx()-10,17,3,1,4,1,4);
  setcolor(15);
  settextstyle(1,HORIZ_DIR,8);
  outtextxy(30,10,"RECENT GAMES");
  setcolor(4);
  rectangle(39,109,getmaxx()-39,461);
  setcolor(3);
  for(i=40;i<=getmaxx()-40;i++)
   {
    line(i,110,i,460);
   }
  LEFT.createbutton("<<",46,116,80,135,3,1,1,1);
  RIGHT.createbutton(">>",555,116,590,135,3,1,1,1);
  setcolor(6);
  settextstyle(1,HORIZ_DIR,2);
  outtextxy(45,150,"GAME NO.");
  outtextxy(175,150,"P1 NAME");
  outtextxy(305,150,"-");
  outtextxy(360,150,"P2 NAME");
  outtextxy(505,150,"ACTION");
  setcolor(4);
  line(40,143,getmaxx()-40,143);
  line(40,180,getmaxx()-40,180);
  line(40,273,getmaxx()-40,273);
  line(40,366,getmaxx()-40,366);
  line(150,144,150,460);
  line(475,144,475,460);
  if(zerocheck==0)
   {
    X.createbutton("",getmaxx()-30,7,getmaxx()-10,17,3,1,4,1,4);
    while(!kbhit()||getch()!=27)
     {
      in.x.ax=3;
      x=in.x.cx;
      y=in.x.dx;
      int86(0x33,&in,&in);
      if(X.Getfocus()==1)
       {
	return 0;
       }
     }
   }
  j=pgno;
  pole=3;
  if(pgno%3==2)
   {
    pole=2;
   }
  else if(pgno%3==1)
   {
    pole=1;
   }
  for(i=0;j>pgno-pole;j--,i++)
   {
    fg[i]=j;
    itoa(j,gamefile,10);
    strcat(gamefile,"MP.dat");
    ifstream f(gamefile,ios::in|ios::binary);
    f.read((char*)&(r[i]),sizeof(r[i]));
    setcolor(15);
    settextstyle(1,HORIZ_DIR,3);
    itoa(r[i].gameno,numb,10);
    outtextxy(82,205+(i*93),numb);
    settextstyle(1,HORIZ_DIR,2);
    outtextxy(170,200+(i*93),r[i].p1name);
    setcolor(4);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(300,205+(i*93),"VS");
    setcolor(15);
    settextstyle(1,HORIZ_DIR,2);
    outtextxy(350,200+(i*93),r[i].p2name);
    if(r[i].status>2&&r[i].status<7)
     {
      setcolor(14);
      settextstyle(1,HORIZ_DIR,2);
      outtextxy(292,240+(i*93),"DNF");
      G[i].createbutton("CONTINUE",483,210+(i*93),593,237+(i*93),3,1,1,2);
     }
    else if(r[i].status==1)
     {
      setcolor(14);
      settextstyle(1,HORIZ_DIR,2);
      outtextxy(200,240+(i*93),"LOST");
      outtextxy(390,240+(i*93),"WON");
      G[i].createbutton("RE-MATCH",483,210+(i*93),593,237+(i*93),3,1,1,2);
     }
    else if(r[i].status==2)
     {
      setcolor(14);
      settextstyle(1,HORIZ_DIR,2);
      outtextxy(200,240+(i*93),"WON");
      outtextxy(390,240+(i*93),"LOST");
      G[i].createbutton("RE-MATCH",483,210+(i*93),593,237+(i*93),3,1,1,2);
     }
    else if(r[i].status==0)
     {
      setcolor(14);
      settextstyle(1,HORIZ_DIR,2);
      outtextxy(255,240+(i*93),"STALEMATE");
      G[i].createbutton("RE-MATCH",483,210+(i*93),593,237+(i*93),3,1,1,2);
     }
    f.close();
   }
  while(!kbhit()||getch()!=27)
   {
    in.x.ax=3;
    x=in.x.cx;
    y=in.x.dx;
    int86(0x33,&in,&in);
    if(X.Getfocus()==1)
     {
      return 0;
     }
    if(G[0].Getfocus()==1)
     {
      itoa(fg[0],gamefile,10);
      strcat(gamefile,"MP.dat");
      ifstream f(gamefile,ios::in|ios::binary);
      f.read((char*)&g,sizeof(g));
      f.close();
      if(g.status>2&&g.status<7)
       {
	return 1;
       }
      else
       {
	strcpy(name1,g.p1name);
	strcpy(name2,g.p2name);
	return 2;
       }
     }
    if(pole>=2)
    {
    if(G[1].Getfocus()==1)
     {
      itoa(fg[1],gamefile,10);
      strcat(gamefile,"MP.dat");
      ifstream f(gamefile,ios::in|ios::binary);
      f.read((char*)&g,sizeof(g));
      f.close();
      if(g.status>2&&g.status<7)
       return 1;
      else
       {
	strcpy(name1,g.p1name);
	strcpy(name2,g.p2name);
	return 2;
       }
     }
    }
    if(pole==3)
    if(G[2].Getfocus()==1)
     {
      itoa(fg[2],gamefile,10);
      strcat(gamefile,"MP.dat");
      ifstream f(gamefile,ios::in|ios::binary);
      f.read((char*)&g,sizeof(g));
      f.close();
      if(g.status>2&&g.status<7)
       {
	return 1;
       }
      else
       {
	strcpy(name1,g.p1name);
	strcpy(name2,g.p2name);
	return 2;
       }
     }
    if(pgno>3)
     {
      if(LEFT.Getfocus()==1)
       {
	if(pgno!=pages*3)
	 {
	  pgno-=nos%3;
	 }
	else
	 {
	  pgno-=3;
	 }
	pages--;
	goto move;
       }
     }
    if(pgno<nos)
     {
      if(RIGHT.Getfocus()==1)
       {
	pages++;
	if(pgno+(nos%3)==nos)
	 {
	  pgno+=nos%3;
	 }
	else
	 {
	  pgno+=3;
	 }
	goto move;
       }
     }
   }
  return 0;
 }

void ShowBMP(int x, int y, char* FileName)
{
 int b,a;
 struct BMP Obj;
 unsigned char* Datas;
int in=0;
unsigned char c=0; FILE * fp; fp = fopen(FileName,"rb");

if(!fp)
 {
 printf("Error : Unable to open file ..");
 exit(0);
 }
 fread(&Obj, sizeof(Obj), 1, fp);
 if(Obj.BitsPerPixel!=4)
 {
  fclose(fp);
  printf("Error : File format not supported ..");
  exit(0);
 };
  fseek(fp,Obj.OffSet,SEEK_SET);
  Datas=(unsigned char*) calloc(Obj.Width/2+1, sizeof(unsigned char));
  for(b=Obj.Height-1;b>=0;b--)
   {
   fread(Datas, sizeof(unsigned char), Obj.Width/2, fp);
   c=0; in=0;
   for(a=0;a<Obj.Width;a+=2)
   {
    c = (Datas[in] | 0x00) >>4;
    putpixel(a+x,b+y,c);
    c = (Datas[in] | 0xF0) & 0x0F;
    putpixel(a+1+x,b+y,c); in++;
   }
  }
 free (Datas);
 fclose(fp);
 }

initmouse()
 {
  in.x.ax=0;
  int86(0x33,&in,&out);
  return(out.x.ax);
 }

void showmouseptr()
 {
  in.x.ax=1;
  int86(0x33,&in,&out);
 }

int buton::Getfocus()
  {
    if(x>X0&&y>Y0&&x<X1&&y<Y1&&in.x.bx==0)
      {
       if(flag==0)
       {
       flag=1;
       setcolor(8);
       rectangle(X0,Y0,X1,Y1);
       for(int id=X0+1;id<=X1-1;id++)
	line(id,Y0+1,id,Y1-1);
       Display(DESIGN);
       return 0;
       }
       else
       {
	return 0;
       }
      }
     else if(x>X0&&y>Y0&&x<X1&&y<Y1&&in.x.bx==1)
      {
       setcolor(12);
       rectangle(X0+2,Y0-1,X1+2,Y1-1);
       for(int idb=X0+2;idb<=X1+2;idb++)
	line(idb,Y0-1,idb,Y1-1);
       Display(DESIGN);
       delay(200);
       setcolor(COLOUR);
       bar3d(X0,Y0,X1,Y1,DEPTH,TOP_FLAG);
       for(idb=X0+1;idb<=X1-1;idb++)
	line(idb,Y0+1,idb,Y1-1);
       Display(DESIGN);
       delay(300);
       return 1;
      }
     else if(flag==1)
      {
       flag=0;
       setcolor(COLOUR);
       bar3d(X0,Y0,X1,Y1,DEPTH,TOP_FLAG);
       setcolor(COLOUR);
       for(int ida=X0+1;ida<=X1-1;ida++)
	line(ida,Y0+1,ida,Y1-1);
       Display(DESIGN);
       return 0;
      }
   return 0;
  }

int buton::Getresponce(int h)
 {
  int row=-1,column=-1;
  if(h==1)
   flag=1;
  if(x>X0&&y>Y0&&x<X1&&y<Y1&&in.x.bx==0)
   {
    if(flag==0)
    {
    flag=1;
    setcolor(1);
    arc(X0+2,Y0+2,270,0,5);
    arc(X0+48,Y0+2,180,270,5);
    arc(X0+2,Y0+48,0,90,5);
    arc(X0+48,Y0+48,90,180,5);
    line(X0+7,Y0+2,X0+43,Y0+2);
    line(X0+7,Y0+48,X0+43,Y0+48);
    line(X0+2,Y0+7,X0+2,Y0+43);
    line(X0+48,Y0+7,X0+48,Y0+43);
    return 0;
    }
    else
     return 0;
   }
  else if(x>X0&&y>Y0&&x<X1&&y<Y1&&in.x.bx==1)
   {
    if(flag!=2)
    {
    setcolor(1);
    for(int i=0;i<=22;i++)
    {
    arc(X0+2,Y0+2,270,0,5+i);
    arc(X0+48,Y0+2,180,270,5+i);
    arc(X0+2,Y0+48,0,90,5+i);
    arc(X0+48,Y0+48,90,180,5+i);
    line(X0+7,Y0+2+i,X0+43,Y0+2+i);
    line(X0+7,Y0+48-i,X0+43,Y0+48-i);
    line(X0+2+i,Y0+7,X0+2+i,Y0+43);
    line(X0+48-i,Y0+7,X0+48-i,Y0+43);
    }
    if(PIECE>0&&PIECE<7)
     {
      setcolor(0);
     }
    else if(PIECE>6&&PIECE<13)
     {
      setcolor(7);
     }
    if(PIECE==1)
     {
      pawn(X0+5,Y0+3);
     }
    else if(PIECE==2)
     {
      rook(X0+5,Y0+3);
     }
    else if(PIECE==3)
     {
      knight(X0+5,Y0+3);
     }
    else if(PIECE==4)
     {
      bishop(X0+5,Y0+3);
     }
    else if(PIECE==5)
     {
      queen(X0+5,Y0+3);
     }
    else if(PIECE==6)
     {
      king(X0+5,Y0+3);
     }
    else if(PIECE==7)
     {
      pawn(X0+5,Y0+3);
     }
    else if(PIECE==8)
     {
      rook(X0+5,Y0+3);
     }
    else if(PIECE==9)
     {
      knight(X0+5,Y0+3);
     }
    else if(PIECE==10)
     bishop(X0+5,Y0+3);
    else if(PIECE==11)
     queen(X0+5,Y0+3);
    else if(PIECE==12)
     king(X0+5,Y0+3);
    flag=2;
    return 1;
    }
    return 0;
   }
  else if(flag==1||flag==2)
   {
    flag=0;
    int aa=610,bb=-10,cc=0,i,j;
    for(i=0;i<8;i++)
     {
      aa-=400;
      bb+=50;
      if(cc==0)
       cc=1;
      else
       cc=0;
      for(j=0;j<8;j++)
       {
	if(cc==0)
	 cc=1;
	else
	 cc=0;
	if(X0==aa&&Y0==bb)
	 {
	  if(cc==0)
	   setfillstyle(1,15);
	  else
	   setfillstyle(1,6);
	  break;
	 }
	aa+=50;
       }
     }
    bar(X0,Y0,X1,Y1);
    if(flag1==0)
    {
    if(PIECE>0&&PIECE<7)
     setcolor(0);
    else if(PIECE>6&&PIECE<13)
     setcolor(7);
    if(PIECE==1)
     pawn(X0+5,Y0+3);
    else if(PIECE==2)
     rook(X0+5,Y0+3);
    else if(PIECE==3)
     knight(X0+5,Y0+3);
    else if(PIECE==4)
     bishop(X0+5,Y0+3);
    else if(PIECE==5)
     queen(X0+5,Y0+3);
    else if(PIECE==6)
     king(X0+5,Y0+3);
    else if(PIECE==7)
     pawn(X0+5,Y0+3);
    else if(PIECE==8)
     rook(X0+5,Y0+3);
    else if(PIECE==9)
     knight(X0+5,Y0+3);
    else if(PIECE==10)
     bishop(X0+5,Y0+3);
    else if(PIECE==11)
     queen(X0+5,Y0+3);
    else if(PIECE==12)
     king(X0+5,Y0+3);
    }
    else
    {
     for(int zz=0;zz<bcount;zz++)
      {
       row=-1;column=-1;aa=610;bb=-10;
       for(i=0;i<8;i++)
       {
	row++;
	column=-1;
	aa-=400;
	bb+=50;
	for(j=0;j<8;j++)
	 {
	  column++;
	  if(aa==p[zz].ax&&p[zz].ay==bb)
	   goto backjump;
	  aa+=50;
	 }
       }
      backjump:
      if(ch[row][column]>0&&ch[row][column]<7)
       setcolor(0);
      else if(ch[row][column]>6&&ch[row][column]<13)
       setcolor(7);
      if(ch[row][column]==1)
       pawn(aa+5,bb+3);
      else if(ch[row][column]==2)
       rook(aa+5,bb+3);
      else if(ch[row][column]==3)
       knight(aa+5,bb+3);
      else if(ch[row][column]==4)
       bishop(aa+5,bb+3);
      else if(ch[row][column]==5)
       queen(aa+5,bb+3);
      else if(ch[row][column]==6)
       king(aa+5,bb+3);
      else if(ch[row][column]==7)
       pawn(aa+5,bb+3);
      else if(ch[row][column]==8)
       rook(aa+5,bb+3);
      else if(ch[row][column]==9)
       knight(aa+5,bb+3);
      else if(ch[row][column]==10)
       bishop(aa+5,bb+3);
      else if(ch[row][column]==11)
       queen(aa+5,bb+3);
      else if(ch[row][column]==12)
       king(aa+5,bb+3);
      aa=610;
      bb=-10;
      setcolor(14);
      for(int k=0;k<15;k++)
       circle(p[zz].ax+25,p[zz].ay+25,15-k);
     }
    }
    return 0;
   }
  return 0;
 }

void buton::Showpmoves()
 {
  int s,kk,ik,jk,aa=610,bb=-10,cc=0,row=-1,column=-1,fll;
  for(kk=0;kk<c;kk++)
   {
    aa=610;bb=-10;cc=0;
    for(ik=0;ik<8;ik++)
     {
      aa-=400;
      bb+=50;
      if(cc==0)
       cc=1;
      else
       cc=0;
      for(jk=0;jk<8;jk++)
       {
	if(cc==0)
	 cc=1;
	else
	 cc=0;
	if(pmoves[kk][0]==ik&&pmoves[kk][1]==jk)
	 {
	  if(cc==0)
	   setfillstyle(1,15);
	  else
	   setfillstyle(1,6);
	  goto erase1;
	 }
	aa+=50;
       }
     }
    erase1 :
    bar(aa,bb,aa+50,bb+50);
    if(ch[pmoves[kk][0]][pmoves[kk][1]]>0&&ch[pmoves[kk][0]][pmoves[kk][1]]<7)
     setcolor(0);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]>6&&ch[pmoves[kk][0]][pmoves[kk][1]]<13)
     setcolor(7);
    if(ch[pmoves[kk][0]][pmoves[kk][1]]==1)
     pawn(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==2)
     rook(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==3)
     knight(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==4)
     bishop(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==5)
     queen(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==6)
     king(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==7)
     pawn(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==8)
     rook(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==9)
     knight(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==10)
     bishop(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==11)
     queen(aa+5,bb+3);
    else if(ch[pmoves[kk][0]][pmoves[kk][1]]==12)
     king(aa+5,bb+3);
   }
  aa=610;bb=-10;
  for(ik=0;ik<8;ik++)
     {
      aa-=400;
      bb+=50;
      row++;
      column=-1;
      for(jk=0;jk<8;jk++)
       {
	column++;
	if(X0==aa&&Y0==bb)
	 goto yes;
	aa+=50;
       }
     }
  yes:
  bcount=0;
  check(PIECE,row,column);
  if(PIECE==6||PIECE==12)
   {
    for(kk=0;kk<cm;kk++)
     {
      pmoves[kk][0]=kpmoves[kk][0];
      pmoves[kk][1]=kpmoves[kk][1];
     }
    c=cm;
   }
  if(statue==1)
   {
    for(ik=0;ik<c;ik++)
     {
      fll=0;
      for(jk=0;jk<pc;jk++)
      {
       if(pcmoves[jk][0]==PIECE)
	{
	 if(pmoves[ik][0]==pcmoves[jk][1]&&pmoves[ik][1]==pcmoves[jk][2])
	  {
	   fll=1;
	  }
	}
      }
      if(fll==0)
       {
	for(kk=ik;kk<c-1;kk++)
	 {
	  pmoves[kk][0]=pmoves[kk+1][0];
	  pmoves[kk][1]=pmoves[kk+1][1];
	 }
	c--;
	ik--;
       }
     }
   }
  for(kk=0;kk<c;kk++)
  {
  aa=610;bb=-10;
  for(ik=0;ik<8;ik++)
     {
      aa-=400;
      bb+=50;
      for(jk=0;jk<8;jk++)
       {
	if(pmoves[kk][0]==ik&&pmoves[kk][1]==jk)
	 goto jump;
	aa+=50;
       }
     }
  jump:
  setcolor(14);
  for(s=0;s<15;s++)
   circle(aa+25,bb+25,15-s);
  p[bcount++].button(aa,bb,PIECE,row,column);

  }
 }

int buton::Showresponce()
 {
  int temp,row=-1,column=-1,aa=610,bb=-10,cc=0,find=0;
  if(p[jij].Getresponce()==1)
   {
    prevstat[prevstatctr]=stat;
    prevstatctr++;
    for(i=0;i<8;i++)
     {
      aa-=400;
      bb+=50;
      row++;
      column=-1;
      if(cc==0)
       cc=1;
      else
       cc=0;
      for(j=0;j<8;j++)
       {
	column++;
	if(cc==0)
	  cc=1;
	 else
	  cc=0;
	if(X0==aa&&Y0==bb)
	{
	 if(cc==0)
	  {
	   setfillstyle(1,15);
	   bar(X0,Y0,X1,Y1);
	  }
	 else
	  {
	   setfillstyle(1,6);
	   bar(X0,Y0,X1,Y1);
	  }
	 goto found;
	}
	aa+=50;
       }
     }
   found:
   for(i=0;i<c;i++)
    {
     if(pmoves[i][0]==row&&pmoves[i][1]==column)
      {
       temp=pmoves[i][0];
       pmoves[i][0]=pmoves[i+1][0];
       pmoves[i+1][0]=temp;
       temp=pmoves[i][1];
       pmoves[i][1]=pmoves[i+1][1];
       pmoves[i+1][1]=temp;
      }
    }
   c--;
   if(ch[row][column]==1)
   {
    p1p[0][0]++;
    p1p[0][p1ctr[0]++]=nomoves2;
   }
   else if(ch[row][column]==2)
   {
    p1p[1][0]++;
    p1p[1][p1ctr[1]++]=nomoves2;
   }
   else if(ch[row][column]==3)
   {
    p1p[2][0]++;
    p1p[2][p1ctr[2]++]=nomoves2;
   }
   else if(ch[row][column]==4)
   {
    p1p[3][0]++;
    p1p[3][p1ctr[3]++]=nomoves2;
   }
   else if(ch[row][column]==5)
   {
    p1p[4][0]++;
    p1p[4][p1ctr[4]++]=nomoves2;
   }
   else if(ch[row][column]==7)
   {
    p2p[0][0]++;
    p2p[0][p2ctr[0]++]=nomoves1;
   }
   else if(ch[row][column]==8)
   {
    p2p[1][0]++;
    p2p[1][p2ctr[1]++]=nomoves1;
   }
   else if(ch[row][column]==9)
   {
    p2p[2][0]++;
    p2p[2][p2ctr[2]++]=nomoves1;
   }
   else if(ch[row][column]==10)
   {
    p2p[3][0]++;
    p2p[3][p2ctr[3]++]=nomoves1;
   }
   else if(ch[row][column]==11)
   {
    p2p[4][0]++;
    p2p[4][p2ctr[4]++]=nomoves1;
   }
   if(PIECE==6||PIECE==12)
    {
     for(i=0;i<cm;i++)
      {
       if(row==castle[i][0]&&column==castle[i][1])
	find=1;
      }
    }
   if(PIECE==1)
    {
     for(i=0;i<ep1;i++)
      {
       if(row==enpassant1[i][0]&&column==enpassant1[i][1])
	find=2;
      }
    }
   if(PIECE==7)
    {
     for(i=0;i<ep2;i++)
      {
       if(row==enpassant2[i][0]&&column==enpassant2[i][1])
	find=2;
      }
    }
   if(find==0)
    {
     ch[row][column]=ch[ROW][COLUMN];
     ch[ROW][COLUMN]=0;
    }
   else if(find==2)
    {
     ch[row][column]=ch[ROW][COLUMN];
     ch[ROW][COLUMN]=0;
     if(ROW==3)
      {
       p1p[0][0]++;
       p1p[0][p1ctr[0]++]=nomoves2;
       revenp2[p1ctr[0]-1][0]=nomoves2;
       revenp2[p1ctr[0]-1][1]=7;
       ch[row+1][column]=0;
      }
     else if(ROW==4)
      {
       p2p[0][0]++;
       p2p[0][p2ctr[0]++]=nomoves1;
       revenp1[p2ctr[0]-1][0]=nomoves1;
       revenp1[p2ctr[0]-1][1]=1;
       ch[row-1][column]=0;
      }
    }
   else if(find==1)
    {
     ch[row][column]=ch[ROW][COLUMN];
     ch[ROW][COLUMN]=0;
     if(column<4)
      {
       ch[row][column+1]=ch[row][column-2];
       ch[row][column-2]=0;
      }
     else
      {
       ch[row][column-1]=ch[row][column+1];
       ch[row][column+1]=0;
      }
    }
   if(PIECE>0&&PIECE<7)
    {
     if(PIECE==6&&castlecheck1[0]==0)
      castlecheck1[0]=nomoves1;
     if(PIECE==2)
      {
       if(COLUMN==0&&castlecheck1[1]==0)
	castlecheck1[1]=nomoves1;
       if(COLUMN==7&&castlecheck1[2]==0)
	castlecheck1[2]=nomoves1;
      }
     p1mf[nomoves1][0]=row;
     p1mf[nomoves1][1]=column;
     p1mt[nomoves1][0]=ROW;
     p1mt[nomoves1][1]=COLUMN;
     nomoves1++;
     stat=4;
    }
   else if(PIECE>6&&PIECE<13)
    {
     if(PIECE==12&&castlecheck2[0]==0)
      castlecheck2[0]=nomoves2;
     if(PIECE==8)
      {
       if(COLUMN==0&&castlecheck2[1]==0)
	castlecheck2[1]=nomoves2;
       if(COLUMN==7&&castlecheck2[2]==0)
	castlecheck2[2]=nomoves2;
      }
     p2mf[nomoves2][0]=row;
     p2mf[nomoves2][1]=column;
     p2mt[nomoves2][0]=ROW;
     p2mt[nomoves2][1]=COLUMN;
     nomoves2++;
     stat=3;
    }
   return 1;
   }
  return 0;
 }

int checkking()
 {
  int l,m,n,krow,kcolumn;
  if(stat==3||stat==5)
   {
    for(l=0;l<8;l++)
     for(m=0;m<8;m++)
      {
       if(ch[l][m]==6)
	{
	 krow=l;
	 kcolumn=m;
	}
      }
    for(l=0;l<8;l++)
     for(m=0;m<8;m++)
      {
       if(ch[l][m]>6&&ch[l][m]<12)
	{
	 check(ch[l][m],l,m);
	 for(n=0;n<c;n++)
	  {
	   if(pmoves[n][0]==krow&&pmoves[n][1]==kcolumn)
	    {
	     if(stat==3)
	      stat=5;
	     return 1;
	    }
	  }
	}
      }
   }
   else if(stat==4||stat==6)
    {
     for(l=0;l<8;l++)
     for(m=0;m<8;m++)
      {
       if(ch[l][m]==12)
	{
	 krow=l;
	 kcolumn=m;
	}
      }
     for(l=0;l<8;l++)
     for(m=0;m<8;m++)
      {
       if(ch[l][m]>0&&ch[l][m]<6)
	{
	 check(ch[l][m],l,m);
	 for(n=0;n<c;n++)
	  {
	   if(pmoves[n][0]==krow&&pmoves[n][1]==kcolumn)
	    {
	     if(stat==4)
	      stat=6;
	     return 1;
	    }
	  }
	}
     }
    }
  else
   return 0;
 return 0;
 }

int checkmateking(int frow,int fcolumn,int trow,int tcolumn)
 {
  int tmp,tempstat=stat;
  tmp=ch[trow][tcolumn];
  ch[trow][tcolumn]=ch[frow][fcolumn];
  ch[frow][fcolumn]=0;
  if(checkking()==1)
   {
    stat=tempstat;
    statue=1;
    ch[frow][fcolumn]=ch[trow][tcolumn];
    ch[trow][tcolumn]=tmp;
    return 1;
   }
  else
   {
    stat=tempstat;
    ch[frow][fcolumn]=ch[trow][tcolumn];
    ch[trow][tcolumn]=tmp;
    return 0;
   }
 }

void pawn(int x,int y)
 {
  line(x+10,y+35,x+30,y+35);
  for(int i=x+10;i<=x+30;i++)
   {
    line(x+20,y+15,i,y+30);
   }
  line(x+13,y+30,x+27,y+30);
  line(x+10,y+35,x+15,y+25);
  line(x+30,y+35,x+25,y+25);
  circle(x+20,y+10,5);
 }

void rook(int x,int y)
 {
  for(int z=x+15;z<=x+25;z++)
   line(z,y+12,z,y+26);
  for(z=1;z<=3;z++)
   line(x+15-z,y+26+z,x+25+z,y+26+z);
  for(z=1;z<=3;z++)
   line(x+15-z,y+12-z,x+25+z,y+12-z);
  for(z=x+12;z<=x+28;z++)
   line(z,y+30,z,y+32);
  for(z=x+10;z<=x+30;z++)
   line(z,y+33,z,y+35);
  for(z=x+12;z<=x+28;z++)
   line(z,y+6,z,y+8);
  for(z=x+12;z<x+16;z++)
   line(z,y+3,z,y+6);
  for(z=x+18;z<x+23;z++)
   line(z,y+3,z,y+6);
  for(z=x+25;z<x+29;z++)
   line(z,y+3,z,y+6);
 }

void knight(int x,int y)
 {
   for(int z=x+7;z<=x+35;z++)
    line(z,y+33,z,y+35);
   for(z=x+9;z<=x+33;z++)
    line(z,y+30,z,y+32);
   for(z=x+13;z<=x+24;z++)
    line(z,y+14,z,y+29);
   for(z=y+14;z<=y+29;z++)
    line(x+25,z,x+29,y+29);
   for(z=x+13;z<=x+33;z++)
    line(z,y+10,z,y+13);
   for(z=y+5;z<=y+9;z++)
    line(x+13,z,x+33,y+9);
   for(z=y+6;z<=y+21;z+=3)
    line(x+7,z+3,x+12,z);
 }

void bishop(int x,int y)
 {
  for(int z=x+10;z<=x+30;z++)
   line(z,y+33,z,y+35);
  for(z=x+12;z<=x+28;z++)
   line(z,y+30,z,y+32);
  for(z=0;z<=6;z++)
   line(x+14+(z/2),y+29-z,x+26-(z/2),y+29-z);
  for(z=x+15;z<=x+25;z++)
   line(z,y+21,z,y+22);
  for(z=0;z<=4;z++)
   circle(x+20,y+15,5-z);
  for(z=x+18;z<=x+22;z++)
   line(z,y+5,z,y+10);
 }

void queen(int x,int y)
 {
  for(int z=x+10;z<=x+30;z++)
   line(z,y+33,z,y+35);
  for(z=x+12;z<=x+28;z++)
   line(z,y+30,z,y+32);
  for(z=0;z<=8;z++)
   line(x+14+(z/4),y+29-z,x+26-(z/4),y+29-z);
  for(z=x+15;z<=x+25;z++)
   line(z,y+18,z,y+20);
  for(z=x+16;z<=x+24;z++)
   line(z,y+16,z,y+17);
  for(z=0;z<=7;z++)
   line(x+16-(z/2),y+15-z,x+24+(z/2),y+15-z);
  for(z=x+14;z<=x+16;z++)
   line(z,y+6,z,y+8);
  for(z=x+24;z<=x+26;z++)
   line(z,y+6,z,y+8);
  for(z=x+18;z<=x+22;z++)
   line(z,y+5,z,y+8);
  }
void king(int x,int y)
 {
  for(int z=x+10;z<=x+30;z++)
   line(z,y+33,z,y+35);
  for(z=x+12;z<=x+28;z++)
   line(z,y+30,z,y+32);
  for(z=0;z<=6;z++)
   line(x+14+(z/3),y+29-z,x+26-(z/3),y+29-z);
  for(z=x+15;z<=x+25;z++)
   line(z,y+20,z,y+22);
  for(z=x+16;z<=x+24;z++)
   line(z,y+18,z,y+19);
  for(z=0;z<=4;z++)
   line(x+16-(z/2),y+18-z,x+24+(z/2),y+18-z);
  for(z=x+19;z<=x+21;z++)
   line(z,y+5,z,y+13);
  for(z=x+15;z<=x+25;z++)
   line(z,y+8,z,y+10);
 }

void check(int a,int fr, int fc)
 {
  c=0;
  int i,j,k,flag=0;
  switch(a)
   {
    case 1:
     ep1=0;
     if(ch[fr+1][fc]==0&&fr+1<8)
      {
       if(ch[fr+2][fc]==0&&fr==1)
	{
	 pmoves[c][0]=fr+1;
	 pmoves[c][1]=fc;
	 c++;
	 pmoves[c][0]=fr+2;
	 pmoves[c][1]=fc;
	 c++;
	}
       else
	{
	 pmoves[c][0]=fr+1;
	 pmoves[c][1]=fc;
	 c++;
	}
      }
     if(ch[fr+1][fc+1]==0&&fr==4&&ch[fr][fc+1]==7&&fc+1<8&&p2mf[nomoves2-1][0]==4&&p2mf[nomoves2-1][1]==fc+1&&p2mt[nomoves2-1][0]==6&&p2mt[nomoves2-1][1]==fc+1)
      {
       pmoves[c][0]=fr+1;
       pmoves[c][1]=fc+1;
       c++;
       enpassant1[ep1][0]=fr+1;
       enpassant1[ep1][1]=fc+1;
       ep1++;
      }
     if(ch[fr+1][fc-1]==0&&fr==4&&ch[fr][fc-1]==7&&fc-1>=0&&p2mf[nomoves2-1][0]==4&&p2mf[nomoves2-1][1]==fc-1&&p2mt[nomoves2-1][0]==6&&p2mt[nomoves2-1][1]==fc-1)
      {
       pmoves[c][0]=fr+1;
       pmoves[c][1]=fc-1;
       c++;
       enpassant1[ep1][0]=fr+1;
       enpassant1[ep1][1]=fc-1;
       ep1++;
      }
     if((ch[fr+1][fc+1]>6&&ch[fr+1][fc+1]<13)&&(fr+1<8&&fc+1<8))
      {
       pmoves[c][0]=fr+1;
       pmoves[c][1]=fc+1;
       c++;
      }
     if((ch[fr+1][fc-1]>6&&ch[fr+1][fc-1]<13)&&(fr+1<8&&fc-1>=0))
      {
       pmoves[c][0]=fr+1;
       pmoves[c][1]=fc-1;
       c++;
      }
     break;

    case 2:
     flag=0;
     for(i=fr+1;i<8;i++)
      {
       if(flag==0)
       {
       if(ch[i][fc]==0)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	}
       else if(ch[i][fc]>6&&ch[i][fc]<13)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fr-1;i>-1;i--)
      {
       if (flag==0)
       {
       if(ch[i][fc]==0)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	}
       else if(ch[i][fc]>6&&ch[i][fc]<13)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fc+1;flag==0,i<8;i++)
      {
       if(flag==0)
       {
       if(ch[fr][i]==0)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	}
       else if(ch[fr][i]>6&&ch[fr][i]<13)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fc-1;flag==0,i>=0;i--)
      {
       if(flag==0)
       {
       if(ch[fr][i]==0)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	}
       else if(ch[fr][i]>6&&ch[fr][i]<13)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     break;

    case 3:
     if((ch[fr+2][fc+1]==0||(ch[fr+2][fc+1]>6&&ch[fr+2][fc+1]<13))&&(fr+2<8&&fc+1<8))
      {
       pmoves[c][0]=fr+2;
       pmoves[c][1]=fc+1;
       c++;
      }
     if((ch[fr+2][fc-1]==0||(ch[fr+2][fc-1]>6&&ch[fr+2][fc-1]<13))&&(fr+2<8&&fc-1>=0))
      {
       pmoves[c][0]=fr+2;
       pmoves[c][1]=fc-1;
       c++;
      }
     if((ch[fr-2][fc+1]==0||(ch[fr-2][fc+1]>6&&ch[fr-2][fc+1]<13))&&(fr-2>=0&&fc+1<8))
      {
       pmoves[c][0]=fr-2;
       pmoves[c][1]=fc+1;
       c++;
      }
     if((ch[fr-2][fc-1]==0||(ch[fr-2][fc-1]>6&&ch[fr-2][fc-1]<13))&&(fr-2>=0&&fc-1>=0))
      {
       pmoves[c][0]=fr-2;
       pmoves[c][1]=fc-1;
       c++;
      }
     if((ch[fr+1][fc+2]==0||(ch[fr+1][fc+2]>6&&ch[fr+1][fc+2]<13))&&(fr+1<8&&fc+2<8))
      {
       pmoves[c][0]=fr+1;
       pmoves[c][1]=fc+2;
       c++;
      }
     if((ch[fr+1][fc-2]==0||(ch[fr+1][fc-2]>6&&ch[fr+1][fc-2]<13))&&(fr+1<8&&fc-2>=0))
      {
       pmoves[c][0]=fr+1;
       pmoves[c][1]=fc-2;
       c++;
      }
     if((ch[fr-1][fc+2]==0||(ch[fr-1][fc+2]>6&&ch[fr-1][fc+2]<13))&&(fr-1>=0&&fc+2<8))
      {
       pmoves[c][0]=fr-1;
       pmoves[c][1]=fc+2;
       c++;
      }
     if((ch[fr-1][fc-2]==0||(ch[fr-1][fc-2]>6&&ch[fr-1][fc-2]<13))&&(fr-1>=0&&fc-2>=0))
      {
       pmoves[c][0]=fr-1;
       pmoves[c][1]=fc-2;
       c++;
      }
     break;

    case 4:
     flag=0;
      for(i=fr+1,j=fc+1;i<8&&j<8;i++,j++)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>6&&ch[i][j]<13)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr+1,j=fc-1;i<8&&j>=0;i++,j--)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>6&&ch[i][j]<13)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr-1,j=fc+1;i>=0&&j<8;i--,j++)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>6&&ch[i][j]<13)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr-1,j=fc-1;i>=0&&j>=0;i--,j--)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>6&&ch[i][j]<13)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
      break;

     case 5 :
      flag=0;
      for(i=fr+1;i<8;i++)
      {
       if(flag==0)
       {
       if(ch[i][fc]==0)
	{

	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	}
       else if(ch[i][fc]>6&&ch[i][fc]<13)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fr-1;i>=0;i--)
      {
       if (flag==0)
       {
       if(ch[i][fc]==0)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	}
       else if(ch[i][fc]>6&&ch[i][fc]<13)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fc+1;i<8;i++)
      {
       if(flag==0)
       {
       if(ch[fr][i]==0)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	}
       else if(ch[fr][i]>6&&ch[fr][i]<13)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fc-1;i>=0;i--)
      {
       if (flag==0)
       {
       if(ch[fr][i]==0)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	}
       else if(ch[fr][i]>6&&ch[fr][i]<13)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
      for(i=fr+1,j=fc+1;i<8&&j<8;i++,j++)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>6&&ch[i][j]<13)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr+1,j=fc-1;i<8&&j>=0;i++,j--)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>6&&ch[i][j]<13)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr-1,j=fc+1;i>=0&&j<8;i--,j++)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>6&&ch[i][j]<13)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr-1,j=fc-1;i>=0&&j>=0;i--,j--)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>6&&ch[i][j]<13)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
      break;

     case 6:
     cm=0;
      int ii,jj,temp;
      if(stat==3)
       {
	if(fr==0&&fc==4&&ch[fr][fc+1]==0&&ch[fr][fc+2]==0&&ch[fr][fc+3]==2)
	 {
	  flag=0;
	  ch[fr][fc+2]=6;
	  ch[fr][fc+1]=2;
	  ch[fr][fc+3]=0;
	  ch[fr][fc]=0;
	  for(ii=0;ii<8;ii++)
	   for(jj=0;jj<8;jj++)
	    {
	     if(ch[ii][jj]>6&&ch[ii][jj]<12)
	      {
	       check(ch[ii][jj],ii,jj);
	       for(k=0;k<c;k++)
		if(pmoves[k][0]==fr&&(pmoves[k][1]==fc+2||pmoves[k][1]==fc+1))
		 {
		  flag=1;
		 }
	      }
	    }
	  if(ch[fr+1][fc+2]==12&&fr+1<8&&fc+2<8)
	   flag=1;
	  if(castlecheck1[2]!=0)
	   flag=1;
	  if(castlecheck1[0]!=0)
	   flag=1;
	  if(flag==0)
	   {
	    kpmoves[cm][0]=fr;
	    kpmoves[cm][1]=fc+2;
	    castle[cm][0]=fr;
	    castle[cm][1]=fc+2;
	    cm++;
	   }
	  ch[fr][fc]=6;
	  ch[fr][fc+1]=0;
	  ch[fr][fc+2]=0;
	  ch[fr][fc+3]=2;
	 }
	if(fr==0&&fc==4&&ch[fr][fc-1]==0&&ch[fr][fc-2]==0&&ch[fr][fc-3]==0&&ch[fr][fc-4]==2)
	 {
	  flag=0;
	  ch[fr][fc-2]=6;
	  ch[fr][fc-1]=2;
	  ch[fr][fc-3]=0;
	  ch[fr][fc-4]=0;
	  ch[fr][fc]=0;
	  for(ii=0;ii<8;ii++)
	   for(jj=0;jj<8;jj++)
	    {
	     if(ch[ii][jj]>6&&ch[ii][jj]<12)
	      {
	       check(ch[ii][jj],ii,jj);
	       for(k=0;k<c;k++)
		if(pmoves[k][0]==fr&&(pmoves[k][1]==fc-1||pmoves[k][1]==fc-2))
		 {
		  flag=1;
		 }
	      }
	    }
	  if(ch[fr+1][fc-2]==12&&fr+1<8&&fc-2>=0)
	   flag=1;
	  else if(ch[fr+1][fc-3]==12&&fr+1<8&&fc-3>=0)
	   flag=1;
	  if(castlecheck1[1]!=0)
	   flag=1;
	  if(castlecheck1[0]!=0)
	   flag=1;
	  if(flag==0)
	   {
	    kpmoves[cm][0]=fr;
	    kpmoves[cm][1]=fc-2;
	    castle[cm][0]=fr;
	    castle[cm][1]=fc-2;
	    cm++;
	   }
	  ch[fr][fc]=6;
	  ch[fr][fc-1]=0;
	  ch[fr][fc-2]=0;
	  ch[fr][fc-3]=0;
	  ch[fr][fc-4]=2;
	 }
       }
      flag=0;
      if((ch[fr+1][fc]==0||(ch[fr+1][fc]>6&&ch[fr+1][fc]<12))&&fr+1<8)
       {
	temp=ch[fr+1][fc];
	ch[fr+1][fc]=6;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>6&&ch[ii][jj]<12)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr+1&&pmoves[k][1]==fc)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr+2][fc]==12&&fr+2<8)
	 flag=1;
	else if(ch[fr+2][fc+1]==12&&fr+2<8&&fc+1<8)
	 flag=1;
	else if(ch[fr+2][fc-1]==12&&fr+2<8&&fc-1>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr+1;
	kpmoves[cm][1]=fc;
	cm++;
	}
	ch[fr][fc]=6;
	ch[fr+1][fc]=temp;
       }
      flag=0;
      if((ch[fr-1][fc]==0||(ch[fr-1][fc]>6&&ch[fr-1][fc]<12))&&fr-1>=0)
       {
	temp=ch[fr-1][fc];
	ch[fr-1][fc]=6;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>6&&ch[ii][jj]<12)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr-1&&pmoves[k][1]==fc)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr-2][fc]==12&&fr-2>=0)
	 flag=1;
	else if(ch[fr-2][fc+1]==12&&fr-2>=0&&fc+1<8)
	 flag=1;
	else if(ch[fr-2][fc-1]==12&&fr-2>=0&&fc-1>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr-1;
	kpmoves[cm][1]=fc;
	cm++;
	}
	ch[fr][fc]=6;
	ch[fr-1][fc]=temp;
       }
      flag=0;
      if((ch[fr][fc+1]==0||(ch[fr][fc+1]>6&&ch[fr][fc+1]<12))&&fc+1<8)
       {
	temp=ch[fr][fc+1];
	ch[fr][fc+1]=6;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>6&&ch[ii][jj]<12)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr&&pmoves[k][1]==fc+1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr][fc+2]==12&&fc+2<8)
	 flag=1;
	else if(ch[fr+1][fc+2]==12&&fr+1<8&&fc+2<8)
	 flag=1;
	else if(ch[fr-1][fc+2]==12&&fr-1>=0&&fc+2<8)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr;
	kpmoves[cm][1]=fc+1;
	cm++;
	}
	ch[fr][fc]=6;
	ch[fr][fc+1]=temp;
       }
      flag=0;
      if((ch[fr][fc-1]==0||(ch[fr][fc-1]>6&&ch[fr][fc-1]<12))&&fc-1>=0)
       {
	temp=ch[fr][fc-1];
	ch[fr][fc-1]=6;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>6&&ch[ii][jj]<12)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr&&pmoves[k][1]==fc-1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr][fc-2]==12&&fc-2>=0)
	 flag=1;
	else if(ch[fr+1][fc-2]==12&&fr+1<8&&fc-2>=0)
	 flag=1;
	else if(ch[fr-1][fc-2]==12&&fr-1>=0&&fc-2>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr;
	kpmoves[cm][1]=fc-1;
	cm++;
	}
	ch[fr][fc]=6;
	ch[fr][fc-1]=temp;
       }
      flag=0;
      if((ch[fr+1][fc+1]==0||(ch[fr+1][fc+1]>6&&ch[fr+1][fc+1]<12))&&(fr+1<8&&fc+1<8))
       {
	temp=ch[fr+1][fc+1];
	ch[fr+1][fc+1]=6;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>6&&ch[ii][jj]<12)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr+1&&pmoves[k][1]==fc+1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr+2][fc]==12&&fr+2<8)
	 flag=1;
	else if(ch[fr+2][fc+1]==12&&fr+2<8&&fc+1<8)
	 flag=1;
	else if(ch[fr][fc+2]==12&&fc+2<8)
	 flag=1;
	else if(ch[fr+1][fc+2]==12&&fr+1<8&&fc+2<8)
	 flag=1;
	else if(ch[fr+2][fc+2]==12&&fr+2<8&&fc+2<8)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr+1;
	kpmoves[cm][1]=fc+1;
	cm++;
	}
	ch[fr][fc]=6;
	ch[fr+1][fc+1]=temp;
       }
      flag=0;
      if((ch[fr+1][fc-1]==0||(ch[fr+1][fc-1]>6&&ch[fr+1][fc-1]<12))&&(fr+1<8&&fc-1>=0))
       {
	temp=ch[fr+1][fc-1];
	ch[fr+1][fc-1]=6;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>6&&ch[ii][jj]<12)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr+1&&pmoves[k][1]==fc-1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr+2][fc]==12&&fr+2<8)
	 flag=1;
	else if(ch[fr+2][fc-1]==12&&fr+2<8&&fc-1>=0)
	 flag=1;
	else if(ch[fr][fc-2]==12&&fc-2>=0)
	 flag=1;
	else if(ch[fr+1][fc-2]==12&&fr+1<8&&fc-2>=0)
	 flag=1;
	else if(ch[fr+2][fc-2]==12&&fr+2<8&&fc-2>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr+1;
	kpmoves[cm][1]=fc-1;
	cm++;
	}
	ch[fr][fc]=6;
	ch[fr+1][fc-1]=temp;
       }
      flag=0;
      if((ch[fr-1][fc+1]==0||(ch[fr-1][fc+1]>6&&ch[fr-1][fc+1]<12))&&(fr-1>=0&&fc+1<8))
       {
	temp=ch[fr-1][fc+1];
	ch[fr-1][fc+1]=6;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>6&&ch[ii][jj]<12)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr-1&&pmoves[k][1]==fc+1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr-2][fc]==12&&fr-2>=0)
	 flag=1;
	else if(ch[fr-2][fc+1]==12&&fr-2>=0&&fc+1<8)
	 flag=1;
	else if(ch[fr][fc+2]==12&&fc+2<8)
	 flag=1;
	else if(ch[fr-1][fc+2]==12&&fr-1>=0&&fc+2<8)
	 flag=1;
	else if(ch[fr-2][fc+2]==12&&fr-2>=0&&fc+2<8)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr-1;
	kpmoves[cm][1]=fc+1;
	cm++;
	}
	ch[fr][fc]=6;
	ch[fr-1][fc+1]=temp;
       }
      flag=0;
      if((ch[fr-1][fc-1]==0||(ch[fr-1][fc-1]>6&&ch[fr-1][fc-1]<12))&&(fr-1>=0&&fc-1>=0))
       {
	temp=ch[fr-1][fc-1];
	ch[fr-1][fc-1]=6;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>6&&ch[ii][jj]<12)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr-1&&pmoves[k][1]==fc-1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr-2][fc]==12&&fr-2>=0)
	 flag=1;
	else if(ch[fr-2][fc-1]==12&&fr-2>=0&&fc-1>=0)
	 flag=1;
	else if(ch[fr][fc-2]==12&&fc-2>=0)
	 flag=1;
	else if(ch[fr-1][fc-2]==12&&fr-1>=0&&fc-2>=0)
	 flag=1;
	else if(ch[fr-2][fc-2]==12&&fr-2>=0&&fc-2>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr-1;
	kpmoves[cm][1]=fc-1;
	cm++;
	}
      ch[fr][fc]=6;
      ch[fr-1][fc-1]=temp;
     }
     break;

     case 7:
      ep2=0;
      if(ch[fr-1][fc]==0&&fr-1>=0)
      {
       if(ch[fr-2][fc]==0&&fr==6)
	{
	 pmoves[c][0]=fr-1;
	 pmoves[c][1]=fc;
	 c++;
	 pmoves[c][0]=fr-2;
	 pmoves[c][1]=fc;
	 c++;
	}
       else
	{
	 pmoves[c][0]=fr-1;
	 pmoves[c][1]=fc;
	 c++;
	}
      }
     if(ch[fr-1][fc+1]==0&&fr==3&&ch[fr][fc+1]==1&&fc+1<8&&p1mf[nomoves1-1][0]==3&&p1mf[nomoves1-1][1]==fc+1&&p1mt[nomoves1-1][0]==1&&p1mt[nomoves1-1][1]==fc+1)
      {
       pmoves[c][0]=fr-1;
       pmoves[c][1]=fc+1;
       c++;
       enpassant2[ep2][0]=fr-1;
       enpassant2[ep2][1]=fc+1;
       ep2++;
      }
     if(ch[fr-1][fc-1]==0&&fr==3&&ch[fr][fc-1]==1&&fc-1>=0&&p1mf[nomoves1-1][0]==3&&p1mf[nomoves1-1][1]==fc-1&&p1mt[nomoves1-1][0]==1&&p1mt[nomoves1-1][1]==fc-1)
      {
       pmoves[c][0]=fr-1;
       pmoves[c][1]=fc-1;
       c++;
       enpassant2[ep2][0]=fr-1;
       enpassant2[ep2][1]=fc-1;
       ep2++;
      }
     if((ch[fr-1][fc+1]>0&&ch[fr-1][fc+1]<7)&&(fr-1>=0&&fc+1<8))
      {
       pmoves[c][0]=fr-1;
       pmoves[c][1]=fc+1;
       c++;
      }
     if((ch[fr-1][fc-1]>0&&ch[fr-1][fc-1]<7)&&(fr-1>=0&&fc-1>=0))
      {
       pmoves[c][0]=fr-1;
       pmoves[c][1]=fc-1;
       c++;
      }
     break;

     case 8 :
      flag=0;
      for(i=fr+1;i<8;i++)
      {
       if(flag==0)
       {
       if(ch[i][fc]==0)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	}
       else if(ch[i][fc]>0&&ch[i][fc]<7)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fr-1;flag==0&&i>=0;i--)
      {
       if(ch[i][fc]==0)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	}
       else if(ch[i][fc]>0&&ch[i][fc]<7)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	 flag=1;
	}
       else
	flag=1;
      }
     flag=0;
     for(i=fc+1;i<8;i++)
      {
       if(flag==0)
       {
       if(ch[fr][i]==0)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	}
       else if(ch[fr][i]>0&&ch[fr][i]<7)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fc-1;i>=0;i--)
      {
       if (flag==0)
       {
       if(ch[fr][i]==0)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	}
       else if(ch[fr][i]>0&&ch[fr][i]<7)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     break;

     case 9 :
      if((ch[fr+2][fc+1]==0||(ch[fr+2][fc+1]>0&&ch[fr+2][fc+1]<7))&&(fr+2<8&&fc+1<8))
      {
       pmoves[c][0]=fr+2;
       pmoves[c][1]=fc+1;
       c++;
      }
     if((ch[fr+2][fc-1]==0||(ch[fr+2][fc-1]>0&&ch[fr+2][fc-1]<7))&&(fr+2<8&&fc-1>=0))
      {
       pmoves[c][0]=fr+2;
       pmoves[c][1]=fc-1;
       c++;
      }
     if((ch[fr-2][fc+1]==0||(ch[fr-2][fc+1]>0&&ch[fr-2][fc+1]<7))&&(fr-2>=0&&fc+1<8))
      {
       pmoves[c][0]=fr-2;
       pmoves[c][1]=fc+1;
       c++;
      }
     if((ch[fr-2][fc-1]==0||(ch[fr-2][fc-1]>0&&ch[fr-2][fc-1]<7))&&(fr-2>=0&&fc-1>=0))
      {
       pmoves[c][0]=fr-2;
       pmoves[c][1]=fc-1;
       c++;
      }
     if((ch[fr+1][fc+2]==0||(ch[fr+1][fc+2]>0&&ch[fr+1][fc+2]<7))&&(fr+1<8&&fc+2<8))
      {
       pmoves[c][0]=fr+1;
       pmoves[c][1]=fc+2;
       c++;
      }
     if((ch[fr+1][fc-2]==0||(ch[fr+1][fc-2]>0&&ch[fr+1][fc-2]<7))&&(fr+1<8&&fc-2>=0))
      {
       pmoves[c][0]=fr+1;
       pmoves[c][1]=fc-2;
       c++;
      }
     if((ch[fr-1][fc+2]==0||(ch[fr-1][fc+2]>0&&ch[fr-1][fc+2]<7))&&(fr-1>=0&&fc+2<8))
      {
       pmoves[c][0]=fr-1;
       pmoves[c][1]=fc+2;
       c++;
      }
     if((ch[fr-1][fc-2]==0||(ch[fr-1][fc-2]>0&&ch[fr-1][fc-2]<7))&&(fr-1>=0&&fc-2>=0))
      {
       pmoves[c][0]=fr-1;
       pmoves[c][1]=fc-2;
       c++;
      }
     break;

     case 10 :
      flag=0;
      for(i=fr+1,j=fc+1;i<8&&j<8;i++,j++)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>0&&ch[i][j]<7)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr+1,j=fc-1;i<8&&j>=0;i++,j--)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>0&&ch[i][j]<7)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr-1,j=fc+1;i>=0&&j<8;i--,j++)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>0&&ch[i][j]<7)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr-1,j=fc-1;i>=0&&j>=0;i--,j--)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>0&&ch[i][j]<7)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
      break;

     case 11 :
      flag=0;
      for(i=fr+1;i<8;i++)
      {
       if(flag==0)
       {
       if(ch[i][fc]==0)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	}
       else if(ch[i][fc]>0&&ch[i][fc]<7)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fr-1;i>-1;i--)
      {
       if (flag==0)
       {
       if(ch[i][fc]==0)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	}
       else if(ch[i][fc]>0&&ch[i][fc]<7)
	{
	 pmoves[c][0]=i;
	 pmoves[c][1]=fc;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fc+1;flag==0,i<8;i++)
      {
       if(flag==0)
       {
       if(ch[fr][i]==0)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	}
       else if(ch[fr][i]>0&&ch[fr][i]<7)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
     flag=0;
     for(i=fc-1;flag==0,i>=0;i--)
      {
       if (flag==0)
       {
       if(ch[fr][i]==0)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	}
       else if(ch[fr][i]>0&&ch[fr][i]<7)
	{
	 pmoves[c][0]=fr;
	 pmoves[c][1]=i;
	 c++;
	 flag=1;
	}
       else
	flag=1;
       }
      }
      flag=0;
      for(i=fr+1,j=fc+1;i<8&&j<8;i++,j++)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>0&&ch[i][j]<7)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr+1,j=fc-1;i<8&&j>=0;i++,j--)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>0&&ch[i][j]<7)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr-1,j=fc+1;i>=0&&j<8;i--,j++)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>0&&ch[i][j]<7)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
     flag=0;
      for(i=fr-1,j=fc-1;i>=0&&j>=0;i--,j--)
       {
	if(flag==0)
	 {
	  if(ch[i][j]==0)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	   }
	  else if(ch[i][j]>0&&ch[i][j]<7)
	   {
	    pmoves[c][0]=i;
	    pmoves[c][1]=j;
	    c++;
	    flag=1;
	   }
	  else
	   flag=1;
	 }
       }
      break;

     case 12 :
      cm=0;
      if(stat==4)
       {
	if(fr==7&&fc==4&&ch[fr][fc+1]==0&&ch[fr][fc+2]==0&&ch[fr][fc+3]==8)
	 {
	  flag=0;
	  ch[fr][fc+2]=12;
	  ch[fr][fc+1]=8;
	  ch[fr][fc+3]=0;
	  ch[fr][fc]=0;
	  for(ii=0;ii<8;ii++)
	   for(jj=0;jj<8;jj++)
	    {
	     if(ch[ii][jj]>0&&ch[ii][jj]<6)
	      {
	       check(ch[ii][jj],ii,jj);
	       for(k=0;k<c;k++)
		if(pmoves[k][0]==fr&&(pmoves[k][1]==fc+2||pmoves[k][1]==fc+1))
		 {
		  flag=1;
		 }
	      }
	    }
	  if(ch[fr+1][fc+2]==6&&fr+1<8&&fc+2<8)
	   flag=1;
	  if(castlecheck2[2]!=0)
	   flag=1;
	  if(castlecheck2[0]!=0)
	   flag=1;
	  if(flag==0)
	   {
	    kpmoves[cm][0]=fr;
	    kpmoves[cm][1]=fc+2;
	    castle[cm][0]=fr;
	    castle[cm][1]=fc+2;
	    cm++;
	   }
	  ch[fr][fc]=12;
	  ch[fr][fc+1]=0;
	  ch[fr][fc+2]=0;
	  ch[fr][fc+3]=8;
	 }
	if(fr==7&&fc==4&&ch[fr][fc-1]==0&&ch[fr][fc-2]==0&&ch[fr][fc-3]==0&&ch[fr][fc-4]==8)
	 {
	  flag=0;
	  ch[fr][fc-2]=12;
	  ch[fr][fc-1]=8;
	  ch[fr][fc-3]=0;
	  ch[fr][fc-4]=0;
	  ch[fr][fc]=0;
	  for(ii=0;ii<8;ii++)
	   for(jj=0;jj<8;jj++)
	    {
	     if(ch[ii][jj]>0&&ch[ii][jj]<6)
	      {
	       check(ch[ii][jj],ii,jj);
	       for(k=0;k<c;k++)
		if(pmoves[k][0]==fr&&(pmoves[k][1]==fc-2||pmoves[k][1]==fc-1))
		 {
		  flag=1;
		 }
	      }
	    }
	  if(ch[fr+1][fc-2]==6&&fr+1<8&&fc-2>=0)
	   flag=1;
	  else if(ch[fr+1][fc-3]==6&&fr+1<8&&fc-3>=0)
	   flag=1;
	  if(castlecheck2[1]!=0)
	   flag=1;
	  if(castlecheck2[0]!=0)
	   flag=1;
	  if(flag==0)
	   {
	    kpmoves[cm][0]=fr;
	    kpmoves[cm][1]=fc-2;
	    castle[cm][0]=fr;
	    castle[cm][1]=fc-2;
	    cm++;
	   }
	  ch[fr][fc]=12;
	  ch[fr][fc-1]=0;
	  ch[fr][fc-2]=0;
	  ch[fr][fc-3]=0;
	  ch[fr][fc-4]=8;
	 }
       }
      flag=0;
      if((ch[fr+1][fc]==0||(ch[fr+1][fc]>0&&ch[fr+1][fc]<6))&&fr+1<8)
       {
	temp=ch[fr+1][fc];
	ch[fr+1][fc]=12;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>0&&ch[ii][jj]<6)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr+1&&pmoves[k][1]==fc)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr+2][fc]==6&&fr+2<8)
	 flag=1;
	else if(ch[fr+2][fc+1]==6&&fr+2<8&&fc+1<8)
	 flag=1;
	else if(ch[fr+2][fc-1]==6&&fr+2<8&&fc-1>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr+1;
	kpmoves[cm][1]=fc;
	cm++;
	}
	ch[fr][fc]=12;
	ch[fr+1][fc]=temp;
       }
      flag=0;
      if((ch[fr-1][fc]==0||(ch[fr-1][fc]>0&&ch[fr-1][fc]<6))&&fr-1>=0)
       {
	temp=ch[fr-1][fc];
	ch[fr-1][fc]=12;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>0&&ch[ii][jj]<6)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr-1&&pmoves[k][1]==fc)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr-2][fc]==6&&fr-2>=0)
	 flag=1;
	else if(ch[fr-2][fc+1]==6&&fr-2>=0&&fc+1<8)
	 flag=1;
	else if(ch[fr-2][fc-1]==6&&fr-2>=0&&fc-1>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr-1;
	kpmoves[cm][1]=fc;
	cm++;
	}
	ch[fr][fc]=12;
	ch[fr-1][fc]=temp;
       }
      flag=0;
      if((ch[fr][fc+1]==0||(ch[fr][fc+1]>0&&ch[fr][fc+1]<6))&&fc+1<8)
       {
	temp=ch[fr][fc+1];
	ch[fr][fc+1]=12;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>0&&ch[ii][jj]<6)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr&&pmoves[k][1]==fc+1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr][fc+2]==6&&fc+2<8)
	 flag=1;
	else if(ch[fr+1][fc+2]==6&&fr+1<8&&fc+2<8)
	 flag=1;
	else if(ch[fr-1][fc+2]==6&&fr-1>=0&&fc+2<8)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr;
	kpmoves[cm][1]=fc+1;
	cm++;
	}
	ch[fr][fc]=12;
	ch[fr][fc+1]=temp;
       }
      flag=0;
      if((ch[fr][fc-1]==0||(ch[fr][fc-1]>0&&ch[fr][fc-1]<6))&&fc-1>=0)
       {
	temp=ch[fr][fc-1];
	ch[fr][fc-1]=12;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>0&&ch[ii][jj]<6)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr&&pmoves[k][1]==fc-1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr][fc-2]==6&&fc-2>=0)
	 flag=1;
	else if(ch[fr+1][fc-2]==6&&fr+1<8&&fc-2>=0)
	 flag=1;
	else if(ch[fr-1][fc-2]==6&&fr-1>=0&&fc-2>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr;
	kpmoves[cm][1]=fc-1;
	cm++;
	}
	ch[fr][fc]=12;
	ch[fr][fc-1]=temp;
       }
      flag=0;
      if((ch[fr+1][fc+1]==0||(ch[fr+1][fc+1]>0&&ch[fr+1][fc+1]<6))&&(fr+1<8&&fc+1<8))
       {
	temp=ch[fr+1][fc+1];
	ch[fr+1][fc+1]=12;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>0&&ch[ii][jj]<6)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr+1&&pmoves[k][1]==fc+1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr+2][fc]==6&&fr+2<8)
	 flag=1;
	else if(ch[fr+2][fc+1]==6&&fr+2<8&&fc+1<8)
	 flag=1;
	else if(ch[fr][fc+2]==6&&fc+2<8)
	 flag=1;
	else if(ch[fr+1][fc+2]==6&&fr+1<8&&fc+2<8)
	 flag=1;
	else if(ch[fr+2][fc+2]==6&&fr+2<8&&fc+2<8)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr+1;
	kpmoves[cm][1]=fc+1;
	cm++;
	}
	ch[fr][fc]=12;
	ch[fr+1][fc+1]=temp;
       }
      flag=0;
      if((ch[fr+1][fc-1]==0||(ch[fr+1][fc-1]>0&&ch[fr+1][fc-1]<6))&&(fr+1<8&&fc-1>=0))
       {
	temp=ch[fr+1][fc-1];
	ch[fr+1][fc-1]=12;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>0&&ch[ii][jj]<6)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr+1&&pmoves[k][1]==fc-1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr+2][fc]==6&&fr+2<8)
	 flag=1;
	else if(ch[fr+2][fc-1]==6&&fr+2<8&&fc-1>=0)
	 flag=1;
	else if(ch[fr][fc-2]==6&&fc-2>=0)
	 flag=1;
	else if(ch[fr+1][fc-2]==6&&fr+1<8&&fc-2>=0)
	 flag=1;
	else if(ch[fr+2][fc-2]==6&&fr+2<8&&fc-2>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr+1;
	kpmoves[cm][1]=fc-1;
	cm++;
	}
	ch[fr][fc]=12;
	ch[fr+1][fc-1]=temp;
       }
      flag=0;
      if((ch[fr-1][fc+1]==0||(ch[fr-1][fc+1]>0&&ch[fr-1][fc+1]<6))&&(fr-1>=0&&fc+1<8))
       {
	temp=ch[fr-1][fc+1];
	ch[fr-1][fc+1]=12;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>0&&ch[ii][jj]<6)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr-1&&pmoves[k][1]==fc+1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr-2][fc]==6&&fr-2>=0)
	 flag=1;
	else if(ch[fr-2][fc+1]==6&&fr-2>=0&&fc+1<8)
	 flag=1;
	else if(ch[fr][fc+2]==6&&fc+2<8)
	 flag=1;
	else if(ch[fr-1][fc+2]==6&&fr-1>=0&&fc+2<8)
	 flag=1;
	else if(ch[fr-2][fc+2]==6&&fr-2>=0&&fc+2<8)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr-1;
	kpmoves[cm][1]=fc+1;
	cm++;
	}
	ch[fr][fc]=12;
	ch[fr-1][fc+1]=temp;
       }
      flag=0;
      if((ch[fr-1][fc-1]==0||(ch[fr-1][fc-1]>0&&ch[fr-1][fc-1]<6))&&(fr-1>=0&&fc-1>=0))
       {
	temp=ch[fr-1][fc-1];
	ch[fr-1][fc-1]=12;
	ch[fr][fc]=0;
	for(ii=0;ii<8;ii++)
	 for(jj=0;jj<8;jj++)
	  {
	   if(ch[ii][jj]>0&&ch[ii][jj]<6)
	    {
	     check(ch[ii][jj],ii,jj);
	     for(k=0;k<c;k++)
	      if(pmoves[k][0]==fr-1&&pmoves[k][1]==fc-1)
	      {
	       flag=1;
	      }
	    }
	  }
	if(ch[fr-2][fc]==6&&fr-2>=0)
	 flag=1;
	else if(ch[fr-2][fc-1]==6&&fr-2>=0&&fc-1>=0)
	 flag=1;
	else if(ch[fr][fc-2]==6&&fc-2>=0)
	 flag=1;
	else if(ch[fr-1][fc-2]==6&&fr-1>=0&&fc-2>=0)
	 flag=1;
	else if(ch[fr-2][fc-2]==6&&fr-2>=0&&fc-2>=0)
	 flag=1;
	if(flag==0)
	{
	kpmoves[cm][0]=fr-1;
	kpmoves[cm][1]=fc-1;
	cm++;
	}
      ch[fr][fc]=12;
      ch[fr-1][fc-1]=temp;
      }
      break;
   }
  }

void retryfn()
 {
  int charu;
  if((stat==4||stat==6||stat==2||(stat==0&&prevstat[prevstatctr-1]==1)||(stat==0&&prevstat[prevstatctr-1]==3)||(stat==0&&prevstat[prevstatctr-1]==5))&&nomoves1!=0)
   {
    if(move50>0&&move50<51)
     move50--;
    nomoves1--;
    prevstatctr--;
    for(charu=0;charu<3;charu++)
     {
      if(castlecheck1[charu]==nomoves1)
       castlecheck1[charu]=0;
     }
    stat=prevstat[prevstatctr];
    prevstat[prevstatctr]=0;
    ch[p1mt[nomoves1][0]][p1mt[nomoves1][1]]=ch[p1mf[nomoves1][0]][p1mf[nomoves1][1]];
    ch[p1mf[nomoves1][0]][p1mf[nomoves1][1]]=0;
    if(p1changed[p1mf[nomoves1][0]][0]==nomoves1&&p1changed[p1mf[nomoves1][0]][1]==ch[p1mt[nomoves1][0]][p1mt[nomoves1][1]])
     ch[p1mt[nomoves1][0]][p1mt[nomoves1][1]]=1;
    if(revenp1[p2ctr[0]-1][0]==nomoves1&&revenp1[p2ctr[0]-1][1]==ch[p1mt[nomoves1][0]][p1mt[nomoves1][1]])
     {
      ch[p1mf[nomoves1][0]-1][p1mf[nomoves1][1]]=7;
      p2p[0][0]--;
      p2p[0][--p2ctr[0]]=-1;
     }
    if(p1mf[nomoves1][1]-p1mt[nomoves1][1]==2&&ch[p1mt[nomoves1][0]][p1mt[nomoves1][1]]==6)
     {
      ch[0][7]=2;
      ch[0][5]=0;
     }
    else if((p1mf[nomoves1][1]-p1mt[nomoves1][1])==-2&&ch[p1mt[nomoves1][0]][p1mt[nomoves1][1]]==6)
     {
      ch[0][0]=2;
      ch[0][3]=0;
     }
    if(p2p[0][p2ctr[0]-1]==nomoves1&&p2ctr[0]>1)
     {
      ch[p1mf[nomoves1][0]][p1mf[nomoves1][1]]=7;
      p2p[0][0]--;
      p2p[0][--p2ctr[0]]=-1;
     }
    else if(p2p[1][p2ctr[1]-1]==nomoves1&&p2ctr[1]>1)
     {
      ch[p1mf[nomoves1][0]][p1mf[nomoves1][1]]=8;
      p2p[1][0]--;
      p2p[1][--p2ctr[1]]=-1;
     }
    else if(p2p[2][p2ctr[2]-1]==nomoves1&&p2ctr[2]>1)
     {
      ch[p1mf[nomoves1][0]][p1mf[nomoves1][1]]=9;
      p2p[2][0]--;
      p2p[2][--p2ctr[2]]=-1;
     }
    else if(p2p[3][p2ctr[3]-1]==nomoves1&&p2ctr[3]>1)
     {
      ch[p1mf[nomoves1][0]][p1mf[nomoves1][1]]=10;
      p2p[3][0]--;
      p2p[3][--p2ctr[3]]=-1;
     }
    else if(p2p[4][p2ctr[4]-1]==nomoves1&&p2ctr[4]>1)
     {
      ch[p1mf[nomoves1][0]][p1mf[nomoves1][1]]=11;
      p2p[4][0]--;
      p2p[4][--p2ctr[4]]=-1;
     }
   }
  else if(stat==3||stat==5||stat==1||(stat==0&&prevstat[prevstatctr-1]==4)||(stat==0&&prevstat[prevstatctr-1]==6)||(stat==0&&prevstat[prevstatctr-1]==2))
   {
    if(move50>50&&move50<101)
     move50--;
    nomoves2--;
    prevstatctr--;
    for(charu=0;charu<3;charu++)
     {
      if(castlecheck2[charu]==nomoves2)
       castlecheck2[charu]=0;
     }
    stat=prevstat[prevstatctr];
    prevstat[prevstatctr]=0;
    ch[p2mt[nomoves2][0]][p2mt[nomoves2][1]]=ch[p2mf[nomoves2][0]][p2mf[nomoves2][1]];
    ch[p2mf[nomoves2][0]][p2mf[nomoves2][1]]=0;
    if(p2changed[p2mf[nomoves2][0]][0]==nomoves2&&p2changed[p2mf[nomoves2][0]][1]==ch[p2mt[nomoves2][0]][p2mt[nomoves2][1]])
     ch[p2mt[nomoves2][0]][p2mt[nomoves2][1]]=7;
    if(revenp2[p1ctr[0]-1][0]==nomoves2&&revenp2[p1ctr[0]-1][1]==ch[p2mt[nomoves2][0]][p2mt[nomoves2][1]])
     {
      ch[p2mf[nomoves2][0]+1][p2mf[nomoves2][1]]=1;
      p1p[0][0]--;
      p1p[0][--p1ctr[0]]=-1;
     }
    if(p2mf[nomoves2][1]-p2mt[nomoves2][1]==2&&ch[p2mt[nomoves2][0]][p2mt[nomoves2][1]]==12)
     {
      ch[7][7]=8;
      ch[7][5]=0;
     }
    else if(p2mf[nomoves2][1]-p2mt[nomoves2][1]==-2&&ch[p2mt[nomoves2][0]][p2mt[nomoves2][1]]==12)
     {
      ch[7][0]=8;
      ch[7][3]=0;
     }
    if(p1p[0][p1ctr[0]-1]==nomoves2&&p1ctr[0]>1)
     {
      ch[p2mf[nomoves2][0]][p2mf[nomoves2][1]]=1;
      p1p[0][0]--;
      p1p[0][--p1ctr[0]]=-1;
     }
    else if(p1p[1][p1ctr[1]-1]==nomoves2&&p1ctr[1]>1)
     {
      ch[p2mf[nomoves2][0]][p2mf[nomoves2][1]]=2;
      p1p[1][0]--;
      p1p[1][--p1ctr[1]]=-1;
     }
    else if(p1p[2][p1ctr[2]-1]==nomoves2&&p1ctr[2]>1)
     {
      ch[p2mf[nomoves2][0]][p2mf[nomoves2][1]]=3;
      p1p[2][0]--;
      p1p[2][--p1ctr[2]]=-1;
     }
    else if(p1p[3][p1ctr[3]-1]==nomoves2&&p1ctr[3]>1)
     {
      ch[p2mf[nomoves2][0]][p2mf[nomoves2][1]]=4;
      p1p[3][0]--;
      p1p[3][--p1ctr[3]]=-1;
     }
    else if(p1p[4][p1ctr[4]-1]==nomoves2&&p1ctr[4]>1)
     {
      ch[p2mf[nomoves2][0]][p2mf[nomoves2][1]]=5;
      p1p[4][0]--;
      p1p[4][--p1ctr[4]]=-1;
     }
   }
 }

void move50stalemate()
 {
  int piec[12]={0,0,0,0,0,0,0,0,0,0,0,0};
  for(i=0;i<8;i++)
   for(j=0;j<8;j++)
    {
     if(ch[i][j]==1)
      piec[0]++;
     else if(ch[i][j]==2)
      piec[1]++;
     else if(ch[i][j]==3)
      piec[2]++;
     else if(ch[i][j]==4)
      piec[3]++;
     else if(ch[i][j]==5)
      piec[4]++;
     else if(ch[i][j]==6)
      piec[5]++;
     else if(ch[i][j]==7)
      piec[6]++;
     else if(ch[i][j]==8)
      piec[7]++;
     else if(ch[i][j]==9)
      piec[8]++;
     else if(ch[i][j]==10)
      piec[9]++;
     else if(ch[i][j]==11)
      piec[10]++;
     else if(ch[i][j]==12)
      piec[11]++;
    }
  if(stat==4||stat==6)
   {
    if(piec[1]==0&&piec[2]==0&&piec[3]==0&&piec[4]==0)
     {
      if(ch[p1mf[nomoves1-1][0]][p1mf[nomoves1-1][1]]==6)
       move50++;
      else if(ch[p1mf[nomoves1-1][0]][p1mf[nomoves1-1][1]]==1)
       {
	move50=0;
       }
     }
   }
  else if(stat==5||stat==3)
   {
    if(piec[7]==0&&piec[8]==0&&piec[9]==0&&piec[10]==0)
     {
      if(ch[p2mf[nomoves2-1][0]][p2mf[nomoves2-1][1]]==12)
       {
	if(move50==0)
	 move50=51;
	else
	 move50++;
       }
      else if(ch[p2mf[nomoves2-1][0]][p2mf[nomoves2-1][1]]==7)
       {
	move50=0;
       }
     }
   }
 }

int stalemate()
 {
  buton yes,no;
  int piec[12]={0,0,0,0,0,0,0,0,0,0,0,0},flng=1;
  if(stat==3)
   {
    if(ctr[0]==0)
     return 1;
    for(i=0;i<8;i++)
     for(j=0;j<8;j++)
      {
       if(ch[i][j]==1)
	piec[0]++;
       else if(ch[i][j]==2)
	piec[1]++;
       else if(ch[i][j]==3)
	piec[2]++;
       else if(ch[i][j]==4)
	piec[3]++;
       else if(ch[i][j]==5)
	piec[4]++;
       else if(ch[i][j]==6)
	piec[5]++;
       else if(ch[i][j]==7)
	piec[6]++;
       else if(ch[i][j]==8)
	piec[7]++;
       else if(ch[i][j]==9)
	piec[8]++;
       else if(ch[i][j]==10)
	piec[9]++;
       else if(ch[i][j]==11)
	piec[10]++;
       else if(ch[i][j]==12)
	piec[11]++;
      }
    if(move50==100)
     return 1;
    if(piec[1]==0&&piec[2]==0&&piec[3]==0&&piec[4]==0&&piec[6]==0&&piec[7]==0&&piec[8]==0&&piec[9]==0&&piec[10]==0)
     return 1;
    else if(piec[0]==0&&piec[1]==0&&piec[2]==0&&piec[3]==0&&piec[4]==0&&piec[6]==0&&piec[7]==0&&piec[8]==0&&piec[9]==1&&piec[10]==0)
     return 1;
    else if(piec[0]==0&&piec[1]==0&&piec[2]==0&&piec[3]==0&&piec[4]==0&&piec[6]==0&&piec[7]==0&&piec[9]==0&&piec[10]==0)
     return 1;
    if(bdcount1==0)
    {
    for(i=0;i<8;i++)
     for(j=0;j<8;j++)
      {
       bd1[i][j]=ch[i][j];
       nm1=nomoves1;
       bdcount1=1;
      }
    return 0;
    }
    for(i=0;i<8;i++)
     for(j=0;j<8;j++)
      {
       if(nm1==nomoves1-2)
	{
	 if(ch[i][j]!=bd1[i][j])
	  flng=0;
	}
       else
	{
	 return 0;
	}
      }
    if(flng==1)
     {
      bdcount1++;
      nm1=nomoves1;
      if(bdcount1==3)
       {
	 setcolor(0);
	 rectangle(getmaxx()/2-201,getmaxy()/2-51,getmaxx()/2+200,getmaxy()/2+51);
	 rectangle(getmaxx()/2-202,getmaxy()/2-52,getmaxx()/2+201,getmaxy()/2+52);
	 setcolor(3);
	 for(int k=0;k<400;k++)
	 line(getmaxx()/2-200+k,getmaxy()/2-50,getmaxx()/2-200+k,getmaxy()/2+50);
	 setcolor(15);
	 settextstyle(1,HORIZ_DIR,3);
	 outtextxy(getmaxx()/2-190,getmaxy()/2-44,"DO YOU WANT TO FORCE A DRAW");
	 outtextxy(getmaxx()/2-175,getmaxy()/2-25,"ACCUSING 3-MOVE REPETITION");
	 setcolor(0);
	 yes.createbutton("YES",getmaxx()/2-80,getmaxy()/2+10,getmaxx()/2-24,getmaxy()/2+40,3,1,1,3);
	 no.createbutton("NO",getmaxx()/2+40,getmaxy()/2+10,getmaxx()/2+83,getmaxy()/2+40,3,1,1,3);
	 while(!kbhit())
	  {
	   in.x.ax=3;
	   x=in.x.cx;
	   y=in.x.dx;
	   int86(0x33,&in,&in);
	   if(yes.Getfocus()==1)
	    return 1;
	   else if(no.Getfocus()==1)
	    {
	     bdcount1=1;
	     return 2;
	    }
	  }
       }
      else
       return 0;
     }
    else
     {
      bdcount1=1;
      nm1=nomoves1;
      for(i=0;i<8;i++)
       for(j=0;j<8;j++)
	bd1[i][j]=ch[i][j];
      return 0;
     }
   }
  else if(stat==4)
   {
    if(ctr[1]==0)
     return 1;
    for(i=0;i<8;i++)
     for(j=0;j<8;j++)
      {
       if(ch[i][j]==1)
	piec[0]++;
       else if(ch[i][j]==2)
	piec[1]++;
       else if(ch[i][j]==3)
	piec[2]++;
       else if(ch[i][j]==4)
	piec[3]++;
       else if(ch[i][j]==5)
	piec[4]++;
       else if(ch[i][j]==6)
	piec[5]++;
       else if(ch[i][j]==7)
	piec[6]++;
       else if(ch[i][j]==8)
	piec[7]++;
       else if(ch[i][j]==9)
	piec[8]++;
       else if(ch[i][j]==10)
	piec[9]++;
       else if(ch[i][j]==11)
	piec[10]++;
       else if(ch[i][j]==12)
	piec[11]++;
      }
    if(move50==50)
     return 1;
    if(piec[0]==0&&piec[1]==0&&piec[2]==0&&piec[3]==0&&piec[4]==0&&piec[6]==0&&piec[7]==0&&piec[8]==0&&piec[9]==0&&piec[10]==0)
     return 1;
    else if(piec[0]==0&&piec[1]==0&&piec[2]==0&&piec[3]==1&&piec[4]==0&&piec[6]==0&&piec[7]==0&&piec[8]==0&&piec[9]==0&&piec[10]==0)
     return 1;
    else if(piec[0]==0&&piec[1]==0&&piec[3]==0&&piec[4]==0&&piec[6]==0&&piec[7]==0&&piec[8]==0&&piec[9]==0&&piec[10]==0)
     return 1;
    if(bdcount==0)
    {
    for(i=0;i<8;i++)
     for(j=0;j<8;j++)
      {
       bd[i][j]=ch[i][j];
       nm=nomoves2;
       bdcount=1;
      }
    return 0;
    }
    for(i=0;i<8;i++)
     for(j=0;j<8;j++)
      {
       if(nm==nomoves2-2)
	{
	 if(ch[i][j]!=bd[i][j])
	  flng=0;
	}
       else
	return 0;
      }
    if(flng==1)
     {
      bdcount++;
      nm=nomoves2;
      if(bdcount==3)
       {
	 setcolor(0);
	 rectangle(getmaxx()/2-201,getmaxy()/2-51,getmaxx()/2+200,getmaxy()/2+51);
	 rectangle(getmaxx()/2-202,getmaxy()/2-52,getmaxx()/2+201,getmaxy()/2+52);
	 setcolor(3);
	 for(int k=0;k<400;k++)
	 line(getmaxx()/2-200+k,getmaxy()/2-50,getmaxx()/2-200+k,getmaxy()/2+50);
	 setcolor(15);
	 settextstyle(1,HORIZ_DIR,3);
	 outtextxy(getmaxx()/2-190,getmaxy()/2-44,"DO YOU WANT TO FORCE A DRAW");
	 outtextxy(getmaxx()/2-175,getmaxy()/2-25,"ACCUSING 3-MOVE REPETITION");
	 setcolor(0);
	 yes.createbutton("YES",getmaxx()/2-80,getmaxy()/2+10,getmaxx()/2-24,getmaxy()/2+40,3,1,1,3);
	 no.createbutton("NO",getmaxx()/2+40,getmaxy()/2+10,getmaxx()/2+83,getmaxy()/2+40,3,1,1,3);
	 while(!kbhit())
	  {
	   in.x.ax=3;
	   x=in.x.cx;
	   y=in.x.dx;
	   int86(0x33,&in,&in);
	   if(yes.Getfocus()==1)
	    return 1;
	   else if(no.Getfocus()==1)
	    {
	     bdcount=1;
	     return 2;
	    }
	  }
       }
      else
       return 0;
     }
    else if(flng==0)
     {
      bdcount=1;
      nm=nomoves2;
      for(i=0;i<8;i++)
       for(j=0;j<8;j++)
	bd[i][j]=ch[i][j];
      return 0;
     }
   }
  else
   return 0;
 return 0;
 }

void pawnswapper()
 {
  buton b1,b2,b3,b4;
  for(int i=0;i<8;i++)
   for(int j=0;j<8;j++)
    {
     if(stat==4)
      {
       if(i==7&&ch[i][j]==1)
	{
	 setcolor(0);
	 rectangle(getmaxx()/2-201,getmaxy()/2-51,getmaxx()/2+200,getmaxy()/2+51);
	 rectangle(getmaxx()/2-202,getmaxy()/2-52,getmaxx()/2+201,getmaxy()/2+52);
	 setcolor(3);
	 for(int k=0;k<400;k++)
	 line(getmaxx()/2-200+k,getmaxy()/2-50,getmaxx()/2-200+k,getmaxy()/2+50);
	 setcolor(15);
	 settextstyle(1,HORIZ_DIR,3);
	 outtextxy(getmaxx()/2-190,getmaxy()/2-40,"SELECT A SWAP FOR YOUR PAWN");
	 setcolor(0);
	 b1.button(getmaxx()/2-175,getmaxy()/2-10,2);
	 b1.Getresponce(1);
	 b2.button(getmaxx()/2-75,getmaxy()/2-10,3);
	 b2.Getresponce(1);
	 b3.button(getmaxx()/2+25,getmaxy()/2-10,4);
	 b3.Getresponce(1);
	 b4.button(getmaxx()/2+125,getmaxy()/2-10,5);
	 b4.Getresponce(1);
	 while(!kbhit())
	  {
	   in.x.ax=3;
	   x=in.x.cx;
	   y=in.x.dx;
	   int86(0x33,&in,&in);
	   if(b1.Getresponce()==1)
	    {
	     p1changed[i][0]=nomoves1-1;
	     p1changed[i][1]=2;
	     ch[i][j]=2;
	     return ;
	    }
	   if(b2.Getresponce()==1)
	    {
	     p1changed[i][0]=nomoves1-1;
	     p1changed[i][1]=3;
	     ch[i][j]=3;
	     return ;
	    }
	   if(b3.Getresponce()==1)
	    {
	     p1changed[i][0]=nomoves1-1;
	     p1changed[i][1]=4;
	     ch[i][j]=4;
	     return ;
	    }
	   if(b4.Getresponce()==1)
	    {
	     p1changed[i][0]=nomoves1-1;
	     p1changed[i][1]=5;
	     ch[i][j]=5;
	     return ;
	    }
	  }
	}
      }
     else if(stat==3)
      {
       if(i==0&&ch[i][j]==7)
	{
	 setcolor(0);
	 rectangle(getmaxx()/2-201,getmaxy()/2-51,getmaxx()/2+200,getmaxy()/2+51);
	 rectangle(getmaxx()/2-202,getmaxy()/2-52,getmaxx()/2+201,getmaxy()/2+52);
	 setcolor(3);
	 for(int k=0;k<400;k++)
	 line(getmaxx()/2-200+k,getmaxy()/2-50,getmaxx()/2-200+k,getmaxy()/2+50);
	 setcolor(0);
	 settextstyle(1,HORIZ_DIR,3);
	 outtextxy(getmaxx()/2-190,getmaxy()/2-40,"SELECT A SWAP FOR YOUR PAWN");
	 setcolor(15);
	 b1.button(getmaxx()/2-175,getmaxy()/2-10,8);
	 b1.Getresponce(1);
	 b2.button(getmaxx()/2-75,getmaxy()/2-10,9);
	 b2.Getresponce(1);
	 b3.button(getmaxx()/2+25,getmaxy()/2-10,10);
	 b3.Getresponce(1);
	 b4.button(getmaxx()/2+125,getmaxy()/2-10,11);
	 b4.Getresponce(1);
	 while(!kbhit())
	  {
	   in.x.ax=3;
	   x=in.x.cx;
	   y=in.x.dx;
	   int86(0x33,&in,&in);
	   if(b1.Getresponce()==1)
	    {
	     p2changed[i][0]=nomoves2-1;
	     p2changed[i][1]=8;
	     ch[i][j]=8;
	     return ;
	    }
	   if(b2.Getresponce()==1)
	    {
	     p2changed[i][0]=nomoves2-1;
	     p2changed[i][1]=9;
	     ch[i][j]=9;
	     return ;
	    }
	   if(b3.Getresponce()==1)
	    {
	     p2changed[i][0]=nomoves2-1;
	     p2changed[i][1]=10;
	     ch[i][j]=10;
	     return ;
	    }
	   if(b4.Getresponce()==1)
	    {
	     p2changed[i][0]=nomoves2-1;
	     p2changed[i][1]=11;
	     ch[i][j]=11;
	     return ;
	    }
	  }
	}
      }
    }
  return ;
 }

void showboard()
 {
  int li;
  setcolor(13);
  rectangle(190,20,630,460);
  rectangle(191,21,629,459);
  setcolor(5);
  rectangle(192,22,628,458);
  for(li=193;li<628;li++)
   line(li,23,li,457);
  setcolor(15);
  rectangle(210,40,610,440);
  for(li=211;li<610;li++)
   line(li,41,li,439);
  setcolor(6);
  setfillstyle(1,6);
  bar(560,40,610,90);
  bar(460,40,510,90);
  bar(360,40,410,90);
  bar(260,40,310,90);
  bar(210,90,260,140);
  bar(310,90,360,140);
  bar(410,90,460,140);
  bar(510,90,560,140);
  bar(560,140,610,190);
  bar(460,140,510,190);
  bar(360,140,410,190);
  bar(260,140,310,190);
  bar(210,190,260,240);
  bar(310,190,360,240);
  bar(410,190,460,240);
  bar(510,190,560,240);
  bar(560,240,610,290);
  bar(460,240,510,290);
  bar(360,240,410,290);
  bar(260,240,310,290);
  bar(210,290,260,340);
  bar(310,290,360,340);
  bar(410,290,460,340);
  bar(510,290,560,340);
  bar(560,340,610,390);
  bar(460,340,510,390);
  bar(360,340,410,390);
  bar(260,340,310,390);
  bar(210,390,260,440);
  bar(310,390,360,440);
  bar(410,390,460,440);
  bar(510,390,560,440);
  settextstyle(1,HORIZ_DIR,7);
  x=615;y=-7;
  for(i=0;i<8;i++)
   {
    y+=50;
    x-=400;
    for(j=0;j<8;j++)
     {
      if(ch[i][j]>0&&ch[i][j]<=6)
       setcolor(0);
      else
       setcolor(7);
      if(ch[i][j]==1)
       pawn(x,y);
      else if(ch[i][j]==2)
       rook(x,y);
      else if(ch[i][j]==3)
       knight(x,y);
      else if(ch[i][j]==4)
       bishop(x,y);
      else if(ch[i][j]==5)
       queen(x,y);
      else if(ch[i][j]==6)
       king(x,y);
      else if(ch[i][j]==7)
       pawn(x,y);
      else if(ch[i][j]==8)
       rook(x,y);
      else if(ch[i][j]==9)
       knight(x,y);
      else if(ch[i][j]==10)
       bishop(x,y);
      else if(ch[i][j]==11)
       queen(x,y);
      else if(ch[i][j]==12)
       king(x,y);
      x+=50;
     }
   }
  setcolor(15);
  settextstyle(0,HORIZ_DIR,1);
  outtextxy(230,28,"a");
  outtextxy(280,28,"b");
  outtextxy(330,28,"c");
  outtextxy(380,28,"d");
  outtextxy(430,28,"e");
  outtextxy(480,28,"f");
  outtextxy(530,28,"g");
  outtextxy(580,28,"h");
  outtextxy(230,446,"a");
  outtextxy(280,446,"b");
  outtextxy(330,446,"c");
  outtextxy(380,446,"d");
  outtextxy(430,446,"e");
  outtextxy(480,446,"f");
  outtextxy(530,446,"g");
  outtextxy(580,446,"h");
  outtextxy(199,63,"8");
  outtextxy(199,113,"7");
  outtextxy(199,163,"6");
  outtextxy(199,213,"5");
  outtextxy(199,263,"4");
  outtextxy(199,313,"3");
  outtextxy(199,363,"2");
  outtextxy(199,413,"1");
  outtextxy(617,63,"8");
  outtextxy(617,113,"7");
  outtextxy(617,163,"6");
  outtextxy(617,213,"5");
  outtextxy(617,263,"4");
  outtextxy(617,313,"3");
  outtextxy(617,363,"2");
  outtextxy(617,413,"1");
 }


void main()
 {
  int gd=VGA,gm,kc,k;
  gm = VGAHI;
  buton play,game,instr,db,w[16],b[16],pause,retry,X,ng;
  initgraph(&gd,&gm,"c:\\tc\\bgi");
  cleardevice();
  initmouse();
  showmouseptr();
  setbkcolor(15);
  setcolor(11);
  for(i=0;i<640;i++)
   line(i,0,i,getmaxy());
  ShowBMP(15,0,"main.bmp");
  ShowBMP(15,0,"main1.bmp");
  ShowBMP(15,0,"main2.bmp");
  ShowBMP(15,0,"main3.bmp");
  ShowBMP(15,0,"main.bmp");
  delay(700);
  setcolor(15);
  play.createbutton("PLAY",255,150,388,200,3,1,1,6);
  while(!kbhit()||getch()!='\n')
    {
     in.x.ax=3;
     x=in.x.cx;
     y=in.x.dx;
     int86(0x33,&in,&in);
     if(play.Getfocus()==1)
      {
       break;
      }
    }

  MAINMENU:
  cleardevice();
  setbkcolor(10);
  setcolor(14);
  rectangle(0,0,getmaxx(),getmaxy());
  setcolor(6);
  rectangle(4,4,getmaxx()-4,18);
  setfillstyle(1,6);
  floodfill(5,5,6);
  setcolor(15);
  settextstyle(0,HORIZ_DIR,1);
  outtextxy(10,8,"chess.exe");
  X.createbutton("",getmaxx()-20,7,getmaxx()-10,17,3,1,4,1,3);
  setcolor(4);
  settextstyle(1,HORIZ_DIR,5);
  outtextxy(38,10,"WELCOME TO THE WORLD OF");
  settextstyle(0,HORIZ_DIR,10);
  outtextxy(135,60,"CHESS");
  setcolor(5);
  settextstyle(2,HORIZ_DIR,6);
  outtextxy(18,145,"CHESS IS A TWO-PLAYER BOARD GAME UTILIZING AN 8 X 8 CHESSBOARD ");
  outtextxy(18,160,"AND 16 PIECES OF 6 TYPES FOR EACH PLAYER. EACH TYPE OF PIECE ");
  outtextxy(18,175,"MOVES IN A DISTINCT WAY. THE GOAL OF THE GAME IS TO CHECKMATE");
  outtextxy(18,190,"THE OPPONENT KING. LET'S SEE WHO AMONG YOU WINS ");
  outtextxy(73,420,"SIT BACK AND RELAX IF YOUR FRIEND FLIPS THE BOARD");
  outtextxy(112,435,"THIS GAME HAS AUTOSAVE FEATURE IN IT !");
  settextstyle(1,HORIZ_DIR,4);
  outtextxy(13,210,"ARE YOU READY FOR THE CHALLENGE ?");
  game.createbutton("BRING IT ON!",30,260,188,290,3,1,1,3);
  instr.createbutton("TEACH ME SOME MOVES",325,290,605,320,3,1,1,3);
  db.createbutton("SHOW ME YOUR DATABASE",130,370,440,400,3,1,1,3);
  setcolor(1);
  circle(254,313,20);
  circle(254,313,30);
  line(254,293,254,283);
  line(237,323,230,330);
  line(271,323,278,330);
  while(!kbhit()||getch()!=27)
    {
     in.x.ax=3;
     x=in.x.cx;
     y=in.x.dx;
     int86(0x33,&in,&in);
     if(X.Getfocus()==1)
      goto END;
     else if(game.Getfocus()==1)
      {
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,91,210,20+i);
       delay(200);
       setcolor(0);
       for(i=1;i<10;i++)
	arc(254,313,91,210,20+i);
       delay(200);
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,91,210,20+i);
       delay(200);
       setcolor(0);
       for(i=1;i<10;i++)
	arc(254,313,91,210,20+i);
       delay(200);
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,91,210,20+i);
       delay(200);
       NEW:
       neww=0;
       ch[0][0]=2;
       ch[0][1]=3;
       ch[0][2]=4;
       ch[0][3]=5;
       ch[0][4]=6;
       ch[0][5]=4;
       ch[0][6]=3;
       ch[0][7]=2;
       for(i=0;i<8;i++)
	ch[1][i]=1;
       for(i=2;i<6;i++)
	for(j=0;j<8;j++)
	 ch[i][j]=0;
       for(i=0;i<8;i++)
	ch[6][i]=7;
       ch[7][0]=8;
       ch[7][1]=9;
       ch[7][2]=10;
       ch[7][3]=11;
       ch[7][4]=12;
       ch[7][5]=10;
       ch[7][6]=9;
       ch[7][7]=8;
       for(i=0;i<3;i++)
	{
	 castlecheck1[i]=0;
	 castlecheck2[i]=0;
	}
       for(i=0;i<250;i++)
	for(j=0;j<2;j++)
	{
	 p1mf[i][j]=0;
	 p1mt[i][j]=0;
	 p2mf[i][j]=0;
	 p2mt[i][j]=0;
	}
       for(i=0;i<5;i++)
	for(j=1;j<9;j++)
	{
	 p1ctr[i]=1;
	 p2ctr[i]=1;
	 p1p[i][0]=0;
	 p1p[i][j]=-1;
	 p2p[i][0]=0;
	 p2p[i][j]=-1;
	}
       nomoves1=0;nomoves2=0;
       move50=0;
       stat=4;prevstatctr=0;gamenumber=recentgames(1);
       bcount=0;pc=0;bdcount=0;nm=0;bdcount1=0;nm1=0;
       for(i=0;i<250;i++)
	prevstat[i]=0;
       for(i=0;i<8;i++)
	{
	 castle[i][0]=0;
	 castle[i][1]=0;
	}
       for(i=0;i<8;i++)
	for(j=0;j<8;j++)
	 {
	  bd[i][j]=0;
	  bd[i][j]=0;
	 }
       for(i=0;i<100;i++)
	{
	 pcmoves[i][0]=0;
	 pcmoves[i][0]=0;
	 pcmoves[i][0]=0;
	}
       for(i=0;i<8;i++)
	for(j=0;j<2;j++)
	 {
	  revenp1[i][j]=0;
	  revenp2[i][j]=0;
	  p1changed[i][j]=0;
	  p2changed[i][j]=0;
	 }
       strcpy(name1,"Player 1");
       strcpy(name2,"Player 2");
       n1=8;n2=8;
       g.startit();
       goto GAME;
      }
     else if(instr.Getfocus()==1)
      {
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,330,87,20+i);
       delay(200);
       setcolor(0);
       for(i=1;i<10;i++)
	arc(254,313,330,87,20+i);
       delay(200);
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,330,87,20+i);
       delay(200);
       setcolor(0);
       for(i=1;i<10;i++)
	arc(254,313,330,87,20+i);
       delay(200);
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,330,87,20+i);
       delay(200);
       i=0;
       INS :
       cleardevice();
       setcolor(5);
       rectangle(4,4,getmaxx()-4,18);
       setfillstyle(1,5);
       floodfill(5,5,5);
       setcolor(15);
       settextstyle(0,HORIZ_DIR,1);
       outtextxy(10,8,"chess.exe");
       X.createbutton("",getmaxx()-30,7,getmaxx()-10,17,3,1,4,1,4);
       setbkcolor(6);
       setcolor(14);
       settextstyle(1,HORIZ_DIR,7);
       outtextxy(10,10,"INSTRUCTIONS:");
       setcolor(15);
       settextstyle(0,HORIZ_DIR,1);
       outtextxy(450,45,"Left Click-Prev Page");
       outtextxy(450,65,"Right Click-Next Page");
       if(i==0)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,10);
	cout<<"Rules of chess : ";
	cout<<"\n\n Chess is a two-player board game utilizing a chessboard and sixteen pieces of";
	cout<<"\n six types for each player. Each type of piece moves in a distinct way.The goal";
	cout<<"\n of the game is to checkmate (threaten with unescapable capture) the opponent's";
	cout<<"\n king. Games do not necessarily end with checkmate;players often resign if they";
	cout<<"\n believe they will lose. A game can also end in a draw in several ways.";
	cout<<"\n\n\n Chess is played on a chessboard, a square board divided into 64 squares";
	cout<<"\n (eight-by-eight) of alternating color.  No matter what the actual colors of";
	cout<<"\n the board, the lighter-colored squares are called \"light\" or \"white\", and";
	cout<<"\n the darker-colored squares are called \"dark\" or \"black\". Sixteen \"white\"";
	cout<<"\n and sixteen \"black\" pieces are placed on the board at the beginning of the";
	cout<<"\n game.The board is placed so that a white square is in each player's near-right";
	cout<<"\n corner. Horizontal rows are called ranks and vertical rows are called files.";
       }
      else if(i==1)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,10);
	cout<<"Initial setup : ";
	cout<<"\n\n At the beginning of the game, for each side one king, one queen, two rooks,two";
	cout<<"\n bishops, two knights, and eight pawns. The pieces are placed, one on a square,";
	cout<<"\n as follows:";
	cout<<"\n\n  The rooks are placed on the outside corners, right and left edge.";
	cout<<"\n  The knights are placed immediately inside of the rooks.";
	cout<<"\n  The bishops are placed immediately inside of the knights.";
	cout<<"\n  The queen is placed on the central square of the same color of that of the";
	cout<<"\n   player: white queen on the white square and black queen on the black square.";
	cout<<"\n  The king takes the vacant spot next to the queen.";
	cout<<"\n  The pawns are placed one square in front of all of the other pieces.";
       }
      else if(i==2)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,9);
	cout<<"Basic Moves:";
	cout<<"\n\n Each type of chess piece has its own method of movement. A piece moves to a";
	cout<<"\n vacant square except when capturing an opponent's piece.";
	cout<<"\n\n Except for any move of the knight and castling, pieces cannot jump over";
	cout<<"\n other pieces. A piece is captured (or taken) when an attacking enemy piece";
	cout<<"\n replaces it on its square (en passant is the only exception). The captured";
	cout<<"\n piece is thereby permanently removed from the game.[1] The king can be put";
	cout<<"\n in check but cannot be captured (see below).";
	cout<<"\n\n  The king moves exactly one square horizontally, vertically, or diagonally.";
	cout<<"\n  A special move with the king known as castling is allowed only once per";
	cout<<"\n   player, per game (see below).";
	cout<<"\n  A rook moves any number of vacant squares in a horizontal or vertical";
	cout<<"\n   direction. It also is moved when castling.";
	cout<<"\n  A bishop moves any number of vacant squares in any diagonal direction.";
	cout<<"\n  The queen moves any number of vacant squares in a horizontal, vertical,";
	cout<<"\n   or diagonal direction.";
       }
      else if(i==3)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,8);
	cout<<"Basic Moves : ";
	cout<<"\n\n  A knight moves to the nearest square not on the same rank, file, or";
	cout<<"\n   diagonal. (This can be thought of as moving two squares horizontally then";
	cout<<"\n   one square vertically, or moving one square horizontally then two squares";
	cout<<"\n   vertically,i.e. in an "L" pattern.) The knight is not blocked by other";
	cout<<"\n   pieces: it jumps to the new location.";
	cout<<"\n\n Pawns have the most complex rules of movement:";
	cout<<"\n\n  A pawn moves straight forward one square, if that square is vacant.";
	cout<<"\n   If it has not yet moved, a pawn also has the option of moving two";
	cout<<"\n   squares straight forward, provided both squares are vacant.";
	cout<<"\n   Pawns cannot move backwards.";
	cout<<"\n\n Pawns are the only pieces that capture differently from how they move.";
	cout<<"\n A pawn can capture an enemy piece on either of the two squares diagonally";
	cout<<"\n in front of the pawn(but cannot move to those squares if they are vacant).";
	cout<<"\n The pawn is also involved in the two special moves en passant and promotion";
       }
      else if(i==4)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,7);
	cout<<"Special Moves : ";
	cout<<"\n\n Castling :";
	cout<<"\n\n Castling consists of moving the king two squares towards a rook, then placing";
	cout<<"\n the rook on the other side of the king, adjacent to it.[2] Castling is only";
	cout<<"\n permissible if all of the following conditions hold:";
	cout<<"\n\n  The king and rook involved in castling must not have previously moved;";
	cout<<"\n  There must be no pieces between the king and the rook;";
	cout<<"\n  The king may not currently be in check, nor may the king pass through or end";
	cout<<"\n   up in a square that is under attack by an enemy piece (though the rook is";
	cout<<"\n   permitted to be under attack and to pass over an attacked square);";
	cout<<"\n  The king and the rook must be on the same rank";
	cout<<"\n\n En passant :";
	cout<<"\n\n When a pawn advances two squares from its original square and ends the turn";
	cout<<"\n that adjacent to a pawn of the opponent's on the same rank,it may be captured";
	cout<<"\n by pawn of the opponent's,as if it had moved only one square forward.This";
	cout<<"\n capture is only legal on the opponent's next move immediately following the";
	cout<<"\n first pawn's advance.If the white pawn moves from a2 to a4,the black pawn";
	cout<<"\n on b4 can capture it en passant,moving from b4 to a3 while the white pawn";
	cout<<"\n on a4 is removed from the board.";
       }
      else if(i==5)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,10);
	cout<<"Special Moves :";
	cout<<"\n\n Pawn promotion :";
	cout<<"\n\n If a player advances a pawn to its eighth rank, the pawn is then promoted";
	cout<<"\n (converted) to a queen,rook,bishop,or knight of the same color at the choice";
	cout<<"\n of the player(a queen is usually chosen). The choice is not limited to ";
	cout<<"\n previously captured pieces.Hence it is theoretically possible for a player to";
	cout<<"\n have up to nine queens or up to ten rooks, bishops, or knights if all of their";
	cout<<"\n pawns are promoted. If the desired piece is not available, the player should";
	cout<<"\n call the arbiter to provide the piece.";
	cout<<"\n\n Check :";
	cout<<"\n A king is in check when it is under attack by at least one enemy piece.A piece";
	cout<<"\n unable to move because it would place its own king in check (it is pinned";
	cout<<"\n against its own king) may still deliver check to the opposing player.";
       }
      else if(i==6)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,7);
	cout<<"Check :";
	cout<<"\n\n It is illegal to make a move that places or leaves one's king in check.";
	cout<<"\n The possible ways to get out of check are:";
	cout<<"\n\n  Move the king to a square where it is not in check.";
	cout<<"\n  Capture the checking piece (possibly with the king).";
	cout<<"\n  Block the check by placing a piece between the king and the opponent's";
	cout<<"\n  threatening piece.If it is not possible to get out of check, the king";
	cout<<"\n  is checkmated and the game is over.";
	cout<<"\n\n In informal games, it is customary to announce \"check\" when making a";
	cout<<"\n move that puts the opponent's king in check. However, in formal";
	cout<<"\n competitions check is rarely announced.";
	cout<<"\n\n Stalemate :";
	cout<<"\n\n The game ends in a draw if any of these conditions occur:";
	cout<<"\n\n  The game is automatically a draw if the player to move is not in check";
	cout<<"\n  but has no legal move. This situation is called a stalemate.";
       }
      else if(i==7)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,10);
	cout<<"Stalemate : ";
	cout<<"\n\n The game is immediately drawn when there is no possibility of checkmate";
	cout<<"\n for either side with any series of legal moves. This draw is often due to";
	cout<<"\n insufficient material, including the endgames, as follows :";
	cout<<"\n\n  king against king;";
	cout<<"\n  king against king and bishop;";
	cout<<"\n  king against king and knight;";
	cout<<"\n  king and bishop against king and bishop, with both bishops on squares of";
	cout<<"\n   the same color.";
	cout<<"\n\n Both players can agree to a draw after one of the players makes an offer.";
	cout<<"\n The player having the move may claim a draw by declaring that one of the";
	cout<<"\n following conditions exists, or by declaring an intention to make a move";
	cout<<"\n which will bring about one of these conditions:(in next page)";
       }
      else if(i==8)
       {
	gotoxy(57,6);
	cout<<"page "<<i+1<<" out of 9";
	gotoxy(2,10);
	cout<<"Stalemate : ";
	cout<<"\n\n Fifty-move rule:";
	cout<<"\n\n  There has been no capture or pawn move in the last fifty moves by each player.";
	cout<<"\n\n Threefold repetition:";
	cout<<"\n\n  The same board position has occurred three times with the same player to";
	cout<<"\n  move and all pieces having the same rights to move, including the right to";
	cout<<"\n  castle or capture en passant.";
	cout<<"\n\n If the claim is proven true, the game is drawn.";
       }
      setcolor(4);
      rectangle(0,0,getmaxx(),getmaxy());
      while(!kbhit()||getch()!=27)
       {
	in.x.ax=3;
	x=in.x.cx;
	y=in.x.dx;
	int86(0x33,&in,&in);
	if(in.x.bx==1&&i-1>=0&&y>18)
	 {
	  delay(500);
	  i--;
	  goto INS;
	 }
	if(in.x.bx==2&&i+1<=8&&y>18)
	 {
	  delay(500);
	  i++;
	  goto INS;
	 }
	if(X.Getfocus()==1)
	 goto MAINMENU;
       }
      goto MAINMENU;
      }
    else if(db.Getfocus()==1)
      {
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,216,325,20+i);
       delay(200);
       setcolor(0);
       for(i=1;i<10;i++)
	arc(254,313,216,325,20+i);
       delay(200);
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,216,325,20+i);
       delay(200);
       setcolor(0);
       for(i=1;i<10;i++)
	arc(254,313,216,325,20+i);
       delay(200);
       setcolor(12);
       for(i=1;i<10;i++)
	arc(254,313,216,325,20+i);
       delay(200);
       i=recentgames();
       if(i==1)
	{
	 g.resume();
	 neww=1;
	 goto GAME;
	}
       else if(i==2)
	{
	 gamenumber=g.gameno;
	 neww=1;
	 stat=4;
	 move50=0;
	 for(i=0;i<3;i++)
	  {
	   castlecheck1[i]=0;
	   castlecheck2[i]=0;
	  }
	 ch[0][0]=2;
	 ch[0][1]=3;
	 ch[0][2]=4;
	 ch[0][3]=5;
	 ch[0][4]=6;
	 ch[0][5]=4;
	 ch[0][6]=3;
	 ch[0][7]=2;
	 for(i=0;i<8;i++)
	  ch[1][i]=1;
	 for(i=2;i<6;i++)
	  for(j=0;j<8;j++)
	   ch[i][j]=0;
	 for(i=0;i<8;i++)
	  ch[6][i]=7;
	 ch[7][0]=8;
	 ch[7][1]=9;
	 ch[7][2]=10;
	 ch[7][3]=11;
	 ch[7][4]=12;
	 ch[7][5]=10;
	 ch[7][6]=9;
	 ch[7][7]=8;
	 for(i=0;i<250;i++)
	  for(j=0;j<2;j++)
	  {
	   p1mf[i][j]=0;
	   p1mt[i][j]=0;
	   p2mf[i][j]=0;
	   p2mt[i][j]=0;
	  }
	 for(i=0;i<5;i++)
	  for(j=1;j<9;j++)
	  {
	   p1ctr[i]=1;
	   p2ctr[i]=1;
	   p1p[i][0]=0;
	   p1p[i][j]=-1;
	   p2p[i][0]=0;
	   p2p[i][j]=-1;
	  }
	 nomoves1=0;nomoves2=0;
	 stat=4;prevstatctr=0;gamenumber=recentgames(1);
	 bcount=0;pc=0;bdcount=0;nm=0;bdcount1=0;nm1=0;
	 for(i=0;i<250;i++)
	  prevstat[i]=0;
	 for(i=0;i<8;i++)
	  {
	   castle[i][0]=0;
	   castle[i][1]=0;
	  }
	 for(i=0;i<8;i++)
	  for(j=0;j<8;j++)
	   {
	    bd[i][j]=0;
	    bd[i][j]=0;
	   }
	 for(i=0;i<100;i++)
	  {
	   pcmoves[i][0]=0;
	   pcmoves[i][0]=0;
	   pcmoves[i][0]=0;
	  }
	 for(i=0;i<8;i++)
	  for(j=0;j<2;j++)
	   {
	    revenp1[i][j]=0;
	    revenp2[i][j]=0;
	    p1changed[i][j]=0;
	    p2changed[i][j]=0;
	   }
	 g.startit();
	 goto GAME;
	}
       else
	goto MAINMENU;
      }
     }
  goto END;
  GAME:
  statue=0;
  bcount=0;
  pc=0;
  flg1=2;flg2=2;
  for(i=0;i<8;i++)
   {
    castle[i][0]=-1;
    castle[i][1]=-1;
   }
  cleardevice();
  setbkcolor(0);
  setcolor(13);
  rectangle(0,0,getmaxx(),getmaxy());
  rectangle(1,1,getmaxx()-1,getmaxy()-1);
  setfillstyle(1,3);
  floodfill(getmaxx()-2,getmaxy()-2,13);
  setcolor(1);
  rectangle(4,4,getmaxx()-4,18);
  setfillstyle(1,1);
  floodfill(5,5,1);
  setcolor(15);
  settextstyle(0,HORIZ_DIR,1);
  outtextxy(10,8,"chess.exe");
  pause.createbutton("",10,30,60,80,3,1,1,1,1);
  retry.createbutton("",70,30,120,80,3,1,1,1,2);
  X.createbutton("",getmaxx()-20,7,getmaxx()-10,17,3,1,4,1,3);
  if(neww==0)
   {
    g.getname(0);
    g.record();
    neww=1;
    goto GAME;
   }
  g.display();
  showboard();
  ctr[0]=0;
  ctr[1]=0;
  k=610;
  kc=-10;
  for(i=0;i<8;i++)
  {
   kc+=50;
   k-=400;
   for(j=0;j<8;j++)
    {
     if(stat==3||stat==5)
      {
       if(ch[i][j]==6)
	{
	 check(6,i,j);
	 if(cm!=0)
	  {
	   flg1=0;
	   w[ctr[0]++].button(k,kc,6);
	   for(int kfj=0;kfj<cm;kfj++)
	    {
	     pcmoves[pc][0]=6 ;
	     pcmoves[pc][1]=kpmoves[kfj][0];
	     pcmoves[pc][2]=kpmoves[kfj][1];
	     pc++;
	    }
	  }
	}
       else
	{
	 cp=0;
	 if(ch[i][j]>0&&ch[i][j]<6)
	 {
	 check(ch[i][j],i,j);
	 for(l=0;l<c;l++)
	  {
	   cpmoves[l][0]=pmoves[l][0];
	   cpmoves[l][1]=pmoves[l][1];
	   cp++;
	  }
	 flu=0;
	 for(l=0;l<cp;l++)
	  {
	   if(checkmateking(i,j,cpmoves[l][0],cpmoves[l][1])==0)
	    {
	     flg1=0;
	     if(flu==0)
	      {
	       w[ctr[0]++].button(k,kc,ch[i][j]);
	       flu=1;
	      }
	     pcmoves[pc][0]=ch[i][j];
	     pcmoves[pc][1]=cpmoves[l][0];
	     pcmoves[pc][2]=cpmoves[l][1];
	     pc++;
	    }
	  }
	 }
	}
      }
     else if(stat==4||stat==6)
      {
       if(ch[i][j]==12)
	{
	 check(12,i,j);
	 if(cm!=0)
	  {
	   flg2=0;
	   b[ctr[1]++].button(k,kc,12);
	   for(int kfj=0;kfj<cm;kfj++)
	    {
	     pcmoves[pc][0]=12;
	     pcmoves[pc][1]=kpmoves[kfj][0];
	     pcmoves[pc][2]=kpmoves[kfj][1];
	     pc++;
	    }
	  }
	}
       else
	{
	 if(ch[i][j]>6&&ch[i][j]<12)
	 {
	 cp=0;
	 check(ch[i][j],i,j);
	 for(l=0;l<c;l++)
	  {
	   cpmoves[l][0]=pmoves[l][0];
	   cpmoves[l][1]=pmoves[l][1];
	   cp++;
	  }
	 flu=0;
	 for(l=0;l<cp;l++)
	  {
	   if(checkmateking(i,j,cpmoves[l][0],cpmoves[l][1])==0)
	    {
	     flg2=0;
	     if(flu==0)
	      {
	       b[ctr[1]++].button(k,kc,ch[i][j]);
	       flu=1;
	      }
	     pcmoves[pc][0]=ch[i][j];
	     pcmoves[pc][1]=cpmoves[l][0];
	     pcmoves[pc][2]=cpmoves[l][1];
	     pc++;
	    }
	  }
	 }
	}
      }
     k+=50;
    }
  }
  if(flg1==2&&stat==5)
   {
    stat=1;
    goto checkmate;
   }
  else if(flg2==2&&stat==6)
   {
    stat=2;
    goto checkmate;
   }
  i=stalemate();
  if(i==1)
   {
    stat=0;
    goto stalemate;
   }
  else if(i==2)
   {
    goto GAME;
   }
   while(!kbhit()||getch()!=27)
    {
     in.x.ax=3;
     x=in.x.cx;
     y=in.x.dx;
     int86(0x33,&in,&in);
     if(pause.Getfocus()==1)
      goto MAINMENU;
     if(retry.Getfocus()==1)
      {
       retryfn();
       g.record();
       goto GAME;
      }
     if(X.Getfocus()==1)
      goto END;
     for(white=0;white<ctr[0];white++)
      {
       if(w[white].Getresponce()==1)
	{
	 w[white].Showpmoves();
	}
      }
     for(black=0;black<ctr[1];black++)
      {
       if(b[black].Getresponce()==1)
	{
	 b[black].Showpmoves();
	}
      }
     for(jij=0;jij<bcount;jij++)
      {
       if(p[jij].Showresponce()==1)
	{
	pawnswapper();
	checkking();
	move50stalemate();
	g.record();
	goto GAME;
	}
      }
    }
  goto END;
  checkmate :
  setcolor(3);
  for(i=192;i<629;i++)
   line(i,22,i,458);
  setcolor(0);
  settextstyle(0,HORIZ_DIR,8);
  outtextxy(290,190,"MATE");
  delay(500);
  stalemate :
  if(stat==0)
  {
  setcolor(3);
  for(i=192;i<629;i++)
   line(i,22,i,458);
  setcolor(0);
  settextstyle(0,HORIZ_DIR,8);
  outtextxy(260,190,"STALE");
  delay(500);
  setcolor(3);
  for(i=192;i<629;i++)
   line(i,22,i,458);
  setcolor(0);
  settextstyle(0,HORIZ_DIR,8);
  outtextxy(290,190,"MATE");
  delay(500);
  showboard();
  }
  g.record();
  g.display();
  showboard();
  ng.createbutton("",130,30,180,80,3,1,1,1,5);
  while(!kbhit()||getch()!=27)
   {
    in.x.ax=3;
    x=in.x.cx;
    y=in.x.dx;
    int86(0x33,&in,&in);
    if(pause.Getfocus()==1)
     goto MAINMENU;
    if(ng.Getfocus()==1)
     goto NEW;
    if(retry.Getfocus()==1)
     {
      bdcount=1;
      bdcount1=1;
      retryfn();
      g.record();
      goto GAME;
     }
    if(X.Getfocus()==1)
     goto END;
   }
  END:
  cleardevice();
  setbkcolor(9);
  setcolor(3);
  rectangle(0,0,getmaxx(),getmaxy());
  setcolor(15);
  settextstyle(1,HORIZ_DIR,4);
  outtextxy(100,getmaxy()/2-150,"HOPE YOU HAD FUN PLAYING");
  outtextxy(250,getmaxy()/2-110,"THE GAME");
  ShowBMP(210,170,"bye1.bmp");
  ShowBMP(210,170,"bye2.bmp");
  ShowBMP(210,170,"bye3.bmp");
  ShowBMP(210,170,"bye2.bmp");
  ShowBMP(210,170,"bye1.bmp");
  ShowBMP(210,170,"bye2.bmp");
  ShowBMP(210,170,"bye3.bmp");
  ShowBMP(210,170,"bye2.bmp");
  ShowBMP(210,170,"bye1.bmp");
  closegraph();
 }