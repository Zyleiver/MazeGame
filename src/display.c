#include"MyHeader.h"

int xscale,yscale;

void display(void)
{
	DisplayClear();

	int imap,jmap;
	double Xlength;
	double Ylength;
	double length;
	double x0;
	double y0;

	length=-0.75*((double)xscale+(double)yscale)+36;
	Xlength=(double)xscale*length;
	Ylength=(double)yscale*length;
	x0=150-Xlength/2;
	y0=90-Ylength/2;
    	for(imap = 0;imap<=2*yscale;imap++)
    	{
    		for(jmap = 0;jmap<=2*xscale;jmap++)
    		{
    			if(Map[jmap][imap]==WALL&&jmap%2 == 0 && imap%2 == 1)
				{
					drawBox(x0+jmap/2*length,y0+(imap-1)/2*length,0.1,length,1,"",'M',"Red");
				}
				if(Map[jmap][imap]==WALL&&jmap%2 == 1 && imap%2 == 0)
				{
					drawBox(x0+(jmap-1)/2*length,y0+imap/2*length,length,0.1,1,"",'M',"Red");
				}
				if(Map[jmap][imap]==WALL&&jmap%2 == 0 && imap%2 == 0)
				{
					
				}
    			if(Map[jmap][imap]==COIN)
    			{
					drawBox(x0+(jmap-1)/2*length+length/3,y0+(imap-1)/2*length+length/3,length*2/3,length*2/3,1,"",'M',"Yellow");
				}
    			if(Map[jmap][imap]==END)
				{
					drawBox(x0+(jmap-1)/2*length+length/3,y0+(imap-1)/2*length+length/3,length*2/3,length*2/3,1,"",'M',"Green");
				}
    			if(Map[jmap][imap]==START)
    			{
					drawBox(x0+(jmap-1)/2*length+length/3,y0+(imap-1)/2*length+length/3,length*2/3,length*2/3,1,"",'M',"Blue");
				}
			}
			
		}

	int j=0;
	for(j;j<25;j++){
		if(ButtonEnum[j].visible==VISIBLE)
		{
			if(ButtonEnum[j].stage==Button_UP){
				drawBox(ButtonEnum[j].x,
						ButtonEnum[j].y,
						ButtonEnum[j].lx,
						ButtonEnum[j].ly,
						0,
						ButtonEnum[j].name,
						'M',"Red");
			} else{
				drawBox(ButtonEnum[j].x,
						ButtonEnum[j].y,
						ButtonEnum[j].lx,
						ButtonEnum[j].ly,
						0,
						ButtonEnum[j].name,
						'M',"Black");
			}
				
		}
	}

	
	//char *List[5]={"1","2","3","4","5"};
	//int x= menuList(1, 30, 30, 10, 10, 50, List,5);
	//int x = MessageBox(NULL, "aaa", "djcg", MB_OK| MB_ICONINFORMATION );
}
