.name "yolo"
.comment "swag 22"

#tb:	add r1,r2,r3

hello: live %42

and %42, %62, r2
or r2, %10, r3
xor r3, %2, r4
and r4, r5, r5
xor r1, %-1, r8 
or r8, r9, r10
and %42, r5, r2
#and %42, r6, r2
#and %42, r7, r2
#and %42, r8, r2
#and %42, r9, r2


#and %42, %:hello, r2
#and %42, %:hello, r2
#and %42, %:hello, r2


#and r1, %0, r2 # reg en 1er = 0
#and r2, %0, r2


#and r9, %0, r2 # reg en 1er = 0
#and r3, %0, r2

#and r9, %12, r2 # reg en 1er = 0
#and r3, %189745, r2


#and %42, r5, r2
#and %42, r11, r2
#or r1, %0, r3
#xor r1, %0, r4

tg: live %42

#and %1, %2, r5
#and r1, r2, r6
#			%10, r1, r7
#			and %32, %48, r8
#			and %32, %48, r9


tw:fork %:tg
	zjmp %:hello
