IFDEF PLATFORM_WINDOWS_X86_64
PUBLIC bdDebugBreak_x86_64

.CODE

bdDebugBreak_x86_64 PROC

; To continue, strike the F10 key twice
; Look at the previous call in the Call Stack window to see where you are
INT 3
RET

bdDebugBreak_x86_64 ENDP

ENDIF
END

