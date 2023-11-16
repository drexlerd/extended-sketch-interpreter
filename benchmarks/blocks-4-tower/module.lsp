(:module
    (:signature entry())
    (:extended_sketch
        (:memory_states (m0 m1 m2 m3 m4))
        (:initial_memory_state m0)
        (:registers (r0 r1))
        (:booleans )
        (:numericals )
        (:concepts
            (W "c_primitive(on-table_g,0)")
            (M "c_some(r_primitive(on_g,0,1),c_register(0))")
            (R1 "c_register(1)")
            (C "c_or(c_register(0), c_register(1))")
        )
        (:load_rule (:conditions (:memory m0) (:c_c_gt W)) (:effects (:memory m1) (:load (r0 W))))
        (:load_rule (:conditions (:memory m1) (:c_c_gt M)) (:effects (:memory m2) (:load (r1 M))))
        (:call_rule (:conditions (:memory m2))             (:effects (:memory m3) (:call clear(C))))
        (:call_rule (:conditions (:memory m3))             (:effects (:memory m4) (:call on(r1, r0))))
        (:load_rule (:conditions (:memory m4)) (:effects (:memory m1) (:load (r0 R1))))
    )
)
(:module
    (:signature clear(C))
    (:extended_sketch
        (:memory_states (m0 m1 m2))
        (:initial_memory_state m0)
        (:registers (r0))
        (:booleans
            (H "b_empty(c_primitive(holding,0))")
        )
        (:numericals
            (n "n_count(c_some(r_transitive_closure(r_primitive(on,0,1)),c_register(0)))")
        )
        (:concepts
            (D "c_diff(c_diff(c_argument(0),c_primitive(clear,0)),c_primitive(holding,0))")
        )
        (:load_rule   (:conditions (:memory m0) (:c_c_gt D))              (:effects (:memory m1) (:e_b_bot H) (:e_c_bot D) (:load (r0 D))))
        (:search_rule (:conditions (:memory m0) (:c_b_neg H))             (:effects (:memory m2) (:e_b_pos H) (:e_n_bot n) (:e_c_bot D)))
        (:search_rule (:conditions (:memory m0) (:c_c_eq D))              (:effects (:memory m2)))

        (:search_rule (:conditions (:memory m1) (:c_b_neg H))             (:effects (:memory m1) (:e_b_pos H) (:e_n_bot n) (:e_c_bot D)))
        (:search_rule (:conditions (:memory m1) (:c_b_neg H))             (:effects (:memory m1) (:e_b_pos H) (:e_n_bot n) (:e_c_dec D)))

        (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n)) (:effects (:memory m1) (:e_b_neg H) (:e_n_dec n) (:e_c_bot D)))
        (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n)) (:effects (:memory m1) (:e_b_neg H) (:e_n_dec n) (:e_c_inc D)))
        (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n)) (:effects (:memory m1) (:e_b_neg H) (:e_n_dec n) (:e_c_dec D) (:e_n_gt n)))
        (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n)) (:effects (:memory m0) (:e_b_neg H) (:e_n_dec n) (:e_c_dec D) (:e_n_eq n)))
    )
)
(:module
    (:signature on(B1, B2))
    (:extended_sketch
        (:memory_states (m0 m1 m2 m3 m4))
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
        (:search_rule (:conditions (:memory m3) (:c_b_pos On)) (:effects (:memory m4) (:e_b_neg On) ))
    )
)
