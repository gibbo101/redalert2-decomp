// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_E?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_E?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
#include "shared/unknown_map_generator.hpp"
#include "shared/random2.hpp"
extern Random2Class unknown_map_random_a705c0;
double __cdecl unknown_sqrt_4ba410(double value);
unsigned int __fastcall Map_Random_Range_005797a0(unsigned int minimum,unsigned int maximum);
// @ref ??0?$VectorClass@H@@=0046d020
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ?unknown_sqrt_4ba410@@=004ba410
void UnknownMapGenerator::unknown_0057c0d0(DynamicVectorClass<Rect> *regions,int count,Rect const &area)
{
    int floor=(int)unknown_sqrt_4ba410((double)count);
    int columns=floor*floor==count?floor:floor+1;
    int rows=columns*floor>=count?floor:columns;
    int width=area.Width/columns;
    int height=area.Height/columns;
    int rowX=0,rowY=0;
    int stepX=0,stepY=0;
    if((unsigned int)unknown_map_random_a705c0()*(1.0/4294967295.0)<0.5) {
        width=area.Width/rows;
        stepY=height;
        rowX=width;
    } else {
        height=area.Height/rows;
        stepX=width;
        rowY=height;
    }
    count=rows*columns-count;
    Point2D cursor=Point2D(area.X,area.Y);
    DynamicVectorClass<int> counts;
    DynamicVectorClass<int> choices;
    for(int row=0;row<rows;++row) {
        counts.Add(columns);
        choices.Add(row);
    }
    for(int removed=0;removed<count;++removed) {
        unsigned int maximum=choices.Count()-1;
        struct Range {double Span;};
        Range range={(unsigned int)(maximum+1)};
        unsigned int selected;
        do {selected=(unsigned int)((unsigned int)unknown_map_random_a705c0()*range.Span*(1.0/4294967295.0));} while(selected>maximum);
        counts[choices[selected]]=floor;
        choices.Delete((int)selected);
    }
    for(row=0;row<rows;++row) {
        int columnsInRow=counts[row];
        if(columnsInRow<columns) {
            if(stepX>0)cursor.X+=width/2;
            else cursor.Y+=height/2;
        }
        for(int column=0;column<columnsInRow;++column) {
            regions->Add(Rect(cursor.X+2,cursor.Y+2,width-4,height-4));
            cursor.X+=stepX;
            cursor.Y+=stepY;
        }
        cursor.X+=rowX;
        cursor.Y+=rowY;
        if(stepX>0)cursor.X=area.X;
        else cursor.Y=area.Y;
    }
}
