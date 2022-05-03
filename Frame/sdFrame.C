// Created by liuxin on 2022/05/03.
// 基本Frame


#include <TGClient.h>
#include <TGFrame.h>

class SDBaseFrame: public TGMainFrame {
    
public:
    SDBaseFrame(const TGWindow *p, UInt_t w, UInt_t h);
    virtual ~SDBaseFrame();
};

SDBaseFrame::SDBaseFrame(const TGWindow *p, UInt_t w, UInt_t h): TGMainFrame(p, w, h)
{
    // show
    MapWindow();
}

SDBaseFrame::~SDBaseFrame()
{
    // clean
    Cleanup();
}

void sdFrame()
{
    new SDBaseFrame(gClient->GetRoot(), 350, 80);
}