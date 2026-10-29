
//TODO move to to a apstraction layer
#include "SDL3\SDL.h"
#include "Renderer.h"
#include "Input.h"
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include "WAD/WAD.h"

using namespace std;

unsigned long ApplicationStartStamp;
unsigned long ApplicationLifeTime;
unsigned long LastFrameTimeStamp;
unsigned long FrameTimeStamp;
unsigned long FrameTime;

const int MinimalFrameTime = 33;

void OnExit()
{
    Renderer_quit();
}

int main(int argc, char *argv[])
{
    //TODO -file to load a wad
    //TODO -print for consol printing
    const char *WadFileName = "DOOM1.WAD";

    WAD_Header* WAD = Load_WAD(WadFileName,nullptr);
    if(WAD == nullptr)
    {
        printf("Error loading the Internal WAD aborting...\n");
        abort();
    }

    int Window_flags = SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIGH_PIXEL_DENSITY;
    int window_w = 800;
    int window_h = 600;

    const char *Default_renderer_type = RendererType[0];

    for(int i = 0;i<argc;i++)
    {
        printf("Arg%d: %s \n", i, argv[i]);
        if(strcmp(argv[i],"RenderType=") == 0)
        {
            Default_renderer_type = argv[i+1];
            printf("RenderType=%s\n",argv[i+1]);
        }
    }

    int Renderer_type = Renderer_fetch_Renderer_type_index((char *)Default_renderer_type);

    if(Renderer_type < 0)
    {
        printf("Invalid Renderer type!\n");
        exit(-1);
    }
    
    Rendering_init_result Render_init = Renderer_init(window_w,window_h,Window_flags,"Game",Renderer_type);

    switch(Render_init)
    {
        case Success:
        {
            printf("Rendering Initialised succesfully!\n");
        }
        break;
        case Window_init_error: Rendering_init_error:
        {
            printf("Error initialising rendering %d\n",Render_init);
            throw(Render_init);
            exit(Render_init);
        }
        case Resolution_error:
        {
            printf("Error initialising framebuffer %d\n",Render_init);
            throw(Render_init);
            exit(Render_init);
        }
        break;

        default:
        {
            printf("Uknown case %d\n",Render_init);
        }
        break;
    }
    
    int Main_Font = Renderer_load_texture("Assets/Textures/Main_Font.bmp");

    printf("Entering main loop...\n");
    float DeltaTime = 1;
    //Why?
    struct timeval tv;

    gettimeofday(&tv, NULL);
    ApplicationStartStamp = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;

    std::atexit(OnExit);
    while(1)
    {
        gettimeofday(&tv, NULL);
        float DeltaTime = (float) FrameTime/(float) MinimalFrameTime;
        FrameTimeStamp = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;

        ApplicationLifeTime = FrameTimeStamp-ApplicationStartStamp;

        Update_Input();
        
        FrameTime = FrameTimeStamp-LastFrameTimeStamp;
        LastFrameTimeStamp = FrameTimeStamp;

        //printf("LastFrameTimeStamp: %d \n",LastFrameTimeStamp);
        //printf("FrameTimeStamp: %d \n ",FrameTimeStamp);
        //printf("FrameTime: %d \n",FrameTime);
        //printf("ApplicationLifeTime: %d \n",ApplicationLifeTime);

        //Renderer_draw_text(Main_Font,10,10,"LastFrameTimeStamp: "+std::to_string(LastFrameTimeStamp));
        //Renderer_draw_text(Main_Font,10,20,"FrameTimeStamp: "+std::to_string(FrameTimeStamp));
        //Renderer_draw_text(Main_Font,10,30,"Frame time: "+std::to_string(FrameTime));
        //Renderer_draw_text(Main_Font,10,40,"ApplicationLifeTime: "+std::to_string(ApplicationLifeTime));
        
        Renderer_draw();

        if(FrameTime < MinimalFrameTime)
        {
            int sleep_time =  MinimalFrameTime-FrameTime;
            //printf("To fast sleeping for: %d \n",sleep_time);
            usleep(sleep_time);
        }
    }
}