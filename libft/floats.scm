;;; Fully general free-format algorithm for positive floating-point numbers

;;; It uses the floating-point logarithm to estimate the scaling factor
;;; and a table to look up powers of ten.

;;; Input to flonum->digits:
;;;		  v -- a positive floating-point number, f x b^e
;;;		  f -- mantissa of v
;;;		  e -- exponent of v
;;;	  min-e -- smallest representable exponent
;;;		  p -- fixed size of mantissa
;;;		  b -- input base (usually two)
;;;		 ob -- output base (usually ten)

;;; Output: (k d_1 d_2 ... d_n),
;;;	  where 0.d_1...d_n x ob^k is the shortest correctly rounded base-ob
;;;	  number that rounds to v when input (it does not assume any particular
;;;	  input rounding algorithm)

;;; See also "Printing Floating-Point Numbers Quickly and Accurately"
;;; in Proceedings of the SIGPLAN '96 Conference on Programming Language
;;; Design and Implementation.

;;; Author: Bob Burger	Date: March 1996

(define flonum->digits
  (lambda (v f e min-e p b ob)
	(if (>= e 0)
		(if (not (= f (expt b (- p 1))))
			(let ([be (expt b e)])
			  (scale (* f be 2) 2 be be 0 ob #f #f v))
			(let* ([be (expt b e)] [be1 (* be b)])
			  (scale (* f be1 2) (* b 2) be1 be 0 ob #f #f v)))
		(if (or (= e min-e) (not (= f (expt b (- p 1)))))
			(scale (* f 2) (* (expt b (- e)) 2) 1 1 0 ob #f #f v)
			(scale (* f b 2) (* (expt b (- 1 e)) 2)
				   b 1 0 ob #f #f v)))))

(define scale
  (lambda (r s m+ m- k ob low-ok? high-ok? v)
	(let ([est (inexact->exact (ceiling (- (logB ob v) 1e-10)))])
	  (if (>= est 0)
		  (fixup r (* s (exptt ob est)) m+ m- est ob low-ok? high-ok?)
		  (let ([scale (exptt ob (- est))])
			(fixup (* r scale) s (* m+ scale) (* m- scale)
				   est ob low-ok? high-ok?))))))

(define fixup
  (lambda (r s m+ m- k ob low-ok? high-ok?)
	(if ((if high-ok? >= >) (+ r m+) s) ; too low?
		(cons (+ k 1) (generate r s m+ m- ob low-ok? high-ok?))
		(cons k
			  (generate (* r ob) s (* m+ ob) (* m- ob) ob low-ok? high-ok?)))))

(define generate
  (lambda (r s m+ m- ob low-ok? high-ok?)
	(let ([d (quotient r s)]
		  [r (remainder r s)])
	  (let ([tc1 ((if low-ok? <= <) r m-)]
			[tc2 ((if high-ok? >= >) (+ r m+) s)])
		(if (not tc1)
			(if (not tc2)
				(cons d (generate (* r ob) s (* m+ ob) (* m- ob)
								  ob low-ok? high-ok?))
				(list (+ d 1)))
			(if (not tc2)
				(list d)
				(if (< (* r 2) s)
					(list d)
					(list (+ d 1)))))))))

(define exptt
  (let ([table (make-vector 326)])
	(do ([k 0 (+ k 1)] [v 1 (* v 10)])
		((= k 326))
	  (vector-set! table k v))
	(lambda (B k)
	  (if (and (= B 10) (<= 0 k 325))
		  (vector-ref table k)
		  (expt B k)))))

(define logB
  (let ([table (make-vector 37)])
	(do ([B 2 (+ B 1)])
		((= B 37))
	  (vector-set! table B (/ (log B))))
	(lambda (B x)
	  (if (<= 2 B 36)
		  (* (log x) (vector-ref table B))
		  (/ (log x) (log B))))))
