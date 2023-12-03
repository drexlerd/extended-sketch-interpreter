

(define (problem BW-2-tower-reverse-middle-block-exchanged)
(:domain blocksworld)
(:objects b1 b2 b3 b4 b5 b6 )
(:init
(arm-empty)
(on b3 b5)
(on b5 b1)
(on-table b1)
(clear b3)
(on b6 b2)
(on b2 b4)
(on-table b4)
(clear b6)
)
(:goal
(and
(on b1 b2)
(on b2 b3)
(on b4 b5)
(on b5 b6)
)
)
)


