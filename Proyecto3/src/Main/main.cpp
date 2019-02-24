#include <iostream>
#include <saluda.h>
#include <OgreRoot.h>
#include <OgreBuildSettings.h>

int main()
{
	saluda();
	Ogre::Root* root;
	//
	#if _DEBUG
		root = new Ogre::Root("plugins_d.cfg");
	#else
		root = new Ogre::Root("plugins.cfg");
	#endif

	system("pause");
	return 0;
}
