(:extended_sketch
    (:memory_states (m0 m1 m2))
    (:initial_memory_state m0)
    (:registers (r0))
    (:booleans
        (H "b_empty(c_primitive(holding,0))")
    )
    (:numericals
        (n "n_count(c_some(r_transitive_closure(r_primitive(on,0,1)),c_register(0)))")
        (nC "n_count(c_diff(c_primitive(clear,0),c_primitive(clear_g,0)))")
    )
    (:concepts
        (C "c_diff(c_primitive(clear,0),c_primitive(clear_g,0))")
    )
    (:load_rule   (:conditions (:memory m0) (:c_n_gt nC)             ) (:effects (:memory m1) (:load (r0 C) (:c_n_unk n))))
    (:search_rule (:conditions (:memory m1) (:c_b_neg H)             ) (:effects (:memory m1) (:c_b_pos H)))
    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n) ) (:effects (:memory m1) (:c_b_neg H) (:c_n_dec n)))
    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n) ) (:effects (:memory m2) (:c_b_neg H) (:c_n_dec n) (:c_n_dec nC)))
    (:search_rule (:conditions (:memory m2) (:c_b_neg H)             ) (:effects (:memory m0) (:c_b_pos H)))
)
