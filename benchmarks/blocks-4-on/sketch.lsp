(:extended_sketch
    (:memory_states (m0))
    (:initial_memory_state m0 m1)
    (:registers ())
    (:booleans
        (H "b_empty(c_primitive(holding,0))")
        (On "b_empty(c_and(c_some(r_primitive(on,0,1),c_one_of(b2)),c_one_of(b1)))")
    )
    (:numericals )
    (:concepts
        (C "c_diff(c_or(c_one_of(b1), c_one_of(b2)),c_primitive(clear,0))")
        (D "c_some(r_transitive_closure(r_primitive(on,0,1)),c_or(c_one_of(b1), c_one_of(b2)))")
    )
    (:search_rule (:conditions (:memory m0) (:c_c_gt D))   (:effects (:memory m0) (:e_c_dec D) (:e_b_pos H)))
    (:search_rule (:conditions (:memory m0) (:c_b_pos On)) (:effects (:memory m1) (:e_b_neg On)))
)
