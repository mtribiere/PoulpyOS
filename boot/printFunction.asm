[bits 16]
print:
    pusha

start:
    ;If the next char is null
    mov al, [bx] 
    cmp al, 0 
    je done

    ; Print char
    mov ah, 0x0e
    int 0x10 

    ; Go to the next char
    add bx, 1
    jmp start

done:
    popa
    ret

[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_pm_loop:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK

    ;If the next char is null
    cmp al, 0
    je print_pm_done

    mov [edx], ax
    add ebx, 1 ; Next char
    add edx, 2 ; Next video memory position

    jmp print_pm_loop

print_pm_done:
    popa
    ret