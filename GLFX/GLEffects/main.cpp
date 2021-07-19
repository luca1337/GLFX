#include "Engine.h"
#include "GameManager.h"

#include "ObjLoader.h"

int main(int argc, char* argv[])
{
	glfx::Engine::Init(4, 6);

	auto& gm = glfx::GameManager::Get();

	gm.Init(1920, 1080, "GLFX");
	gm.Run();

	return 0;
}