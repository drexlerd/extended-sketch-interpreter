

(define (problem BW-rand-4)
(:domain blocksworld)
(:objects b3 b4 )
(:init
(holding b3)
(on-table b1)
(on-table b2)
(on b4 b2)
(clear b1)
(clear b3)
(clear b4)
)
(:goal
(and
(on b1 b2))
)
)


