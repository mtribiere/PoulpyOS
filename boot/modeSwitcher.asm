[bits 16]
switch_to_pm:
    cli ; Disable interrupts
    lgdt [gdt_descriptor] ; Load the GDT descriptor

    ; Enable 32-bit mode bit in cr0
    mov eax, cr0
    or eax, 0x1 
    mov cr0, eax
	
    call CODE_SEG:init_pm ; Jump to the new 32-bit code segement

[bits 32]
init_pm: ; First 32-bit instruction

    ; Update the segment registers
    mov ax, DATA_SEG     	    
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	
    ; Reset the stack address
    mov ebp, 0x90000 
    mov esp, ebp

    call BEGIN_PM
