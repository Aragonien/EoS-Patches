; ------------------------------------------------------------------------------
; CheckTSBox
; No Params
; Return Values are described in the code
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
;.definelabel XPos, 0x22A35DC ;1-254 pixels on the x-axis, in hex:  0x01-0xFE
;.definelabel YPos, 0x22A35E0 ;1-191 pixels on the y-axis, in hex:  0x01-0xBF
;.definelabel Pressed, 0x22A35E4 ; 0x00 or 0x01

; For EU
.include "lib/stdlib_eu.asm"
.definelabel ProcStartAddress, 0x022E7B88
.definelabel ProcJumpAddress, 0x022E8400
.definelabel XPos, 0x22A3F1C ;1-254, 0x01-0xFE
.definelabel YPos, 0x22A3F20 ;1-191  0x01-0xBF
.definelabel Pressed, 0x22A3F24 ; 0x00 or 0x01

; File creation
.create "./code_out.bin", 0x022E7B88 ; For US change address to: 0x022E7248
	.org ProcStartAddress
	.area MaxSize
		mov r0, #0	;Returns 0 if the screen is pressed, but no defined box is hit
		ldr r10,=Pressed
		ldrb r10,[r10]
		cmp r10,0x00
		beq @@notPressed
		ldr r4,=XPos 
		ldrb r4,[r4]
		ldr r5,=YPos
		ldrb r5,[r5]
		;Example Check 1, Checks for a 20x20 pixel box in the middle of the screen and returns 1 if the box is hit
		mov r8,0x76	; Lower X Border of the Box
		mov r9,0x8A	; Upper X Border of the Box
		mov r10,0x56; Lower Y Border of the Box
		mov r11,0x6A; Upper Y Border of the Box
		cmp r4,r8
		blt @@Check2
		cmp r4,r9
		bgt @@Check2
		cmp r5,r10
		blt @@Check2
		cmp r5,r11
		bgt @@Check2
		mov r0,#1
		b @@end
		@@Check2:


		;Add more checks with this template:
		;mov r8,0x00	; Change 0x00 to the lower pixel border on your x-axis in hex
		;mov r9,0x00	; Change 0x00 to the upper pixel border on your x-axis in hex
		;mov r10,0x00	; Change 0x00 to the lower pixel border on your y-axis in hex
		;mov r11,0x00	; Change 0x00 to the upper pixel border on your y-axis in hex
		;cmp r4,r8
		;blt @@CheckX	;replace X with a number. Every branch label has to be unique!
		;cmp r4,r9
		;bgt @@CheckX
		;cmp r5,r10
		;blt @@CheckX
		;cmp r5,r11
		;bgt @@CheckX
		;mov r0,#Y		;replace Y with your desired return value in decimal
		;b @@end
		;@@CheckX:

		b @@end
		@@notPressed:
		mov r0,#255 ;returns 255 if the screen isn't pressed
		@@end:
		b ProcJumpAddress
		.pool
	.endarea
.close
