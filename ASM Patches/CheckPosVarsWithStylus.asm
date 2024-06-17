; ------------------------------------------------------------------------------
; CheckPosVarsWithStylus
; This patch checks if the stylus position is close to positions stored in all indexes of POSITION_X and POSITION_Y when the screen is pressed
; No Params
; Returns: 255 = Screen not pressed, 128 = Screen pressed, but not close to any values,
; 0 = Stylus pos close to index 0 of pos vars, 1 = Stylus pos close to index 1 of pos vars, 2 = Stylus pos close to index 2 of pos vars
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

; For EU
.include "lib/stdlib_eu.asm"
.definelabel ProcStartAddress, 0x022E7B88
.definelabel ProcJumpAddress, 0x022E8400
.definelabel XPos, 0x22A3F1C 
.definelabel YPos, 0x22A3F20 
.definelabel Pressed, 0x22A3F24 
.definelabel LoadScriptVariableValueAtIndex, 0x204B9B0
.definelabel SaveScriptVariableValueAtIndex, 0x204BCC0

; File creation
.create "./code_out.bin", 0x022E7B88 ; For US change address to: 0x022E7248
	.org ProcStartAddress
	.area MaxSize
		ldr r10,=Pressed
		ldrb r10,[r10]
		cmp r10,0x00
		beq @@notPressed
		ldr r4,=XPos 
		ldrb r4,[r4]
		ldr r5,=YPos
		ldrb r5,[r5]
		mov r1, #256
		mul r4, r4, r1
		mul r5, r5, r1
		mov r1,0x58
		mov r2,#0
		bl LoadScriptVariableValueAtIndex 
		mov r6, r0
		mov r1,0x59
		mov r2,#0
		bl LoadScriptVariableValueAtIndex 
		mov r7, r0
		sub r8, r6, #2560
		add r9, r6, #2560
		sub r10, r7, #5120
		mov r11, r7
		add r11, r11, #1280
		cmp r4, r8
		blt @@CheckXY1
		cmp r4, r9
		bgt @@CheckXY1
		cmp r5, r10
		blt @@CheckXY1
		cmp r5, r11
		bgt @@CheckXY1
		mov r0,#0
		b @@end
		@@CheckXY1:
		mov r1,0x58
		mov r2,#1
		bl LoadScriptVariableValueAtIndex
		mov r6, r0
		mov r1,0x59
		mov r2,#1
		bl LoadScriptVariableValueAtIndex 
		mov r7, r0
		sub r8, r6, #2560
		add r9, r6, #2560
		sub r10, r7, #5120
		mov r11, r7
		add r11, r11, #1280
		cmp r4, r8
		blt @@CheckXY2
		cmp r4, r9
		bgt @@CheckXY2
		cmp r5, r10
		blt @@CheckXY2
		cmp r5, r11
		bgt @@CheckXY2
		mov r0,#1
		b @@end
		@@CheckXY2:
		mov r1,0x58
		mov r2,#2
		bl LoadScriptVariableValueAtIndex 
		mov r6, r0
		mov r1,0x59
		mov r2,#2
		bl LoadScriptVariableValueAtIndex 
		mov r7, r0
		sub r8, r6, #2560
		add r9, r6, #2560
		sub r10, r7, #5120
		mov r11, r7
		add r11, r11, #1280
		cmp r4, r8
		blt @@missed
		cmp r4, r9
		bgt @@missed
		cmp r5, r10
		blt @@missed
		cmp r5, r11
		bgt @@missed
		mov r0,#2
		b @@end
		@@missed:
		mov r0,#128
		b @@end
		@@notPressed:
		mov r0,#255
		@@end:
		b ProcJumpAddress
		.pool
	.endarea
.close
