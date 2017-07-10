;
; file - vector.S
; author - Harlan J. Waldrop <root@aboyandhisgnu.org>
;

.SECTION .vectors
.ORG 0x00000

p_vector_table:
	;	Function		Addr.	Def.
	JMP	p_init_stack		; $00	reset

.ORG 0x0068

.SECTION .text

p_init_stack:
	rjmp	g_start
