.code16        # use 16-bit assembly 
.global start  # tells linker where to start 

# Author: Kejian Shi
# NetID:  ks4765
# A simple guessing game on qemu-simulated xv6 BIOS real mode



# DESCRIPTION of register used:
# al: multipurpose
# cl: stores the generated number (correct answer)  (cl also for "correct line")
# si: dst for string 
# dl: flag to indicate whether to print another round of prompt
#     more explanation: when user input is not equal to the cl, it should print two messages: "Wrong!" and the prompt


#   movb $0x0E, %ah     # prepares register for BIOS print. $0x0E to %ah is to print single char
#   int $0x10     software interrupt for BIOS

# todo1: generate a random number 

start:
    movw $prompt , %si   # load the offset. Destination for string  #  Note: preparing
    movb $0x00, %ah      # 0x00 - set video mode 
    movb $0x03 , %al     # 0x03 - 80x25 text mode 
    int  $0x10          # software interrupt for BIOS ; fetch the 10 descriptor from IDT

generate:
    # according to the reference, "in" instruction uses format IN $imm8, $AL , RTC is byte 
    # 	OUT %al, $imm8	Output byte in AL to I/O port address imm8.

    xorb %al, %al 
    out  %al, $0x70  # send 0 to port 70,
    in   $0x71, %al  # fetch "second" field in CMOS RTC to al
    movb $0x0A, %ch
    div  %ch     # div 10 to get the digit 
    # Unsigned divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder.
    movb %ah, %cl    # we use cl for correct number, since ax is going to be frequently used     
    xorw %ax, %ax   

    xorb %dl, %dl    # reset %dl


output:
# todo2: write a prompt block
    lodsb 
    testb %al, %al      #check if null (end of string)
    jz look_up
    movb $0x0E, %ah         # prepare register, and trap 
    int $0x10
    jmp output

look_up:
# check if the "print_another_prompt" indicator is set
    cmp $0x1, %dl 
    je print_prompt_when_wrong
    # otherwise fall through

input: 
    xorb %ah, %ah # prepare register for BIOS read
    int $0x16 
    movb $0X0E, %ah 
    int $0x10 
    sub $0x30, %al  # the user input is a char, substract decimal 48, '0' in ASCII, to get int val
    cmp %cl, %al
    je correct


wrong: 
    #   print CR and LF 
    #   load the wrong msg , movw $wrong_msg, %si  
    movb $0xE, %ah
    movb $'\r', %al 
    int $0x10
    movb $'\n', %al
    int $0x10
    # print carrige return and line feed
    movw $wrong_msg, %si
    movb $0x01, %dl  # set our indicator to print another prompt after printing the Wrong! msg.
    jmp output


print_prompt_when_wrong:
    xorb %dl, %dl   # reset the flag, 
    movw $prompt , %si
    movb $0xE, %ah
    movb $'\r', %al 
    int $0x10
    movb $'\n', %al
    int $0x10
    # print carrige return and line feed
    jmp output    


correct:
    # mov the cursor, then print the correct message 
    # WRITING a line feed, meaning still have to PRINT 
    # !! movw $prompt, %si is just PREPARING 
    # BIOS software interrupt 10 is outputing the byte in AL !!! (have to set up ah = 0xE)
    # recall 0xE = 0x0E. (AUTO Fill) ; Because it has the ability to infer the reg size

    movb $0X0E, %ah 
    movb $'\r', %al  
    int $0x10 
    # write a carriage return (move cursor)
    movb $'\n', %al  
    int $0x10 
    # write a line feed
    movw $correct_msg, %si


correct_output:
    lodsb 
    testb %al, %al 
    jz done
    movb $0XE, %ah 
    int $0x10 
    jmp correct_output
# output the correct msg and jmp forever when done 

done:
    jmp done


# set up the data
prompt: 
    .string "What number am I thinking of (0-9)? "
wrong_msg:
    .string "Wrong!"
correct_msg:
    .string "Right! Congratulations." 


# pads out the rest of the 512 byte sector 
.fill 510 - (. - start), 1, 0 
# and put the bytes BIOS expects to see at the end 
.byte 0x55 
.byte 0xAA 


