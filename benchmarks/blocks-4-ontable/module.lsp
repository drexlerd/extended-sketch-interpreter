(:module
    (:signature on_table_entry())
    (:extended_sketch
        (:memory_states (m0))
        (:initial_memory_state m0)
        (:registers )
        (:booleans )
        (:numericals )
        (:concepts
            (B1 "c_one_of(b1)")
        )
        (:roles )
        (:call_rule (:conditions (:memory m0)) (:effects (:memory m0) (:call on_table((:concepts (B1))))))
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
