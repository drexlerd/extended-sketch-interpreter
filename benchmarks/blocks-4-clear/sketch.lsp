(:extended_sketch
    (:memory_states (m0 m1 m2 m3 m4))
    (:initial_memory_state m0)
    (:registers (r0 r1))
    (:booleans
        (H "b_empty(c_primitive(holding,0))")
        (A "b_empty(c_and(c_some(r_transitive_closure(r_primitive(on,0,1)),c_primitive(clear_g,0)),c_register(1)))")
    )
    (:numericals )
    (:concepts
        (N "c_diff(c_primitive(clear_g,0),c_primitive(clear,0))")
        (T "c_and(c_some(r_transitive_closure(r_primitive(on,0,1)),c_register(0)),c_primitive(clear,0))")
    )
    (:search_rule (:conditions (:memory m0) (:c_b_neg H))              (:effects (:memory m1) (:e_b_pos H) (:e_b_bot A) (:e_c_bot T)))
    (:search_rule (:conditions (:memory m0) (:c_b_pos H))              (:effects (:memory m1) (:e_b_bot H) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T)))

    (:load_rule   (:conditions (:memory m1) (:c_c_gt N))               (:effects (:memory m2) (:e_b_bot H) (:e_b_bot A) (:e_c_bot N) (:load (r0 N))))
    (:load_rule   (:conditions (:memory m2) (:c_c_gt T))               (:effects (:memory m3) (:e_b_bot H) (:e_c_bot N) (:e_c_bot T) (:load (r1 T))))
    (:load_rule   (:conditions (:memory m2) (:c_c_eq T))               (:effects (:memory m1) (:e_b_bot H) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T) (:load (r1 r1))))

    (:search_rule (:conditions (:memory m3) (:c_b_pos H) (:c_b_neg A)) (:effects (:memory m4) (:e_b_neg H) (:e_b_pos A)))
    (:search_rule (:conditions (:memory m4) (:c_b_neg H))              (:effects (:memory m2) (:e_b_pos H) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T)))
    (:search_rule (:conditions (:memory m4) (:c_b_neg H))              (:effects (:memory m2) (:e_b_pos H) (:e_b_bot A) (:e_c_dec N) (:e_c_bot T)))
)
