#pragma once
#include <stdio.h>
#include <string>

using namespace std;

enum Rendering_init_result
{
    Unknown,
    Success,
    Window_init_error,
    Rendering_init_error,
    Resolution_error,
    FallbackTexture_error
};

extern int Frame_widht;
extern int Frame_height;

extern int Error_texture;

extern const char *RendererType[];

int Renderer_fetch_Renderer_type_index(char *Renderer_Type);
Rendering_init_result Renderer_init(int Screen_widht,int Screen_height,int Flags,std::string WindowName,int Renderer_Type);
void Renderer_quit();

void *Renderer_get_window();

int Renderer_load_texture(std::string FileName);
void Renderer_unload_texture(int index);

void Renderer_draw_texture(int index,float x,float y,float w,float h,float uv_x,float uv_y,float uv_w,float uv_h);
void Renderer_draw_texture(int index,float x,float y,float w,float h,float uv_x,float uv_y);
void Renderer_draw_texture(int index,float x,float y,float w,float h);
void Renderer_draw_texture(int index,float x,float y);

void Renderer_draw_text(int font,float x,float y,std::string text);

void Renderer_draw();

void *Renderer_get_window();