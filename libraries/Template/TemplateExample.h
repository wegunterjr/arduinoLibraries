// ---------------------------------------------------------------------------
// Created by Steffan Benamou, Aledyne Engineering Inc. on 6/24/2015.
// Copyright 2015 - Under creative commons license 3.0:
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
//
//
// @file TemplateExample.h
// This file shows a simple example of a C helper file for the Arduino
// Compatible Compiler for LabVIEW user addon capabilities.  This allows
// users to create their own LabVIEW based Arduino libraries.
// 
// ---------------------------------------------------------------------------
#ifndef TemplateExample_h
#define TemplateExample_h

#include "Stream.h"
#include "Arduino.h"
#include <math.h>
 
 int TemplateAdd(int x, int y)
 {
   return (x+y);
 }
 
  int TemplateSubtract(int x, int y)
 {
   return (x-y);
 }
 
#endif