#include "ntrack.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;

ntrack::ntrack(int argc, char *argv[])
{
    mgr = new SettingsManager("settings.xml");
    //All settings provided via command line over ride the default settings or the settings in the xml.
    for(int i=0; i < argc; i++)
    {
			if(i != 0)
			{
				if(strcmp("-D", argv[i]) == 0)
				{
                    mgr->dedicatedServer = true; //Make sure to store this for later.
				}

			}
    }
    game = createDevice(mgr->drvType, dimension2d<u32>(mgr->screen_w, mgr->screen_h), 16, mgr->fullscreen, false, true, this);
    if(game == NULL)
    {
        //Device creation failed
    }
    driver = game->getVideoDriver();
    smgr = game->getSceneManager();
    guienv = game->getGUIEnvironment();
    run();

}

ntrack::~ntrack()
{
    //dtor
}

bool ntrack::OnEvent(const SEvent& event)
{
    return false;
}

//Build the gui for our connection window
void ntrack::buildConnectWindow()
{
    IGUIWindow *theWin = guienv->addWindow(rect<s32>(40,20,250,140), false, L"Connect", 0, GUI_ID_CONNECT_WINDOW);
    guienv->addEditBox(L"",rect<s32>(90,30,190,50), false, theWin, GUI_ID_IP_TEXTBOX);
    guienv->addEditBox(L"",rect<s32>(90, 55, 190, 75), false,theWin, GUI_ID_PORT_TEXTBOX);
    guienv->addStaticText(L"Port: ",rect<s32>(10,55,80,75), false, false, theWin, 0, false);
    guienv->addStaticText(L"IP Address: ",rect<s32>(10,30,80,50), false, false, theWin, 0, false);
    guienv->addButton(rect<s32>(10, 80, 80, 100), theWin, 0 ,L"Connect");
}

void ntrack::run()
{
    buildConnectWindow();
    while(game->run())
    {
        driver->beginScene(true, true, SColor(255,0,0,0));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
    }
    game->drop();
}
