;
; PoulpyOS Main Boot Sector
;
[org 0x7c00] ; Boot Sector initial offset 
[bits 16]
KERNEL_OFFSET equ 0x1000
mov [BOOT_DRIVE], dl 
jmp BOOT_SECTOR_ENTRY

; Include files
%include "boot/GDT.asm"
%include "boot/modeSwitcher.asm"
%include "boot/printFunction.asm"
%include "boot/drive_loader.asm"

SECTION .text
[bits 16]
BOOT_SECTOR_ENTRY:
mov bp, 0x9000 ; Set the stack position
mov sp, bp

; Print welcome message
mov bx, BOOT_MSG_1
call print

;Load the kernel
mov ebx,MSG_LOAD_KERNEL
call print

mov bx, KERNEL_OFFSET ; Read from disk and store at 0x1000
mov dh, 32
mov dl, [BOOT_DRIVE]
call disk_load

mov ebx,MSG_OK
call print

; Switch to 32 bits mode
call switch_to_pm

[bits 32]
BEGIN_PM:
    mov ebx, BOOT_MSG_2
    call print_pm
    call KERNEL_OFFSET
    jmp $


; Data
BOOT_DRIVE db 0 

BOOT_MSG_1:
    db 'Entering 16 bits mode...', 13, 10, 0

BOOT_MSG_2:
    db 'Entering 32 bits mode...', 0

MSG_LOAD_KERNEL:
     db "Copying kernel into memory...", 0

MSG_OK:
    db "[OK]",0


; Padding and magic number
times 510-($-$$) db 0
dw 0xaa55