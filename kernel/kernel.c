#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>
void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();

    asm("int $2");
    asm("int $3");
    clear_screen();
    kprint("Type HELP for commands\n> ");
}
void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    } else if (strcmp(input, "CLEAR") == 0) {
        clear_screen();
        kprint("\n> ");
    } else if (strcmp(input, "DAKSH SUCKS") == 0) {
        kprint("ikr");
        kprint("\n> ");  
    } else if (strcmp(input, "HELP")==0) {
        kprint("END - Stop CPU\n");
        kprint("PAGE - Test malloc\n");
        kprint("CLEAR - Clear Screen\n");
        kprint("<int>PLUS<int> - BROKEN\n");
        kprint("\n> ");
    } else if (plus(input)!=0){
        char X = plus(input) + '0';
        kprint(X);
        kprint("\n> ");
    } else{   
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}}

