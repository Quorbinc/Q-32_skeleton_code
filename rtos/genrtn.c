//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                            General Functions Processing Code
//                  -----------------------------------------------------
//
//    This code is for use on the STM32F446 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//         Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//---------------------------------------------------------------------------------------------
//                        Zero All of a Strings Member Bytes n Length
//---------------------------------------------------------------------------------------------
void  fnZeroString (u08 ubS[], u16 uwLen)
{
  u16 uwP;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  if ((uwLen <1) || (uwLen > 8)) return;        //--- Exit if bad length

  for (uwP = 0; uwP < uwLen; uwP++)
  {
    ubS[uwP] = 0;
  }
}

//---------------------------------------------------------------------------------------------
//                          Place a string within another string
//---------------------------------------------------------------------------------------------
u32   fnMergString (u08 ubDst[], u08 ubSrc[], u16 uwPos, u16 uwLen)
{
  u16 uwLD;
  u16 uwLS;
  u16 uwP;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  uwLS = strlen(ubSrc);
  uwLD = strlen(ubDst);

  //--- Test that all the lengths are within range

  if (uwLen > uwLD) return FALSE;                 //--- Destination too small
  if (uwLen > uwLS) return FALSE;                 //--- Source too small
  if ((!uwLS) || (!uwLD) || (!uwLen)) return FALSE; //--- Zero length strings
  if ((uwPos + uwLen) > uwLD) return FALSE;       //--- Result won't fit

  //--- Copy characters from Src to Dst

  for (uwP = 0; uwP < uwLen; uwP++)
  {
    ubDst[uwPos + uwP] = ubSrc[uwP];
  }

  return TRUE;
}

//---------------------------------------------------------------------------------------------
//                       Find one string inside of another String
//
//           Returns (-1) if not found or Character N+1 for Starting Location
//---------------------------------------------------------------------------------------------
s16   fnFindSinS (u08 ubFind[], u08 ubSrc[])
{
  u16 uwLF;
  u16 uwLS;
  u16 uwA;
  u16 uwB;
  u16 uwFlag;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  uwLF = fnStrLen (ubFind);
  uwLS = fnStrLen (ubSrc);

  //--- Scan Source String for "Find" String
  for (uwA = 0; uwA < (uwLS - uwLF); uwA++)
  {
    uwFlag = TRUE;                                //--- Preset Flag for Success
    for (uwB = 0; uwB < uwLF; uwB++)
    {
      if (ubSrc[uwA+uwB] != ubFind[uwB])          //--- Check each Src byte for match in Find
      {
        uwFlag = FALSE;                           //--- If non match set flag & Exit
        break;
      }
    }

    //--- If every thing matched then exit function with pos16er to start of string
    if (uwFlag)
    {
      return uwA;
    }
  }
  return -1;                                      //--- -1 is failed to find
}

//---------------------------------------------------------------------------------------------
//                          Extract Part of A Character Array
//---------------------------------------------------------------------------------------------
void  fnGrabArrayBytes (u08 ubDstArray[], u08 ubSrcArray[], u16 uwPtr, u16 uwCount)
{
  u16 uwC;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  for (uwC = 0; uwC < uwCount; uwC++)
  {
    ubDstArray[uwC] = ubSrcArray[uwPtr];
    uwPtr++;
  }
}

//---------------------------------------------------------------------------------------------
//                         Remove Left Most Tabs and Spaces from String
//---------------------------------------------------------------------------------------------
u32  fnLTRIM (u08  ubSrc[])
{
  u32 ulP;
  u32 ulL;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  ulL = strlen (ubSrc);

  if (!ulL) return ulL;

  //--- Test for Space or TAB as First Character

  while ((ubSrc[0] == 0x20) || (ubSrc[0] == 0x09))
  {
    for (ulP = 0; ulP < (ulL - 1); ulP++)
    {
      ubSrc[ulP] = ubSrc[ulP + 1];
    }
    ubSrc[ulP] = 0;
    ulL--;
  }

  ulL = strlen (ubSrc);
  return ulL;
}

//---------------------------------------------------------------------------------------------
//                        Remove Right Most Tabs and Spaces from String
//---------------------------------------------------------------------------------------------
u32  fnRTRIM (u08  ubSrc[])
{
  u32 ulP;
  u32 ulL;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  ulL = strlen (ubSrc);

  if (!ulL) return ulL;
  ulP = ulL - 1;

  //--- Test for Space or TAB as First Character

  while (((ubSrc[ulP] == 0x20) || (ubSrc[ulP] == 0x09)) && (ulL > 0))
  {
    ubSrc[ulP] = 0x00;
    ulL--;
    ulP--;
  }

  ulL = strlen (ubSrc);
  return ulL;
}


//---------------------------------------------------------------------------------------------
//                       Functions to extract Hi & Lo Bytes of Word
//---------------------------------------------------------------------------------------------

u08   fnLoByte (u16 uwWord)
{
  return  (u08)(uwWord & 0x00FF);
}

u08   fnHiByte (u16 uwWord)
{
  return  (u08)((uwWord / 0x100) & 0x00FF);
}

u16   fnBytesToWord (u08 ubLoByte, u08 ubHiByte)
{
  u16   uwWork;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  uwWork = (u16) ubHiByte;
  uwWork = uwWork << 8;
  uwWork |= (u16) ubLoByte;
  return uwWork;
}


//---------------------------------------------------------------------------------------------
//                       Functions to Convert BCD to Binary and Back
//---------------------------------------------------------------------------------------------
u08   fnBCD2Bin (u08  ubBCD)
{
  u08 ubWork;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  ubWork = ((ubBCD >> 4) & 0x0F) * 10;
  ubWork += ubBCD & 0x0F;
  return ubWork;
}

u08   fnBin2BCD (u08  ubBin)
{
  u08 ubWork;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  ubWork = ((ubBin / 10) << 4) & 0xF0;
  ubWork |= ((ubBin % 10) & 0x0F);
  return ubWork;
}


//---------------------------------------------------------------------------------------------
//                     Functions to Convert a Byte Value to 2 Hex Characters
//---------------------------------------------------------------------------------------------
void  fnByte2Hex (u08 ubByte, u08 ubOut[])
{
  u08 ubWork;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  ubWork = (ubByte & 0xF0) / 0x10;
  ubOut[0] = fnByte2Chr (ubWork);
  ubWork = (ubByte & 0x0F);
  ubOut[1] = fnByte2Chr (ubWork);
}

//---------------------------------------------------------------------------------------------
//                   Functions to Convert a Byte Value a Hex Character 0-9/A-F
//---------------------------------------------------------------------------------------------
u08 fnByte2Chr (u08 ubByte)
{
  u08 ubWork = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  ubByte &= 0x0F;

  switch (ubByte)
  {
    case 0: case 1: case 2: case 3: case 4:
    case 5: case 6: case 7: case 8: case 9:
      ubWork = 0x30 + ubByte;
      break;

    case 10: case 11: case 12: case 13: case 14: case 15:
      ubWork = ubByte + 0x37;
      break;
  }

  return ubWork;
}


//---------------------------------------------------------------------------------------------
//                        Function to simply copy 1 string to another
//---------------------------------------------------------------------------------------------
void  fnStrCpy (u08 ubDst[], u08 ubSrc[])
{
  u16 uwPtr = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  while (ubSrc[uwPtr])
  {
    ubDst[uwPtr] = ubSrc[uwPtr];
    uwPtr++;
  }

  ubDst[uwPtr] = 0;
}


//---------------------------------------------------------------------------------------------
//                      Function to simply measure the length of a string
//---------------------------------------------------------------------------------------------
u16   fnStrLen (u08 ubSrc[])
{
  u16 uwLen = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  while (ubSrc[uwLen])
  {
    uwLen++;
  }
  return uwLen;
}

//---------------------------------------------------------------------------------------------
//                        Convert Single Precision Value to Closest integer
//---------------------------------------------------------------------------------------------
s32 fnCINTF (flt sfFloat)
{
  s32 slWork;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  slWork = (s32)sfFloat;

  //--- Test if we round up or down

  if (fabsf(sfFloat - (flt)slWork) > 0.5)
  {
    if (slWork >= 0)
      slWork = slWork + 1;
    else
      slWork = slWork - 1;
  }
  return slWork;
}

//---------------------------------------------------------------------------------------------
//                   Convert Float Double Precision Value to Closest integer
//---------------------------------------------------------------------------------------------
s32 fnCINTD (dbl dblFloat)
{
  s32 slWork;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  slWork = (s32)dblFloat;

  //--- Test if we round up or down

  if (fabs(dblFloat - (dbl)slWork) > 0.5)
  {
    if (slWork >= 0)
      slWork = slWork + 1;
    else
      slWork = slWork - 1;
  }
  return slWork;
}

//---------------------------------------------------------------------------------------------
//                       Convert a lower case (a-z) to Upper Case (A-Z)
//---------------------------------------------------------------------------------------------
u08 fnLc2Uc (u08  ubChar)
{
  if ((ubChar > 0x60) && (ubChar < 0x7B))
  {
    ubChar -= 0x20;
  }

  return ubChar;
}

//---------------------------------------------------------------------------------------------
//                Converts a Single Precision Floating-Point number to a String
//---------------------------------------------------------------------------------------------
void fnFtoA(flt sfIn, u08 sOut[])
{
  s16   swDigit;                                  //--- Magnititude Values
  flt   sfMag, sfM1;                              //--- Magnititude Values
  u08   ubNflag = False;                          //--- Negative Number Flag
  u08   ubEflag = False;                          //--- Use Exponent Flag
  flt   sfWeight;                                 //--- Weight Temp Storage
  u16   uwFlag;                                   //--- Generic Boolean Flag
  u16   uwPtr;                                    //--- String Pointer
  s16   swI, swJ, swM0, swM1;                     //--- Temporary Variables

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  uwPtr = 0;                                      //--- Reset output character pointer
  sOut[uwPtr] = 0;

  //--- Handle special cases
  uwFlag = isnan(sfIn);
  if (uwFlag)                                     //--- Not a Number
  {
    strcpy(sOut, "#NaN");                         //--- Copy Notation and Exit
    return;
  }

  uwFlag = isinf(sfIn);                          //--- Infinite
  if (uwFlag)                                     //--- Not a Number
  {
    strcpy(sOut, "#Inf");                         //--- Copy Notation and Exit
    return;
  }

  if (sfIn == 0.0)
  {
    strcpy(sOut, "0.0");                          //--- Copy Notation and Exit
    return;
  }

  //--- If number is negative then flip sign & set flag
  if (sfIn < 0)
  {
    ubNflag = True;                               //--- Cet Negative Flag
    sfIn = -sfIn;                                 //--- Reverse sign of number
    sOut[uwPtr] = '-';                            //--- Add Negative sign to output string
    uwPtr++;
  }
  else
  {
    ubNflag = False;                              //--- Clear negative flag
  }

  //--- Calculate magnitude of number as an integer
  sfMag = log10(sfIn);

  //--- See if we use exponent notation
  if ((sfMag > 6.0) || (sfMag < -6.0) || (ubNflag && (sfMag > 6.0)))
  {
    ubEflag = True;
  }

  //  ubEflag = (m >= 7 || (ubNflag && m >= 7) || m <= -7);

  //--- If there are more than 6 digits then
  //    Set up for scientific notation
  if (ubEflag)
  {
    //--- is Exponent Negative?
    if (sfMag < 0.0) sfMag -= 1.0;
    sfIn = sfIn / pow(10.0, sfMag);
    sfM1 = sfMag;
    sfMag = 0;
  }

  //--- Correct underflow
  if (sfMag < 1.0) sfMag = 0;
  swM0 = (s16)sfMag;                              //--- Save integer magnititude

  //--- Convert the number
  while ((sfIn > 0.0000001f) || swM0 >= 0)
  {
    sfWeight = powf(10.0, swM0);

    //--- Check Range
    if ((sfWeight > 0) && (!isinf(sfWeight)))
    {
      swDigit = floor(sfIn / sfWeight);           //--- Calculate the Exponent Digits
      sfIn -= ((float)swDigit * sfWeight);
      sOut[uwPtr] = 0x30 + swDigit;               //--- Add Digit to output string
      uwPtr++;
    }

    //--- Place the decimal Point
    if ((swM0 == 0) && (sfIn > 0))
    {
      sOut[uwPtr] = '.';
      uwPtr++;
    }

    swM0 -= 1;
  }

  //--- Process The Exponent
  //    Convert the exponent
  if (ubEflag)
  {
    sOut[uwPtr] = 'E';                            //--- Add exponent character to string
    uwPtr++;                                      //--- Bump Pointer

    if (sfM1 > 0)                                 //--- Add exponent sign to string
    {
      sOut[uwPtr] = '+';                          //--- Add exponent + sign to string
      uwPtr++;                                    //--- Bump Pointer
    }
    else
    {
      sOut[uwPtr] = '-';                          //--- Add exponent - sign to string
      uwPtr++;                                    //--- Bump Pointer
      sfM1 = -sfM1;
    }

    //--- Number of Digits as integer
    swM1 = (s16)sfM1;
    swM0 = 0;

    //--- Add padded zeros to string
    while (swM1 > 0)
    {
      sOut[uwPtr] = '0' + (swM1 % 10);            //--- Place Numeric Character in String
      uwPtr++;                                    //--- Bump Pointer
      swM1 /= 10;                                 //=== Divide by 10
      swM0++;                                     //--- Increment Magnitude
    }

    //--- Correct length of string for padding

    for (swI = 0, swJ = swM0 - 1; swI < swJ; swI++, swJ--)
    {
      //--- Swap Without Temporary
      sOut[swI] ^= sOut[swJ];
      sOut[swJ] ^= sOut[swI];
      sOut[swI] ^= sOut[swJ];
    }

    uwPtr += swM0;                                //--- Point to end of string
  }

  sOut[uwPtr] = 0;                                //--- Terminate output string
  return;
}

//=============================================================================================
//    Substitute Source for _sbrk
//    low level bulk memory allocator - used by malloc
//=============================================================================================
extern s16 _HEAP_START;
extern s16 _HEAP_END;
static caddr_t heap = NULL;

//--- Note: HEAP Starts at Highest Address of Stack Space BSS + StackSize and progresses
//          upward to end of RAM.  Stack progresses from highest Stack Address to lowest
//          and decrements for each value pushed onto stack.

caddr_t _sbrk ( int increment )
{
  caddr_t prevHeap;
  caddr_t nextHeap;

  if (heap == NULL)
  {
    // first allocation
    heap = (caddr_t)&_HEAP_START;
  }

  prevHeap = heap;

  // Always return data aligned on a 8 byte boundary
  nextHeap = (caddr_t)(((s16)(heap + increment) + 7) & ~7);

  // get current stack pos16er
  // register caddr_t stackPtr asm ("sp");
  // Check enough space and there is no collision with stack coming the other way
  // if stack is above start of heap

//  if ((((caddr_t)&_HEAP_START < stackPtr) && (nextHeap > stackPtr)) || (nextHeap >= (caddr_t)&_HEAP_END))

  if (((nextHeap < (caddr_t)&_HEAP_START)) || (nextHeap >= (caddr_t)&_HEAP_END))
  {
    return NULL; // error - no more memory
  }
  else
  {
    heap = nextHeap;
    return (caddr_t) prevHeap;
  }
}

//|....|....|....*....|....|....*....|....|....^....|....|....*....|....|....*....|....|....|..

//=============================================================================================
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //-------------------------------------------------------------------------------------------
  //
  //-------------------------------------------------------------------------------------------

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //-----------------------------------------------------------------------------------------
    //
    //-----------------------------------------------------------------------------------------

      //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

      //---------------------------------------------------------------------------------------
      //
      //---------------------------------------------------------------------------------------

        //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
