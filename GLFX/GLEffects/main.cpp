#include "Engine.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
	glfx::Engine::Init(4, 6);

	auto& gm = glfx::GameManager::Get();

	gm.Init(800, 600, "GLFX");
	gm.Run();

	return 0;
}