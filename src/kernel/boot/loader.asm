global loader                           ; the entry symbol for ELF


section .text                           ; Start of the code section

extern kmain        

loader:                                 ; the loader label (defined as entry point in linker script)
    mov eax, 0xCAFEBABE 
    call kmain      
;   mov eax, 0xCAFEBABE                ; place the number 0xCAFEBABE in the register eax



.loop:      
    jmp .loop                           ; loop forever
