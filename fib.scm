(define (f x) 
	(if (equal? x 0) 0
		(if (equal? x 1) 1
			(+ (f (- x 1)) (f (- x 2)))
		)
	)
)

(display (f 0))
(display (f 1))
(display (f 2))
(display (f 3))
(display (f 4))
(display (f 5))
(display (f 6))