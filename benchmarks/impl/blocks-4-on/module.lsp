(:module
    (:signature on_entry())
    (:extended_sketch
        (:memory_states (m0))
        (:initial_memory_state m0)
        (:registers ())
        (:booleans )
        (:numericals )
        (:concepts
            (B1 "c_one_of(b1)")
            (B2 "c_one_of(b2)")
        )
        (:call_rule (:conditions (:memory m0)) (:effects (:memory m0) (:call on(B1, B2))))
    )
)
(:module
    (:signature on(B1, B2))
    (:extended_sketch
        (:memory_states (m0 m1 m2 m3))
        (:initial_memory_state m0)
        (:registers (r0 r1))
        (:booleans
            (On "b_empty(c_and(c_some(r_primitive(on,0,1),c_argument(1)),c_argument(0)))")
        )
        (:numericals )
        (:concepts
            (C "c_diff(c_or(c_argument(0), c_argument(1)), c_primitive(clear, 0))")
        )
        (:load_rule   (:conditions (:memory m0) (:c_c_gt B1))  (:effects (:memory m1) (:e_c_bot C) (:load (r0 B1))))
        (:load_rule   (:conditions (:memory m1) (:c_c_gt B2))  (:effects (:memory m2) (:e_c_bot C) (:load (r1 B2))))
        (:search_rule (:conditions (:memory m2) (:c_c_gt C))   (:effects (:memory m2) (:e_b_bot On) (:e_c_dec C)))
        (:search_rule (:conditions (:memory m2) (:c_c_eq C))   (:effects (:memory m3)))
        (:search_rule (:conditions (:memory m3) (:c_b_pos On)) (:effects (:memory m3) (:e_b_neg On) ))
    )
)
