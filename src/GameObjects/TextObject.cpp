#include "TextObject.hpp"
#include "../Cythe.hpp"
#include <SDL2/SDL_gpu.h>
#define FC_USE_SDL_GPU
#define NFONT_USE_SDL_GPU
#include "../NFont/NFont_gpu.h"
#include "../Util/AssetLoader.hpp"

void TextObject::Initialize(){
	mainWindow->Assets->FontRequiredPath(fontPath, defaultTextSize);
}

void TextObject::Load(){
	font = mainWindow->Assets->Fonts[std::pair<std::string, int>(fontPath, defaultTextSize)];
}

void TextObject::Update(){
	font->setDefaultColor((SDL_Color)drawColor);
}

void TextObject::Draw(){
	if(size.get() == std::pair<float, float>(0, 0)){
		font->draw(renderWindow->window, position.get().first, position.get().second, scale.get(), text.get().c_str());
	}else{
		GPU_Rect DestR;
		DestR.x = position.get().first;
		DestR.y = position.get().second;
		DestR.w = size.get().first;
		DestR.h = size.get().second;
		font->drawBox(renderWindow->window, DestR,scale.get(), text.get().c_str());
	}
}

TextObject::~TextObject(){

}
