#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024,0x9A),
dataSegmentSelector(0,64*1024*1024,0x92)
{

    uint32_t i[2];
    i[0] = (uint32_t) this;
    i[1] = sizeof(GlobalDescriptorTable) << 16;// i dont really get this part but ill research it a bit more

    asm volatile("lgdt (%0)": :"p"(((uint8_t *)i)+2));
}


GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

uint16_t GlobalDescriptorTable::DataSegmentSelector() //index of the data segment
{
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector() //index of the code segment
{
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type)
{
    uint8_t* target = (uint8_t*) this;
    if(limit<= 65536)
    {
        target[6] = 0x40;
    }
    else
    {
        if((limit & 0xFFF) != 0xFFF)
            limit = (limit >> 12)-1;
        else
            limit = limit >> 12;
        target[6] = 0xC0;
    }
    target[0] = limit & 0xFF; //first byte of limit
    target[1] = (limit >> 8) & 0xFF; //second byte of limit
    target[6] |= (limit >> 16 ) & 0xF //the 4 bit pat of the limit



}