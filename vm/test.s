.name "test"
.comment "yolo"

		live %42
		st r1, 6
code:	live %42
		ld   %917504,r12		#7	
		ld   %1,r11			#7
		ld   %6,r10			#7
		ldi  %4, %:code, r15 		#set des octets 5-8
		lldi  %4, %:code, r15 		#set des octets 5-8
		live %12
		add r16, r16, r16
		zjmp %:code 
