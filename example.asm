format ELF executable 3

include "objfasm32.inc"

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
    ! esp & 0xFFFFFFF0
    CALL main(0, 0)
    ! ebx = eax
    ! eax = 1
    int 0x80

FN main(argc, argv)
    CALL print(message, [length])
    RETURN 0
END

FN print(string)
    virtual at string
        string_ str
    end virtual
    ! ecx = string->data
    ! edx = string->length
    ! edx = [edx]
    mov eax, 4
    mov ebx, 1
    int 0x80
    RETURN
END

CONST message: db = "Hello, world!", 10, 0
CONST length: dd = $ - message - 1
