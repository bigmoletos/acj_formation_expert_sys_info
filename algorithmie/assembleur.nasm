section .data
    hello_msg db "Hello, World!", 0xA  ; Message à afficher (0xA est le saut de ligne)
    hello_len equ $ - hello_msg        ; Longueur du message

section .text
    global _start                      ; Point d'entrée du programme

_start:
    ; Appel au système write (sys_write)
    mov eax, 4                         ; Numéro de l'appel système (sys_write)
    mov ebx, 1                         ; Descripteur de fichier (1 = stdout)
    mov ecx, hello_msg                 ; Adresse du message
    mov edx, hello_len                 ; Longueur du message
    int 0x80                           ; Interruption pour effectuer l'appel système

    ; Appel au système exit (sys_exit)
    mov eax, 1                         ; Numéro de l'appel système (sys_exit)
    xor ebx, ebx                       ; Code de retour (0)
    int 0x80                           ; Interruption pour quitter le programme


