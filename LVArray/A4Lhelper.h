// ---------------------------------------------------------------------------
//  Created by Steffan Benamou, Aledyne Engineering Inc. on 11/3/2014.
//
//  The copyright to the computer program(s) herein is the property of
//  Aledyne Engineering, Inc.  The program(s) may be used and/or copied
//  only with the written permission of Aledyne Engineering, Inc. or in
//  accordance with the terms and conditions stipulated in the
//  agreement/contract under which the program(s) have been supplied.

//  Copyright (C) 2014, Aledyne Engineering, Inc.
//  P.O. Box 1530
//  Morgan Hill, CA. 95038
//  (408) 465-9825

// @file A4LHelper.h
// This file implements support for the Arduino Compatible Compiler for
// LabVIEW.  It contains support functions for native LabVIEW primitives
// as well as some Arduino specific APIs.
// ---------------------------------------------------------------------------
#ifndef A4LHelper_h
#define A4LHelper_h

#include "Stream.h"
#include "Arduino.h"
#include <math.h>

signed long MatchPattern(String * after, String * match, String * before, String input, String RegExpr, signed long offset)
{
  signed long idx = input.indexOf(RegExpr, offset);
  if(idx < 0)
  {
    if(before != NULL)
	{
      *before = input;
	}
    if(match != NULL)
	{	
		*match = "";
	}
    if(after != NULL)
	{	
		*after = "";
	}
    return -1;
  }
  else
  {
    if(before != NULL)
	{
      *before = input.substring(0, idx);
	}
	if(after != NULL)
	{
      *after = input.substring(idx+RegExpr.length(), input.length());
	}
	if(match != NULL)
	{
      *match = input.substring(idx, idx+RegExpr.length());
	}
    return (idx+RegExpr.length());
  }
}

void ReverseString(String * stringOut, String  stringIn)
{
    String temp = stringIn;
    
    for(unsigned long i=0; i<stringIn.length(); i++)
    {
        temp.setCharAt((stringIn.length()-1-i), stringIn[i]);
    }

    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void RotateString(String * stringOut, String  stringIn)
{
    String temp = stringIn;
    
    // rotate all chars down by 1
    for(unsigned long i=0; i<(stringIn.length()-1); i++)
    {
        temp.setCharAt(i, stringIn[i+1]);
    }
    // put the first char at the end
    temp.setCharAt((stringIn.length()-1), stringIn[0]);
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void ReplaceString(String * stringOut, String  stringIn, String findStr, String replaceStr)
{
    String temp = stringIn;
    temp.replace(findStr, replaceStr);
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, unsigned char num, signed short width)
{
    String temp = String((unsigned short)num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String((unsigned short)num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, signed char num, signed short width)
{
    String temp = String((signed short)num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String((signed short)num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, unsigned short num, signed short width)
{
    String temp = String(num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String(num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, signed short num, signed short width)
{
    String temp = String(num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String(num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, unsigned long num, signed short width)
{
    String temp = String(num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String(num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, signed long num, signed short width)
{
    String temp = String(num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String(num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, unsigned long long num, signed short width)
{
    String temp = String((unsigned long)num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String((unsigned long)num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, signed long long num, signed short width)
{
    String temp = String((long)num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String((long)num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, float num, signed short width)
{
    String temp = String((long)num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String((long)num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void NumberToDecString(String * stringOut, double num, signed short width)
{
    String temp = String((long)num);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String((long)num);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

template <typename Type>
void NumberToFracString(String * stringOut, Type num, signed short prec, signed short width)
{
    String temp = String((double)num, prec);
    if((unsigned short)width > temp.length())
    {
      short padsize = width - temp.length();
      temp = "";
      // pad with spaces on left  
      for(short i=0; i < padsize; i++)
      {
        temp += " ";
      }
	  
      temp += String((double)num, prec);
    }
	
    if(stringOut != NULL)
    {
      *stringOut = temp;
    }
}

void inRangeCoerce(signed long num, signed long lowerlim, signed long upperlim, bool agg, bool inclower, bool incupper, signed long * coerced, bool * inrange)
{

    if(inrange!=NULL)
    {
      *inrange = (inclower)?(num >= lowerlim):(num > lowerlim);
      *inrange &= (incupper)?(num <= upperlim):(num < upperlim);
    }

    if(coerced!=NULL)
    {
      *coerced = constrain(num, lowerlim, upperlim);
    }
}

void inRangeCoerce(unsigned long num, unsigned long lowerlim, unsigned long upperlim, bool agg, bool inclower, bool incupper, unsigned long * coerced, bool * inrange)
{

    if(inrange!=NULL)
    {
      *inrange = (inclower)?(num >= lowerlim):(num > lowerlim);
      *inrange &= (incupper)?(num <= upperlim):(num < upperlim);
    }

    if(coerced!=NULL)
    {
      *coerced = constrain(num, lowerlim, upperlim);
    }
}

void inRangeCoerce(signed short num, signed short lowerlim, signed short upperlim, bool agg, bool inclower, bool incupper, signed short * coerced, bool * inrange)
{

    if(inrange!=NULL)
    {
      *inrange = (inclower)?(num >= lowerlim):(num > lowerlim);
      *inrange &= (incupper)?(num <= upperlim):(num < upperlim);
    }

    if(coerced!=NULL)
    {
      *coerced = constrain(num, lowerlim, upperlim);
    }
}

void inRangeCoerce(unsigned short num, unsigned short lowerlim, unsigned short upperlim, bool agg, bool inclower, bool incupper, unsigned short * coerced, bool * inrange)
{

    if(inrange!=NULL)
    {
      *inrange = (inclower)?(num >= lowerlim):(num > lowerlim);
      *inrange &= (incupper)?(num <= upperlim):(num < upperlim);
    }

    if(coerced!=NULL)
    {
      *coerced = constrain(num, lowerlim, upperlim);
    }
}

void inRangeCoerce(signed char num, signed char lowerlim, signed char upperlim, bool agg, bool inclower, bool incupper, signed char * coerced, bool * inrange)
{

    if(inrange!=NULL)
    {
      *inrange = (inclower)?(num >= lowerlim):(num > lowerlim);
      *inrange &= (incupper)?(num <= upperlim):(num < upperlim);
    }

    if(coerced!=NULL)
    {
      *coerced = constrain(num, lowerlim, upperlim);
    }
}

void inRangeCoerce(unsigned char num, unsigned char lowerlim, unsigned char upperlim, bool agg, bool inclower, bool incupper, unsigned char * coerced, bool * inrange)
{

    if(inrange!=NULL)
    {
      *inrange = (inclower)?(num >= lowerlim):(num > lowerlim);
      *inrange &= (incupper)?(num <= upperlim):(num < upperlim);
    }

    if(coerced!=NULL)
    {
      *coerced = constrain(num, lowerlim, upperlim);
    }
}

unsigned char Rotate(unsigned char x, signed short numbits)
{
  if(numbits > 0)
  {
    return ((x <<  (numbits%8)) | (x >> (8 - (numbits%8))));
  }
  else if(numbits < 0)
  {
    return ((x >> ((-numbits)%8)) | (x << (8 - ((-numbits)%8))));
  }
  else
  {
    return x;
  }
}

signed char Rotate(signed char x, signed short numbits)
{
  if(numbits > 0)
  {
    return (((unsigned char)x <<  (numbits%8)) | ((unsigned char)x >> (8 - (numbits%8))));
  }
  else if(numbits < 0)
  {
    return (((unsigned char)x >> ((-numbits)%8)) | ((unsigned char)x << (8 - ((-numbits)%8))));
  }
  else
  {
    return x;
  }
}

unsigned short Rotate(unsigned short x, signed short numbits)
{
  if(numbits > 0)
  {
    return ((x <<  (numbits%16)) | (x >> (16 - (numbits%16))));
  }
  else if(numbits < 0)
  {
    return ((x >> ((-numbits)%16)) | (x << (16 - ((-numbits)%16))));
  }
  else
  {
    return x;
  }
}

signed short Rotate(signed short x, signed short numbits)
{
  if(numbits > 0)
  {
    return (((unsigned short)x <<  (numbits%16)) | ((unsigned short)x >> (16 - (numbits%16))));
  }
  else if(numbits < 0)
  {
    return (((unsigned short)x >> ((-numbits)%16)) | ((unsigned short)x << (16 - ((-numbits)%16))));
  }
  else
  {
    return x;
  }
}

unsigned long Rotate(unsigned long x, signed short numbits)
{
  if(numbits > 0)
  {
    return ((x <<  (numbits%32)) | (x >> (32 - (numbits%32))));
  }
  else if(numbits < 0)
  {
    return ((x >> ((-numbits)%32)) | (x << (32 - ((-numbits)%32))));
  }
  else
  {
    return x;
  }
}

signed long Rotate(signed long x, signed short numbits)
{
  if(numbits > 0)
  {
    return (((unsigned long)x <<  (numbits%32)) | ((unsigned long)x >> (32 - (numbits%32))));
  }
  else if(numbits < 0)
  {
    return (((unsigned long)x >> ((-numbits)%32)) | ((unsigned long)x << (32 - ((-numbits)%32))));
  }
  else
  {
    return x;
  }
}

unsigned long long Rotate(unsigned long long x, signed short numbits)
{
  if(numbits > 0)
  {
    return ((x <<  (numbits%64)) | (x >> (64 - (numbits%64))));
  }
  else if(numbits < 0)
  {
    return ((x >> ((-numbits)%64)) | (x << (64 - ((-numbits)%64))));
  }
  else
  {
    return x;
  }
}

signed long long Rotate(signed long long x, signed short numbits)
{
  if(numbits > 0)
  {
    return (((unsigned long)x <<  (numbits%64)) | ((unsigned long)x >> (64 - (numbits%64))));
  }
  else if(numbits < 0)
  {
    return (((unsigned long)x >> ((-numbits)%64)) | ((unsigned long)x << (64 - ((-numbits)%64))));
  }
  else
  {
    return x;
  }
}

unsigned long Rotate(double x, signed short numbits)
{
  if(numbits > 0)
  {
    return (((unsigned long)lrint(x) <<  (numbits%32)) | ((unsigned long)lrint(x) >> (32 - (numbits%32))));
  }
  else if(numbits < 0)
  {
    return (((unsigned long)lrint(x) >> ((-numbits)%32)) | ((unsigned long)lrint(x) << (32 - ((-numbits)%32))));
  }
  else
  {
    return ((unsigned long)lrint(x));
  }
}

unsigned long Rotate(float x, signed short numbits)
{
  if(numbits > 0)
  {
    return (((unsigned long)lrint(x) <<  (numbits%32)) | ((unsigned long)lrint(x) >> (32 - (numbits%32))));
  }
  else if(numbits < 0)
  {
    return (((unsigned long)lrint(x) >> ((-numbits)%32)) | ((unsigned long)lrint(x) << (32 - ((-numbits)%32))));
  }
  else
  {
    return ((unsigned long)lrint(x));
  }
}

void RotateWC(signed char x, boolean carry, boolean direction, boolean * carryout, signed char * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x80)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | (carry << 7));
    }
  }
}

void RotateWC(unsigned char x, boolean carry, boolean direction, boolean * carryout, unsigned char * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x80)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | (carry << 7));
    }
  } 
}

void RotateWC(unsigned short x, boolean carry, boolean direction, boolean * carryout, unsigned short * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x8000)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | ((unsigned short)carry << 15));
    }
  } 
}

void RotateWC(signed short x, boolean carry, boolean direction, boolean * carryout, signed short * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x8000)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | ((unsigned short)carry << 15));
    }
  } 
}

void RotateWC(unsigned long x, boolean carry, boolean direction, boolean * carryout, unsigned long * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x80000000)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | ((unsigned long)carry << 31));
    }
  }  
}

void RotateWC(signed long x, boolean carry, boolean direction, boolean * carryout, signed long * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x80000000)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | ((signed long)carry << 31));
    }
  }  
}

void RotateWC(unsigned long long x, boolean carry, boolean direction, boolean * carryout, unsigned long long * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x8000000000000000)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | ((unsigned long long)carry << 63));
    }
  }  
}

void RotateWC(signed long long x, boolean carry, boolean direction, boolean * carryout, signed long long * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x8000000000000000)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | ((signed long long)carry << 63));
    }
  }  
}

void RotateWC(signed long x, boolean carry, boolean direction, boolean * carryout, unsigned long * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = (x & 0x80000000)?true:false;
    }
    else // Right
    {
      *carryout = (x & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = ((x << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = ((x >> 1) | ((unsigned long)carry << 31));
    }
  }  
}

void RotateWC(double x, boolean carry, boolean direction, boolean * carryout, unsigned long * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = ((unsigned long)lrint(x) & 0x80000000)?true:false;
    }
    else // Right
    {
      *carryout = ((unsigned long)lrint(x) & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = (((unsigned long)lrint(x) << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = (((unsigned long)lrint(x) >> 1) | ((unsigned long)carry << 31));
    }
  }  
}

void RotateWC(float x, boolean carry, boolean direction, boolean * carryout, unsigned long * out)
{
  if(carryout != NULL)
  {
    if(direction) // Left
    {
      *carryout = ((unsigned long)lrint(x)& 0x80000000)?true:false;
    }
    else // Right
    {
      *carryout = ((unsigned long)lrint(x) & 0x01)?true:false;
    }
  }
  
  if(out != NULL)
  {
    if(direction) // Left
    {
      *out = (((unsigned long)lrint(x) << 1) | (carry & 0x01));
    }
    else // Right
    {
      *out = (((unsigned long)lrint(x) >> 1) | ((unsigned long)carry << 31));
    }
  }  
}

unsigned char LogicalShift(unsigned char x, signed short numbits)
{
  if(numbits > 0)
  {
    return (x <<  numbits);
  }
  else if(numbits < 0)
  {
    return (x >> (-numbits));
  }
  else
  {
    return x;
  }
}

signed char LogicalShift(signed char x, signed short numbits)
{
  if(numbits > 0)
  {
    return (x <<  numbits);
  }
  else if(numbits < 0)
  {
    return (x >> (-numbits));
  }
  else
  {
    return x;
  }
}

unsigned short LogicalShift(unsigned short x, signed short numbits)
{
  if(numbits > 0)
  {
    return (x <<  numbits);
  }
  else if(numbits < 0)
  {
    return (x >> (-numbits));
  }
  else
  {
    return x;
  }
}

signed short LogicalShift(signed short x, signed short numbits)
{
  if(numbits > 0)
  {
    return (x <<  numbits);
  }
  else if(numbits < 0)
  {
    return (x >> (-numbits));
  }
  else
  {
    return x;
  }
}

unsigned long LogicalShift(unsigned long x, signed short numbits)
{
  if(numbits > 0)
  {
    return (x <<  numbits);
  }
  else if(numbits < 0)
  {
    return (x >> (-numbits));
  }
  else
  {
    return x;
  }
}

signed long LogicalShift(signed long x, signed short numbits)
{
  if(numbits > 0)
  {
    return (x <<  numbits);
  }
  else if(numbits < 0)
  {
    return (x >> (-numbits));
  }
  else
  {
    return x;
  }
}

unsigned long long LogicalShift(unsigned long long x, signed short numbits)
{
  if(numbits > 0)
  {
    return (x <<  numbits);
  }
  else if(numbits < 0)
  {
    return (x >> (-numbits));
  }
  else
  {
    return x;
  }
}

signed long long LogicalShift(signed long long x, signed short numbits)
{
  if(numbits > 0)
  {
    return (x <<  numbits);
  }
  else if(numbits < 0)
  {
    return (x >> (-numbits));
  }
  else
  {
    return x;
  }
}

unsigned long LogicalShift(double x, signed short numbits)
{

  if(numbits > 0)
  {
    return (((unsigned long)lrint(x)) <<  numbits);
  }
  else if(numbits < 0)
  {
    return (((unsigned long)lrint(x)) >> (-numbits));
  }
  else
  {
    return ((unsigned long)lrint(x));
  }
}

unsigned long LogicalShift(float x, signed short numbits)
{
  if(numbits > 0)
  {
    return (((unsigned long)lrint(x)) <<  numbits);
  }
  else if(numbits < 0)
  {
    return (((unsigned long)lrint(x)) >> (-numbits));
  }
  else
  {
    return ((unsigned long)lrint(x));
  }
}

void JoinNumbers(unsigned long long * out, unsigned long high, unsigned long low)
{
  if(out != NULL)
  {
    *out = ((unsigned long long)high << 32) | (unsigned long long)low;
  }
}

void JoinNumbers(unsigned long * out, unsigned short high, unsigned short low)
{
  if(out != NULL)
  {
    *out = ((unsigned long)high << 16) | (unsigned long)low;
  }
}

void JoinNumbers(unsigned short * out, unsigned char high, unsigned char low)
{
  if(out != NULL)
  {
    *out = ((unsigned short)high << 8) | (unsigned short)low;
  }
}

void SplitNumbers(unsigned long long in, unsigned long * high, unsigned long * low)
{
  if(high != NULL)
  {
    *high = (unsigned long)((in & 0xFFFFFFFF00000000) >> 32);
  }
  
  if(low != NULL)
  {
    *low = (unsigned long)(in & 0x000000000000FFFF);
  }
}
void SplitNumbers(long long in, unsigned long * high, unsigned long * low)
{
  if(high != NULL)
  {
    *high = (unsigned short)((in & 0xFFFFFFFF00000000) >> 32);
  }
  
  if(low != NULL)
  {
    *low = (unsigned short)(in & 0x000000000000FFFF);
  }
}
void SplitNumbers(unsigned long in, unsigned short * high, unsigned short * low)
{
  if(high != NULL)
  {
    *high = (unsigned short)((in & 0xFFFF0000) >> 16);
  }
  
  if(low != NULL)
  {
    *low = (unsigned short)(in & 0x0000FFFF);
  }
}
void SplitNumbers(long in, unsigned short * high, unsigned short * low)
{
  if(high != NULL)
  {
    *high = (unsigned short)((in & 0xFFFF0000) >> 16);
  }
  
  if(low != NULL)
  {
    *low = (unsigned short)(in & 0x0000FFFF);
  }
}
void SplitNumbers(unsigned short in, unsigned char * high, unsigned char * low)
{
  if(high != NULL)
  {
    *high = (unsigned char)((in & 0xFF00) >> 8);
  }
  
  if(low != NULL)
  {
    *low = (unsigned char)(in & 0x00FF);
  }
}
void SplitNumbers(signed short in, unsigned char * high, unsigned char * low)
{
  if(high != NULL)
  {
    *high = (unsigned char)((in & 0xFF00) >> 8);
  }
  
  if(low != NULL)
  {
    *low = (unsigned char)(in & 0x00FF);
  }
}

void SplitNumbers(unsigned char in, unsigned char * high, unsigned char * low)
{
  if(high != NULL)
  {
    *high = 0;
  }
  
  if(low != NULL)
  {
    *low = in;
  }
}
void SplitNumbers(signed char in, unsigned char * high, unsigned char * low)
{
  if(high != NULL)
  {
    *high = 0;
  }
  
  if(low != NULL)
  {
    *low = (unsigned char)in;
  }
}

unsigned char swapBytes(unsigned char x)
{
  return x;
}
signed char swapBytes(signed char x)
{
  return x;
}
unsigned short swapBytes(unsigned short x)
{
  return ( ((x&0x00FF) << 8) | ((x&0xFF00) >> 8) );
}
signed short swapBytes(signed short x)
{
  return ( ((x&0x00FF) << 8) | ((x&0xFF00) >> 8) );
}
unsigned long swapBytes(unsigned long x)
{
  return ( ((x&0x00FF0000) << 8) | ((x&0xFF000000) >> 8) | ((x&0x000000FF) << 8) | ((x&0x0000FF00) >> 8) );
}
signed long swapBytes(signed long x)
{
  return ( ((x&0x00FF0000) << 8) | ((x&0xFF000000) >> 8) | ((x&0x000000FF) << 8) | ((x&0x0000FF00) >> 8) );
}
unsigned long long swapBytes(unsigned long long x)
{
  return ( ((x&0x00FF0000) << 8) | ((x&0xFF000000) >> 8) | ((x&0x000000FF) << 8) | ((x&0x0000FF00) >> 8) );
}
signed long long swapBytes(signed long long x)
{
  return ( ((x&0x00FF0000) << 8) | ((x&0xFF000000) >> 8) | ((x&0x000000FF) << 8) | ((x&0x0000FF00) >> 8) );
}
float swapBytes(float x)
{
  return x;
}
double swapBytes(double x)
{
  return x;
}

unsigned char swapWords(unsigned char x)
{
  return x;
}
signed char swapWords(signed char x)
{
  return x;
}
unsigned short swapWords(unsigned short x)
{
  return x;
}
signed short swapWords(signed short x)
{
  return x;
}
unsigned long swapWords(unsigned long x)
{
  return ( ((x&0x0000FFFF) << 16) | ((x&0xFFFF0000) >> 16) );
}
signed long swapWords(signed long x)
{
  return ( ((x&0x0000FFFF) << 16) | ((x&0xFFFF0000) >> 16) );
}
unsigned long long swapWords(unsigned long long x)
{
  return ( ((x&0x0000FFFF) << 16) | ((x&0xFFFF0000) >> 16) );
}
signed long long swapWords(signed long long x)
{
  return ( ((x&0x0000FFFF) << 16) | ((x&0xFFFF0000) >> 16) );
}
float swapWords(float x)
{
  return x;
}
double swapWords(double x)
{
  return x;
}

void inRangeCoerce(double x, double lower, double upper, boolean agg, boolean inclower, boolean incupper, double * coerced, boolean * inrange)
{
  boolean tempinrange = false;
  double tempcoerced;
  double temp;
  
  // first check if lower limit is larger than upper
  if(lower > upper)
  {
    // in range is always false, but switch lower and upper
	temp = lower;
	lower = upper;
	upper = temp;
  }
  else
  {
    // check if in range only if lower limit is less than upper
    tempinrange = (inclower)?(x>=lower):(x>lower);
    tempinrange &= (incupper)?(x<=upper):(x<upper);
  }

  // do coercion if in Compare Elements
  if(!agg)
  {
    tempcoerced = (x > upper)?upper:x;
    tempcoerced = (tempcoerced < lower)?lower:tempcoerced; 
  }
  else
  {
    // if in Aggregates mode just return the input
    tempcoerced = x;
  }
    
  if(coerced != NULL)
  {
    *coerced = tempcoerced;
  }
  if(inrange != NULL)
  {
    *inrange = tempinrange;
  }
}

void inRangeCoerce(String x, String lower, String upper, boolean agg, boolean inclower, boolean incupper, String * coerced, boolean * inrange)
{
  boolean tempinrange = false;
  String tempcoerced;
  String temp;
  
  // first check if lower limit is larger than upper
  if(lower > upper)
  {
    // in range is always false, but switch lower and upper
	temp = lower;
	lower = upper;
	upper = temp;
  }
  else
  {
    // check if in range only if lower limit is less than upper
    tempinrange = (inclower)?(x>=lower):(x>lower);
    tempinrange &= (incupper)?(x<=upper):(x<upper);
  }

  // do coercion if in Compare Elements
  if(!agg)
  {
    tempcoerced = (x > upper)?upper:x;
    tempcoerced = (tempcoerced < lower)?lower:tempcoerced; 
  }
  else
  {
    // if in Aggregates mode just return the input
    tempcoerced = x;
  }
    
  if(coerced != NULL)
  {
    *coerced = tempcoerced;
  }
  if(inrange != NULL)
  {
    *inrange = tempinrange;
  }
}

#ifdef __AVR__
int freeRam(void) 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
#endif

#ifdef __AVR__
void DigitalWritePort(unsigned char startpin, unsigned char val)
{
  volatile uint8_t *out;
  unsigned char reg;
  uint8_t port = digitalPinToPort(startpin);

  if (port == NOT_A_PIN) return;

  out = portOutputRegister(port);
  reg = *out; // start with current port value
  
  for(unsigned char i=0; i<8; i++)
  {
	if((1<<i) < digitalPinToBitMask(startpin))
    {
      // this pin is before the start pin specified
      // maintain current value
    }
    else
    {
      // start pin has been met, update values
      if(val & (1<<i))
      {
        reg |= (1<<i);
      }
      else
      {
        reg &= ~(1<<i);     
      }      
    }
  }
  out = portOutputRegister(port);
  *out = reg;   
}

unsigned char DigitalReadPort(unsigned char startpin)
{
  volatile uint8_t *out;
  unsigned char reg;
  uint8_t port = digitalPinToPort(startpin);

  if (port == NOT_A_PIN) return 0;
  return *portInputRegister(port);
} 
#endif

#endif