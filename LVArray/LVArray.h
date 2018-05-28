// ---------------------------------------------------------------------------
//  Created by Steffan Benamou, Aledyne Engineering Inc. on 10/24/2014.
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

// @file LVArray.h
// This file implements support for the Arduino Compatible Compiler for
// LabVIEW.  It contains 1-D Array classes for numeric and string datatypes.
// ---------------------------------------------------------------------------
#ifndef LVArray_h
#define LVArray_h

#include "Stream.h"
#include <math.h>
#include "A4Lhelper.h"

 enum MathOp
{
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  OR,
  AND,
  XOR
};
 
// Minimal class to replace std::vector

template<typename Data>
class LVOneDimArray
{
  int data_size; // Stores no. of actually stored objects
  int data_capacity; // Stores allocated capacity
  Data * data_ptr; // Stores data
	
  public:
    LVOneDimArray() : data_size(0), data_capacity(0), data_ptr(0) {}; // Default constructor
    LVOneDimArray(int num_elements, Data val)
    {
        data_size = num_elements;
        data_capacity = data_size*sizeof(Data);
        data_ptr = (Data *)malloc(data_capacity);
        if(data_ptr)
        {
          for(int i=0; i < data_size; i++)
          {
            data_ptr[i] = val;
          }
        }
    }; // Initialization constructor	
	
    LVOneDimArray(LVOneDimArray const &other) : data_size(other.data_size), data_capacity(other.data_capacity), data_ptr(0)
    {
	 // hasData = true;
      data_ptr = (Data *)malloc(data_capacity);
      if(data_ptr)
      {
        memcpy(data_ptr, other.data_ptr, data_size*sizeof(Data));
      }
    }; // Copy constuctor
		
    ~LVOneDimArray()
    {
        if(data_ptr)
        {
          free(data_ptr);
          data_ptr = NULL;
        }
    }; // Destructor
	
	void reinit(int num_elements, Data val)
	{
	  if(data_size != num_elements)
      {
        // new size is not same as old, reallocate
	    if(data_ptr)
	    {
	      free(data_ptr);
          data_ptr = NULL;
        }
	    data_size = num_elements;
        data_capacity = data_size*sizeof(Data);
        data_ptr = (Data *)malloc(data_capacity);
      }
	  
      // update values
      if(data_ptr)
      {	  
        for(int i=0; i < data_size; i++)
        {
          data_ptr[i] = val;
        }
      }
	}
	
	void reinit(int num_elements)
	{
	  if(data_size == num_elements)
      {
        // new size is equivalent to old, just return
        return;
      }
	  
	  if(data_ptr)
	  {
	    free(data_ptr);
        data_ptr = NULL;
      }
	  data_size = num_elements;
      data_capacity = data_size*sizeof(Data);
      data_ptr = (Data *)malloc(data_capacity);
	}
	
	void freeArray(void)
	{
	  if(data_ptr)
	  {
	    free(data_ptr);
        data_ptr = NULL;
      }
	}
	
    LVOneDimArray &operator=(LVOneDimArray const &other)
    {
	  // all equates are handled as a simple pointer reference to the other class
	  // to eliminate excessive memory copies
	  // If the destination has data, it must be freed first before setting the pointer
	  if(this != &other)
	  { 
	    if(data_ptr)
	    {
	      free(data_ptr);
          data_ptr = NULL;
        }
        data_size = other.data_size;
		data_capacity = data_size * sizeof(Data);
        data_ptr = (Data *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, other.data_ptr, data_capacity);
        }
	  }
	  
      return *this;
    };

    void copy(LVOneDimArray<unsigned char> const &rhs)
    {
      copyArray(rhs);
    };
    void copy(LVOneDimArray<signed char> const &rhs)
    {
      copyArray(rhs);
    };
    void copy(LVOneDimArray<unsigned short> const &rhs)
    {
      copyArray(rhs);
    };
    void copy(LVOneDimArray<signed short> const &rhs)
    {
      copyArray(rhs);
    };	
    void copy(LVOneDimArray<unsigned long> const &rhs)
    {
      copyArray(rhs);
    };
    void copy(LVOneDimArray<signed long> const &rhs)
    {
      copyArray(rhs);
    };
    void copy(LVOneDimArray<unsigned long long> const &rhs)
    {
      copyArray(rhs);
    };	
    void copy(LVOneDimArray<signed long long> const &rhs)
    {
      copyArray(rhs);
    };	
    void copy(LVOneDimArray<float> const &rhs)
    {
      copyArray(rhs);
    };
    void copy(LVOneDimArray<double> const &rhs)
    {
      copyArray(rhs);
    };
    void copy(LVOneDimArray<bool> const &rhs)
    {
      copyArray(rhs);
    };
	
    void copy(Data const rhs)
    {
	  reinit(1);
      if(data_ptr == NULL)
      {
        return;
      }
      data_ptr[0]=(Data)rhs;
    };
	
    LVOneDimArray &operator!(void)
    {
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i]=!data_ptr[i];
      }	
	  
      return *this;
    };

    LVOneDimArray &operator~(void)
    {
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i]=~data_ptr[i];
      }	
	  
      return *this;
    };
	
    LVOneDimArray &operator-(void)
    {
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i]=-data_ptr[i];
      }	

      return *this;
    };	
	
   // Add Arrays //
   
    template <typename Type>
    LVOneDimArray &operator+(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      if(data_size != smallest)
      {
        resizeArr(smallest);
      }

      for(int i=0; i<smallest; i++)
      {
        data_ptr[i]+=(Data)other[i];
      }	

      return *this;
    };

    // Substract Arrays //
    template <typename Type>
    LVOneDimArray &operator-(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      if(data_size != smallest)
      {
        resizeArr(smallest);
      }

      for(int i=0; i<smallest; i++)
      {
        data_ptr[i]-=(Data)other[i];
      }	

      return *this;
    };
 
    // Multiply Arrays //
    template <typename Type>
    LVOneDimArray &operator*(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      if(data_size != smallest)
      {
        resizeArr(smallest);
      }

      for(int i=0; i<smallest; i++)
      {
        data_ptr[i]*=(Data)other[i];
      }	

      return *this;
    };
	
    // Divide Arrays //
    template <typename Type>
    LVOneDimArray &operator/(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      if(data_size != smallest)
      {
        resizeArr(smallest);
      }

      for(int i=0; i<smallest; i++)
      {
        data_ptr[i]/=(Data)other[i];
      }	

      return *this;
    };
	
    // Or Arrays //
    template <typename Type>
    LVOneDimArray &operator|(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      if(data_size != smallest)
      {
        resizeArr(smallest);
      }

      for(int i=0; i<smallest; i++)
      {
        data_ptr[i]|=(Data)other[i];
      }	

      return *this;
    };
 
    // And Arrays //
    template <typename Type>
    LVOneDimArray &operator&(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      if(data_size != smallest)
      {
        resizeArr(smallest);
      }

      for(int i=0; i<smallest; i++)
      {
        data_ptr[i]&=(Data)other[i];
      }	

      return *this;
    };
	
    // XOR Arrays //
    template <typename Type>
    LVOneDimArray &operator^(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      if(data_size != smallest)
      {
        resizeArr(smallest);
      }

      for(int i=0; i<smallest; i++)
      {
        data_ptr[i]^=(Data)other[i];
      }	

      return *this;
    };
	

    LVOneDimArray &operator+(Data element)
    {
        for(int i=0; i<data_size; i++)
		{
		  data_ptr[i]+=element;
		}
  
      return *this;
    };
	
    LVOneDimArray &operator-(Data element)
    {
        for(int i=0; i<data_size; i++)
		{
		  data_ptr[i]-=element;
		}
  
      return *this;
    };

    LVOneDimArray &operator*(Data element)
    {
        for(int i=0; i<data_size; i++)
		{
		  data_ptr[i]*=element;
		}
  
      return *this;
    };

    LVOneDimArray &operator/(Data element)
    {
        for(int i=0; i<data_size; i++)
		{
		  data_ptr[i]/=element;
		}
  
      return *this;
    };

    LVOneDimArray &operator|(Data element)
    {
        for(int i=0; i<data_size; i++)
		{
		  data_ptr[i]|=element;
		}
  
      return *this;
    };
	
    LVOneDimArray &operator&(Data element)
    {
        for(int i=0; i<data_size; i++)
		{
		  data_ptr[i]&=element;
		}
  
      return *this;
    };

    LVOneDimArray &operator^(Data element)
    {
        for(int i=0; i<data_size; i++)
		{
		  data_ptr[i]^=element;
		}
  
      return *this;
    };

     // Compare Aggregates > //
	 
    template <typename Type>	 
    bool operator>(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(data_ptr[i]>other[i])
        {
          return true;
        }
        else if(data_ptr[i]==other[i])
        {
          // elements same, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size>other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };

    // Compare Aggregates >= //
    template <typename Type>
    bool operator>=(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(data_ptr[i]>other[i])
        {
          return true;
        }
        else if(data_ptr[i]==other[i])
        {
          // elements same, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size>=other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };

    // Compare Aggregates < //
    template <typename Type>
    bool operator<(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(data_ptr[i]<other[i])
        {
          return true;
        }
        else if(data_ptr[i]==other[i])
        {
          // elements same, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size<other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };
 
    // Compare Aggregates <= //
    template <typename Type>
    bool operator<=(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(data_ptr[i]<other[i])
        {
          return true;
        }
        else if(data_ptr[i]==other[i])
        {
          // elements same, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size<=other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };

    // Compare Aggregates == //
    template <typename Type>
    bool operator==(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(data_ptr[i]==other[i])
        {
          // elements check out, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size==other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };
 
    // Compare Aggregates != //
    template <typename Type>
    bool operator!=(LVOneDimArray<Type> const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(data_ptr[i]==other[i])
        {
          // elements check out, go on to the next
        }
        else
        {
          return true;
        }
      }	

      if(data_size!=other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };
	
    Data * resizeArr(int newsize)
    {
	    Data * newdata;
		
		if(newsize == data_size)
        {
          return data_ptr;
        }
		
        newdata = (Data *)malloc(newsize*sizeof(Data));
        if(newdata)
        {
		  if(data_size < newsize)
		  {
		    // expanding array, copy over all of old data
            if((data_size > 0) && (data_ptr != NULL))
            {
              memcpy(newdata, data_ptr, data_size * sizeof(Data));
            }
          }
		  else
		  {
		    // shrinking array, only copy up to newsize
            if((data_size > 0) && (data_ptr != NULL))
            {
		      memcpy(newdata, data_ptr, newsize * sizeof(Data));
            }
		  }
		  
          if(data_ptr)
          {
		    free(data_ptr);
          }
		  data_ptr = newdata;	
          data_size = newsize;
		  data_capacity =  data_size*sizeof(Data);
		  return data_ptr;
		}
		else
        {
          return NULL;
		}
    };

    void removeLast(void)
    {
	  // remove the last element
	  data_size--;
	  data_capacity = data_size*sizeof(Data);  
    }
	
    void toString(String * strIn)
    {
        if(strIn != NULL)
        {
		  *strIn = "";
          for(int i=0; i<data_size; i++)
		  {	  
            *strIn += '\0';
		    strIn->setCharAt(i,data_ptr[i]);
		  }
        }
    }	
	
    void push_back(Data const &x)
    {
	  Data * ptemp;
     // if (data_capacity == data_size)
    //  {
    //    // when capacity is reach, space is doubled
    //    resize();
    //  }
      ptemp = (Data *)realloc(ptemp, data_capacity);
	  
	  if(ptemp)
	  {
	    data_ptr = ptemp;
		data_size++;
		data_capacity = data_size*sizeof(Data);
        data_ptr[data_size] = x;
	  }
	  
    }; // Adds new value. If needed, allocates more space
		
    long size() const
    {
      return data_size;
    }; // Size getter
	
    Data * ptr()
    {
      return data_ptr;
    };
	
    Data const &operator[](long idx) const
    {
        return data_ptr[idx];
    }; // Const getter	
	
    Data &operator[](long idx)
    {
      return data_ptr[idx];
    }; // Changeable getter

    long search(Data element, long start)
    {
      for(long i=start; i<data_size; i++)
      {
        if(data_ptr[i] == element)
        {
          return i; 
        }
      }	
      return -1;
    };
	
    Data getdata(long idx)
    {
	  if((idx >= 0) && (idx < data_size))
	  {
        return data_ptr[idx];
	  }
	  else
	  {
	    return 0;
	  }
    };
	
    Data getdata(long idx) const
    {
	  if((idx >= 0) && (idx < data_size))
	  {
        return data_ptr[idx];
	  }
	  else
	  {
	    return 0;
	  }
    };
	
    void setdata(long idx, Data newdata)
    {
	  // automatically resizes an array if necessary
	  // to fit the data at the requested index
	  if(idx >= data_size)
	  {
	    // automatically resize array to fit
		// a new element at the requested index
	    if(resizeArr(idx+1) && data_ptr)
        {
          data_ptr[idx] = newdata;
        }	
	  }
      else
      {
	    if(data_ptr)
        {
          data_ptr[idx] = newdata;
        }		
      }
    };
	
    void getmaxandmin(Data * maxvalue, long * maxidx, Data * minvalue, long * minidx)
    {
      Data maxval = data_ptr[0];
      Data minval = data_ptr[0];		
      long idxmax = 0;
      long idxmin = 0;

      for(long i=0; i<data_size; i++)
      {
        if(data_ptr[i] > maxval)
        {
          idxmax = i;	
          maxval = data_ptr[i];
        }
		  
        if(data_ptr[i] < minval)
        {
          idxmin = i;	
          minval = data_ptr[i];
        }
      }

      if(maxvalue != NULL)
      {
        *maxvalue = maxval;
      }
      if(maxidx != NULL)
      {
        *maxidx = idxmax;
      }		
      if(minvalue != NULL)
      {
        *minvalue = minval;
      }		
      if(minidx != NULL)
      {
        *minidx = idxmin;
      }		
    };
	
    void sort()
    {
      int c, d;
      Data swap;

      if(data_ptr == NULL)
      {
        return;
      }
	  
      for (c = 0 ; c < ( data_size - 1 ); c++)
      {
        for (d = 0 ; d < (data_size - c - 1); d++)
        {
          if (data_ptr[d] > data_ptr[d+1]) // ascending order
          {
            swap       	   = data_ptr[d];
            data_ptr[d]    = data_ptr[d+1];
            data_ptr[d+1]  = swap;
          }
        }
      }
    };
	
    void reverse()
    {
      Data temp;
	  
      if(data_ptr == NULL)
      {
        return;
      }
	  
      for (int i = 0; i < data_size/2; ++i)
      {
        temp = data_ptr[i];
        data_ptr[i] = data_ptr[data_size-i-1];
        data_ptr[data_size-i-1] = temp;
      }	
    };
	
    void rotate(long n)
    {
      int i, j;
      Data temp;
		
      if(data_ptr == NULL)
      {
        return;
      }

      // rotate to the left n times
      if(n < 0)
      {
        n = -n; // make n positive
        for (j = 0; j < n; j++)
        {
          temp = data_ptr[0];
          for (i = 0; i < (data_size-1); i++)
          {
            data_ptr[i] = data_ptr[i+1];
          }
          data_ptr[i] = temp;	
        }
      }
      else
      {
        // rotate to the right n times
        for (j = 0; j < n; j++)
        {
          temp = data_ptr[data_size-1];
          for (i = (data_size-1); i > 0; i--)
          {
            data_ptr[i] = data_ptr[i-1];
          }
          data_ptr[0] = temp;	
        }
      }		
    };
    
    void replace_subset(int index, unsigned char element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };
     void replace_subset(int index, signed char element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };   
    void replace_subset(int index, unsigned short element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };	
	void replace_subset(int index, signed short element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };
    void replace_subset(int index, unsigned long element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };	
    void replace_subset(int index, signed long element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };	
    void replace_subset(int index, unsigned long long element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };	
    void replace_subset(int index, signed long long element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };
    void replace_subset(int index, float element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // Need to do bankers rounding here if the current array
	  // type is not a float or double.  The more specific
	  // case of both floats is handled below
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)lrint(element);
	  }
    };		
    void replace_subset(int index, double element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // Need to do bankers rounding here if the current array
	  // type is not a float or double.  The more specific
	  // case of both floats is handled below
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)lrint(element);
	  }
    };
    void replace_subset(int index, bool element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (Data)element;
	  }
    };   
	
    void replace_subset(int index, LVOneDimArray<unsigned char> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };
    void replace_subset(int index, LVOneDimArray<signed char> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };	
    void replace_subset(int index, LVOneDimArray<unsigned short> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };	
    void replace_subset(int index, LVOneDimArray<signed short> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };
    void replace_subset(int index, LVOneDimArray<unsigned long> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };
    void replace_subset(int index, LVOneDimArray<signed long> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };
    void replace_subset(int index, LVOneDimArray<unsigned long long> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };
    void replace_subset(int index, LVOneDimArray<signed long long> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };
    void replace_subset(int index, LVOneDimArray<float> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // Need to do bankers rounding here if the current array
	  // type is not a float or double.  The more specific
	  // case of both floats is handled below
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)lrint(other[i]);
        }
      }
    };
    void replace_subset(int index, LVOneDimArray<double> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // Need to do bankers rounding here if the current array
	  // type is not a float or double.  The more specific
	  // case of both floats is handled below
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)lrint(other[i]);
        }
      }
    };
    void replace_subset(int index, LVOneDimArray<bool> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (Data)other[i];
        }
      }
    };
	
    template <typename Type>	
    void append(LVOneDimArray<Type> const &other)
    {
      // first make array size equal to current size
      // plus new size
	  if(resizeArr(data_size+other.size()))
      {
        for(int i=0; i<other.size(); i++)
        {
            data_ptr[data_size-other.size()+i] = (Data)other[i];
        }
      }
    };
	
    void append(Data element)
    {
	  if(resizeArr(data_size+1))
      {
	    data_ptr[data_size-1] = (Data)element;
        //push_back(element);
      }
    };
	
    bool orElements(void)
    {
	  bool temp = false;

      for(int i=0; i<data_size; i++)
      {
        temp |= data_ptr[i];
      }
	  
	  return temp;
    };
	
    bool andElements(void)
    {
	  bool temp = true;
	  
      for(int i=0; i<data_size; i++)
      {
        temp &= data_ptr[i];
      }
	  
      return temp;
    };

    Data addElements(void)
    {
	  Data temp = 0;
	  
      for(int i=0; i<data_size; i++)
      {
        temp += data_ptr[i];
      }
	  
      return temp;
    };	
	
    Data multiplyElements(void)
    {
	  Data temp = 1;
	  
      for(int i=0; i<data_size; i++)
      {
        temp *= data_ptr[i];
      }
	  
      return temp;
    };
	
    void roundElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = lrint(data_ptr[i]);
      }
    };
	
    void sqrtElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = sqrt(data_ptr[i]);
      }
    };
	
    void squareElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = pow(data_ptr[i], 2);
      }
    };
	
    void BooleanToNum(LVOneDimArray<boolean> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = (other[i]==true)?1:0;
      }
    };
	
    void absElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = abs(data_ptr[i]);
      }
    };
	
    void recipElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = 1/(double)data_ptr[i];
      }
    };
	
    void swapArrayBytes(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = swapBytes(data_ptr[i]);
      }
    };
	
    void swapArrayWords(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
       data_ptr[i] = swapWords(data_ptr[i]);
      }
    };
	
	// If output is an int array
    void scalePowTwoElements(signed short power)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = data_ptr[i] * lrint(pow(2, power));
      }
    };
	
	// If output is an int array	
    void scalePowTwoElementsRound(double power)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = data_ptr[i] * lrint(pow(2, lrint(power)));
      }
    };
	
    void sinElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = sin(data_ptr[i]);
      }
    };
	
    void asinElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = asin(data_ptr[i]);
      }
    };
	
    void cosElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = cos(data_ptr[i]);
      }
    };
	
    void acosElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = acos(data_ptr[i]);
      }
    };
	
    void tanElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = tan(data_ptr[i]);
      }
    };
	
    void atanElements(void)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = atan(data_ptr[i]);
      }
    };
	
  private:

    template <typename Type>
    void copyArray(LVOneDimArray<Type> const &rhs)
    {
	  reinit(rhs.size());
      if(data_ptr == NULL)
      {
        return;
      }  
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i]=(Data)rhs[i];
      }	
	}
};

    // MORE SPECIFIC OVERLOADS
    template <> void LVOneDimArray<unsigned char>::copy(LVOneDimArray<unsigned char> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(unsigned char);
        data_ptr = (unsigned char *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<signed char>::copy(LVOneDimArray<signed char> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(signed char);
        data_ptr = (signed char *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<unsigned short>::copy(LVOneDimArray<unsigned short> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(unsigned short);
        data_ptr = (unsigned short *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<signed short>::copy(LVOneDimArray<signed short> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(signed short);
        data_ptr = (signed short *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<unsigned long>::copy(LVOneDimArray<unsigned long> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(unsigned long);
        data_ptr = (unsigned long *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<signed long>::copy(LVOneDimArray<signed long> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(signed long);
        data_ptr = (signed long *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<unsigned long long>::copy(LVOneDimArray<unsigned long long> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(unsigned long long);
        data_ptr = (unsigned long long *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<signed long long>::copy(LVOneDimArray<signed long long> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(signed long long);
        data_ptr = (signed long long *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<float>::copy(LVOneDimArray<float> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(float);
        data_ptr = (float *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<double>::copy(LVOneDimArray<double> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(double);
        data_ptr = (double *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
    template <> void LVOneDimArray<bool>::copy(LVOneDimArray<bool> const &rhs)
    {
	  if(this != &rhs)
	  {
        if(data_ptr)
        {
		  free(data_ptr);
        }
        data_size = rhs.data_size;
		data_capacity = data_size * sizeof(bool);
        data_ptr = (bool *)malloc(data_capacity);
        if(data_ptr)
        {
          memcpy(data_ptr, rhs.data_ptr, data_capacity);
        }
	  }
    };
	
    template <> void LVOneDimArray<float>::replace_subset(int index, LVOneDimArray<float> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // No rounding necessary
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = other[i];
        }
      }
    };
    template <> void LVOneDimArray<float>::replace_subset(int index, LVOneDimArray<double> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // No rounding necessary
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (float)other[i];
        }
      }
    };
    template <> void LVOneDimArray<double>::replace_subset(int index, LVOneDimArray<float> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // No rounding necessary
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = (double)other[i];
        }
      }
    };
    template <> void LVOneDimArray<double>::replace_subset(int index, LVOneDimArray<double> const &other)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // No rounding necessary
      for(int i=0; i<other.size(); i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          data_ptr[index+i] = other[i];
        }
      }
    };
	
    template <> void LVOneDimArray<float>::replace_subset(int index, float element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // No rounding necessary	
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = element;
	  }
    };
    template <> void LVOneDimArray<float>::replace_subset(int index, double element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // No rounding necessary	
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (float)element;
	  }
    };
    template <> void LVOneDimArray<double>::replace_subset(int index, float element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // No rounding necessary
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = element;
	  }
    };
    template <> void LVOneDimArray<double>::replace_subset(int index, double element)
    {
      if(data_ptr == NULL)
      {
        return;
      }
	  // No rounding necessary
	  if((index >= 0) && (index < data_size))
	  {
        data_ptr[index] = (double)element;
	  }
    };

    template <> void LVOneDimArray<float>::scalePowTwoElements(signed short power)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = data_ptr[i] * (pow(2, power));
      }
    };
    template <> void LVOneDimArray<float>::scalePowTwoElementsRound(double power)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = data_ptr[i] * (pow(2, lrint(power)));
      }
    };	
    template <> void LVOneDimArray<double>::scalePowTwoElements(signed short power)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = data_ptr[i] * (pow(2, power));
      }
    };
    template <> void LVOneDimArray<double>::scalePowTwoElementsRound(double power)
    {
      if(data_ptr == NULL)
      {
        return;
      }
      for(int i=0; i<data_size; i++)
      {
        data_ptr[i] = data_ptr[i] * (pow(2, lrint(power)));
      }
    };
	
	
template<typename String>
class StringOneDimArray
{
  int data_size; // Stores no. of actually stored objects
  String ** dataStr;
  
  public:
    StringOneDimArray() : data_size(0), dataStr(NULL){}; // Default constructor
    StringOneDimArray(int num_elements, String val)
    {
        data_size = num_elements;
		dataStr = NULL;
		// allocate an array of pointers for each String element
		if(data_size > 0)
		{
          dataStr = new String * [num_elements];
          if(dataStr)
          {
		    // Then create a new string for each element
            for(int i=0; i < data_size; i++)
            {
		      dataStr[i] = new String("");
			  if(dataStr[i])
              {
                *(dataStr)[i] = val;
              }
            }
          }
		}
    }; // Initialization constructor	
	
    StringOneDimArray(StringOneDimArray const &other) : data_size(other.data_size)
    {
	  //hasData = true;
      //data_ptr = (Data *)malloc(data_capacity*sizeof(Data));
      //memcpy(data_ptr, other.data_ptr, data_size*sizeof(Data));
    }; // Copy constuctor
		
    ~StringOneDimArray()
    {
	  for(int i=0; i < data_size; i++)
      {
        if(dataStr[i])
        {
          delete(dataStr[i]);
		  dataStr[i] = NULL;
        }
	  }
	  
	  if(dataStr)
      {
        delete(dataStr);
		dataStr = NULL;
      }
    }; // Destructor
	
    void reinit(int num_elements, String val)
	{
	  if(dataStr)
      {
        delete(dataStr);
		dataStr = NULL;
      }
      data_size = num_elements;
	  
      // allocate an array of pointers for each String element
      if(data_size > 0)
      {
        dataStr = new String * [data_size];
        if(dataStr)
        {
          // Then create a new string for each element
          for(int i=0; i < data_size; i++)
          {
            dataStr[i] = new String("");
            if(dataStr[i])
            {
              *(dataStr)[i] = val;
            }
          }
        }
      }
	}
	
	void reinit(int num_elements)
	{
	  if(dataStr)
      {
        delete(dataStr);
        dataStr = NULL;
      }
      data_size = num_elements;
	  
      // allocate an array of pointers for each String element
      if(data_size > 0)
      {
        dataStr = new String * [data_size];
        if(dataStr)
        {
          // Then create a new string for each element
          for(int i=0; i < data_size; i++)
          {
            dataStr[i] = new String("");
          }
        }
      }
	}
	
    String ** resizeArr(int newsize)
    {
        String ** newdata;
		
		if(newsize == data_size)
        {
          return dataStr;
        }
		
        newdata = new String * [newsize];

        if(newdata)
        {
		  // first allocate a String for each new index
          for(int i=0; i < newsize; i++)
          {
		    newdata[i] = new String("");
          }
		
		  if(data_size < newsize)
		  {
		    // expanding array, copy over all of old data
            for(int i=0; i < data_size; i++)
            {
              if(newdata[i])
              {
                *(newdata)[i] = *(dataStr)[i];
              }
            }
          }
		  else
		  {
		    // shrinking array, only copy up to newsize
            for(int i=0; i < newsize; i++)
            {
              if(newdata[i])
              {
                *(newdata)[i] = *(dataStr)[i];
              }
            }			
		  }
		  
		  if(data_size > 0)
		  {
		    // cleanup the old array by first deleting each string
	        for(int i=0; i < data_size; i++)
            {
              delete(dataStr[i]);
              dataStr[i] = NULL;
	        }
		    // then delete the array
            if(dataStr)
            {
	          delete(dataStr); 
              dataStr = NULL;
            }
          }
		  
		  dataStr = newdata;	
          data_size = newsize;
		  return dataStr;
		}
		else
        {
          return NULL;
		}
    };	 	
		
    StringOneDimArray &operator=(StringOneDimArray const &other)
    {
	  if(this != &other)
	  {
        if(data_size > 0)
		{
	      for(int i=0; i < data_size; i++)
          {
            delete(dataStr[i]);
            dataStr[i] = NULL;
	      }
        }
		
		if(dataStr)
        {
	      delete(dataStr);
          dataStr = NULL;
        }
		
        data_size = other.data_size;
 
		// allocate an array of pointers for each String element
        dataStr = new String * [data_size];
        if(dataStr)
        {
		  // Then create a new string for each element
          for(int i=0; i < data_size; i++)
          {
		    dataStr[i] = new String("");
            if(dataStr[i])
            {
              *(dataStr)[i] = *other.dataStr[i];
            }
          }
        }
	  }
      return *this;
    };
	
    StringOneDimArray &copy(StringOneDimArray const &other)
    {
	  if(this != &other)
	  {
        if(data_size != other.data_size)
        {
          // only destroy and recreate memory if new size is not the same
          if(data_size > 0)
		  {
	        for(int i=0; i < data_size; i++)
            {
              delete(dataStr[i]);
              dataStr[i] = NULL;
	        }
          }
        
		  if(dataStr)
          {
	        delete(dataStr);
            dataStr = NULL;
          }
  
          data_size = other.data_size;
 
		  // allocate an array of pointers for each String element
          dataStr = new String * [data_size];
        }
		
		// Then create a new string for each element
		if(dataStr)
        {
          for(int i=0; i < data_size; i++)
          {
		    dataStr[i] = new String("");
		    if(dataStr[i])
            {
              *(dataStr)[i] = *other.dataStr[i];
            }
          }
        }
	  }
      return *this;
    };
	
    void copy(String element)
    {
	  reinit(1);
      if(dataStr == NULL)
      {
        return;
      }
      *(dataStr)[0]=element;
	  
    };	
	
    String const &operator[](long idx) const
    {
	  if((idx >= 0) && (idx < data_size))
	  {
        return *(dataStr)[idx];
	  }
	  else
	  {
	    return String();
	  }
    }; // Const getter	
	
    String &operator[](long idx)
    {
      return *(dataStr)[idx];
    }; // Changeable getter
	
    String getdata(long idx)
    {
	  if((idx >= 0) && (idx < data_size))
	  {
        return *(dataStr)[idx];
	  }
	  else
	  {
	    return "";
	  }
    };
	
    void setdata(long idx, String newdata)
    {
	  // dont check for NULL here in case the string
	  // hasn't been initialized.  It will get resized here
	  
      //if(dataStr == NULL)
      //{
      //  return;
      //}
	  
	  // automatically resizes an array if necessary
	  // to fit the data at the requested index
	  if(idx >= data_size)
	  {
	    // automatically resize array to fit
		// a new element at the requested index
	    if(resizeArr(idx+1))
        {	
          *(dataStr)[idx] = newdata;
        }	
	  }
      else
      {
        *(dataStr)[idx] = newdata;	  
      }
    };	
	
    long search(String element, long start)
    {
      if(dataStr == NULL)
      {
        return -1;
      }
	  
      for(long i=start; i<data_size; i++)
      {
        if(*(dataStr)[i] == element)
        {
          return i; 
        }
      }	
      return -1;
    };
	
    void sort()
    {
      int c, d;
      String swap;
	  
      if(dataStr == NULL)
      {
        return;
      }

      for (c = 0 ; c < ( data_size - 1 ); c++)
      {
        for (d = 0 ; d < (data_size - c - 1); d++)
        {
          if (*(dataStr)[d] > *(dataStr)[d+1]) // ascending order
          {
            swap       	   = *(dataStr)[d];
            *(dataStr)[d]    = *(dataStr)[d+1];
            *(dataStr)[d+1]  = swap;
          }
        }
      }
    };

    void reverse()
    {
      String temp;
	  
      if(dataStr == NULL)
      {
        return;
      }
      for (int i = 0; i < data_size/2; ++i)
      {
        temp = *(dataStr)[i];
        *(dataStr)[i] = *(dataStr)[data_size-i-1];
        *(dataStr)[data_size-i-1] = temp;
      }	
    };	
	
    void reverseString()
    {
      if(dataStr == NULL)
      {
        return;
      }
	  
      for(int i=0; i<data_size; i++)
      {
        ReverseString(dataStr[i], *(dataStr)[i]);
      }
    }
	
    void getmaxandmin(String * maxvalue, long * maxidx, String * minvalue, long * minidx)
    {
      String maxval = *(dataStr)[0];
      String minval = *(dataStr)[0];		
      long idxmax = 0;
      long idxmin = 0;

      if(dataStr == NULL)
      {
        return;
      }
	  
      for(long i=0; i<data_size; i++)
      {
        if(*(dataStr)[i] > maxval)
        {
          idxmax = i;	
          maxval = *(dataStr)[i];
        }
		  
        if(*(dataStr)[i] < minval)
        {
          idxmin = i;	
          minval = *(dataStr)[i];
        }
      }

      if(maxvalue != NULL)
      {
        *maxvalue = maxval;
      }
      if(maxidx != NULL)
      {
        *maxidx = idxmax;
      }		
      if(minvalue != NULL)
      {
        *minvalue = minval;
      }		
      if(minidx != NULL)
      {
        *minidx = idxmin;
      }		
    };	
	
    void rotate(long n)
    {
      int i, j;
      String temp;
		
      if(dataStr == NULL)
      {
        return;
      }
	  
      // rotate to the left n times
      if(n < 0)
      {
        n = -n; // make n positive
        for (j = 0; j < n; j++)
        {
          temp = *(dataStr)[0];
          for (i = 0; i < (data_size-1); i++)
          {
            *(dataStr)[i] = *(dataStr)[i+1];
          }
          *(dataStr)[i] = temp;	
        }
      }
      else
      {
        // rotate to the right n times
        for (j = 0; j < n; j++)
        {
          temp = *(dataStr)[data_size-1];
          for (i = (data_size-1); i > 0; i--)
          {
            *(dataStr)[i] = *(dataStr)[i-1];
          }
          *(dataStr)[0] = temp;	
        }
      }		
    };
	
    void rotateString()
    {
      if(dataStr == NULL)
      {
        return;
      }
	  
      for(int i=0; i<data_size; i++)
      {
        RotateString(dataStr[i], *(dataStr)[i]);
      }
    }
    
    void replace_subset(int index, String element)
    {
      if(dataStr == NULL)
      {
        return;
      }
	  if((index >= 0) && (index < data_size))
	  {
        *(dataStr)[index] = element;
	  }
    };
    
    void replace_subset(int index, StringOneDimArray const &other)
    {
      if(dataStr == NULL)
      {
        return;
      }
      for(int i=0; i<other.data_size; i++)
      {
        if((index >= 0) && ((index+i) < data_size))
        {
          *(dataStr)[index+i] = other[i];
        }
      }
    };
	
    void append(StringOneDimArray const &other)
    {
      // first make array size equal to current size
      // plus new size
	  if(resizeArr(data_size+other.data_size))
      {
        for(int i=0; i<other.data_size; i++)
        {
            *(dataStr)[data_size-other.data_size+i] = other[i];
        }
      }
    };
	
    void append(String element)
    {
	  if(resizeArr(data_size+1))
      {
	    *(dataStr)[data_size-1] = element;
      }
    };	
	
	// Adding array with one element adds all internal elements
    // then adds the single element to the end
    String operator+(String element)
    {
      String temp = "";
	  
      for(int i=0; i<data_size; i++)
      {
        temp += *(dataStr)[i];
      }
      temp += element;
	  
	  return temp;
    };		

    String operator+(StringOneDimArray const &other)
    {
      String temp = "";
	  int i;
	  
      for(i=0; i<data_size; i++)
      {
        temp += *(dataStr)[i];
      }
	  
      for(i=0; i<other.data_size; i++)
      {
        temp += other[i];
      }	  
	  
	  return temp;
    };	
	
    String toSinString(void)
    {
      String temp = "";
	  int i;
	  
      for(int i=0; i<data_size; i++)
      {
        temp += *(dataStr)[i];
      }
	  
	  return temp;
    }
	
     // Compare Aggregates > //
    bool operator>(StringOneDimArray const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(*(dataStr)[i]>*(other.dataStr)[i])
        {
          return true;
        }
        else if(*(dataStr)[i]==*(other.dataStr)[i])
        {
          // elements same, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size>other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };	

     // Compare Aggregates >= //
    bool operator>=(StringOneDimArray const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(*(dataStr)[i]>*(other.dataStr)[i])
        {
          return true;
        }
        else if(*(dataStr)[i]==*(other.dataStr)[i])
        {
          // elements same, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size>=other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };		

     // Compare Aggregates < //
    bool operator<(StringOneDimArray const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(*(dataStr)[i]<*(other.dataStr)[i])
        {
          return true;
        }
        else if(*(dataStr)[i]==*(other.dataStr)[i])
        {
          // elements same, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size<other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };	
	
     // Compare Aggregates <= //
    bool operator<=(StringOneDimArray const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(*(dataStr)[i]<*(other.dataStr)[i])
        {
          return true;
        }
        else if(*(dataStr)[i]==*(other.dataStr)[i])
        {
          // elements same, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size<=other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };
	
    // Compare Aggregates == //
    bool operator==(StringOneDimArray const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(*(dataStr)[i]==*(other.dataStr)[i])
        {
          // elements check out, go on to the next
        }
        else
        {
          return false;
        }
      }	

      if(data_size==other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };	 
		 
    // Compare Aggregates != //	
    bool operator!=(StringOneDimArray const &other)
    {
      int smallest = (other.size() < data_size)?other.size():data_size;

      for(int i=0; i<smallest; i++)
      {
        if(*(dataStr)[i]==*(other.dataStr)[i])
        {
          // elements check out, go on to the next
        }
        else
        {
          return true;
        }
      }	

      if(data_size!=other.size())
      {
        return true;
      }
      else
      {
        return false;
      }
    };
	
    void toInt(LVOneDimArray<unsigned char> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toInt();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toInt();
          }
        }
      }
    };
    void toInt(LVOneDimArray<signed char> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toInt();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toInt();
          }
        }
      }
    };
    void toInt(LVOneDimArray<unsigned short> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toInt();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toInt();
          }
        }
      }
    };
    void toInt(LVOneDimArray<signed short> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
         for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toInt();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toInt();
          }
        }
      }
    };	
    void toInt(LVOneDimArray<unsigned long> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toInt();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toInt();
          }
        }
      }
    };
    void toInt(LVOneDimArray<signed long> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toInt();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toInt();
          }
        }
      }
    };	
    void toInt(LVOneDimArray<float> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toInt();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toInt();
          }
        }
      }
    };
    void toInt(LVOneDimArray<double> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toInt();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toInt();
          }
        }
      }
    };	
	
    void toFloat(LVOneDimArray<unsigned char> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toFloat();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toFloat();
          }
        }
      }
    };
    void toFloat(LVOneDimArray<signed char> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toFloat();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toFloat();
          }
        }
      }
    };
    void toFloat(LVOneDimArray<unsigned short> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toFloat();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toFloat();
          }
        }
      }
    };
    void toFloat(LVOneDimArray<signed short> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toFloat();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toFloat();
          }
        }
      }
    };	
    void toFloat(LVOneDimArray<unsigned long> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toFloat();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toFloat();
          }
        }
      }
    };
    void toFloat(LVOneDimArray<signed long> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toFloat();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toFloat();
          }
        }
      }
    };	
    void toFloat(LVOneDimArray<float> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toFloat();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toFloat();
          }
        }
      }
    };
    void toFloat(LVOneDimArray<double> &output, int offset)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          if(offset > 0)
          {
            String temp = (*(dataStr)[i]).substring(offset);
			output[i]=temp.toFloat();
          }
		  else
          {
            output[i]=(*(dataStr)[i]).toFloat();
          }
        }
      }
    };		
	
    void length(LVOneDimArray<signed long> &output)
    {
      if(output.resizeArr(data_size) != NULL)
      {
        for(int i=0; i<data_size; i++)
        {
          output[i]=(*(dataStr)[i]).length();
        }
      }		
    };		

    long size() const
    {
      return data_size;
    }; // Size getter	
};

#endif
