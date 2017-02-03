//class version
#include<conio.h>
#include<iostream.h>
#include<time.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream.h>

class player
{
    int x,y;
    int step;
		void movement();
	public:
  	char key;
    player();
    int check();
  	void execute();
}p;

player::player()
{
	key= 'w';
  x= 315;
  y= 235;
}

void player::execute()
{
  movement();
}

//"Yoh better check yohself befor you wreck yohselff"
int player::check()
{
	step=getpixel(x, y);
  if(step!=0)
  {
  	return 0;
  }
  return 1;
}

void player::movement()
{
	putpixel(x, y, 2);
	if(kbhit())
	{
		key=getch();
	}
	delay(5);                       //time management
	switch (key)
	{
		case 'w': y--;
		break;
		case 'a': x--;
		break;
		case 's': y++;
		break;
		case 'd': x++;
		break;
		case 'e': cleardevice();
		break;
    default: break;
	}
}

class bots
{
		char dir;
    int m, n;
    int step;
    int rdm;
    int ahead, left, right, up, down;
    int dirCount;
    char validDir;
    int color;

    int check();
    void randomize();
    void pathTurn();
    void validMove();
    void movement();
	public:
  	bots();
    void position(char, int, int, int);
    int execute();
}bot[4];

bots::bots()
{
	dir= 'u';
  m=n=step=rdm=ahead=left=right=up=down=dirCount=0;
  validDir='u';
}

void bots::position(char d, int x, int y, int c)
{
	dir= d;
  m= x;
  n= y;
  color= c;
}

int bots::check()
{
	step=getpixel(m, n);
  if(step!=0)
  {
  	return 0;
  }
  return 1;
}

void bots::randomize()
{
  rdm=random(250);
  if(rdm==0)
  {
  	if(dir=='u'||dir=='d')
    {
    	dir='r';
    }
    else
    {
    	dir='u';
    }
  }
  else if(rdm==1)
  {
  	if(dir=='u'||dir=='d')
    {
    	dir='l';
    }
    else
    {
    	dir='d';
    }
  }
  else
  {
  	//do nothing
  }
}

void bots::pathTurn()
{
  rdm= rdm%2;
	switch(dir)
  {
  	case 'u':	ahead=getpixel(m, n-1);
							break;
    case 'd': ahead=getpixel(m, n+1);
							break;
    case 'l': ahead=getpixel(m-1, n);
							break;
    case 'r': ahead=getpixel(m+1, n);
							break;
    default: break;
  }
  if(ahead!=0)
  {
    if(dir=='u'|| dir=='d')
    {
      left=getpixel(m-1, n);
      right=getpixel(m+1, n);
      if(left==0 || right==0)
      {
      	if(rdm==0)
        {
        	dir='l';
        }
        else
        {
        	dir='r';
        }
      }
      else
      {
      	if(left==0)
        {
        	dir='l';
        }
        else
        {
        	dir='r';
        }
      }
    }
    else
    {
    	up=getpixel(m, n-1);
      down=getpixel(m, n+1);
      if(up==0 || down==0)
      {
      	if(rdm==0)
        {
        	dir='u';
        }
        else
        {
        	dir='d';
        }
      }
      else
      {
      	if(up==0)
        {
        	dir='u';
        }
        else
        {
        	dir='d';
        }
      }
    }
  }
}

void bots::validMove()
{
	dirCount=0;
  if(up==0)
  {
  	++dirCount;
    validDir='u';
  }
  if(down==0)
  {
  	++dirCount;
    validDir='d';
  }
  if(right==0)
  {
  	++dirCount;
    validDir='r';
  }
  if(left==0)
  {
  	++dirCount;
    validDir='l';
  }
  if(dirCount==1)
  {
  	dir= validDir;
  }
}

void bots::movement()
{
	putpixel(m, n, color);
  switch(dir)
	{
		case 'u': n--;
		break;
		case 'l': m--;
		break;
		case 'd': n++;
		break;
		case 'r': m++;
		break;
		default: break;
  }
}

int bots::execute()
{
  if(check())
  {
		randomize();
  	pathTurn();
  	validMove();
  	movement();
    return 1;
  }
  return 0;
}

class misc
{
	public:
		void border();
    void intro();
    void win(int);
    void lose(int);
    void save(char);
    int check();
    void print();
}setup;

void misc::border()
{
	line(0, 0, 630, 0);
  line(630, 0, 630, 470);
  line(630, 470, 0, 470);
  line(0, 470, 0, 0);
}

void misc::intro()
{
	outtextxy(10, 235, "You have entered the grid, user. Press any key to continue:");
  getch();
  outtextxy(10, 350, "You have been given a green LightCycle.");
	outtextxy(10, 400, "Your aim, don't trip on other LightCycle trails(lines).");
	outtextxy(10, 420, "Use only WASD to control. Press any key to continue:");
  getch();
  cleardevice();
  outtextxy(10, 235, "Version 2.0: Screenshot and view previous shots.");
  outtextxy(10, 250, "Press 'o' anytime to snap a screenshot!");
  getch();
  cleardevice();
}

void misc::win(int count)
{
	if(!count)
    {
    	outtextxy(100, 235, "You have mastered the grid, user.");
    }
}

void misc::lose(int count)
{
	if(count)
  {
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
		outtextxy(315, 235, "Game Over, Flynn.");
    settextstyle(3, HORIZ_DIR, 2);
  }
}

void misc::save(char ch)
{
	if(ch=='o')
  {
  	char x[631];
    ofstream scr("screenshot.txt", ios::out);
    for(int i= 0; i <= 470; i++)
    {
    	for(int j= 0; j <= 630; j++)
      {
      	x[j]= (getpixel(j, i) + '0');
      }
      scr.write(x, sizeof(x));
      scr.put('\n');
    }
    outtextxy(10, 10, "Screenshot taken successfully.");
  	scr.close();
  }
}

int misc::check()
{
	ifstream f("screenshot.txt");
  return f.good();
}

void misc::print()
{
  cleardevice();
  ifstream scr("screenshot.txt", ios::in);
  char x[631];
	for(int i= 0; i <= 470; ++i)
  {
    scr.getline(x, 631);
   	for(int j= 0; j <= 630; ++j)
  	{
     	putpixel(j, i, x[j]-'0');
    }
	}
  outtextxy(10, 10, "Last screenshot printed.");
  outtextxy(10, 30, "Press any key to exit:");
}

void main()
{
  clrscr();
  int i= 0, count= 0;
  //graphics initialization
	int gdriver=DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode,"C:\\TC\\BGI");
	errorcode=graphresult();
	if(errorcode!=0)
	{
		cout<<"Graphics error"<<grapherrormsg(errorcode);
		getch();
		exit(1);
	}
  randomize();
  setup.intro();
  setup.border();
	bot[0].position('d', 100, 100, 3);
  bot[1].position('d', 550, 100, 4);
  bot[2].position('u', 100, 400, 1);
  bot[3].position('u', 550, 400, 5);
  p.key=getch();
  //GameOver loop
	while(p.check())
	{
    p.execute();
    count= 0;
    for(i= 0; i < 4; i++)
    	{
				count+= bot[i].execute();
      }
    setup.win(count);
    setup.save(p.key);
  }
  setup.lose(count);
  getch();
  cleardevice();
  if(setup.check())
  {
    char choice;
  	outtextxy(10, 10, "Screenshot found. Press 'y' to display:");
    getch();
    setup.print();
  }
  else
  {
  	outtextxy(10, 10, "Screenshot not found.");
  }
  getch();
	closegraph();
}