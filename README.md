# Библиотека для длинной арифметики

### Версия 0.2
* Реализована функция абсолютного значения числа `big_integer.abs()`
* Реализована операция сложения, совмещённое с присваиванием `+=` для любых пар чисел
* Реализована операция вычитания, совмещённое с присваиванием `-=` для любых пар чисел
* Реализована операция умножения, совмещённое с присваиванием `*=` для любых пар чисел
* Реализована операция сложения `+`
* Реализована операция вычитания `-`
* Реализована операция умножения `*`
* Реализованы унарные операции `+big_integer, -big_integer, ~big_integer, ++big_integer, --big_integer, big_integer++, big_integer--`

### Версия 0.1
* Реализованы конструкторы:
  * Дефолтный конструктор (безнаковый 0)
  * Конструктор из другого числа представленного длинной арифметикой
  * Конструктор из типа `int`
  * Конструктор из типа `string`
* Реализованы операция сравнения `<, >, <=, >=, ==, !=`
* Реализована операция присваивания `=`
* Реализована операция сложения, совмещённое с присваиванием `+=` для чисел с одинаковым знаком
* Реализована функция `to_string` - перевод числа в строку

__________

# Library for Arbitrary-precision arithmetic

### Version 0.2
* Implemented the function the absolute value of the number `big_integer.abs()`
* Implemented the addition operation, combined with the assignment of `+=` for any pairs of numbers
* Implemented a subtraction operation combined with the assignment of `-=` for any pairs of numbers
* Implemented a multiplication operation, combined with the assignment of `*=` for any pairs of numbers
* Implemented the addition operation `+`
* Implemented the subtraction operation `-`
* Implemented multiplication operation `*`
* Implemented unary operations  `+big_integer, -big_integer, ~big_integer, ++big_integer, --big_integer, big_integer++, big_integer--`

### Version 0.1
* Constructors are implemented:
  * Default constructor (unsigned 0)
  * Constructor from another number represented by arbitrary-precision arithmetic
  * Constructor from type `int`
  * Constructor from type `string`
* Implemented a comparison operation `<, >, <=, >=, ==, !=`
* Implemented the assignment operation `=`
* Implemented the addition operation, combined with the assignment of  `+=` for numbers with the same sign
* Implemented the `to_string` function - converting a number to a string
