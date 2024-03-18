format ELF executable 3

include "objfasm.inc"

entry _start


segment executable readable writeable

STRUCT str
    MEMBER data: db 
    MEMBER length: dd
ENDS

;METHOD str::test_method(arg1, arg2)
;    .. do nothing ..
;END

_start:
    and esp, -8
    CALL main(0, 0)
    !e ebx = eax
    !e eax = 1
    int 0x80

FN main(argc, argv)
    CALL print(message, [length])
    RETURN 0
END

FN print(string)
    virtual at string
        string_ str
    end virtual
    !e ecx = string->data
    !e edx = [string->length]
    mov eax, 4
    mov ebx, 1
    int 0x80
    RETURN
END

CONST message: db = "Hello, world!", 10, 0
CONST length: dd = $ - message - 1
