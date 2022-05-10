// Create by liuxin on 2022/05/10

#include <TApplication.h>
#include <TGClient.h>
#include <TGFrame.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TGResourcePool.h>

class MyMainFrame : public TGMainFrame
{
private:
    TGLabel *flabel1, *flabel2, *flabel3, *flabel4;
public:
    MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
    virtual ~MyMainFrame();

    void DoSwitch();
    void DoExit();
};

void MyMainFrame::DoSwitch()
{
   if (flabel1->IsDisabled()) {
        printf("Enabled labels\n");
        flabel1->Enable();
        flabel2->Enable();
   } else {
        printf("Disabled labels\n");
        flabel1->Disable();
        flabel2->Disable();
   }
}

void MyMainFrame::DoExit()
{
   printf("Slot DoExit()");
   gApplication->Terminate(0);
}

MyMainFrame::MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p, w, h)
{
    TGGC *fTextGC;
    const TGFont *font = gClient->GetFont("-*-times-bold-r-*-*-18-*-*-*-*-*-*-*");
    if (!font)
       font = gClient->GetResourcePool()->GetDefaultFont();
    FontStruct_t labelfont = font->GetFontStruct();
    GCValues_t   gval;
    gval.fMask = kGCBackground | kGCFont | kGCForeground;
    gval.fFont = font->GetFontHandle();
    gClient->GetColorByName("yellow", gval.fBackground);
    fTextGC = gClient->GetGC(&gval, kTRUE);

    ULong_t bcolor, ycolor;
    gClient->GetColorByName("yellow", ycolor);
    gClient->GetColorByName("blue", bcolor);

    flabel1 = new TGLabel(this, "OwnFont & BCK/ForgrColor", fTextGC->GetGC(), labelfont, kChildFrame, bcolor);
    AddFrame(flabel1, new TGLayoutHints(kLHintsNormal, 5, 5, 3, 4));
    flabel1->SetTextColor(ycolor);

    flabel2 = new TGLabel(this, "I am Normal Label");
    AddFrame(flabel2, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));

    TGTextButton *toggleButton = new TGTextButton(this, "&Toggle Labels");
    toggleButton->Connect("clicked()", "MyMainFrame", this, "DoSwitch()");
    toggleButton->SetToolTipText("Click on the button to toggle label's state (enable/disable)");
    AddFrame(toggleButton, new TGLayoutHints(kLHintsExpandX, 5, 5, 3, 4));

    TGTextButton *exit = new TGTextButton(this, "&Exit ");
    exit->Connect("Pressed()", "MyMainFrame", this, "DoExit()");
    AddFrame(exit, new TGLayoutHints(kLHintsExpandX, 5, 5, 3, 4));

    SetWindowName("Labels");

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
}

MyMainFrame::~MyMainFrame()
{
    Cleanup();
}

void labelTest()
{
    // Popup
    new MyMainFrame(gClient->GetRoot(), 200, 200);
}
