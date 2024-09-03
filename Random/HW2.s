	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 1	sdk_version 11, 1
	.globl	_main                   ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16             ; =16
	.cfi_def_cfa_offset 16
	str	wzr, [sp, #12]
	str	wzr, [sp, #8]
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #8]
	cmp	w8, #1024               ; =1024
	b.ge	LBB0_4
; %bb.2:                                ;   in Loop: Header=BB0_1 Depth=1
	ldrsw	x8, [sp, #8]
	adrp	x9, _vec@GOTPAGE
	ldr	x9, [x9, _vec@GOTPAGEOFF]
	ldrb	w10, [x9, x8]
	adrp	x8, _result@PAGE
	add	x8, x8, _result@PAGEOFF
	ldr	w11, [x8]
	add	w10, w11, w10
	str	w10, [x8]
; %bb.3:                                ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #8]
	add	w8, w8, #1              ; =1
	str	w8, [sp, #8]
	b	LBB0_1
LBB0_4:
	ldr	w0, [sp, #12]
	add	sp, sp, #16             ; =16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_result                 ; @result
.zerofill __DATA,__common,_result,4,2
	.comm	_vec,1024,0             ; @vec
.subsections_via_symbols
