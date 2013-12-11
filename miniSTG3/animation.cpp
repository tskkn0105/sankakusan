#include "game_main.h"
#include "mymain.h"



void ani_syori(int& count,int x,int& animation,int y,int z)
{
	count++;
	if(count>=x)
	{
		animation += y;
		if(animation==z)
		{
			animation = 0;
		}
		if(animation==-1)
		{
			animation = z-1;
		}
		count = 0;
	}
}
//ポインタ使おうぜ