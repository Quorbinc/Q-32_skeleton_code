# Q-32_skeleton_code
This is the skeleton code for Quorb Inc's QMX-32 board.  All you need to do is write your code, compile it, and upload it and then  your board is programmed.

## Getting started
Getting a project running is easy.  
1. Open PROJECT.c.
2. Scroll down to the main function
3. Add your code to the main function.
4. load it into the QMX-32 and you're off.
```C
//--- some code omitted for clarity
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
The above code is a simple blink led function.  It will set PA_14 as an output, turn it on, wait for a half second, turn it off, wait for another half second and repeat the loop.  This looping method is a common way microcontrollers are programmed to operate but we have thrown in a different operating method.

## Task Definition

**ALL Tasks MUST use this Function Structure Definition**  
```C
//---Task function
output_value name_of_function (union DFLWB name_of_task_data)

//---Task structure
struct Task
{
    u16     uwTimer;                            //--- Task Timer delay value (0 - 65KmSec)
    u16     uwFlags;                            //--- Task Extra Flags Pass Data
    void    (*ptrTask);                         //--- Address Pointer To Task
    union DFLWB16 unTaskData;                   //--- Generic (16 Byte) PassData Union
};
```
uwFlags     = Generic Status Information for Task Call
uwTimer     = Task Execution delay time in mSec (0 = no delay else execution delayed n mSec)
*ptrTask    = Memory address of schedueled Task
unTaskData  = Task Data Payload as an 16 byte union

### Task Data Union Definition

Double Float Long Word Byte Pointer Union
64 Bit Variable union (8 Bytes)
16 Byte Variable union

A Task will return a 32 bit code showing the Task Error or Return Condition

```C
//--- 32 Bit Returned Value from Task
struct TaskRet
{
    u16 uwErrCode;          //--- Returned Error Code Value.  (0x0000 = No Error)
    u16 uwRetVal;           //--- Generic Unsigned Word
}
```

Task Data Union Definition

This union definition allows a multitude of different variable types to be passed to a Task
all within a single 8 Byte data load.

```C
union DFLWB16                   //--- 16 Bytes Binary / Integer Storage
{
    dbl   dfFlt[2];               //--- 2 Double Precision Float
    u64   uxBig[2];               //--- 2 Unsigned 64 Bit Integer
    s64   sxBig[2];               //--- 2 Signed 64 Bit Integer
    flt   sfFlt[4];               //--- 4 Single Precision Floats
    u32   ulLong[4];              //--- 4 Unsigned Long
    s32   slLong[4];              //--- 4 Signed Long
    u16   uwWord[8];              //--- 8 Unsigned Words
    s16   swWord[8];              //--- 8 Signed Words
    u08   ubByte[16];             //--- 16 Unsigned Bytes
    s08   sbByte[16];             //--- 16 Signed Bytes
    u08*  ubPtr[4];               //--- 4 General Purpose Pointers (byte]
    void* vPtr[4];                //--- 4 Void Type Pointers
};
```
Format for schedueling a Task:

To Schedule a Task the following Code Should be Used

1.  Create the Task Structure Locally or use the globally defined temporary Task Structure struct Task stNewTask;

2.  Define the Task Properties  
stNewTask.ubPriority = Value (0 to 15):  Task Priority  
stNewTask.ubFlags = Value (0 to 255):  Random Signal Byte to Pass to Task  
stNewTask.uwTimer = execution delay in mSec:  Deley Time  
stNewTask.ulTime Stamp = System Time Stamp:  System Time at Schedueling  
stNewTask.*ptrTask = Memory Address of Task:  Calls this address when Dispatched  
stNewTask.unTaskData = 8 Bytes of union Data:  Data Load to Pass to Task  

Schedueler Function Prototype  
union LWB fnSchedule (struct Task stInTask)


## Using Tasks for real time operations
To use the RTOS nature of our software, we revolve everything we do around tasks, and task dispatching.  Tasks to start with are functions which start with the aforementioned format with examples below.  These functions get addressed in a task assignment and are then executed by the dispatcher
```C
//--- General format
output_value name_of_function (union DFLWB name_of_task_data)
{
    //--- code
}

//--- Examples
void BlinkLED (union DFLWB taskdata)
{
    //--- Your code goes here
}

u16 temperature_measurement (union DFLWB temperaturedata)
{
    //--- Your code goes here
}
```
How do you get your defined tasks assigned you ask?  Simple,  You fill out a task struct.  You can have one you work with for everything as many as you need.  Defining a task is as simple as ```struct  Task  nameOfTask``` and then you fill oin the data for the task to get assigned.  A task is laid out below.
```C
struct Task
{
    u16     uwTimer;                              //--- Task Timer delay value (0 - 65KmSec)
    u16     uwFlags;                              //--- Task Extra Flags Pass Data
    void    (*ptrTask);                           //--- Address Pointer of Task
    union DFLWB16 unTaskData;                     //--- Generic (16 Byte) PassData Union
};
```

## Putting it all together
To schedule and use tasks, you can make a program like the program below in project.c and project.h to blink an LED
```C
//-----Some code omitted for clarity-----//

struct Task LEDTask //--- Defines a task to be used.

int main (void)
{
    PA14_OUT;                              //--- Set PA14 as Output

    //--- Lines 73 through 77 schedule the blinkLED task to kick the program off
    LEDTask.uwTimer = 333;
    LEDTask.ptrTask = &BlinkLED;
    LEDTask.uwFlags = 0;
    LEDTask.unTaskData = unEmptyData;      //--- Empty Data to Start
    uwReturnVal = fnScheduleTask(LEDTask);

    //--- Main Infinite Loop entry point calls Dispatcher and any polled actions

    while (1)
    {
        fnDispatcher();
    }
}

//-----Function for a a task to blink the LED-----//
void BlinkLED (union DFLWB unTD)
{
    struct  Task stTask;                              //--- Task Model for Scheduling Tasks

    if (TST_PA14)     //--- Test to see if the pin is high
    {
        CLR_PA14;     //--- Turn the pin off
    }

    else
    {
        SET_PA14;     //--- Turn the pin on
    }

    //--- This task will reschedule itself 2 times / Second
    stTask.uwTimer = 500;                             
    stTask.ptrTask = &BlinkLED;
    stTask.uwFlags = 0;
    stTask.unTaskData = unTD;
    uwReturnVal = fnScheduleTask (stTask);
}
```
Make sure you include the below line in project.h
```C
void BlinkLED (union DFLWB unTD);
```
What the above program will do is enter main and schedule the blinkled function.  The program will then enter the loop in which it will continue to execute the dispatcher.  Once the first scheduled task counts down to zero, it will execute the BlinkLED function which will toggle the pin accordingly and then schedule itself again as a continuous loop blinking the LED in the same manor as the loop method above.

## When where to use tasks
You can use tasks anywhere you decide so long as your program is able to get to a point where it can hit the task schedule.  If you schedule a task within a function that is never called, then the task will never be scheduled, so this allows you a lot of freedom in where you can place tasks.  Like earlier, you can call the task call at the beginning of the main function before the loop is called.  You can use an if statement in the main loop so if a condition is met, such as a button gets pressed, it will then schedule a task.  You can have an interrupt schedule a task, which has an added bonus of getting you in and out of the interrupt faster than if you have the interrupt run through lines upon lines of code.     

## How the RTOS Functions Work

The RTOS centers around a Task Queue of executable code sections which are called a "Task"

This RTOS System is a powerful yet simplified event driven operating system. Operating with very little system resource overhead.  It is composed of 4 main sections.

1. The Task Definition:  A Task is defined as a function with a predefined Data Input Construct and a predefined Data Return Construct.  A Task has definiton is pointer to a function location.  Along with the function upto 8 bytes of task data may be passed.  The data may be of any allowable "C" type (Numeric, String, Pointers, Etc.) which allows for flexible data and variable passage. In addition each task contains a TimeStamp within the data field so analysis related to time synchronization can be easily be accomplished.  

2. The Task Scheduling and Dispatching section:  This section takes requests for Tasks and places them in either a Task Queue or into a Timer Queue. All Tasks, when schedueled, have a system Time  Stamp Value This time stamp allows for timing corrections should the Task require it.  

3. The Event Driven Interrupts:  These interrupts occur after a particular hardware or software event occurs.  The interrupt services the hardware and either takes immediate action or the event is converted to a Task and is schedueled for execution. The Task may be schedueled to execute at a pre determined time delay if required.  

4. The uninterruptable PACER time and phase interrupt ("SysTick"):  This is the "HeartBeat" of the system and is known as "The Pacer" interrupt which occurs at interval of 100 uSec or (10,000 times / second). Items that need to occur at precise intervals are scheduled by the Pacer.  In addition the Pacer handles the transmission of data via USART1 or USART2 and automatically adjusts for different Baud Rates.

Tasks may be recursive in nature giving them the ability to periodically reschedule themselves with little or no operating system burden.  

The Task Sheduling and Dispatching allowes for fast reaction to events with the ability to process important data and calculations in the background.  An event schedules a Task and passes the data for that Task to a FIFO buffer.  When the current Task finishes its operations it returns to the Dispatcher where the next Task is fetched and executed.  For an RTOS system Very little time is spent in an Interrupt service routine. Events typically acquire data from hardware stimulii and schedule a Task for action on the data at the appropriate time thus making sure there are little or no conflicts between hardware interrupts, events and the system thread operation.

In the RTOS system there exists a set of 10 delayed action timers that allow for execution of functions at an exact time in the future (+/- 1mSec). Each time the Pacer Interrupt is entered the timers are decremented by 1.  When a timer value reaches 0 the corrisponding function is scheduled to be executed. This frees the system from loop polling and pausing delays.

Task Data Definition:  Task Data is passed by a data 'UNION' of 16 Bytes Length.  This union allows for the passing of virtually any type information to a task from the scheduling function.  16 byte length was chosen because it covers all language defined types.  If a special type of data is required to be passed or the type to be passed is > 16 Bytes then the user should set asside a dynamic section of memory using malloc and passing a pointer to the associated area.  The allocated memory area can then be used or returned to the heap within the Task.

## Time Keeping within the Quorb RTOS:

The SysTick timer is an exceptionally high priority function that cannot be interrupted or disabled by normal program thread operation.  This is the "Pacer" that controls the timing of Quorb RTOS.  Each time the Pacer code is executed a 64 bit counter is incremented.  This value allows for high accuracy time value that is accurate to within +/- 100 uSec.  If the Quorb RTOS time keeping functions are enabled then the RTOS can synchronize it self to an external time source for stratum 1 time accuracy to less than 1 mSec Time uncertanty. (See the Quorb Time keeping library)

## conventions within code.  
### Codeing Definitions and pre naming convention

All Variable Names begin with a 2 or three lower case letter sequence which defines the variable type. A source code program type identifier us added to the front of the name to distiguish the Name and the type

| Defined Types                    | precursor     | Type Name Examplefor Name |
|:--------------------------------:|:-------------:|:-------------------------:|
| Unsigned Char                    | ch            | chExample                 |
| Unsigned Byte and Char Types     | ub            | ubExample                 |
| Signed Byte and Char Types       | sb            | sbExample                 |
| Unsigned Integer/Word Types      | uw            | uwExample                 |
| Signed Integer/Word Types        | sw            | swExample                 |
| Unsigned Long (32bit) Types      | ul            | ulExample                 |
| Signed Long (32bit) Types        | sl            | slExample                 |
| Unsigned Long Long (64bit) Types | ux            | uxExample                 |
| Signed Long Long (64bit) Types   | sx            | sxExample                 |
| Signed Long Long (64bit) Types   | sd            | sdExample                 |
| Single Precision Float           | sf            | sfExample                 |
| Double Precision Float           | df            | dfExample                 |
| Structures                       | st            | stExample.uwData          |
| Unions                           | un            | unExample.uwData          |
| Functions                        | fn            | fnExample ()              |
| Tasks                            | tk            | tkA_Task                  |
| pointer to byte                  | pb            | *pbPointer                |
| pointer to word                  | pw            | *pwPointer                |
| pointer to long                  | pl            | *plPointer                |
| pointer to float                 | pf            | *pfPointer                |
| pointer to double                | pd            | *pdPointer                |
| pointer to void                  | pv            | *pvPointer                |

A Byte is defined as an 8 bit binary number.  
A Word is defined as a 16 bit binary number.  
A Long is defined as a 32 bit binary number.  
A LongLong is defined as a 64 bit binary number.  


### GPIO Pin Alternate Function Definitions


#### Alternate function AF0 to AF7
| Pin  | AF0          | AF1        | AF2        | AF3       | AF4       | AF5       | AF6       | AF7       |
|:----:|:------------:|:----------:|:----------:|:---------:|:---------:|:---------:|:---------:|:---------:|
| PA00 | -            | TIM2_CH1   | -          | -         | -         | -         | -         | UART2_CTS |
| PA01 | -            | TIM2_CH2   | -          | -         | I2C1_SMBA | SPI1_SCK  | -         | UART2_RTS |
| PA02 | -            | TIM2_CH3   | -          | -         | -         | -         | -         | UART2_TX  |
| PA03 | -            | TIM2_CH4   | -          | -         | -         | -         | -         | UART2_RX  |
| PA04 | -            |     -      | -          | -         | -         | SPI1_NSS  | SPI3_NSS  | UART2_CK  |
| PA05 | -            | TIM2_CH1   | TIM2_ETR   | -         | -         | SPI1_SCK  | -         | -         |
| PA06 | -            | TIM1_BKIN  | -          | -         | -         | SPI1_MISO | COMP1_OUT | UART3_CTS |
| PA07 | -            | TIM1_CH1N  | -          | -         | I2C3_SCL  | SPI1_MOSI | -         | -         |
| PA08 | MCO          | TIM1_CH1   | -          | -         | -         | -         | -         | UART1_CK  |
| PA09 | -            | TIM1_CH2   | -          | -         | I2C1_SCL  | -         | -         | UART1_TX  |
| PA10 | -            | TIM1_CH3   | -          | -         | I2C1_SDA  | -         | -         | UART1_RX  |
| PA11 | -            | TIM1_CH4   | TIM1_BKIN2 | -         | -         | SPI1_MISO | COMP1_OUT | UART1_CTS |
| PA12 | -            | TIM1_ETR   | -          | -         | -         | SPI1_MOSI | -         | UART1_RTS |
| PA13 | JTMS-SWDIO   | IR_OUT     | -          | -         | -         | -         | -         | -         |
| PA14 | JTCK-SWCLK   | LPTIM1_O   | -          | -         | I2C1_SMBA | -         | -         | -         |
| PA15 | JTDI         | TIM2_CH1   | TIM2_ETR   | USART2_RX | -         | SPI1_NSS  | SPI3_NSS  | UART3_RTS |
| PB00 | -            | TIM1_CH2N  | -          | -         | -         | SPI1_NSS  | -         | UART3_CK  |
| PB01 | -            | TIM1_CH3N  | -          | -         | -         | -         | -         | UART3_RTS |
| PB03 | JTDOTRACESWO | TIM2_CH2   | -          | -         | -         | SPI1_SCK  | SPI3_SCK  | UART1_RTS |
| PB04 | NJTRST       | -          | -          | -         | I2C3_SDA  | SPI1_MISO | SPI3_MISO | UART1_CTS |
| PB05 | -            | LPTIM1_IN1 | -          | -         | I2C1_SMBA | SPI1_MOSI | SPI3_MOSI | UART1_CK  |
| PB06 | -            | LPTIM1_ETR | -          | -         | I2C1_SCL  | -         | -         | UART1_TX  |
| PB07 | -            | LPTIM1_IN2 | -          | -         | I2C1_SDA  | -         | -         | UART1_RX  |
| PC14 | -            | -          | -          | -         | -         | -         | -         | -         |
| PC15 | -            | -          | -          | -         | -         | -         | -         | -         |
| PH03 | -            | -          | -          | -         | -         | -         | -         | -         |


### Alternate function AF8 to AF15
| Pin  | AF8         | AF9       | AF10       | AF11 | AF12      | AF13      | AF14      | AF15     |
|:----:|:-----------:|:---------:|:----------:|:----:|:---------:|:---------:|:---------:|:--------:|
| PA00 | -           | -         | -          | -    | COMP1_OUT | SAI1_ECLK | TIM2_ETR  | EVENTOUT |
| PA01 | -           | -         | -          | -    | -         | -         | TIM15_C1N | EVENTOUT |
| PA02 | LPUART1_TX  | -         | QSPI_BK1   | -    | COMP2_OUT | -         | TIM15_CH1 | EVENTOUT |
| PA03 | LPUART1_RX  | -         | QSPI_CLK   | -    | -         | SAI1MCLK  | TIM15_CH2 | EVENTOUT |
| PA04 | -           | -         | -          | -    | -         | SAI1_FS_B | LTIM2_OUT | EVENTOUT |
| PA05 | -           | -         | -          | -    | -         | -         | LTIM2_ETR | EVENTOUT |
| PA06 | LPUART1_CTS | -         | QSPI_IO3   | -    | TIM1_BKIN | -         | TIM16_CH1 | EVENTOUT |
| PA07 | -           | -         | QSPI_IO2   | -    | COMP2_OUT | -         | -         | EVENTOUT |
| PA08 | -           | -         | -          | -    | SWPMI1_IO | SAI1_SCKA | LTIM2_OUT | EVENTOUT |
| PA09 | -           | -         | -          | -    | -         | SAI1_FS_A | TIM15BKIN | EVENTOUT |
| PA10 | -           | -         | USBCRSSNC  | -    | -         | SAI1_SD_A | -         | EVENTOUT |
| PA11 | -           | CAN1_RX   | USB_DM     | -    | TIM1_BKC1 | -         | -         | EVENTOUT |
| PA12 | -           | CAN1_TX   | USB_DP     | -    | -         | -         | -         | EVENTOUT |
| PA13 | -           | -         | USB_NOE    | -    | SWPMI1TX  | SAI1_SD_B | -         | EVENTOUT |
| PA14 | -           | -         | -          | -    | SWPMI1RX  | SAI1_FS_B | -         | EVENTOUT |
| PA15 | -           | TSCG3_IO1 | -          | -    | SWPMI1SUS | -         | -         | EVENTOUT |
| PB00 | -           | -         | QSPIBK1IO1 | -    | COMP1_OUT | SAI1_ECLK | -         | EVENTOUT |
| PB01 | LUART1RTS   | -         | QSPIBK1IO0 | -    | -         | -         | LTIM2_IN1 | EVENTOUT |
| PB03 | -           | -         | -          | -    | -         | SAI1_SCKB | -         | EVENTOUT |
| PB04 | -           | TSC_G2IO1 | -          | -    | -         | SAI1_MCKB | -         | EVENTOUT |
| PB05 | -           | TSC_G2IO2 | -          | -    | -         | SAI1_SDB  | -         | EVENTOUT |
| PB06 | -           | TSC_G2IO3 | -          | -    | -         | SAI1_FSB  | -         | EVENTOUT |
| PB07 | -           | TSC_G2IO4 | -          | -    | -         | -         | -         | EVENTOUT |
| PC14 | -           | -         | -          | -    | -         | -         | -         | EVENTOUT |
| PC15 | -           | -         | -          | -    | -         | -         | -         | EVENTOUT |
| PH03 | -           | -         | -          | -    | -         | -         | -         | EVENTOUT |

### Interrupt Definition Table

#### STM32L432 Nested Interrupt Controller Interrupt number defines

| interrupt             | number | description                             |
|:---------------------:|:------:|:---------------------------------------:|
| Reset_IRQn            | 15     | 2 Cortex-M4 Non Maskable Interrupt      |
| NonMaskableInt_IRQn   | -14    | 2 Cortex-M4 Non Maskable Interrupt      |
| HardFault_IRQn        | -13    | 3 Cortex-M4 Hard Fault Interrupt        |
| MemoryManagement_IRQn | -12    | 4 Cortex-M4 Memory Management Interrupt |
| BusFault_IRQn         | -11    | 5 Cortex-M4 Bus Fault Interrupt         |
| UsageFault_IRQn       | -10    | 6 Cortex-M4 Usage Fault Interrupt       |
| uuIRQm9               | -9     | N/A                                     |
| uuIRQm8               | -8     | N/A                                     |
| uuIRQm7               | -7     | N/A                                     |
| uuIRQm9               | -6     | N/A                                     |
| SVCall_IRQn           | -5     | 11 Cortex-M4 SV Call Interrupt          |
| DebugMonitor_IRQn     | -4     | 12 Cortex-M4 Debug Monitor Interrupt    |
| PendSV_IRQn           | -2     | 14 Cortex-M4 Pend SV Interrupt          |
| SysTick_IRQn          | -1     | 15 Cortex-M4 System Tick Interrupt      |

#### Peripherial Function Interrupts

| interrupt             | number | description                                           |
|:---------------------:|:------:|:-----------------------------------------------------:|
| WWDG_IRQn             | 0      | Window WatchDog Interrupt                             |
| PVD_PVM_IRQn          | 1      | PVD/PVM3/PVM4 through EXTI Line detection Interrupts  |
| TAMP_STAMP_IRQn       | 2      | Tamper and TimeStamp interrupts through the EXTI line |
| RTC_WKUP_IRQn         | 3      | RTC Wakeup interrupt through the EXTI line            |
| FLASH_IRQn            | 4      | FLASH global Interrupt                                |
| RCC_IRQn              | 5      | RCC global Interrupt                                  |
| EXTI0_IRQn            | 6      | EXTI Line0 Interrupt                                  |
| EXTI1_IRQn            | 7      | EXTI Line1 Interrupt                                  |
| EXTI2_IRQn            | 8      | EXTI Line2 Interrupt                                  |
| EXTI3_IRQn            | 9      | EXTI Line3 Interrupt                                  |
| EXTI4_IRQn            | 10     | EXTI Line4 Interrupt                                  |
| DMA1_Channel1_IRQn    | 11     | DMA1 Channel 1 global Interrupt                       |
| DMA1_Channel2_IRQn    | 12     | DMA1 Channel 2 global Interrupt                       |
| DMA1_Channel3_IRQn    | 13     | DMA1 Channel 3 global Interrupt                       |
| DMA1_Channel4_IRQn    | 14     | DMA1 Channel 4 global Interrupt                       |
| DMA1_Channel5_IRQn    | 15     | DMA1 Channel 5 global Interrupt                       |
| DMA1_Channel6_IRQn    | 16     | DMA1 Channel 6 global Interrupt                       |
| DMA1_Channel7_IRQn    | 17     | DMA1 Channel 7 global Interrupt                       |
| ADC1_IRQn             | 18     | ADC1 global Interrupt                                 |
| CAN1_TX_IRQn          | 19     | CAN1 TX Interrupt                                     |
| CAN1_RX0_IRQn         | 20     | CAN1 RX0 Interrupt                                    |
| CAN1_RX1_IRQn         | 21     | CAN1 RX1 Interrupt                                    |
| CAN1_SCE_IRQn         | 22     | CAN1 SCE Interrupt                                    |
| EXTI9_5_IRQn          | 23     | External Line[9:5] Interrupts                         |
| TIM1_BRK_TIM15_IRQn   | 24     | TIM1 Break interrupt and TIM15 global interrupt       |
| TIM1_UP_TIM16_IRQn    | 25     | TIM1 Update Interrupt and TIM16 global interrupt      |
| TIM1_TRG_COM_IRQn     | 26     | TIM1 Trigger and Commutation Interrupt                |
| TIM1_CC_IRQn          | 27     | TIM1 Capture Compare Interrupt                        |
| TIM2_IRQn             | 28     | TIM2 global Interrupt                                 |
| uuIRQi29              | 29     | N/A                                                   |
| uuIRQi30              | 30     | N/A                                                   |
| I2C1_EV_IRQn          | 31     | I2C1 Event Interrupt                                  |
| I2C1_ER_IRQn          | 32     | I2C1 Error Interrupt                                  |
| I2C2_EV_IRQn          | 33     | I2C2 Event Interrupt                                  |
| I2C2_ER_IRQn          | 34     | I2C2 Error Interrupt                                  |
| SPI1_IRQn             | 35     | SPI1 global Interrupt                                 |
| SPI2_IRQn             | 36     | SPI2 global Interrupt                                 |
| USART1_IRQn           | 37     | USART1 global Interrupt                               |
| USART2_IRQn           | 38     | USART2 global Interrupt                               |
| USART3_IRQn           | 39     | USART3 global Interrupt                               |
| EXTI15_10_IRQn        | 40     | External Line[15:10] Interrupts                       |
| RTC_Alarm_IRQn        | 41     | RTC Alarm (A and B) through EXTI Line Interrupt       |
| uuIRQi42              | 42     | N/A                                                   |
| uuIRQi43              | 43     | N/A                                                   |
| uuIRQi44              | 44     | N/A                                                   |
| uuIRQi45              | 45     | N/A                                                   |
| uuIRQi46              | 46     | N/A                                                   |
| uuIRQi47              | 47     | N/A                                                   |
| uuIRQi48              | 48     | N/A                                                   |
| SDMMC1_IRQn           | 49     | SDMMC1 global Interrupt                               |
| uuIRQi50              | 50     | N/A                                                   |
| SPI3_IRQn             | 51     | SPI3 global Interrupt                                 |
| uuIRQi52              | 52     | N/A                                                   |
| uuIRQi53              | 53     | N/A                                                   |
| TIM6_DAC_IRQn         | 54     | TIM6 global and DAC1&2 underrun error  interrupts     |
| TIM7_IRQn             | 55     | TIM7 global interrupt                                 |
| DMA2_Channel1_IRQn    | 56     | DMA2 Channel 1 global Interrupt                       |
| DMA2_Channel2_IRQn    | 57     | DMA2 Channel 2 global Interrupt                       |
| DMA2_Channel3_IRQn    | 58     | DMA2 Channel 3 global Interrupt                       |
| DMA2_Channel4_IRQn    | 59     | DMA2 Channel 4 global Interrupt                       |
| DMA2_Channel5_IRQn    | 60     | DMA2 Channel 5 global Interrupt                       |
| uuIRQi61              | 61     | N/A                                                   |
| uuIRQi62              | 62     | N/A                                                   |
| uuIRQi63              | 63     | N/A                                                   |
| COMP_IRQn             | 64     | COMP1 and COMP2 Interrupts                            |
| LPTIM1_IRQn           | 65     | LP TIM1 interrupt                                     |
| LPTIM2_IRQn           | 66     | LP TIM2 interrupt                                     |
| USB_IRQn              | 67     | USB event Interrupt                                   |
| DMA2_Channel6_IRQn    | 68     | DMA2 Channel 6 global interrupt                       |
| DMA2_Channel7_IRQn    | 69     | DMA2 Channel 7 global interrupt                       |
| LPUART1_IRQn          | 70     | LP UART1 interrupt                                    |
| QUADSPI_IRQn          | 71     | Quad SPI global interrupt                             |
| I2C3_EV_IRQn          | 72     | I2C3 event interrupt                                  |
| I2C3_ER_IRQn          | 73     | I2C3 error interrupt                                  |
| SAI1_IRQn             | 74     | Serial Audio Interface 1 global interrupt             |
| uuIRQi75              | 75     | N/A                                                   |
| SWPMI1_IRQn           | 76     | Serial Wire Interface 1 global interrupt              |
| TSC_IRQn              | 77     | Touch Sense Controller global interrupt               |
| uuIRQi78              | 78     | N/A                                                   |
| uuIRQi79              | 79     | N/A                                                   |
| RNG_IRQn              | 80     | RNG global interrupt                                  |
| FPU_IRQn              | 81     | FPU global interrupt                                  |
| CRS_IRQn              | 82     | CRS global interrupt                                  |
| uuIRQi83              | 83     | N/A                                                   |
| uuIRQi84              | 84     | N/A                                                   |
| uuIRQi85              | 85     | N/A                                                   |
| uuIRQi86              | 86     | N/A                                                   |
| uuIRQi87              | 87     | N/A                                                   |
| uuIRQi88              | 88     | N/A                                                   |
| uuIRQi89              | 89     | N/A                                                   |
| uuIRQi90              | 90     | N/A                                                   |
| uuIRQi91              | 91     | N/A                                                   |
| uuIRQi92              | 92     | N/A                                                   |
| uuIRQi93              | 93     | N/A                                                   |
| uuIRQi94              | 94     | N/A                                                   |
| uuIRQi95              | 95     | N/A                                                   |
| uuIRQi96              | 96     | N/A                                                   |
| uuIRQi97              | 97     | N/A                                                   |
| uuIRQi98              | 98     | N/A                                                   |
| uuIRQi99              | 99     | N/A                                                   |

###  Error Processing

16 Bit Error Code

Error Code Numbers are Signed Decimal Values Error Code Numbers 1 to 32767 represent errors returned by Tasks to the dispatcher Error Code Numbers < 0 represent system level errors either Operating System or Hardware The actual user code Error Code Values are defined by the program creator.  

All Errors fall into ONE of these 16 classes
System Error Classes:

- -1     Scheduling Error Timer
- -2     Scheduling Error Task
- -8     System Control Block Error
- -9     Memory Protection Error
- -10    FPU Error
- -11    STACK Over/Under Flow
- -12    Math HW (+-*\)
- -13    Math Library Error
- -14    Peripherial HW Error
- -15    NMI Fault
- -16    SysTick Error
- -17    Hard Fault Error
- -18    USB Vom Error
- -99    RTOS Error
- -9999  Undefined Error

Error Codes developed from Drivers should be defined within the Driver Code Blocks or interrupt handeling code blocks

### Other errors
- 0  0000 = Unknown
- 1  0001 = CORTEX CORE Error
- 2  0010 = System Control Block
- 3  0011 = Memory Protection Error
- 4  0100 = FPU Error
- 5  0101 = STACK Over/Under Flow
- 6  0110 = Math HW (+-*\)
- 7  0111 = Math SW Library
- 8  1000 = Peripherial HW Error
- 9  1001 = User SW Error
- A  1010 = RTOS Error
- B  1011 = NMI Fault
- C  1100 = SysTick Error
- D  1101 = Hard Fault Error
- E  1110 = System Timer (SysTick) Error
- F  1111 =

## Using Uarts.  
In linux, if you want to see the uart output, connect the uart communicator to the correct uart pins and plug it into your usb through usb.  in your terminal command, input the below command
```
screen /dev/ttyUSB0 115200

//--- screen is an application that lets you see serial input on the terminal,
//--- /dev/ttyUSB0 is the active serial interface from your device.
//--- 115200 is the Baud rate as defined in uart_com.c.  
```
