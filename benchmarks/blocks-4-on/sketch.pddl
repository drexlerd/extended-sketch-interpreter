(:extended_sketch
    (:memory_states (m0 m1 m2 m3))
    (:initial_memory_state m0)
    (:registers (r0 r1))
    (:booleans
        (On "b_empty(r_and(r_primitive(on,0,1),r_primitive(on_g,0,1)))")
    )
    (:numericals
        (nX "n_count(c_one_of(b1))")
        (nY "n_count(c_one_of(b2))")
        (nC "n_count(c_diff(c_or(c_one_of(b1), c_one_of(b2)), c_primitive(clear, 0)))")
    )
    (:concepts
        (X "c_one_of(b1)")
        (Y "c_one_of(b2)")
        (C "c_diff(c_or(c_one_of(b1), c_one_of(b2)), c_primitive(clear, 0))")
    )
    (:load_rule   (:conditions (:memory m0) (:c_n_gt nX)             ) (:effects (:memory m1) (:e_n_bot nC) (:load (r0 X))))
    (:load_rule   (:conditions (:memory m1) (:c_n_gt nY)             ) (:effects (:memory m2) (:e_n_bot nC) (:load (r1 Y))))
    (:search_rule (:conditions (:memory m2) (:c_n_gt nC)            ) (:effects (:memory m2) (:e_b_bot On) (:e_n_dec nC)))
    (:load_rule   (:conditions (:memory m2) (:c_n_eq nC)            ) (:effects (:memory m3) (:e_b_bot On) (:e_n_bot nC) (:load (r0 X))))
    (:search_rule (:conditions (:memory m3) (:c_b_pos On)           ) (:effects (:memory m3) (:e_b_neg On) ))
)
