## Support the latest pico-sdk (v1.5.0)
- The code is developed based on [Pico_Template](https://github.com/GorgonMeducer/Pico_Template)

- Compiler: Arm Compiler 6.15 and above (Using non-intrusive wrapper to support pico-sdk which is written in GCC)

- Add support for popular [LCD 1.3inc module](https://www.waveshare.com/wiki/Pico-LCD-1.3) 

- Support an ultra-lightweight python VM: [PikaScript](https://github.com/pikasTech/pikascript) (via cmsis-pack)

- Compatible with CMSIS 5.7.0, CMSIS 5.8.0 and above

- Provide users an option to use the ***stdio*** solution from ***pico-sdk (by default)*** or retarget the ***stdin/stdout*** to a user specified location directly. (See note in ***env_wrapper.c***).

- **Support Debug in MDK**

  - [Using CMSIS-DAP](https://github.com/majbthrd/pico-debug) (Validated in MDK and **highly recommended**)
  - **Support Flash Downloading**

- Add dedicated project configurations for:
  - [**AC6-flash**] Running code in Flash (XIP)

  - [**AC6-RunInSRAM**] Running code in SRAM (code is still stored in FLASH)

  - [**AC6-DebugInSRAM**] "no_flash" mode in the original pico-sdk.

    


# How to Use

## 1. Get the code

I assume that you have the lastest MDK installed on your PC. Please clone the code with following command line:

```
mkdir game-snake
cd pico-snake

git clone https://github.com/spencergotowork/GAME-2D.git .

git submodule update --init
```

## 2. Use the demo

The MDK project could be found in the path "ROOT\project\mdk". I assume you know how to use MDK for normal compilation. 

### 2.1 How to set the Stack and Heap size

Usually, people want to adjust the size of stack and heap, and it is very easy in this template. Please find the file "RP2040.sct" in the same MDK project directory. Find the macro ***STACK_0_SIZE*** for stack and ***HEAP_0_SIZE*** for the heap.  



```
#define STACK_0_SIZE        (1024*4)
#define STACK_1_SIZE        (1024*1)

#define HEAP_0_SIZE         (1024*32)
#define HEAP_1_SIZE         (1024*1)
```

***NOTE***: 

1. Please do **NOT** add "**u**" behind those constant values. 
2. The STACK_1_SIZE and HEAP_1_SIZE are not in use. You can set their value to reasonable smaller ones if you do want to reduce the RAM footprint. 


# Known issue

- Not all peripheral modules are added to the compilation. But I guess it is just a piece of cake for you : P

- ***Please use the elf2uf2 tool in this template*** to convert the generated axf into uf2.

- Might need more documents...

