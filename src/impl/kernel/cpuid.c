#include "types.h"

void CPUID(uint i, ui32 regs[4]) {
    asm volatile
      ("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
       : "a" (i), "c" (0));
    // ECX is set to zero for CPUID function 4
}

void CPUID_vendor_string(char vendor_str[13]) {
    ui32 regs[4];
    CPUID(0, regs);
    vendor_str[0] = regs[1] & 0xFF;
    vendor_str[1] = (regs[1] >> 8) & 0xFF;
    vendor_str[2] = (regs[1] >> 16) & 0xFF;
    vendor_str[3] = (regs[1] >> 24) & 0xFF;
    vendor_str[4] = regs[3] & 0xFF;
    vendor_str[5] = (regs[3] >> 8) & 0xFF;
    vendor_str[6] = (regs[3] >> 16) & 0xFF;
    vendor_str[7] = (regs[3] >> 24) & 0xFF;
    vendor_str[8] = regs[2] & 0xFF;
    vendor_str[9] = (regs[2] >> 8) & 0xFF;
    vendor_str[10] = (regs[2] >> 16) & 0xFF;
    vendor_str[11] = (regs[2] >> 24) & 0xFF;
    vendor_str[12] = '\0';
}
