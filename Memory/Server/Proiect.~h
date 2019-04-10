//---------------------------------------------------------------------------

#ifndef ProiectH
#define ProiectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ScktComp.hpp>
#include "Imagine.h"
//---------------------------------------------------------------------------
class Tx32 : public TForm
{
__published:	// IDE-managed Components
        TLabel *lYourScore;
        TLabel *lEnemyScore;
        TButton *btnExit;
        TButton *btnStart;
        TImageList *ImageList1;
        TTimer *ImaginiIdentice;
        TTimer *ImaginiDiferite;
        TServerSocket *Server;
        TLabel *lWait;
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall ImaginiIdenticeTimer(TObject *Sender);
        void __fastcall ImaginiDiferiteTimer(TObject *Sender);
        void __fastcall ImageClick(TObject *Sender);
        void __fastcall ServerClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        //void __fastcall ClientRead(TObject *Sender,
          //TCustomWinSocket *Socket);
private:	// User declarations
public:		// User declarations
        Imagine *vector[32];
        Face *myscore;
        Face *enemyscore;
        void ImageEnabledChange();
        __fastcall Tx32(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tx32 *x32;
//---------------------------------------------------------------------------
#endif
