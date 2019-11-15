.name "ldi"
.comment "by eviana"

start:	st r1, :data 	# stock la valeur du registre en premier par
			# et le met dans le 2eme param
	zjmp %:load

pause:	live %0

load:	ldi r2, %:start, r2 	# additionnes les 2 premiers, en fait
				# une addr et met dans le 3 eme

store:	sti r2, r1, %10	# additionne les 2 derniers, trouve addresse
			# et y copie le 1er

data:	live %0
