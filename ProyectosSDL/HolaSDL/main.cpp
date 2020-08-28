#include "checkML.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include "SDLApplication.h"

using namespace std;
using uint = unsigned int;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDLApplication app;
	try {
		app.run();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	return 0;
}