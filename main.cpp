#include "GameManager.h"

int main()
{
	GameManager::getSingleton()->run();
	GameManager::killSingleton();

	return 0;
}
