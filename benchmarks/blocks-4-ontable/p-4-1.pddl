

(define (problem BW-rand-4)
(:domain blocksworld)
(:objects b2 b3 b4 )
(:init
(arm-empty)
(on b2 b3)
(on b3 b1)
(on b1 b4)
(on-table b4)
(clear b2)
)
(:goal
(and
(on-table b1)
)
)
)


