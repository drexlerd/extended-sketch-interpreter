(:module
    (:signature entry())
    (:extended_sketch
        (:memory_states (m0))
        (:initial_memory_state m0)
        (:registers ())
        (:booleans )
        (:numericals )
        (:concepts
            (lowest-misplaced-blocks "c_or(c_diff(c_some(r_primitive(on_g,0,1),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))),c_diff(c_diff(c_some(r_transitive_reflexive_closure(r_primitive(on_g,0,1)),c_top),c_some(r_transitive_closure(r_primitive(on_g,0,1)),c_top)),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))))")
        )
        (:roles (On_g "r_primitive(on_g,0,1)"))
        (:call_rule (:conditions (:memory m0) (:c_c_gt lowest-misplaced-blocks))             (:effects (:memory m0) (:call tower_rec((:concepts (lowest-misplaced-blocks)) (:roles (On_g))))))
    )
)
(:module
    (:signature tower_rec((:concepts (X)) (:roles (On_g))))
    (:extended_sketch
        (:memory_states (m0 m1 m2 m3 m4 m5 m6))
        (:initial_memory_state m0)
        (:registers (r0 r1 r2))
        (:booleans )
        (:numericals )
        (:concepts
            (W "c_some(r_inverse(r_argument(0)),c_register(0))")
            (M "c_some(r_argument(0),c_register(0))")
        )
        (:load_rule (:conditions (:memory m0) (:c_c_gt X)) (:effects (:memory m1) (:load (r0 X))))

        (:call_rule (:conditions (:memory m1) (:c_c_eq W)) (:effects (:memory m3) (:call on_table((:concepts (r0))))))

        (:call_rule (:conditions (:memory m1) (:c_c_gt W)) (:effects (:memory m3) (:e_c_bot W) (:e_c_bot M) (:call on((:concepts (r0 W))))))
        (:call_rule (:conditions (:memory m3) (:c_c_gt M)) (:effects (:memory m4) (:call tower_rec((:concepts (M)) (:roles (On_g))))))
    )
)
(:module
    (:signature on_table((:concepts (B1))))
    (:extended_sketch
        (:memory_states (m0 m1))
        (:initial_memory_state m0)
        (:registers (r0 r1))
        (:booleans
            (OnTable "b_empty(c_and(c_primitive(on-table,0),c_argument(0)))")
        )
        (:numericals )
        (:concepts
            (D "c_some(r_transitive_closure(r_primitive(on,0,1)),c_argument(0))")
        )
        (:search_rule (:conditions (:memory m0) (:c_c_gt D))   (:effects (:memory m0) (:e_c_dec D)))
        (:search_rule (:conditions (:memory m0) (:c_b_pos OnTable)) (:effects (:memory m1) (:e_b_neg OnTable)))
    )
)
(:module
    (:signature on((:concepts (B1 B2))))
    (:extended_sketch
        (:memory_states (m0 m1))
        (:initial_memory_state m0)
        (:registers (r0 r1))
        (:booleans
            (On "b_empty(c_and(c_some(r_primitive(on,0,1),c_argument(1)),c_argument(0)))")
        )
        (:numericals )
        (:concepts
            (D "c_some(r_transitive_closure(r_primitive(on,0,1)),c_or(c_argument(0), c_argument(1)))")
        )
        (:search_rule (:conditions (:memory m0) (:c_c_gt D))   (:effects (:memory m0) (:e_b_bot On) (:e_c_dec D)))
        (:search_rule (:conditions (:memory m0) (:c_c_eq D) (:c_b_pos On)) (:effects (:memory m1) (:e_b_neg On)))
    )
)

