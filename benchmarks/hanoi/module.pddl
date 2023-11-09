(:module
    (:signature entry())
    (:extended_sketch
        (:memory_states (m0 m1 m2 m3 m4 m5))
        (:initial_memory_state m0)
        (:registers (r0 r1 r2 r3))
        (:booleans )
        (:numericals
            (nP1 "n_count(c_one_of(peg1))")
            (nP2 "n_count(c_one_of(peg2))")
            (nP3 "n_count(c_one_of(peg3))")
            (nL "n_count(c_some(r_primitive(next,0,1),c_one_of(peg1)))"))
        (:concepts
            (P1 "c_one_of(peg1)")
            (P2 "c_one_of(peg2)")
            (P3 "c_one_of(peg3)")
            (L "c_some(r_primitive(next,0,1),c_one_of(peg1))")
        )
        (:load_rule   (:conditions (:memory m0) (:c_n_gt nL) ) (:effects (:memory m1) (:load (r0 L))))
        (:load_rule   (:conditions (:memory m1) (:c_n_gt nP1)) (:effects (:memory m2) (:load (r1 P1))))
        (:load_rule   (:conditions (:memory m2) (:c_n_gt nP2)) (:effects (:memory m3) (:load (r2 P2))))
        (:load_rule   (:conditions (:memory m3) (:c_n_gt nP3)) (:effects (:memory m4) (:load (r3 P3))))
        (:call_rule   (:conditions (:memory m4))              (:effects (:memory m5) (:call hanoi(:register r0, :register r1, :register r2, :register r3))))
    )
)
(:module
    (:signature hanoi(:register r0, :register r1, :register r2, :register r3))
    (:extended_sketch
        (:memory_states (m0 m1 m2 m3 m4))
        (:initial_memory_state m0)
        (:registers (r4))
        (:booleans )
        (:numericals
            (nS "n_count(c_some(r_primitive(next,0,1),c_register(0)))")
        )
        (:concepts
            (S "c_some(r_primitive(next,0,1),c_register(0))")
        )
        (:load_rule   (:conditions (:memory m0) (:c_n_gt nS)             ) (:effects (:memory m1) (:load (r4 S))))
        (:call_rule (:conditions (:memory m1) ) (:effects (:memory m2) (:call hanoi(:register r4, :register r1, :register r3, :register r2))))
        (:call_rule (:conditions (:memory m2) ) (:effects (:memory m3) (:call hanoi(:register r4, :register r1, :register r3, :register r2))))

        (:action_rule (:conditions (:memory m2)             ) (:effects (:memory m3) (:action move(:register r0, :register r1, :register r2))))
    )
)