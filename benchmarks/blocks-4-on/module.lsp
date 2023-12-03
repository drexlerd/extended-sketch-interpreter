(:module
    (:signature on_entry())
    (:extended_sketch
        (:memory_states (m0))
        (:initial_memory_state m0)
        (:registers )
        (:booleans )
        (:numericals )
        (:concepts
            (B1 "c_one_of(b1)")
            (B2 "c_one_of(b2)")
        )
        (:roles )
        (:call_rule (:conditions (:memory m0)) (:effects (:memory m0) (:call on((:concepts (B1 B2))))))
    )
)
(:module
    (:signature on((:concepts (B1 B2))))
    (:extended_sketch
        (:memory_states (m0 m1))
        (:initial_memory_state m0)
        (:registers (r0 r1))
        (:booleans
            (On "b_empty(c_and(c_some(r_primitive(on,0,1),c_argument(1)),c_argument(0)))")
        )
        (:numericals )
        (:concepts
            (D "c_some(r_transitive_closure(r_primitive(on,0,1)),c_or(c_argument(0), c_argument(1)))")
        )
        (:search_rule (:conditions (:memory m0) (:c_c_gt D))   (:effects (:memory m0) (:e_b_bot On) (:e_c_dec D)))
        (:search_rule (:conditions (:memory m0) (:c_c_eq D) (:c_b_pos On)) (:effects (:memory m1) (:e_b_neg On)))
    )
)
