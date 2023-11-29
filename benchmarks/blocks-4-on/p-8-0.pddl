

(define (problem BW-rand-4)
(:domain blocksworld)
(:objects b3 b4 b5 b6 b7 b8)
(:init
(arm-empty)
(on-table b1)
(on-table b2)
(on b3 b1)
(on b5 b3)
(on b7 b5)
(on b4 b2)
(on b6 b4)
(on b8 b6)
(clear b7)
(clear b8)
)
(:goal
(and
(on b1 b2))
)
)


