// Create by liuxin on 2022/05/05
/*
 *  布局问题（TGCompositeFrame/TGLayoutHints）
 *  1. 使用自适应布局，默认从上往下排列。
 *  2. TGCompositeFrame为复合布局控件，可以管理子控件的布局。
 *  3. 控件的layout是(left, right, top, bottom)这个形式。
 *  4. 最后使用Resize(GetDefaultSize());来开启自适应尺寸。
 */
/*
 *  构造函数与析构函数问题
 *  1. 构造函数使用MapSubwindows();Mapwindows();来显示控件。
 *  2. 析构函数使用Cleanup();来释放控件。
 */
#include <TGClient.h>
#include <TGFrame.h>
#include <TGButton.h>

class MyMainFrame : public TGMainFrame {

private:
    TGCompositeFrame *fCframe;
    TGTextButton *fStart, *fPause, *fExit;
    Bool_t start, pause;
public:
    MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
    virtual ~MyMainFrame();

    void ChangeStartLabel();
    void ChangePauseLabel();
};

void MyMainFrame::ChangeStartLabel()
{
    fStart->SetState(kButtonDown);
    if (!start)
    {
        fStart->SetText("&Stop");
        start = kTRUE;
    } else {
        fStart->SetText("&Start");
        start = kFALSE;
  }
    fStart->SetState(kButtonUp);
}

void MyMainFrame::ChangePauseLabel()
{
    fPause->SetState(kButtonDown);
    if (!pause) {
        fPause->SetText("&Resume");
        pause = kTRUE;
    } else {
        fPause->SetText("&Pause");
        pause = kFALSE;
    }
    fPause->SetState(kButtonUp);
}

MyMainFrame::MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p, w, h)
{
    fCframe = new TGCompositeFrame(this, 170, 20, kHorizontalFrame | kFixedWidth);
    fCframe->SetBackgroundColor(0xff0000);

    fStart = new TGTextButton(fCframe, "&Start");
    fStart->SetBackgroundColor(0x00ff00);
    fStart->Connect("Clicked()", "MyMainFrame", this, "ChangeStartLabel()");
    fCframe->AddFrame(fStart, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 3, 2, 2, 2));
    fStart->SetToolTipText("Click to toggle the button label (Start/Stop)");
    start = kFALSE;

    fPause = new TGTextButton(fCframe, "&Pause");
    fPause->SetBackgroundColor(0x0000ff);
    fPause->Connect("Clicked()", "MyMainFrame", this, "ChangePauseLabel()");
    fPause->SetToolTipText("Click to toggle the button label (Pause/Resume)");
    fCframe->AddFrame(fPause, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
                                               3, 2, 2, 2));
    pause = kFALSE;

    AddFrame(fCframe, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));

    fExit = new TGTextButton(this, "&Exit ","gApplication->Terminate(0)");
    fExit->SetBackgroundColor(0xffff00);
    AddFrame(fExit, new TGLayoutHints(kLHintsTop | kLHintsExpandX,5,5,2,2));

    SetWindowName("Change Labels");

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
}

MyMainFrame::~MyMainFrame()
{
    Cleanup();
}

void buttonChangeLabel()
{
    new MyMainFrame(gClient->GetRoot(), 500, 80);
}