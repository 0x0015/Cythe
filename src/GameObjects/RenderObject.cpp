#include "RenderObject.hpp"
#include "Sprite.hpp"
#include "../Cythe.hpp"
#include "../TPScheduler/TPScheduler.hpp"
#include <algorithm>
#include <execution>

void RenderObject::Initialize(){
	for(auto& o : GameObjects){
		o->mainWindow = mainWindow;
		o->renderWindow = this;
	}
	for(auto& o : GameObjects){
		o->Initialize();
	}
}
void RenderObject::Load(){
	//ImageSurface = IMG_Load(ImagePath.c_str());
	//if(!ImageSurface){
	//	std::cout<<"Image load error"<<std::endl;
	//}
	//Texture = SDL_CreateTextureFromSurface(mainWindow->renderer, Image);
	//SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
	Image = GPU_CreateImage(resolution.first, resolution.second, GPU_FORMAT_RGBA);
	if(!Image){
		std::cout<<"GPU_Image create error"<<std::endl;
	}
	GPU_LoadTarget(Image);
	ImageTarget = Image->target;
	window = Image->target;
	GPU_Clear(Image->target);
	//GPU_AddDepthBuffer(ImageTarget);
	for(auto& o : GameObjects){
		o->Load();
	}
}
void RenderObject::Draw(){
	
	GPU_SetActiveTarget(Image->target);
	GPU_Clear(Image->target);
	for(auto& o : GameObjects){
		o->Draw();
	}
	GPU_SetActiveTarget(renderWindow->window);
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
	GPU_Flip(Image->target);
}
void RenderObject::Update(){
	for(auto& o : GameObjects){
		mainWindow->TPSchedule->queueFunction(1, [&](){o->Update();});
	}
	//for(int i=0;i<GameObjects.size();i++){
	//	if(GameObjects[i]->toDelete){
	//		delete(GameObjects[i]);
	//		GameObjects.erase(GameObjects.begin()+i);
	//		i--;
	//		continue;
	//	}else{
	//		GameObjects[i]->Update();
	//	}
	//}
	//std::sort(GameObjects.begin(), GameObjects.end(), [](const std::shared_ptr<GameObject> obj1, const std::shared_ptr<GameObject> obj2){
	//		return(obj1->depth < obj2->depth);
	//		});//sort of clunky, using std::sort to sort the z buffer, but I guess it's fine.

}

SDL_Color RenderObject::GetPixelColor(std::pair<int, int> pixelPos){
	//float pixel[4];
	//glReadPixels(pixelPos.first, pixelPos.second, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	return(GPU_GetPixel(Image->target, pixelPos.first, pixelPos.second));
}

RenderObject::~RenderObject(){
	//for(int i=0;i<GameObjects.size();i++){
	//	delete(GameObjects[i]);
	//}
	GPU_FreeTarget(window);
	GPU_FreeTarget(ImageTarget);
	GPU_FreeImage(Image);
}
