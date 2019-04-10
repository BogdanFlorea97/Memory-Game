//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Proiect.h"
#include "Imagine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tx32 *x32;
int counter = 0;


//---------------------------------------------------------------------------
                //**********INITIALIZARE JOC**********
__fastcall Tx32::Tx32(TComponent* Owner)
        : TForm(Owner)
{
        myscore=new MyScore();
        enemyscore=new EnemyScore();
        lYourScore->Caption = myscore->ct1=0;
        lEnemyScore->Caption = enemyscore->ct2=0;
        lYourScore->Visible = false;
        lEnemyScore->Visible = false;
        int x=50,y=50;
        for(int i=0;i<32;i++)
        {
                if(i%8==0 && i!=0)
                        y+=110;
                vector[i]=new Imagine(x+(i%8)*110,y,0,0);
        }
        ImaginiIdentice->Enabled=false;
        ImageEnabledChange();

}
//---------------------------------------------------------------------------
                //**********EVENIMENT IMAGINE CLICK**********
void __fastcall Tx32::ImageClick(TObject *Sender)
{


        TImage *temp=dynamic_cast<TImage*>(Sender);
        if(vector[temp->Tag]->face==1)
                return;
        counter++;
        if(counter>2)
                return;

        AnsiString Mesaj;
        Mesaj="int";
        if(temp->Tag<10)
                {
                        Mesaj=Mesaj + "tip1" + IntToStr(temp->Tag);
                }
        if(temp->Tag>=10)
                {
                        Mesaj=Mesaj + "tip2" + IntToStr(temp->Tag);
                }

        Client->Socket->SendText(Mesaj);

        vector[temp->Tag]->face=1;
        ImageList1->GetBitmap(vector[temp->Tag]->GetIndex(),vector[temp->Tag]->imagine->Picture->Bitmap);
        vector[temp->Tag]->imagine->Refresh();

        if(counter==2)
                {
                        ImageEnabledChange();
                        int pos1=35,pos2=35;
                        for(int i=0;i<32;i++)
                                {
                                        if((vector[i]->face==1) && (pos1!=35))
                                                pos2=i;
                                        if((vector[i]->face==1) && (pos1==35))
                                                pos1=i;
                                }
                        if(vector[pos1]->GetIndex()==vector[pos2]->GetIndex())
                                {
                                ImaginiIdentice->Enabled=true;
                                ImageEnabledChange();
                                }
                        else
                                ImaginiDiferite->Enabled=true;
                }
}

//---------------------------------------------------------------------------
                //**********EVENIMENT BUTON EXIT CLICK**********
void __fastcall Tx32::btnExitClick(TObject *Sender)
{
      exit(0);
}
//---------------------------------------------------------------------------
                //**********EVENIMENT BUTON START CLICK**********
void __fastcall Tx32::btnStartClick(TObject *Sender)
{
        btnStart->Visible=false;
        for(int i=0;i<32;i++)
        {
                ImageList1->GetBitmap(16,vector[i]->imagine->Picture->Bitmap);
                vector[i]->imagine->Visible=true;
                vector[i]->imagine->Tag=i;
                vector[i]->imagine->Enabled=false;
        }
        lYourScore->Visible = true;
        lEnemyScore->Visible = true;
        ImageEnabledChange();
}
//---------------------------------------------------------------------------
                //**********TIMER IMAGINI IDENTICE**********
void __fastcall Tx32::ImaginiIdenticeTimer(TObject *Sender)
{
        bool myTurn= false;
        for(int i=0;i<32;i++)
        {
                if(vector[i]->face==1)
                {
                        vector[i]->imagine->Hide();
                        vector[i]->face=2;
                        myTurn = true;
                }
                if(vector[i]->face==5)
                {
                        vector[i]->face=10;
                        vector[i]->imagine->Hide();
                        myTurn = false;
                }

        }
        ImaginiIdentice->Enabled=false;
        counter=0;
        if(myTurn)
        {
                myscore->score();
                lYourScore->Caption=myscore->ct1;
        }
        else
        {
                enemyscore->score();
                lEnemyScore->Caption=enemyscore->ct2;
        }
        if(((myscore->ct1+enemyscore->ct2)==16))
        {
                if(myscore->ct1>enemyscore->ct2)
                {
                     ShowMessage("AI CASTIGAT!");
                     exit(0);
                }
                else if(myscore->ct1<enemyscore->ct2)
                {
                         ShowMessage("AI PIERDUT!");
                         exit(0);
                }
                else
                {
                        ShowMessage("REMIZA");
                        exit(0);
                }
        }
        //ImageEnabledChange();
}
//---------------------------------------------------------------------------
                //**********TIMER IAMGINI DIFERITE**********
void __fastcall Tx32::ImaginiDiferiteTimer(TObject *Sender)
{
        ImaginiDiferite->Enabled=false;
         for(int i=0;i<32;i++)
                {
                        if((vector[i]->face==1)||(vector[i]->face==5))
                         {
                                vector[i]->imagine->Hide();
                                ImageList1->GetBitmap(16,vector[i]->imagine->Picture->Bitmap);
                                vector[i]->imagine->Show();
                                vector[i]->face=2;
                                counter=0;
                         }
                }
        //ImageEnabledChange();

}
//---------------------------------------------------------------------------
                //**********IMAGINI ENABLE/DISABLE**********
void Tx32::ImageEnabledChange()
{
        if(vector[1]->imagine->Enabled==true)
                for(int i=0;i<32;i++)
                        vector[i]->imagine->Enabled=false;
        else
                for(int i=0;i<32;i++)
                        vector[i]->imagine->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall Tx32::ClientRead(TObject *Sender, TCustomWinSocket *Socket)
{


        AnsiString Mesaj;
        int pic,ind;
        Mesaj=Socket->ReceiveText();
                //**********DECODIFICARE MESAJE CAND SE GENEREAZA**********
        if(Mesaj.SubString(1,3)=="new")
        {
                int iLocal=4;
                for(int i=0;i<32;i++)
                {
                        if(Mesaj.SubString(iLocal,4) == "tip1")
                        {
                                pic = StrToInt(Mesaj.SubString(iLocal+4,1));
                                iLocal+=5;
                        }
                        else if(Mesaj.SubString(iLocal,4) == "tip2")
                        {
                                pic = StrToInt(Mesaj.SubString(iLocal+4,2));
                                iLocal+=6;
                        }
                        vector[i]->SetIndex(pic);
                }
                btnStart->Visible=true;

        }
        
                //**********DECODIFICARE MESAJE INTOARCERE IMAGINI**********
        if(Mesaj.SubString(1,3)=="int")
        {
                if(Mesaj.SubString(4,4)=="tip1")
                {
                        ind=StrToInt(Mesaj.SubString(8,1));
                }
                else
                {
                        ind=StrToInt(Mesaj.SubString(8,2));
                }
                vector[ind]->face=5;
                vector[ind]->imagine->Hide();
                ImageList1->GetBitmap(vector[ind]->GetIndex(),vector[ind]->imagine->Picture->Bitmap);
                vector[ind]->imagine->Show();
                counter++;
                if(counter==2)
                {

                        int pos1=35,pos2=35;
                        for(int i=0;i<32;i++)
                                {
                                        if((vector[i]->face==5) && (pos1!=35))
                                                pos2=i;
                                        if((vector[i]->face==5) && (pos1==35))
                                                pos1=i;
                                }
                        if(vector[pos1]->GetIndex()==vector[pos2]->GetIndex())
                                {
                                ImaginiIdentice->Enabled=true;
                                ImageEnabledChange();
                                }
                        else
                                ImaginiDiferite->Enabled=true;
                                ImageEnabledChange();
                }



        }


}
//---------------------------------------------------------------------------
                //**********EVENIMENT BUTON CONECTARE CLICK**********
void __fastcall Tx32::btnConectareClick(TObject *Sender)
{

        if(Edit->Text=="")
        {
                ShowMessage("Va rugam introduceti o adresa!");
        }
        Client->Active=false;
        Client->Address=Edit->Text;
        Client->Active=true;
        Label->Visible=false;
        Edit->Visible=false;
        btnConectare->Visible=false;

}
//---------------------------------------------------------------------------
                //**********CONECTAREA LA SERVER**********
void __fastcall Tx32::ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        ShowMessage("Inamicul s-a conectat.Fii mai bun ca el!");
}
//---------------------------------------------------------------------------

