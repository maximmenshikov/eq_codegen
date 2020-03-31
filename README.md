# Codegen

This project is a demonstration of code generation capabilities as applied to
static analyzers. It is not intended for usage outside the main project.

The main concept is a model, it defines what should be generated. The supported
models are 'enum' (deprecated), 'expression' (deprecated), 'command',
'vmir\_mapping', 'enum\_verify'.

## Bulding
Use ```cmake``` for building.

## Usage
The typical use case would be to use it on an existing model, e.g.:

```
codegen model.yml output_path
```

To verify the usage of enumerations, use this line:

```
codegen model.yml path_to_file verify
```
