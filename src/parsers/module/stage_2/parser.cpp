




static Signature parse(const stage_1::ast::Signature& node, const error_handler_type& error_handler, Context& context) {
    const auto name = parse(node.name, error_handler, context, symbol_table);
    ArgumentList arguments;
    for (const auto& child_node : node.arguments) {
        arguments.push_back(parse(child_node, error_handler, context, symbol_table));
    }
    return Signature(name, arguments);
}