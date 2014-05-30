


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../invariant/math/vector.h"
#include "../../invariant/math/vector.h"
#include "../../platform/native/platform.h"
#include "delay.h"
//#include <iostream>
#include "math/math.h"
#include "math/const.h"
	
void SDLH_circle (SDL_Renderer *ren, int R, int N, int cx, int cy,int e1,int e2, int e3) 
	{
	Vector<2,float> np, nprev;
	SDL_SetRenderDrawColor(ren,e1,e2,e3,5);
	for (int i=0;i < N*2+1;i++){
	np[0]=cx + R * cos(PI/N*i);
	np[1]=cy + R * sin(PI/N*i);		
	if (i>0) SDL_RenderDrawLine(ren,nprev[0],nprev[1],np[0],np[1]);	
	i++;
	nprev[0]=np[0];nprev[1]=np[1];
	};};
	
	int main ()
	{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    //std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
	}
	
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
if (win == nullptr){
    //std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    return 1;
}

//SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
if (ren == nullptr){
    //std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    return 1;
}
	
	SDL_Surface *bmp = SDL_LoadBMP("./res/GenOS.bmp");
if (bmp == nullptr){
    //std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    return 1;
}

SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
SDL_FreeSurface(bmp);
if (tex == nullptr){
    //std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    return 1;
}

//TTF_Init();


SDL_RenderClear(ren);
SDL_RenderCopy(ren, tex, NULL, NULL);



SDL_RenderPresent(ren);
SDL_RenderClear(ren);
//SDL_Delay(2000);
//SDL_Point np,c;


Vector<2,float> c={300,300};
//Vector<2,float> nst={400,300};
Vector<2,float> np,nprev;
int i=0;
SDL_SetRenderDrawColor(ren,255,255,255,5);
	
	
	
float t1=50,tprev1=50,t2=0,tprev2=0;
float tt1=100,ttprev1=100,tt2=0,ttprev2=0;

SDLH_circle(ren,10,80,200,200,255,255,255);
while(1){
t1=t1+0.05*(t2);
t2=t2-0.05*(t1);
tt1=tt1+0.01*(tt2);
tt2=tt2-0.01*(tt1);

SDLH_circle(ren,10,80,200+tprev1+ttprev1,200+tprev2+ttprev2,0,0,0);
SDLH_circle(ren,10,80,200+t1+tt1,200+t2+tt2,255,255,255);
//SDL_RenderClear(ren);
SDL_RenderPresent(ren);
SDL_Delay(10);
tprev1=t1;
tprev2=t2;
ttprev1=tt1;
ttprev2=tt2;
//if (t1==500) break;
};
//delay(1000);
	
//while(1);	
}
