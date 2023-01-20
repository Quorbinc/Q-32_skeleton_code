# Q-32_skeleton_code
This is the skeleton code for Quorb Inc's QMX-32 board.  All you need to do is write your code, compile it, and upload the .hex file into your board is programmed.

## Getting started
Getting a project running is easy.  
1. Open PROJECT.c.
2. Scroll down to the main function
3. Add your code to main similar to below. 
4. load it into the QMX-32 and you're off.

```
//--- some code from main in the skeleton code omitted for clarity
int main (void)
{
  PA14_OUT;
  while (1)
  {
    SET_PA14;
    fnTickDelay(5000);
    CLR_PA14;
    fnTickDelay(5000);
  }
}
```
The above code will set PA_14 as an output, turn it on, wait for a half second, turn it off, wait for another half second and repeat the loop.  This looping method is a common way microcontrollers are programmed to operate but we have thrown in a different operating method.
