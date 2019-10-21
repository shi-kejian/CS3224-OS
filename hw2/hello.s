.code16        # use 16-bit assembly 
.global start  # tells linker where to start 


start:
    movw $message , %si  # load the offset? What is offset, si is a 2 bytes 
    movb $0x00, %ah      # 0x00 - set video mode 
    movb $0x03 , %al     # 0x03 - 80x25 text mode 
    int  $0x10          # fetch the descriptor from IDT, software interrupt for BIOS 
print_char:
    lodsb               # loads a single byte from (%si) in to %al and increment %si
    testb %al, %al      # checks if the byte is 0, 说明null ! 
    je done             # if equal jump to done 
    movb $0x0E, %ah     # prepares register for BIOS print. $0x0E to %ah is single char
    int $0x10            # software interrupt for BIOS 
    jmp print_char      # 
# It's actually  pretty easy, print byte by byte. prepare reg, trap, and print 


done: 
    jmp done            # loop forever, stop

# The .string command inserts an ASCII string with a  null terminator
message: 
    .string "Hello world" 


# pads out the rest of the 512 byte sector 
.fill 510 - (. - start), 1, 0 
# and put the bytes BIOS expects to see at the end 
.byte 0x55 
.byte 0xAA 




