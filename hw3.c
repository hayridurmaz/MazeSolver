#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int maxX=0; 
int minX=0; 
int maxY=0; 
int minY=0;

typedef struct NodeCell{
  int x;
  int y;
  char data;
  struct NodeCell * west;
  struct NodeCell * north;
  struct NodeCell * east;
  struct NodeCell * south;
}Cell;

void setMaxMin(Cell *cell){
	if(cell->x < minX){
		minX=cell->x;
	}
	if(cell->y < minY){
		minY=cell->y;
	}
	if(cell->x > maxX){
		maxX = cell->x;
	}
	if (cell->y > maxY){
		maxY = cell->y;

	}
}
void checkNeighbour(Cell *cell){
	if(cell->south->west==0){
		cell->south->west=cell->west->south;
	}
	if(cell->west->south==0){
		cell->west->south=cell->south->west;
	}

	if(cell->north->west==0){
		cell->north->west=cell->west->north;
	}
	if(cell->west->north==0){
		cell->west->north=cell->north->west;
	}

	if(cell->east->north==0){
		cell->east->north=cell->north->east;
	}
	if(cell->north->east==0){
		cell->north->east=cell->east->north;
	}

	if(cell->east->south==0){
		cell->east->south=cell->south->east;
	}
	if(cell->south->east==0){
		cell->south->east=cell->east->south;
	}
}
void setNeighbour(Cell * cell, char a, char b, char c, char d){
	cell->west->data = a;
	cell->north->data=b;
	cell->east->data=c;
	cell->south->data=d;

	cell->west->x=cell->x-1;
	cell->west->y=cell->y;

	cell->north->y=cell->y+1;
	cell->north->x=cell->x;

	cell->east->x=cell->x+1;
	cell->east->y=cell->y;

	cell->south->y=cell->y-1;
	cell->south->x=cell->x;

	setMaxMin(cell->west);
	setMaxMin(cell->north);
	setMaxMin(cell->east);
	setMaxMin(cell->south);
	setMaxMin(cell);
}

Cell* findCell(int x, int y, Cell *c){
	if(x>0 && y>0){// EŞİTTİRLERİ KOY!!!!!!
		for (int i = 0; i<y; ++i)
		{
			if(c->north!=0){
				c=(c->north);
			}
			else
				return 0;
		}
		for (int i = 0; i < x; ++i)
		{
			if(c->east!=0){
				c=(c->east);
			}
			else
				return 0;
		}
		
	}
	if(x<0 && y>0){
		
		
		for (int i = 0; i > x; --i)
		{
			if(c->west!=0){
				c=(c->west);
			}
			else
				return 0;
			
		}
		for (int i = 0; i<y; ++i)
		{
			if(c->north!=0){
				c=(c->north);
			}
			else
				return 0;
			
		}
	}
	if(x>0 && y<0){
		for (int i = 0; i>y; --i)
		{
			if(c->south!=0){
				c=(c->south);
			}
			else
				return 0;
		}
		for (int i = 0; i < x; ++i)
		{
			if(c->east!=0){
				c=(c->east);
			}
			else
				return 0;
		}
		
	}
	if(x<0 && y<0){
		for (int i = 0; i>y; --i)
		{
			if(c->south!=0){
				c=(c->south);
			}
			else
				return 0;
		}
		for (int i = 0; i > x; --i)
		{
			if(c->west!=0){
				c=(c->west);
			}
			else
				return 0;
		}
		
	}
	if(x==0 && y!=0){
		if(y<0)
		for (int i = 0; i > y; --i)
		{
			if(c->south!=0){
				c=(c->south);
			}
			else 
				return 0;
		}
		if(y>0){
			for (int i = 0; i<y; ++i)
			{
			if(c->north!=0){
				c=(c->north);
			}
			else
				return 0;
			}
		}
	}
	if(x!=0 && y==0){
		if(x>0){
			for (int i = 0; i < x; ++i){
			if(c->east!=0){
				c=(c->east);
			}
			else
				return 0;
			}
		}
		if(x<0){
			for (int i = 0; i > x; --i){
			if(c->west!=0){
				c=(c->west);
			}
			else
				return 0;
			}
		}
	}
	return c;
	
}
void constructCell(Cell * cell, int x, int y, char d){
	if(cell->west==0){
		cell->west=(Cell *)malloc(sizeof(Cell));
	}
	if(cell->north==0){
			cell->north=(Cell *)malloc(sizeof(Cell));
	}
	if(cell->east==0){
		cell->east=(Cell *)malloc(sizeof(Cell));
	}
	
	if(cell->south==0){
		cell->south=(Cell *)malloc(sizeof(Cell));
	}
	cell->data=d;
	cell->x=x;
	cell->y=y; 
}
void printMaze(Cell *origin, int currentX, int currentY){
	int i,j;
	for (i = maxY; i >=minY; --i)
	{
		for (j = minX; j <= maxX; ++j)
		{
			Cell *cell = findCell(j,i,origin);
			if(currentX==j && i == currentY){
				printf(".");
				continue;
			}
			if(cell==0){
				printf("u");
			}
			else{
				if(cell->data=='o'){
					printf(" ");
				}
				else{
					printf("%c",cell->data);	
				}
			}
		}
		printf("\n");
	}
}
void checkUnknown(Cell *origin){
	int i,j;
	for (i = maxY; i >=minY; --i)
	{
		for (j = minX; j <= maxX; ++j)
		{
			
			Cell *cell = findCell(j,i,origin);
			if(cell==0){
				cell = (Cell *)malloc(sizeof(Cell));
				cell->x=j;
				cell->y=i;
				cell->data='u';
				if(findCell(j-1,i,origin)!=0){
					findCell(j-1,i,origin)->east=cell;
					cell->west=findCell(j-1,i,origin);
				}
				if(findCell(j+1,i,origin)!=0){
					findCell(j+1,i,origin)->west=cell;
					cell->east=findCell(j+1,i,origin);
				}
				if(findCell(j,i-1,origin)!=0){
					findCell(j,i-1,origin)->north=cell;
					cell->south=findCell(j,i-1,origin);
				}
				if(findCell(j,i+1,origin)!=0){
					findCell(j,i+1,origin)->south=cell;
					cell->north=findCell(j,i+1,origin);
				}
			}
		}
	}
}
Cell* goeast(Cell *cell, char a, char b, char c, char d){
	Cell *eastCell;
	if(cell->east==0){
		eastCell = (Cell *)malloc(sizeof(Cell));
	}
	else
		eastCell=cell->east;

	constructCell(eastCell,cell->x+1,cell->y,'o');
	eastCell->west=cell;
	cell->east=eastCell;
	setNeighbour(eastCell,a,b,c,d);
	checkNeighbour(cell);
	return eastCell;
}

Cell* gowest(Cell *cell, char a, char b, char c, char d){
	Cell *westCell;
	if(cell->west==0){
		westCell = (Cell *)malloc(sizeof(Cell));
	}
	else
		westCell=cell->west;

	constructCell(westCell,cell->x-1,cell->y,'o');
	westCell->east=cell;
	cell->west=westCell;
	setNeighbour(westCell,a,b,c,d);
	checkNeighbour(cell);
	return westCell;
}
Cell* gonorth(Cell *cell, char a, char b, char c, char d){
	Cell *northCell;
	if(cell->north==0){
		northCell = (Cell *)malloc(sizeof(Cell));
	}
	else
		northCell=cell->north;

	constructCell(northCell,cell->x,cell->y+1,'o');
	northCell->south=cell;
	cell->north=northCell;
	setNeighbour(northCell,a,b,c,d);
	checkNeighbour(cell);
	return northCell;
}

Cell* gosouth(Cell *cell, char a, char b, char c, char d){
	Cell *southCell;
	if(cell->south==0){
		southCell = (Cell *)malloc(sizeof(Cell));
	}
	else
		southCell=cell->south;

	constructCell(southCell,cell->x,cell->y-1,'o');
	southCell->north=cell;
	cell->south=southCell;
	setNeighbour(southCell,a,b,c,d);
	checkNeighbour(cell);
	return southCell;
}

int main(){ 
	char a, b, c, d;
	char string[100];
	int currentX=0,currentY=0;
	

	scanf(" %c %c %c %c", &a, &b,&c, &d);
	Cell *origin = (Cell *)malloc(sizeof(Cell));
	constructCell(origin,0,0,'o');
	setNeighbour(origin,a,b,c,d);
	Cell *currentCell =origin;

	while(scanf("%s",string) != EOF){
		scanf(" %c %c %c %c", &a, &b,&c, &d);
		if(!strcmp(string,"goeast")){
			currentCell = goeast(currentCell,a,b,c,d);
			currentX++;
		}
		if(!strcmp(string,"gowest")){
			currentCell = gowest(currentCell,a,b,c,d);
			currentX--;
		}
		if(!strcmp(string,"gonorth")){
			currentCell = gonorth(currentCell,a,b,c,d);
			currentY++;
		}
		if(!strcmp(string,"gosouth")){
			currentCell = gosouth(currentCell,a,b,c,d);
			currentY--;
		}
		checkUnknown(origin);
	}
	checkUnknown(origin);
	printMaze(origin,currentX,currentY);
	
	


  return 0;
}
