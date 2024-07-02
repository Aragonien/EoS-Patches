; ------------------------------------------------------------------------------
; SaveStylusPosToPosVars
; Made to be used in combination with CheckPosVarsWithStylus and needs the screen to be pressed when called to work
; Param 1: 0-2 (the Index of the POSITION_X and POSITION_Y variables you want to write to)
; Returns: 1 while saving the position, 2 as an "exit" value after storing the last position when the screen is being released, 62 if Param 1 is out of the defined range of 0-2
; For checking for Actor/Object positions, the camera has to be on the top left (default position), else the Actor/Object positions are outside the max. touchscreen values
; Made by Argonien
; ------------------------------------------------------------------------------

.relativeinclude on
.nds
.arm

.definelabel MaxSize, 0x810

; Uncomment/comment the following labels depending on your version.

; For US
;.include "lib/stdlib_us.asm"
;.definelabel ProcStartAddress, 0x022E7248
;.definelabel ProcJumpAddress, 0x022E7AC0
;.definelabel XPos, 0x22A35DC 
;.definelabel YPos, 0x22A35E0 
;.definelabel Pressed, 0x22A35E4 
;.definelabel LoadScriptVariableValueAtIndex, 0x204B678
;.definelabel SaveScriptVariableValueAtIndex, 0x204B988
;.definelabel LastXPosAfterDrag, 0x22A35FC
;.definelabel LastYPosAfterDrag, 0x22A35E4

; For EU
.include "lib/stdlib_eu.asm"
.definelabel ProcStartAddress, 0x022E7B88
.definelabel ProcJumpAddress, 0x022E8400
.definelabel XPos, 0x22A3F1C 
.definelabel YPos, 0x22A3F20 
.definelabel Pressed, 0x22A3F24 
.definelabel LoadScriptVariableValueAtIndex, 0x204B9B0
.definelabel SaveScriptVariableValueAtIndex, 0x204BCC0
.definelabel LastXPosAfterDrag, 0x22A3F3C
.definelabel LastYPosAfterDrag, 0x22A3F40


; File creation
.create "./code_out.bin", 0x022E7B88 ; For US change address to: 0x022E7248
	.org ProcStartAddress
	.area MaxSize
		ldr r10,=Pressed
		ldrb r10,[r10]
		cmp r10,0x00
		beq @@stopMovement
		ldr r4,=XPos 
		ldrb r4,[r4]
		ldr r5,=YPos
		ldrb r5,[r5]
		mov r1, #256
		mul r4, r4, r1
		mul r5, r5, r1
		cmp r7, #0
		beq @@Write_Pos0
		cmp r7, #1
		beq @@Write_Pos1
		cmp r7, #2
		beq @@Write_Pos2
		mov r0,#62
		b @@end
		@@Write_Pos0:
		mov r1,0x58
		mov r2, #0
		mov r3, r4
		bl SaveScriptVariableValueAtIndex
		mov r1,0x59
		mov r2, #0
		mov r3, r5
		bl SaveScriptVariableValueAtIndex
		mov r0, #1
		b @@end
		@@Write_Pos1:
		mov r1,0x58
		mov r2, #1
		mov r3, r4
		bl SaveScriptVariableValueAtIndex
		mov r1,0x59
		mov r2, #1
		mov r3, r5
		bl SaveScriptVariableValueAtIndex
		mov r0, #1
		b @@end
		@@Write_Pos2:
		mov r1,0x58
		mov r2, #2
		mov r3, r4
		bl SaveScriptVariableValueAtIndex
		mov r1,0x59
		mov r2, #2
		mov r3, r5
		bl SaveScriptVariableValueAtIndex
		mov r0, #1
		b @@end
		@@stopMovement:
		ldr r4,=LastXPosAfterDrag 
		ldrb r4,[r4]
		ldr r5,=LastYPosAfterDrag
		ldrb r5,[r5]
		mov r1, #256
		mul r4, r4, r1
		mul r5, r5, r1
		mov r1,0x58
		mov r2, #0
		mov r3, r4
		bl SaveScriptVariableValueAtIndex
		mov r1,0x59
		mov r2, #0
		mov r3, r5
		bl SaveScriptVariableValueAtIndex
		mov r0, #2
		@@end:
		b ProcJumpAddress
		.pool
	.endarea
.close
