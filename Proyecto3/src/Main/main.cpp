#include <iostream>
#include <OgreInterface.h>

int main()
{
	OgreInterface* renderInterface = new OgreInterface();
	renderInterface->initApp();
	delete renderInterface;
	return 0;
}
