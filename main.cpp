
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cstdlib>
#include <time.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Surface *puntos,*vida,*timer;
SDL_Texture *background,*scott_texture,*piggy, *coin, *puntos_texture,*vida_texture,*timer_texture;
SDL_Rect rect_background, rect_scott_texture, rect_piggy, rect_coin, rect_puntos, rect_vida, rect_timer;

vector<SDL_Texture*> scott_movement;
vector<SDL_Texture*> piggy_fly;
vector<SDL_Texture*> coin_rotation;

float Approach(float flGoal, float flCurrent, float dt){
    float flDifference = flGoal - flCurrent;

 	if (flDifference > dt)
 		return flCurrent + dt;
 	if (flDifference < -dt)
 		return flCurrent - dt;

 	return flGoal;
}

int main( int argc, char* args[] )
{

    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }

    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1071/*WIDTH*/, 287/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init SDL_TTF
    TTF_Init();


    SDL_Color blanco;
    blanco.b=255; blanco.g=255; blanco.r = 255;
    TTF_Font *fuente = TTF_OpenFont("ARIAL.TTF",200);

    //Init Surfaces
    SDL_FreeSurface(puntos);
    SDL_FreeSurface(vida);
    SDL_FreeSurface(timer);

    //Init textures
{

    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"ScottSprites/background_frozendsuburbs.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    //movimiento hacia la derecha son de la posicion 0 al 5
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk0.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk1.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk2.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk3.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk4.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk5.png"));

    //movimiento hacia la izquierda son del 6 al 11
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk_left0.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk_left1.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk_left2.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk_left3.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk_left4.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_walk_left5.png"));
    //salto es de la posicion 12 a la 21
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping0.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping1.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping2.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping3.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping4.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping5.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping6.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping7.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping8.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_jumping9.png"));
    //standing de posicion 22 a la 29
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_standing0.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_standing1.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_standing2.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_standing3.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_standing4.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_standing5.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_standing6.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_standing7.png"));
    //winning de posicion 30 a la 35
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_win0.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_win1.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_win2.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_win3.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_win4.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_win5.png"));
    //dying de posicion 36 a la 49
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die0.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die1.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die2.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die3.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die4.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die5.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die6.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die7.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die8.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die9.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die10.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die11.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die12.png"));
    scott_movement.push_back(IMG_LoadTexture(renderer,"ScottSprites/scott_die13.png"));



    //piggy textures
    //piggy fly yo left 0 al 4
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy0.png"));
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy1.png"));
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy2.png"));
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy3.png"));
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy4.png"));
    //piggy fly to right 5 al 9
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy_right0.png"));
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy_right1.png"));
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy_right2.png"));
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy_right3.png"));
    piggy_fly.push_back(IMG_LoadTexture(renderer,"ScottSprites/piggy_right4.png"));

    //Coin Textures
    coin_rotation.push_back(IMG_LoadTexture(renderer,"ScottSprites/Coin1.png"));
    coin_rotation.push_back(IMG_LoadTexture(renderer,"ScottSprites/Coin2.png"));
    coin_rotation.push_back(IMG_LoadTexture(renderer,"ScottSprites/Coin3.png"));
    coin_rotation.push_back(IMG_LoadTexture(renderer,"ScottSprites/Coin4.png"));
    coin_rotation.push_back(IMG_LoadTexture(renderer,"ScottSprites/Coin5.png"));
    coin_rotation.push_back(IMG_LoadTexture(renderer,"ScottSprites/Coin6.png"));

}
    //SCOTT DRAW
    rect_scott_texture.x = 50.0;
    rect_scott_texture.y = 180.0;
    rect_scott_texture.h = 65.0;
    rect_scott_texture.w = 38.0;

    //PIGGY DRAW
    rect_piggy.x = 100.0;
    rect_piggy.y = 20.0;
    rect_piggy.h = 86.0;
    rect_piggy.w = 94.0;

    //COIN DRAW
    rect_coin.x;
    rect_coin.y = 40.0;
    rect_coin.h = 30.0;
    rect_coin.w = 30.0;

    //GUi DRAW
    rect_puntos.x = 900;
    rect_puntos.y = 0;
    rect_puntos.h = 50;
    rect_puntos.w =150;

    rect_vida.x = 0;
    rect_vida.y = 237;
    rect_vida.h = 50;
    rect_vida.w =150;

    rect_timer.x = 900;
    rect_timer.y = 237;
    rect_timer.h = 50;
    rect_timer.w =150;


//  MAIN LOOP
    int FPS = 0;
    float deltatime=0, now=0, last=0;
    int current_sprite=4,current_piggy_sprite=0,current_coin_sprite=0;
    int velocidad_cerdo=15, coin_speed=10;
    int coin_random_pos=0;
    int contador_puntos=0,contador_vida=3, contador_timer=59;
    int contadort_moneda=0;
    srand(time(NULL));
    bool scott_salto=false, coin_ready =false, time =false;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    while(true)
    {
        last = now;
        now = SDL_GetTicks();
        deltatime =now -last;

        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }

        }
        if(contador_puntos>=1000){
            if(FPS%2==0){current_sprite++;}
            if(current_sprite<30||current_sprite>35){current_sprite=30;}
        }
        else if(contador_vida<=0 || contador_timer<=0){
            if(FPS%2==0){current_sprite++;}
            if(current_sprite<36||current_sprite>49){current_sprite=36;}
        }
        else if(scott_salto){
            current_sprite++;
            if(current_sprite>21||current_sprite<12){current_sprite=12;}
            if(current_sprite<=16)
                rect_scott_texture.y = Approach(rect_scott_texture.y-15,rect_scott_texture.y,deltatime);
            if(current_sprite>16)
                rect_scott_texture.y = Approach(rect_scott_texture.y+15,rect_scott_texture.y,deltatime);
            if(current_sprite==21){
                    scott_salto=false;
            }
            if(currentKeyStates[SDL_SCANCODE_RIGHT]){
                rect_scott_texture.x  = Approach(rect_scott_texture.x+15,rect_scott_texture.x,deltatime);
                if(rect_scott_texture.x+rect_scott_texture.w >= rect_background.w){
                        rect_scott_texture.x = rect_background.w-rect_scott_texture.w;
                }
            }
            else if(currentKeyStates[SDL_SCANCODE_LEFT]){
                rect_scott_texture.x = Approach(rect_scott_texture.x-15,rect_scott_texture.x,deltatime);
                if(rect_scott_texture.x<=0){
                    rect_scott_texture.x=0;
                }
            }
        }else{
            if(currentKeyStates[SDL_SCANCODE_RIGHT]){
                rect_scott_texture.x  = Approach(rect_scott_texture.x+6,rect_scott_texture.x,deltatime);
                if(rect_scott_texture.x+rect_scott_texture.w >= rect_background.w){rect_scott_texture.x = rect_background.w-rect_scott_texture.w;}
                current_sprite++;
                if(current_sprite>5){
                    current_sprite=0;
                }
            }
            else if(currentKeyStates[SDL_SCANCODE_LEFT]){
                rect_scott_texture.x = Approach(rect_scott_texture.x-6,rect_scott_texture.x,deltatime);
                if(rect_scott_texture.x<=0){rect_scott_texture.x=0;}
                current_sprite++;
                if(current_sprite>11||current_sprite<6){
                    current_sprite=6;
                }
            }
            else{
                if(FPS%2==0){current_sprite++;}
                if(current_sprite<22||current_sprite>29){current_sprite=22;}
            }
        }

        if(currentKeyStates[SDL_SCANCODE_UP]){
            scott_salto=true;
        }


        //MECANICAS DEL CERDITO
{
        if(FPS%1==0){
            current_piggy_sprite++;
            if(rect_piggy.x<=0||(rect_piggy.x+rect_piggy.w)>=rect_background.w){velocidad_cerdo=velocidad_cerdo*-1;}
            if(velocidad_cerdo>0){
                if(current_piggy_sprite>9||current_piggy_sprite<5){
                    current_piggy_sprite=5;
                }
            }else{
                if(current_piggy_sprite>4){
                    current_piggy_sprite=0;
                }
            }
            rect_piggy.x+=velocidad_cerdo;
        }
}

        //MECANICAS DE LA MONEDA
{

        if(FPS%1==0){
            current_coin_sprite++;
            if(current_coin_sprite>5){
                current_coin_sprite=0;
            }
        }
        //setea la posicion random de la moneda pero aun no se debe dibujar
        if(coin_random_pos==0){
            coin_random_pos = rand()%1022+10;
            rect_coin.x = coin_random_pos;
            cout<<rect_coin.x<<endl;
        }

        if(rect_piggy.x<rect_coin.x && rect_coin.x+rect_coin.w<(rect_piggy.x+rect_piggy.w)){
            coin_ready = true;
            time = true;
            //cout<<"cambia a true"<<endl;
        }

        if(coin_ready){
            if(rect_coin.y<=200){rect_coin.y += coin_speed;}
            if((rect_coin.x>rect_scott_texture.x&& rect_coin.x<rect_scott_texture.x+rect_scott_texture.w)||(rect_coin.x+rect_coin.w>rect_scott_texture.x && rect_coin.x+rect_coin.w<rect_scott_texture.x+rect_scott_texture.w)){
                if(rect_coin.y>rect_scott_texture.y && rect_coin.y+rect_coin.h<rect_scott_texture.y+rect_scott_texture.h){
                    coin_ready=false;
                    coin_random_pos=0;
                    time = false;
                    contadort_moneda=0;
                    rect_coin.y = 30;
                    contador_puntos+=100;
                }
            }
            contadort_moneda++;
        }

        if(contadort_moneda>35){
            if(contadort_moneda>45){
                time=false;
                coin_ready=false;
                coin_random_pos=0;
                contadort_moneda=0;
                rect_coin.y=30;
                contador_vida--;
            }
            else if(contadort_moneda%1==0)
                time=!time;
        }

}
        string textop ="Puntos: ",textov="Vidas: ",textot="Restan: ";
        stringstream sstm,sstm2,sstm3;
        sstm<<textop<<contador_puntos;
        textop = sstm.str();

        sstm2<<textov<<contador_vida;
        textov = sstm2.str();

        if(FPS%15==0)
            contador_timer--;
        sstm3<<textot<<contador_timer;
        textot = sstm3.str();

        puntos = TTF_RenderText_Solid(fuente,textop.c_str(),blanco);
        puntos_texture = SDL_CreateTextureFromSurface(renderer,puntos);

        vida = TTF_RenderText_Solid(fuente,textov.c_str(),blanco);
        vida_texture = SDL_CreateTextureFromSurface(renderer,vida);

        timer = TTF_RenderText_Solid(fuente,textot.c_str(),blanco);
        timer_texture = SDL_CreateTextureFromSurface(renderer,timer);

        //RENDER
        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, puntos_texture, NULL , &rect_puntos);
        SDL_RenderCopy(renderer, vida_texture, NULL , &rect_vida);
        SDL_RenderCopy(renderer, timer_texture, NULL , &rect_timer);
        SDL_RenderCopy(renderer, scott_texture, NULL, &rect_scott_texture);
        SDL_RenderCopy(renderer, scott_movement[current_sprite], NULL, &rect_scott_texture);
        if(time){
            SDL_RenderCopy(renderer, coin, NULL, &rect_coin);
            SDL_RenderCopy(renderer,coin_rotation[current_coin_sprite],NULL,&rect_coin);
        }
        SDL_RenderCopy(renderer, piggy, NULL, &rect_piggy);
        SDL_RenderCopy(renderer, piggy_fly[current_piggy_sprite], NULL, &rect_piggy);
        SDL_RenderPresent(renderer);
        SDL_Delay(80);
        FPS++;
    }

	return 0;
}
