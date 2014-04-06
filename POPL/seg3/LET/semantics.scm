#lang eopl
;; Semantic interpreter for CORE
(provide  (all-defined-out))
(require "syntax.scm")
(require "data-structures.scm")
;; 
;; (execute ...) takes an abstract syntax representation of a program,
;; and returns its Expressed Value
;;
(define (execute prog)
  (cases program prog
    (a-program (exp) (value-of exp))
  )
)
;;
;; (value-of ...) takes an abstract syntax representation of an expression
;; and returns its Expressed Value

(define root-scope '())

;; ** Requires editing the ???s **
(define (value-of expr)                     
  (cases expression expr    
    (const-exp (num) (number-ExpVal num))
    (zero?-exp (exp)
               (apply-unary-op zero? exp)
    )
    (if-exp (test true-exp false-exp)
         (if (ExpVal->bool (value-of test))
                  (value-of true-exp)         
                  (value-of false-exp)       
         ) 
    )
    (equal-exp (x-exp y-exp)
               (apply-binary-op equal? x-exp y-exp))
    (greater-exp (x-exp y-exp)
              (apply-binary-op > x-exp y-exp))
    (less-exp (x-exp y-exp)
                (apply-binary-op < x-exp y-exp))
    (diff-exp (x-exp y-exp)
                (apply-binary-op - x-exp y-exp))
    (eval-exp (varname-exp) 
                (if (assoc (value-of varname-exp) root-scope)
                    (cdr (assoc (value-of varname-exp) root-scope)) 
                    (eopl:error '->ExpVal "~s is undefined in this scope" (value-of varname-exp))))
    (assign-exp (varname-exp x-exp)
                (if (member (value-of varname-exp) root-scope)
                    (set! root-scope (append '((value-of varname-exp) (value-of x-exp)) root-scope)) 
                    (set! !!!replace current value with new value!!!))
                (value-of x-exp))
  )
 
)


(define (apply-binary-op func exp1 exp2)
  (->ExpVal (func (<-ExpVal (value-of exp1)) (<-ExpVal (value-of exp2)))))
(define (apply-unary-op func exp)
  (->ExpVal (func (<-ExpVal (value-of exp)))))


