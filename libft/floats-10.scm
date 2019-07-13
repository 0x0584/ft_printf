;;; Free-format algorithm for printing IEEE double-precision positive
;;; floating-point numbers in base 10

;;; It uses the floating-point logarithm to estimate the scaling factor
;;; and a table to look up powers of ten.

;;; Input to flonum->digits:
;;;		  v -- a positive floating-point number, f x 2^e
;;;		  f -- mantissa of v
;;;		  e -- exponent of v

;;; Output: (k d_1 d_2 ... d_n),
;;;	  where 0.d_1...d_n x 10^k is the shortest correctly rounded base-10
;;;	  number that rounds to v when input (it assumes the input
;;;	  routine rounds to even)

;;; See also "Printing Floating-Point Numbers Quickly and Accurately"
;;; in Proceedings of the SIGPLAN '96 Conference on Programming Language
;;; Design and Implementation.

;;; Author: Bob Burger	Date: March 1996

(define flonum->digits
  (let ([min-e -1074]
		[bp-1 (expt 2 52)])
	(lambda (v f e)
	  (let ([round? (even? f)])
		(if (>= e 0)
			(if (not (= f bp-1))
				(let ([be (expt 2 e)])
				  (scale (* f be 2) 2 be be 0 round? round? v))
				(let ([be (expt 2 e)])
				  (scale (* f be 4) 4 (* be 2) be 0 round? round? v)))
			(if (or (= e min-e) (not (= f bp-1)))
				(scale (* f 2) (expt 2 (- 1 e)) 1 1 0 round? round? v)
				(scale (* f 4) (expt 2 (- 2 e)) 2 1 0 round? round? v)))))))

(define scale
  (lambda (r s m+ m- k low-ok? high-ok? v)
	(let ([est (inexact->exact (ceiling (- (log10 v) 1e-10)))])
	  (if (>= est 0)
		  (fixup r (* s (expt10 est)) m+ m- est low-ok? high-ok?)
		  (let ([scale (expt10 (- est))])
			(fixup (* r scale) s (* m+ scale) (* m- scale)
				   est low-ok? high-ok?))))))

(define fixup
  (lambda (r s m+ m- k low-ok? high-ok?)
	(if ((if high-ok? >= >) (+ r m+) s) ; too low?
		(cons (+ k 1) (generate r s m+ m- low-ok? high-ok?))
		(cons k
			  (generate (* r 10) s (* m+ 10) (* m- 10) low-ok? high-ok?)))))

(define generate
  (lambda (r s m+ m- low-ok? high-ok?)
	(let ([d (quotient r s)]
		  [r (remainder r s)])
	  (let ([tc1 ((if low-ok? <= <) r m-)]
			[tc2 ((if high-ok? >= >) (+ r m+) s)])
		(if (not tc1)
			(if (not tc2)
				(cons d (generate (* r 10) s (* m+ 10) (* m- 10)
								  low-ok? high-ok?))
				(list (+ d 1)))
			(if (not tc2)
				(list d)
				(if (< (* r 2) s)
					(list d)
					(list (+ d 1)))))))))

(define expt10
  (let ([table (make-vector 326)])
	(do ([k 0 (+ k 1)] [v 1 (* v 10)])
		((= k 326))
	  (vector-set! table k v))
	(lambda (k)
	  (vector-ref table k))))

(define log10
  (let ([f (/ (log 10))])
	(lambda (x)
	  (* (log x) f))))
