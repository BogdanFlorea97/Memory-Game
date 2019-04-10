//---------------------------------------------------------------------------

#ifndef ImagineH
#define ImagineH
#include <ExtCtrls.hpp>
#include "Pozitie.h"

class Face
{
public:
        int ct1,ct2;
        virtual int score()=0;
        Face();
};

class Imagine : Pozitie
{
private:
        int index;
public:
        void SetIndex(int index);
        int GetIndex();
        TImage *imagine;
        Imagine(int x0, int y0, int index,int face );
        int face;
};

class MyScore:public Face
{
public:
        int score();
        MyScore();
};

class EnemyScore:public Face
{
public:
        int score();
        EnemyScore();
};



//---------------------------------------------------------------------------
#endif

