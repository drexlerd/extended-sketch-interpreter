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
        (D "c_diff(c_diff(c_primitive(clear_g,0),c_primitive(clear,0)),c_primitive(holding,0))")
    )
    (:load_rule   (:conditions (:memory m0) (:c_c_gt D))              (:effects (:memory m1) (:e_b_bot H) (:e_c_bot D) (:load (r0 D))))
    (:search_rule (:conditions (:memory m0) (:c_b_neg H))             (:effects (:memory m0) (:e_b_pos H) (:e_n_bot n) (:e_c_bot D)))

    (:search_rule (:conditions (:memory m1) (:c_b_neg H))             (:effects (:memory m1) (:e_b_pos H) (:e_n_bot n) (:e_c_bot D)))
    (:search_rule (:conditions (:memory m1) (:c_b_neg H))             (:effects (:memory m1) (:e_b_pos H) (:e_n_bot n) (:e_c_dec D)))

    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n)) (:effects (:memory m1) (:e_b_neg H) (:e_n_dec n) (:e_c_bot D)))
    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n)) (:effects (:memory m1) (:e_b_neg H) (:e_n_dec n) (:e_c_inc D)))
    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n)) (:effects (:memory m1) (:e_b_neg H) (:e_n_dec n) (:e_c_dec D) (:e_n_gt n)))
    (:search_rule (:conditions (:memory m1) (:c_b_pos H) (:c_n_gt n)) (:effects (:memory m0) (:e_b_neg H) (:e_n_dec n) (:e_c_dec D) (:e_n_eq n)))
)
