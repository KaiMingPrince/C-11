#pragma once
extern "C" {
#include "include\SDL.h"
#include "include\SDL_thread.h"
}
#pragma comment(lib, "SDL\\Debug\\SDL2.lib")
#include <thread>
#include <iostream>
#include <fstream>
#undef main
const int g_width = 320;
const int g_height = 180;

void SDL_Thread_Render() {

}

void SDL_Demo()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* sdl_window_ptr = SDL_CreateWindow("YUVPlay", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, g_width, g_height, SDL_WINDOW_OPENGL);
	SDL_Renderer* sdl_renderer_ptr = SDL_CreateRenderer(sdl_window_ptr, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* sdl_texture_ptr = SDL_CreateTexture(sdl_renderer_ptr, SDL_PIXELFORMAT_IYUV,
		SDL_TEXTUREACCESS_STREAMING, g_width, g_height);

	std::thread t([sdl_window_ptr, sdl_renderer_ptr, sdl_texture_ptr]() {
		std::ifstream fs("yuv_420_320_180.yuv", std::ios::binary | std::ios::in);
		int frame_size = g_width * g_height * 3 / 2;
		unsigned char* yuv_buffer_ptr = new unsigned char[frame_size];
		while (1) {
			if (!fs.read(reinterpret_cast<char*>(yuv_buffer_ptr), frame_size)) {
				fs.clear();
				fs.seekg(0, std::ios::beg);
				continue;
			}
			SDL_UpdateTexture(sdl_texture_ptr, nullptr, yuv_buffer_ptr, g_width);
			SDL_RenderClear(sdl_renderer_ptr);
			SDL_RenderCopy(sdl_renderer_ptr, sdl_texture_ptr, nullptr, nullptr);
			SDL_RenderPresent(sdl_renderer_ptr);
			SDL_Delay(40);
		}
		//回收资源
		SDL_DestroyTexture(sdl_texture_ptr);
		SDL_DestroyRenderer(sdl_renderer_ptr);
		SDL_DestroyWindow(sdl_window_ptr);
		SDL_Quit();
	});
	t.join();
}