#include "Cythe.hpp"
#include "TPScheduler/TPScheduler.hpp"
#include "Util/AssetLoader.hpp"
#include "Util/InputHandler.hpp"
#include "Logger/Logger.hpp"
#include "GlobalParams.hpp"
#include "Util/flextGL.h"
#include "Util/audio.h"
#include "DBuffer/BufferManager.hpp"

void Cythe::Draw(){
	GPU_Clear(window);
	GPU_MatrixMode(window, GPU_MODEL);
	GPU_PushMatrix();
	for(auto& o : GameObjects){
		o->Draw();
	}
	//draw game objects
	GPU_PopMatrix();
	GPU_Flip(window);
}

void Cythe::Update(){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE){
			Running = false;
		}else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
			Input->handleKeyboardEvent(&event);
		}else if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL){
			Input->handleMouseEvent(&event);
		}
	}
	ticks++;
	//Update game objects
}

void Cythe::Initialize(){
	Logger::initLogger();
	Logger::log("Initialize");

	GPU_SetRequiredFeatures(GPU_FEATURE_RENDER_TARGETS);
	GPU_SetRequiredFeatures(GPU_FEATURE_BLEND_EQUATIONS);
	GPU_SetRequiredFeatures(GPU_FEATURE_ALL_SHADERS);
	GPU_SetRequiredFeatures(GPU_FEATURE_ALL_BASE);

	if(GlobalParams::debug)
		GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);

	GPU_RendererID rendererID = GPU_MakeRendererID("GPU_RENDERER_OPENGL_4_3", GPU_RENDERER_OPENGL_4, 4, 3);
	window = GPU_InitRendererByID(rendererID, resolution.first, resolution.second, GPU_DEFAULT_INIT_FLAGS);
	SDL_SetWindowTitle(SDL_GetWindowFromID(window->context->windowID), WindowTitle.c_str());

	if(flextInit() == -1){
		Logger::log("Failed to init FlextGL");
		Running = false;
		return;
	}

	Logger::log("Successfully loaded opengl ", FLEXT_MAJOR_VERSION, ".", FLEXT_MINOR_VERSION, " with extension compute_shader=", FLEXT_ARB_compute_shader, ", extension shader_storage__buffer_object=", FLEXT_ARB_shader_storage_buffer_object);

	if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0){
		Logger::log("Failed to initialize SDL2");
		Running = false;
		return;
	}

	initAudio();

	GPU_SetShapeBlending(true);
	GPU_SetShapeBlendMode(GPU_BLEND_NORMAL);

	Assets = std::make_shared<AssetLoader>();
	Input = std::make_shared<InputHandler>();
	TPSchedule = std::make_shared<TPScheduler>();

	RenderObject::Initialize();
}

void Cythe::Load(){
	Logger::log("Load");

	Assets->LoadImages();
	Assets->LoadAudio();
	Assets->LoadFonts();
	Assets->LoadShaders();
	Assets->LoadComputeShaders();

	RenderObject::Load();
}

Cythe::Cythe(){

}

Cythe::~Cythe(){
	GPU_FreeTarget(window);
	GPU_Quit();
	SDL_Quit();
	//Logger::endLogger();
}

void Cythe::Run(){
	Running = true;
	
	Initialize();
	Load();

	currentBufferManager.swap();//put any values that were changed during Initialize into the backs of the buffer

	while(Running){
		Update();
		for(auto& o : GameObjects){
			TPSchedule->queueFunction(1, [&](){o->Update();});
		}
		Draw();
		TPSchedule->waitForQueue();
		RemoveDeletedChildren();
		currentBufferManager.swap();
	}
}
