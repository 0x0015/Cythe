#include "Sprite.hpp"
#include "../Cythe.hpp"
#include "../Util/AssetLoader.hpp"
#include <numbers>

void Sprite::Initialize(){
	mainWindow->Assets->ImageRequiredPath(ImagePath);
}
void Sprite::Load(){
	//ImageSurface = IMG_Load(ImagePath.c_str());
	//if(!ImageSurface){
	//	std::cout<<"Image load error"<<std::endl;
	//}
	//Texture = SDL_CreateTextureFromSurface(mainWindow->renderer, Image);
	//SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
	//Image = GPU_LoadImage(ImagePath.c_str());
	//Image = GPU_CopyImageFromSurface(ImageSurface);
	Image = GPU_CopyImage(mainWindow->Assets->Images[ImagePath]);
	if(!Image){
		std::cout<<"GPU_Image create error.  Image="<<mainWindow->Assets->Images[ImagePath]<<std::endl;
	}
	ImageTarget = GPU_LoadTarget(Image);
	//GPU_AddDepthBuffer(ImageTarget);
	}
void Sprite::Draw(){
	GPU_Rect DestR;
	DestR.x = position.get().first;
	DestR.y = position.get().second;
	DestR.w = size.get().first;
	DestR.h = size.get().second;
	SDL_Point RotP;
	RotP.x = center.get().first;
	RotP.y = center.get().second;
	//SDL_RenderCopyEx(mainWindow->renderer, Texture, NULL, &DestR, (double)rotation, &RotP, SDL_FLIP_NONE);
	
	//GPU_Translate(0, 0, depth);
	GPU_SetBlending(Image, true);
	GPU_SetBlendMode(Image, GPU_BLEND_NORMAL);
	//GPU_SetBlendFunction(Image, GPU_FUNC_SRC_ALPHA, GPU_FUNC_ONE_MINUS_SRC_ALPHA, GPU_FUNC_ONE, GPU_FUNC_ZERO );
	//GPU_SetRGBA(Image, 255, 100, 255, 127.5f + 127.5f*sin(SDL_GetTicks() / 1000.0f) * depth);
	GPU_BlitRectX(Image, NULL, renderWindow->window, &DestR, rotation, center.get().first, center.get().second, GPU_FLIP_NONE);
}
void Sprite::Update(){

}

void Sprite::PointToward(std::shared_ptr<GameObject> other){
	//std::cout<<"Point toward: ("<<other->position.second<<" - "<<position.second<<", "<<other->position.first<<" - "<<position.first<<")";
	rotation = std::atan2(other->position.get().second - position.get().second, other->position.get().first - position.get().first) * ((float)180/(float)std::numbers::pi);
	if(rotation < 0){
		rotation = rotation + 360;//buffered thus can't get += operator
	}
	//std::cout<<" = "<<rotation<<std::endl;
}

Sprite::~Sprite(){
	GPU_FreeTarget(ImageTarget);
	GPU_FreeImage(Image);
}
