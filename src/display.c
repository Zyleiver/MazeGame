#include"MyHeader.h"

void display(void)
{
	DisplayClear();

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
