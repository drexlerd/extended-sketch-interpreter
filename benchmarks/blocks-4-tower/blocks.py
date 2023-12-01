#!/usr/bin/env python3

from dlplan.core import VocabularyInfo, InstanceInfo, State, SyntacticElementFactory


def main():
    vocabulary = VocabularyInfo()
    on = vocabulary.add_predicate("on", 2)
    on_g = vocabulary.add_predicate("on_g", 2)
    on_table = vocabulary.add_predicate("on-table", 1)

    instance = InstanceInfo(0, vocabulary)
    b0 = instance.add_object("b0")
    b1 = instance.add_object("b1")
    b2 = instance.add_object("b2")
    on_b0_b1 = instance.add_atom(on, [b0,b1])
    on_b1_b0 = instance.add_atom(on, [b1,b0])
    on_b0_b2 = instance.add_atom(on, [b0,b2])
    on_b2_b0 = instance.add_atom(on, [b2,b0])
    on_b1_b2 = instance.add_atom(on, [b1,b2])
    on_b2_b1 = instance.add_atom(on, [b2,b1])
    on_table_b0 = instance.add_atom(on_table, [b0])
    on_table_b1 = instance.add_atom(on_table, [b1])
    on_table_b2 = instance.add_atom(on_table, [b2])

    on_g_b0_b1 = instance.add_static_atom(on_g, [b0,b1])
    on_g_b1_b2 = instance.add_static_atom(on_g, [b1,b2])

    s0 = State(0, instance, [on_b1_b2, on_table_b2, on_table_b0])  # T | G G B

    s1 = State(1, instance, [on_b2_b1, on_b1_b0, on_table_b0])  # T | B B B    reverse stacked

    s2 = State(2, instance, [on_b0_b1, on_b1_b2, on_table_b0])  # G G G

    states = {
        "s0": s0,
        "s1": s1,
        "s2": s2
    }

    element_factory = SyntacticElementFactory(vocabulary)

    concepts = {
        "well-placed-blocks": element_factory.parse_concept("c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))"),
        "bottom-most-blocks": element_factory.parse_concept("c_diff(c_some(r_transitive_reflexive_closure(r_primitive(on_g,0,1)),c_top),c_some(r_transitive_closure(r_primitive(on_g,0,1)),c_top))"),
        "bottom-most-misplaced-blocks": element_factory.parse_concept("c_diff(c_diff(c_some(r_transitive_reflexive_closure(r_primitive(on_g,0,1)),c_top),c_some(r_transitive_closure(r_primitive(on_g,0,1)),c_top)),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1))))"),
        "lowest-misplaced-blocks": element_factory.parse_concept("c_or(c_diff(c_some(r_primitive(on_g,0,1),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))),c_diff(c_diff(c_some(r_transitive_reflexive_closure(r_primitive(on_g,0,1)),c_top),c_some(r_transitive_closure(r_primitive(on_g,0,1)),c_top)),c_all(r_transitive_reflexive_closure(r_primitive(on,0,1)),c_equal(r_primitive(on_g,0,1),r_primitive(on,0,1)))))")
    }
    roles = {}
    boolean = {}
    numericals = {}

    for concept_key, concept in concepts.items():
        print(concept_key, end=" ")
        for state_key, state in states.items():
            print(state_key, str(concept.evaluate(state)), end=" ")
        print()



if __name__ == "__main__":
    main()