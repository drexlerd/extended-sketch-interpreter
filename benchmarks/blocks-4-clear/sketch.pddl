(:extended_sketch
    (:memory_states (m0 m1 m2))
    (:initial_memory_state m0)
    (:registers (r0))
    (:booleans
        (H "b_empty(c_primitive(holding,0))")
        (B "b_empty(c_and(c_register(0),c_primitive(clear,0)))")
    )
    (:numericals
        (n "n_count(c_some(r_transitive_closure(r_primitive(on,0,1)),c_register(0)))")
        (nC "n_count(c_diff(c_diff(c_primitive(clear_g,0),c_primitive(clear,0)),c_primitive(holding,0)))")
    )
    (:concepts
        (C "c_diff(c_diff(c_primitive(clear_g,0),c_primitive(clear,0)),c_primitive(holding,0))")
    )
    (:load_rule   (:conditions (:memory m0) (:c_n_gt nC)             ) (:effects (:memory m1) (:e_b_bot H) (:e_n_bot nC) (:load (r0 C))))
    (:search_rule (:conditions (:memory m1) (:c_b_neg H)             ) (:effects (:memory m1) (:e_b_pos H) (:e_n_bot n) (:e_n_bot nC)))
    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n) ) (:effects (:memory m1) (:e_b_neg H) (:e_n_dec n) (:e_b_pos B) (:e_n_bot nC)))
    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n) ) (:effects (:memory m1) (:e_b_neg H) (:e_n_dec n) (:e_b_pos B) (:e_n_dec nC)))
    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n) ) (:effects (:memory m2) (:e_b_neg H) (:e_n_dec n) (:e_b_neg B) (:e_n_dec nC)))
    (:search_rule (:conditions (:memory m2) (:c_b_neg H)             ) (:effects (:memory m0) (:e_b_pos H) (:e_n_bot n) (:e_n_bot nC)))
)
