include 'proc32.inc'

macro END {
}

ENDS fix }

macro MEMBER line& {
    local matched
    match name:type,line \{
        matched equ 1
        .\#name type ?
    \}
    if ~defined matched
        display "Error: Invalid member definition"
        err
    end if
}

macro STRUCT sname {
    struc sname \{
}

macro FN line& {
    local matched
    match fname=(=), line \{
        matched equ 1
        proc fname
    \}
    match fname=(fargs=), line \{
        matched equ 1
        proc fname fargs
    \}
    if ~defined matched
        display "Error: Invalid function definition"
        err
    end if
    macro END \{
        RETURN
        endp
    \}
}

macro .. line& {
    ; skip line ;
}

macro CONST line& {
    match name=:class==value, line \{
        name class value
    \}
}


macro !e line& {
    local matched
    local matched2
    match d==s, line \{
        matched equ 1
        match this=-=>member, s \\{
            matched2 equ 1
            mget d, \\this\\#.\\#member
        \\}
        match this=-=>=[member=], s \\{
            matched2 equ 1
            mget d, [\\#this\\#.\\#member]
        \\}
        if ~defined matched2
            mov d, s
        end if
    \}
    if ~defined matched
        display "Error: Invalid expression"
        err
    end if
}

macro CALL line& {
    local matched
    match fname=(fargs=), line \{
        matched equ 1
        ccall fname, fargs
    \}
    if ~defined matched
        call line
    end if
}

macro RETURN line:0 {
    if ~line eq
        mov eax, line
    end if
    leave
    ret
}

macro FOR line& {
    local matched
    macro END \{
        __finish__:
    \}
    match =(vardef=,cond=,inline=), line \{
        matched = 1
        jmp __next__
        vardef
        __iter__:
        inline
        __next__:
        parsecond __exec__ __finish__
        __exec__:
    \}
    if ~defined matched
        display "Error: Invalid for loop"
        err
    end if
}
