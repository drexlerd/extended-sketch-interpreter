(:module
    (:signature entry())
    (:extended_sketch
        (:memory_states (m0 m1 m2 m3 m4))
        (:initial_memory_state m0)
        (:registers (r0 r1))
        (:booleans )
        (:numericals )
        (:concepts
            (lowest-misplaced-blocks "c_or(c_diff(c_some(r_primitive(on_g,0,1),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))),c_diff(c_diff(c_some(r_transitive_reflexive_closure(r_primitive(on_g,0,1)),c_top),c_some(r_transitive_closure(r_primitive(on_g,0,1)),c_top)),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))))")
        )
        (:roles (On_g "r_primitive(on_g,0,1)"))
        (:call_rule (:conditions (:memory m0))             (:effects (:memory m3) (:call tower-rec((:concepts (Lowest-misplaced-block)) (:roles (On_g))))))
    )
)
(:module
    (:signature tower-rec((:concepts (X)) (:roles (On_g))))
    (:extended_sketch
        (:memory_states (m0 m1 m2 m3 m4))
        (:initial_memory_state m0)
        (:registers (r0 r1))
        (:booleans )
        (:numericals )
        (:concepts
            (W "c_diff(c_some(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_argument(0)),c_some(r_transitive_closure(r_primitive(on,0,1)),c_argument(0)))")
            (M "c_some(r_argument(0),c_register(0))")
            (R1 "c_register(1)")
        )
        (:load_rule (:conditions (:memory m0) (:c_c_gt W)) (:effects (:memory m1) (:load (r0 W))))
        (:load_rule (:conditions (:memory m1) (:c_c_gt M)) (:effects (:memory m2) (:load (r1 M))))
        (:call_rule (:conditions (:memory m2))             (:effects (:memory m3) (:call on((:concepts (r1 r0))))))
        (:load_rule (:conditions (:memory m3))             (:effects (:memory m1) (:load (r0 R1))))
    )
)
(:module
    (:signature on((:concepts (B1 B2))))
    (:extended_sketch
        (:memory_states (m0 m1))
        (:initial_memory_state m0)
        (:registers (r0 r1))
        (:booleans
            (H "b_empty(c_primitive(holding,0))")
            (On "b_empty(c_and(c_some(r_primitive(on,0,1),c_argument(1)),c_argument(0)))")
        )
        (:numericals )
        (:concepts
            (C "c_diff(c_or(c_argument(0), c_argument(1)), c_primitive(clear, 0))")
            (D "c_some(r_transitive_closure(r_primitive(on,0,1)),c_or(c_argument(0), c_argument(1)))")
        )
        (:search_rule (:conditions (:memory m0) (:c_c_gt D))   (:effects (:memory m0) (:e_c_dec D) (:e_b_pos H)))
        (:search_rule (:conditions (:memory m0) (:c_b_pos On)) (:effects (:memory m1) (:e_b_neg On)))
    )
)
