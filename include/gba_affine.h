//---------------------------------------------------------------------------------
#ifndef	_gba_affine_h_
#define	_gba_affine_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

#include "gba_base.h"

//---------------------------------------------------------------------------------
typedef struct {
     s32 x;     //Original data's center X coordinate (8bit fractional portion)
     s32 y;     //Original data's center Y coordinate (8bit fractional portion)
     s16 tX;    //Display's center X coordinate
     s16 tY;    //Display's center Y coordinate
     s16 sX;    //Scaling ratio in X direction (8bit fractional portion)
     s16 sY;    //Scaling ratio in Y direction (8bit fractional portion)
     u16 theta; //Angle of rotation (8bit fractional portion) Effective Range 0-FFFF
} BGAffineSource;

typedef struct {
     s16 pa;  //Difference in X coordinate along same line
     s16 pb;  //Difference in X coordinate along next line
     s16 pc;  //Difference in Y coordinate along same line
     s16 pd;  //Difference in Y coordinate along next line
     s32 x;   //Start X coordinate
     s32 y;   //Start Y coordinate
} BGAffineDest;


typedef struct {
     s16 sX;    //Scaling ratio in X direction (8bit fractional portion)
     s16 sY;    //Scaling ratio in Y direction (8bit fractional portion)
     u16 theta;     //Angle of rotation (8bit fractional portion) Effective Range 0-FFFF
} ObjAffineSource;


typedef struct {
     s16 pa;  //Difference in X coordinate along same line
     s16 pb;  //Difference in X coordinate along next line
     s16 pc;  //Difference in Y coordinate along same line
     s16 pd;  //Difference in Y coordinate along next line
} ObjAffineDest;


void ObjAffineSet(ObjAffineSource *source, void *dest, s32 num, s32 offset);
void BgAffineSet(BGAffineSource *source, BGAffineDest *dest, s32 num);

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif //_gba_affine_h
//---------------------------------------------------------------------------------
