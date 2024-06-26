(:extended_sketch
    (:memory_states (m0 m1 m2 m3 m4 m5 m6 m7 m8))
    (:initial_memory_state m0)
    (:registers (r0 r1))
    (:booleans
        (H "b_empty(c_primitive(holding, 0))")
        (Hx "b_empty(c_and(c_one_of(b1),c_primitive(holding, 0)))")
        (On "b_empty(c_and(c_some(r_primitive(on,0,1),c_one_of(b2)),c_one_of(b1)))")
        (A "b_empty(c_diff(c_register(1),c_some(r_transitive_closure(r_primitive(on,0,1)),c_or(c_one_of(b1),c_one_of(b2)))))")
    )
    (:numericals )
    (:concepts
        (N "c_diff(c_or(c_one_of(b1), c_one_of(b2)),c_primitive(clear,0))")
        (T0 "c_some(r_primitive(on,0,1),c_register(0))")
        (T1 "c_some(r_primitive(on,0,1),c_register(1))")
        (R0 "c_register(0)")
    )
    (:search_rule (:conditions (:memory m0) (:c_b_neg H))                (:effects (:memory m4) (:e_b_bot H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T0) (:e_c_bot T1)))

    (:search_rule (:conditions (:memory m0) (:c_b_pos H) (:c_c_eq N))    (:effects (:memory m7) (:e_b_bot H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T0) (:e_c_bot T1)))

    (:load_rule   (:conditions (:memory m0) (:c_b_pos H) (:c_c_gt N))    (:effects (:memory m1) (:e_b_bot H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T1) (:load (r0 N))))
    (:load_rule   (:conditions (:memory m1) (:c_c_gt R0))                (:effects (:memory m2) (:e_b_bot H) (:e_b_bot Hx) (:e_b_bot On) (:e_c_bot N) (:e_c_bot T0) (:load (r1 r0))))
    (:load_rule   (:conditions (:memory m2) (:c_c_gt T1))                (:effects (:memory m2) (:e_b_bot H) (:e_b_bot Hx) (:e_b_bot On) (:e_c_bot N) (:e_c_bot T0) (:load (r1 T1))))
    (:search_rule (:conditions (:memory m2) (:c_c_eq T1))                (:effects (:memory m5) (:e_b_bot H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T0) (:e_c_bot T1)))

    (:search_rule (:conditions (:memory m3) (:c_c_gt T0))                (:effects (:memory m1) (:e_b_bot H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T0) (:e_c_bot T1)))
    (:search_rule (:conditions (:memory m3) (:c_c_eq T0))                (:effects (:memory m0) (:e_b_bot H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T0) (:e_c_bot T1)))

    (:search_rule (:conditions (:memory m4) (:c_b_neg H))                (:effects (:memory m0) (:e_b_pos H) (:e_b_pos Hx)))

    (:search_rule (:conditions (:memory m5) (:c_b_pos H) (:c_b_pos A))   (:effects (:memory m6) (:e_b_neg H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_neg A) (:e_c_bot T1)))
    (:search_rule (:conditions (:memory m6) (:c_b_neg H) (:c_b_neg A))   (:effects (:memory m3) (:e_b_pos H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T0) (:e_c_bot T1)))
    (:search_rule (:conditions (:memory m6) (:c_b_pos H) (:c_b_neg A))   (:effects (:memory m3) (:e_b_pos H) (:e_b_bot Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_dec N) (:e_c_bot T0) (:e_c_bot T1)))

    (:search_rule (:conditions (:memory m7) (:c_b_pos Hx))               (:effects (:memory m8) (:e_b_neg H) (:e_b_neg Hx) (:e_b_bot On) (:e_b_bot A) (:e_c_bot T0) (:e_c_bot T1)))
    (:search_rule (:conditions (:memory m8) (:c_b_neg Hx) (:c_b_pos On)) (:effects (:memory m8) (:e_b_pos H) (:e_b_pos Hx) (:e_b_neg On) (:e_b_bot A) (:e_c_bot N) (:e_c_bot T0) (:e_c_bot T1)))
)
