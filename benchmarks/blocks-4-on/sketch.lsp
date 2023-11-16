(:extended_sketch
    (:memory_states (m0 m1 m2 m3))
    (:initial_memory_state m0)
    (:registers (r0 r1))
    (:booleans
        (On "b_empty(c_and(c_some(r_primitive(on,0,1),c_one_of(b2)),c_one_of(b1)))")
    )
    (:numericals )
    (:concepts
        (X "c_one_of(b1)")
        (Y "c_one_of(b2)")
        (C "c_diff(c_or(c_one_of(b1), c_one_of(b2)), c_primitive(clear, 0))")
    )
    (:load_rule   (:conditions (:memory m0) (:c_c_gt X))   (:effects (:memory m1) (:e_c_bot C) (:load (r0 X))))
    (:load_rule   (:conditions (:memory m1) (:c_c_gt Y))   (:effects (:memory m2) (:e_c_bot C) (:load (r1 Y))))
    (:search_rule (:conditions (:memory m2) (:c_c_gt C))   (:effects (:memory m2) (:e_b_bot On) (:e_c_dec C)))
    (:search_rule (:conditions (:memory m2) (:c_c_eq C))   (:effects (:memory m3)))
    (:search_rule (:conditions (:memory m3) (:c_b_pos On)) (:effects (:memory m3) (:e_b_neg On) ))
)
