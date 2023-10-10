(:extended_sketch
(:name gripper)
(:memory_states (m0 m1 m2))
(:initial_memory_state m0)
(:registers (r0 r1 r2))
(:booleans (b1 "b_empty(r_primitive(carry, 0, 1))") (b2 "b_empty(r_primitive(carry, 0, 1))"))
(:numericals (n1 "n_count(r_primitive(carry, 0, 1))"))
(:concepts (c1 "c_primitive(carry, 0)"))
(:iwsearch_rules
    (:rule (:memory_condition ) (:memory_effect ) (:feature_conditions ) (:feature_effects ))
)
(:action_rules
    (:rule (:memory_condition ) (:memory_effect ) (:feature_conditions ) (:action_name ) (:registers ))
)
(:call_rules
    (:rule (:memory_condition ) (:memory_effect ) (:feature_conditions ) (:extended_sketch_name ) (:registers ))
)
(:load_rules
    (:rule (:memory_condition ) (:memory_effect ) (:feature_conditions ) (:register ) (:concept ))
)
)