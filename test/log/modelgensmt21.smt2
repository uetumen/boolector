(set-logic QF_BV)
(declare-fun v1 () (_ BitVec 2))
(declare-fun v2 () (_ BitVec 6))
(declare-fun v3 () (_ BitVec 2))
(declare-fun v4 () (_ BitVec 6))
(define-fun $e5 () (_ BitVec 8) (concat v1 v2))
(define-fun $e6 () (_ BitVec 8) (concat v3 v4))
(define-fun $e7 () (_ BitVec 2) (bvudiv v3 v1))
(define-fun $e8 () (_ BitVec 8) (bvudiv $e6 $e5))
(define-fun $e9 () (_ BitVec 2) ((_ extract 7 6) $e8))
(define-fun $e10 () (_ BitVec 1) (ite (bvult $e7 $e9) #b1 #b0))
(assert (not (= (bvnot $e10) #b0)))
(check-sat)
(exit)
