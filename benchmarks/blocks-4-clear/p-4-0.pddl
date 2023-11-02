

(define (problem BW-rand-4)
(:domain blocksworld)
(:objects b1 b2 b3 b4 )
(:init
(arm-empty)
(on b4 b3)
(on b3 b2)
(on b2 b1)
(on-table b1)
(clear b4)
)
(:goal
(and
(clear b1)
(clear b4)
)
)
)


