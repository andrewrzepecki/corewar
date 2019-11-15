.name "ldi"
.comment "by eviana"

start:	st r1, :data
	zjmp %:data

data:	ldi r2, :start, r2

