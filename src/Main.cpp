#include "System.h"

int main(int argc, char* argv[]) {
	System sys;

	if (sys.Init())sys.Run();

	sys.Final();

	return 0;
}