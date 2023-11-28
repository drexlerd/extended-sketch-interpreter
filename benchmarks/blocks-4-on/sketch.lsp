(:extended_sketch
    (:memory_states (m0))
    (:initial_memory_state m0)
    (:registers ())
    (:booleans
        (On "b_empty(c_and(c_some(r_primitive(on,0,1),c_one_of(b2)),c_one_of(b1)))")
    )
    (:numericals )
    (:concepts
        (C "c_diff(c_or(c_one_of(b1), c_one_of(b2)), c_primitive(clear, 0))")
    )
    (:search_rule (:conditions (:memory m0) (:c_c_gt C))               (:effects (:memory m0) (:e_b_bot On) (:e_c_dec C)))
    (:search_rule (:conditions (:memory m0) (:c_c_eq C) (:c_b_pos On)) (:effects (:memory m0) (:e_b_neg On) ))
)
