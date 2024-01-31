

(define (problem BW-rand-4)
(:domain blocksworld)
(:objects b1 b2 b3 )
(:init
(arm-empty)
(on b2 b3)
(on-table b1)
(on-table b3)
(clear b1)
(clear b2)
)
(:goal
(and
(on b1 b2)
)
)
)


