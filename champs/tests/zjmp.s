.name "zjmp"
.comment "by eviana"

debut:
	zjmp	%:debut2

debut2:
	zjmp	%:debut3

debut3:
	st	r1, :debut2
