#include "types.h"
#include "gdt.h"




void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    for(int i =0; str[i] != '\0'; ++i)
    VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i]; // so we keep the high bytes which are information about the color and we modify the ascii character.
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() // we do this so that all constructors are called before the kernel starts so it operates smoothly.
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
}




extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber)
{
    printf("Hello World!---"); // Gonna create a small printf because we cant call the library when there is no os

    // we dont want the kernel to stop so at the end we will just go into an infinite loop:
    GlobalDescriptorTable gdt;

    while(1);

}