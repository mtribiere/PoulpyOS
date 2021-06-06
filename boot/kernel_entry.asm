global _start;

[bits 32]
[extern poulpy]

_start:
    call poulpy 
    jmp $