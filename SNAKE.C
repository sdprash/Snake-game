#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>

struct snake
{
	int  x,y;
	struct snake *link;
} *front;

int foodx,foody;
int score=0;
char dir;


void ini();
void game_over();
void new_game();
void check_key();
void move();
void check_bitten();
int check(int,int);
void create_layout();

void main()
{
	new_game();
}

void new_game()
{
	dir='e';
	clrscr();
	fflush(stdin);
	textcolor(RED);
	create_layout();
	foodx=rand()%40+2;
	foody=rand()%40+2;
	gotoxy(foodx,foody);
	printf("$");
	ini();
	getch();
	while(1)
	{
		delay(70);
		check_key();
		check_bitten();
	}
}

void ini()
{
	int i;
	struct snake *curr,*_new;
	textcolor(YELLOW);
	curr=NULL;
	front=(struct snake *)malloc(sizeof(struct snake));
	front->x=2;
	front->y=2;
	curr=front;
	gotoxy(16,47);
	printf("SCORE : %d\nArrow keys - MOVE\nR - Restart\nQ - Quit",score);
	gotoxy(front->x,front->y);
	cprintf("0");
	for(i=1;i<10;i++)
	{
		_new=(struct snake *)malloc(sizeof(struct snake));
		_new->x=curr->x+1;
		_new->y=curr->y;
		cprintf("0");
		curr->link=_new;
		curr=_new;
	}
	curr->link=front;
	front=curr;
}

void check_key()
{
	char ch;
	if(kbhit())
	{
		fflush(stdin);
		ch=getch();
		if(ch==0)
		{
		ch=getch();
		switch(ch)
		{
			case 75:if(dir!='e')	dir='w';  break;
			case 80:if(dir!='n')	dir='s';  break;
			case 77:if(dir!='w')	dir='e';  break;
			case 72:if(dir!='s')	dir='n';  break;

		}
		move();
		}
		else if(ch=='r')
			new_game();
		else if(ch=='q')
			exit(1);
		else
			move();
	}
	else
		move();
}

void move()
{
	int new_x=front->x,new_y=front->y;
	struct snake *temp;
	switch(dir)
	{
		case 'w':	new_x--;
				break;
		case 's':	new_y++;
				break;
		case 'e':	new_x++;
				break;
		case 'n':	new_y--;
				break;
		default:	exit(1);
	}
	gotoxy(new_x,new_y);
	cprintf("0");
	if(new_x==foodx && new_y==foody)
	{
		temp=(struct snake *)malloc(sizeof(struct snake));
		temp->link=front->link;
		temp->x=new_x;
		temp->y=new_y;
		front->link=temp;
		front=temp;
		do
		{
		foodx=rand()%40+2;
		foody=rand()%40+2;
		}while(check(foodx,foody)!=1);
		gotoxy(foodx,foody);
		printf("$");
		score++;
		gotoxy(24,47);
		printf("%d",score);
		gotoxy(new_x,new_y);
	}
	else
	{
		front=front->link;
		gotoxy(front->x,front->y);
		printf(" ");
		front->x=new_x;
		front->y=new_y;
		gotoxy(new_x,new_y);
	}
}

void check_bitten()
{
	int cx=front->x,cy=front->y;
	struct snake *temp=front->link;
	if(cx==1 || cx==42 || cy==1 || cy==42)
	{
		game_over();

	}
	while(temp!=front)
	{
		if(temp->x==cx && temp->y==cy)
		{
			game_over();
		}
		temp=temp->link;
	}
}

int check(int a,int b)
{
	struct snake *temp=front;
	if(temp->x==a && temp->y==b)
		return 0;
	temp=temp->link;
	while(temp!=front)
	{
		if(temp->x==a && temp->y==b)
			return 0;
		temp=temp->link;
	}
	return 1;
}

void create_layout()
{
	int i=1,j;
	for(j=1;j<=42;j++)
	{
		gotoxy(i,j);
		cprintf("*");
	}
	j=1;
	for(i=2;i<=42;i++)
	{
		gotoxy(i,j);
		cprintf("*");
	}
	i=42;
	for(j=2;j<=42;j++)
	{
		gotoxy(i,j);
		cprintf("*");
	}
	j=42;
	for(i=2;i<=41;i++)
	{
		gotoxy(i,j);
		cprintf("*");
	}
}

void game_over()
{
	char ch;
	gotoxy(16,47);
	printf("GAME OVER !!!");
	do
	{
	ch=getch();
	if(ch=='q')
		exit(1);
	else if(ch=='r')
		new_game();
	}while(ch!='q'||ch!='r');
}