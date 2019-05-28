#include <iostream>
#include "Game.h"
#undef main
using namespace std;

int main() {
	Game GoLEngine(800, 600);
	GoLEngine.onInit();
	return GoLEngine.onExecute();
}