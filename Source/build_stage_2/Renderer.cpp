#include "SDL3\SDL.h"
#include "SDL3_image\SDL_image.h"
#include "Renderer.h"
#include <stdio.h>
#include <string>
#include <list>
#include <vector>

using namespace std;

SDL_Window *Window;
SDL_GPUDevice *GPU;
SDL_Renderer *Renderer;
SDL_WindowFlags Window_flags;

std::vector<SDL_Texture*> Textures;

int Error_texture;

int Frame_widht;
int Frame_height;
SDL_Texture *Frame;

void *Renderer_get_window()
{
    return Window;
}

struct DrawListElement
{
    int index = -1;
    float x, y, w, h = 0;

    float UV_x ,UV_y , UV_w, UV_h = 0;

    DrawListElement(int _index,float _x,float _y)
    {
        int validated_index = _index;

        if(_index < 0 || _index > Textures.size())
        {
            validated_index = Error_texture;
        }
        index = validated_index;

        x = _x;
        y = _y;

        float Sprite_w = 0;
        float Sprite_h = 0;

        SDL_Texture *Texture = Textures.at(index);
        SDL_GetTextureSize(Texture, &Sprite_w, &Sprite_h);

        w = Sprite_w;
        h = Sprite_h;

        UV_x = 0;
        UV_y = 0;
        UV_w = Sprite_w;
        UV_h = Sprite_h;
    }

    DrawListElement(int _index,float _x,float _y,float _w,float _h)
    {
        int validated_index = _index;

        if(_index < 0 || _index > Textures.size())
        {
            validated_index = Error_texture;
        }
        index = validated_index;

        x = _x;
        y = _y;
        w = _w;
        h = _h;

        float Sprite_w = 0;
        float Sprite_h = 0;

        SDL_Texture *Texture = Textures.at(index);
        SDL_GetTextureSize(Texture, &Sprite_w, &Sprite_h);

        UV_x = 0;
        UV_y = 0;
        UV_w = Sprite_w;
        UV_h = Sprite_h;
    }

    DrawListElement(int _index,float _x,float _y,float _w,float _h,float _UV_x ,float _UV_y)
    {
        int validated_index = _index;

        if(_index < 0 || _index > Textures.size())
        {
            validated_index = Error_texture;
        }
        index = validated_index;
        
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        float Sprite_w = 0;
        float Sprite_h = 0;

        SDL_Texture *Texture = Textures.at(index);
        SDL_GetTextureSize(Texture, &Sprite_w, &Sprite_h);

        UV_w = Sprite_w;
        UV_h = Sprite_h;

        UV_x = _UV_x;
        UV_y = _UV_y;
        UV_w = Sprite_w;
        UV_h = Sprite_h;
    } 

    DrawListElement(int _index,float _x,float _y,float _w,float _h,float _UV_x ,float _UV_y,float _UV_w,float _UV_h)
    {
        int validated_index = _index;

        if(_index < 0 || _index > Textures.size())
        {
            validated_index = Error_texture;
        }
        index = validated_index;
        
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        UV_x = _UV_x;
        UV_y = _UV_y;
        UV_w = _UV_w;
        UV_h = _UV_h;
    }  
};

list<DrawListElement> RenderList;

const char *RendererType[] = 
{
    "SDL_renderer",
    "SDL_GPU",
    nullptr
};

int Renderer_fetch_Renderer_type_index(char *Renderer_Type)
{
    const char *Renderer_search_type = RendererType[0];
    int Renderer_search_loop = 0;
    while(Renderer_search_type != nullptr)
    {
        Renderer_search_type = RendererType[Renderer_search_loop];

        if(strcmp(RendererType[Renderer_search_loop],Renderer_Type) == 0)
        {
            return Renderer_search_loop;
        }

        Renderer_search_loop++;
    }

    return -1;
}

int Renderer_type = 0;

Rendering_init_result Renderer_init(int Screen_widht,int Screen_height,int Flags,std::string WindowName,int Renderer_Type)
{
    Frame_widht = Screen_widht;
    Frame_height = Screen_height;

    Renderer_type = Renderer_Type;

    printf("Initialasing rendering type %s \n",RendererType[Renderer_type]);

    Window_flags = Flags;

    Window = SDL_CreateWindow(WindowName.c_str(),Screen_widht,Screen_height,Window_flags);
    if(Window == nullptr)
    {
        printf("Error SDL_CreateWindow %S \n",SDL_GetError());
        return Window_init_error;
    }

    GPU == nullptr;
    if(Renderer_type == 1)
    {
        abort();
        //GPU = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV,true,nullptr);
        //Renderer = SDL_CreateGPURenderer(GPU,Window);
    }
    else
    {
        Renderer = SDL_CreateRenderer(Window,nullptr);
    }

    if(Renderer == nullptr)
    {
        printf("Error SDL_CreateRenderer %S\n",SDL_GetError());

        return Rendering_init_error;
    }

    SDL_Surface *Window_Surface = SDL_GetWindowSurface(Window);
    if(Window_Surface == nullptr)
    {
        printf("Error SDL_GetWindowSurface %S\n",SDL_GetError());
        return Resolution_error;  
    }
    SDL_PixelFormat Window_Surface_Format = Window_Surface->format;

    Frame = SDL_CreateTexture(Renderer,Window_Surface_Format,SDL_TEXTUREACCESS_TARGET,Frame_widht,Frame_height);
    if(Frame == nullptr)
    {
        printf("Error SDL_CreateTextureFromSurface %S\n",SDL_GetError());
        return Resolution_error;  
    }
            
    Textures = std::vector<SDL_Texture*>();

    Error_texture = Renderer_load_texture("Assets/Textures/Error.bmp");

    if(Error_texture < 0)
    {
        return FallbackTexture_error;
    }

    return Success;
}

void Renderer_quit()
{
    if(GPU != nullptr)
    {
        for(int i = 0;i<Textures.size();i++)
        {
            Renderer_unload_texture(i);
        }

        SDL_DestroyGPUDevice(GPU);
        SDL_DestroyRenderer(Renderer);
        SDL_Quit();
    }
}

int Renderer_load_texture(std::string FileName)
{
    SDL_Surface *Surface = IMG_Load(FileName.c_str());
    if(Surface == nullptr)
    {
        printf("Error IMG_Load %S\n",SDL_GetError());
        return -1;
    }

    SDL_Texture *Texture = SDL_CreateTextureFromSurface(Renderer,Surface);
    if(Texture == nullptr)
    {
        printf("Error SDL_CreateTextureFromSurface %S\n",SDL_GetError());
        return -2;
    }

    Textures.push_back(Texture);

    return Textures.size()-1;
}

void Renderer_unload_texture(int index)
{
    if(index > 0 || index < Textures.size())
    {
        return;
    }

    SDL_Texture *Texture = Textures.at(index);

    Textures.assign(index,nullptr);

    SDL_DestroyTexture(Texture);
}

void Renderer_draw_texture(int index,float x,float y,float w,float h,float uv_x,float uv_y)
{
    RenderList.push_back(DrawListElement(index,x,y,w,h,uv_x,uv_y));
}

void Renderer_draw_texture(int index,float x,float y,float w,float h,float uv_x,float uv_y,float uv_w,float uv_h)
{
    RenderList.push_back(DrawListElement(index,x,y,w,h,uv_x,uv_y,uv_w,uv_h));
}

void Renderer_draw_texture(int index,float x,float y,float w,float h)
{
    RenderList.push_back(DrawListElement(index,x,y,w,h));
}

void Renderer_draw_texture(int index,float x,float y)
{
    RenderList.push_back(DrawListElement(index,x,y));
}

void Renderer_draw_text(int font,float x,float y,std::string text)
{
	int string_size = text.size();
	
    SDL_Texture *Font_image = Textures[font];
    float font_w;
    float font_h;
    SDL_GetTextureSize(Font_image, &font_w, &font_h);

	int font_size = font_h;
    char char_code = 0;
	
	for(int i = 0;i<string_size;i++)
	{
		char_code = text[i]-32;
		
        RenderList.push_back(DrawListElement(font,
                                            x+(i*font_size),
                                            y,
                                            font_size,
                                            font_size,
                                            char_code*font_size,
                                            0,
                                            font_size,
                                            font_size
                                            )
                                            );
	}
}

void Renderer_draw()
{
    bool renderer_is_valid = SDL_RenderClear(Renderer);

    if(!renderer_is_valid)
    {
        printf("Warning! the renderer might of been invalidated. Reseting... \n");
        
        SDL_DestroyRenderer(Renderer);
        Renderer = SDL_CreateRenderer(Window,nullptr);
        if(Renderer == nullptr)
        {
            printf("SDL_CreateRenderer error %s recovery failed:\n",SDL_GetError());

            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Renderer warning!","Failed to reopen a renderer",Window);
        }
    }

    SDL_SetRenderTarget(Renderer, Frame);
    SDL_RenderClear(Renderer);

    int render_list_size = RenderList.size();
    DrawListElement *Element = nullptr;

    for(int i = 0;i<render_list_size;i++)
    {
        Element = &RenderList.front();
        int texture_index = Element->index;

        SDL_Texture *Texture = Textures.at(texture_index);

        SDL_FRect pos = {Element->x,Element->y,Element->w,Element->h};

        SDL_FRect uv = {Element->UV_x,Element->UV_y,Element->UV_w,Element->UV_h};

        SDL_RenderTexture(Renderer, Texture, &uv, &pos);

        RenderList.pop_front();
    }

    SDL_SetRenderTarget(Renderer, nullptr);
    
    SDL_RenderTexture(Renderer, Frame, nullptr, nullptr);
    SDL_RenderPresent(Renderer);
}