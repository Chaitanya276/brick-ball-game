#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
int getkey()
{
	union REGS j,o;
	j.h.ah=0;
	int86(22,&j,&o);
	return(o.h.ah);
}
void game()
{
	int i,j,br[5][12],color=0,count=0,lives=3,rlx=0,rrx=50,rly=0,k,rry=30,bx=225,by=300,dx=4,dy=-2,x1=330,x2=400,key;
	setcolor(BLUE);
	rectangle(0,0,600,440); //Boundary Rectangle
	rectangle(x1,410,x2,420); //STRICKER

	printf("You have 3 Lives\n");

//Bricks...
	for(i=0;i<5;i++)
	{
		color+=1;
		if(color==0)
		{
			color=color+1;
		}
		setcolor(color);
		for(j=0;j<12;j++)
		{
		       rectangle(rlx,rly,rrx,rry);
		       rlx+=50;
		       rrx+=50;
		       br[i][j]=1;
		}
		rlx=0;
		rrx=50;
		rly+=30;
		rry+=30;
	}

 //Ball moving and stricker movement...
	while(1)
	{
	      /*	if(count==60)
		{
			clrscr();
			printf("You Won the game... :)\n");
		}   */
		if(lives==0)
		{
			clrscr();
			printf("Loss\n");
			printf("Press Escape\n");
		}
		else if(by+10>440)
		{       lives=lives-1;
			dy=-dy;
		}
		if(bx+10>=600 || bx-10<=0)
		{
			dx=-dx;
		}
		if(by-10<=0)
		{
			dy=-dy;
		}
		if(by+10==410 && bx>=x1 )
		{
			setcolor(BLUE);
			rectangle(x1,410,x2,420);
			dy=-dy;
		}
		if(by+10==410 && bx>=x2)
		{
			setcolor(BLUE);
			rectangle(x1,410,x2,420);
			dy=-dy;
			dx=+dx;

		}
		if(by-10<=150)
		{
			count+=1;
			i=(by-10)/30;
			j=bx/50;
			if(br[i][j]==1)
			{
				br[i][j]=0;
				dy=-dy;
				rly=i*30;
				rlx=j*50;
				rrx=(j+1)*50;
				rry=(i+1)*30;
				setcolor(BLACK);
				rectangle(rlx,rly,rrx,rry);
				setcolor(BLUE);
				rectangle(0,0,600,440);
				if(br[i][j-1]==1)   //Left Brick
				{
					setcolor(WHITE);
					rectangle((j-1)*50,i*30,j*50,(i+1)*30);
				}
				if(br[i-1][j]==1)  // Upper Brick
				{
					setcolor(WHITE);
					rectangle(j*50,(i-1)*30,(j+1)*50,i*30);
				}
				if(i != 2 && j!=11)
				{
					if(br[i][j+1]==1)   //Right Brick
					{
					setcolor(WHITE);
					rectangle((j+1)*50,i*30,(j+2)*50,(i+1)*30);
					}
				}
			}
		}
		bx=bx+dx;
		by=by+dy;
		setcolor(YELLOW);
		circle(bx,by,10);
		delay(30);
		setcolor(BLACK);
		circle(bx,by,10);

	    if(kbhit())
	    {
		setcolor(BLACK);
		rectangle(x1,410,x2,420);
		key=getkey();
		if(key==75 && x1>0)
		{
			x1=x1-20;
			x2=x2-20;
			if(x1==0)
			{
				setcolor(BLUE);
				rectangle(0,0,600,440);
			}
		}
		if(key==77 && x2<600)
		{
			x1=x1+20;
			x2=x2+20;
			if(x2==600)
			{
				setcolor(BLUE);
				rectangle(0,0,600,440);
			}
		}
		if(key==1)
		{
			exit(0);
		}
		setcolor(BLUE);
		rectangle(x1,410,x2,420);
	}
  }
 }
 void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:/TURBOC3/BGI");
	game();
	getch();
	closegraph();
}