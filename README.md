# Библиотека для длинной арифметики

### Версия 0.4
* Реализована операция побитового "and", совмещённое с присваиванием `&=` для любых пар чисел
* Реализована операция побитового "or", совмещённое с присваиванием `|=` для любых пар чисел
* Реализована операция побитового "xor", совмещённое с присваиванием `^=` для любых пар чисел
* Реализована операция побитового "and" `&`
* Реализована операция побитового "or" `|`
* Реализована операция побитового "xor" `^`
	* Правило работы побитовых операций: числа переводятся в двоичное беззнаковое представление и выполняется побитовая операций. Отдельно операция выполняется для знака.
* Реализована операция сдвига вправо, совмещённое с присваиванием `>>=` для big_integer и int
* Реализована операция сдвига влево, совмещённое с присваиванием `<<=` для big_integer и int
* Реализована операция сдвига вправо `>>`
* Реализована операция сдвига влево `<<`
* Реализован оператор вывода `<<`

### Версия 0.3.1
* Исправлены ошибки в операциях

### Версия 0.3
* Реализованы операции деления и остатка от деления `/, %`
* Реализована операция деления, совмещённое с присваиванием `/=` для любых пар чисел
* Реализована операция остатка от деления, совмещённое с присваиванием `%=` для любых пар чисел

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

### Version 0.4
* Implemented a bitwise operation "and", combined with the assignment of`&=` for any pairs of numbers
* Implemented a bitwise operation "or", combined with the assignment of `|=` for any pairs of numbers
* Implemented a bitwise operation "xor", combined with the assignment of`^=` for any pairs of numbers
* Implemented a bitwise operation "and" `&`
* Implemented a bitwise operation "or" `|`
* Implemented a bitwise operation "xor" `^`
	* The rule of operation of bitwise operations: numbers are converted to binary unsigned representation and bitwise operations are performed. The operation is performed separately for the sign.
* Implemented a shift right operation, combined with the assignment of `>>=` for big_integer and int
* Implemented a shift left operation, combined with the assignment of `<<=` for big_integer and int
* Implemented a shift right operation `>>`
* Implemented a shift left operation `<<`
* Implemented a output operator `<<`

### Version 0.3.1
* Fixed bugs in operations

### Version 0.3
* Implemented the division and module operations `/, %`
* Implemented a division operation, combined with the assignment of `/=` for any pairs of numbers
* Implemented a module operation, combined with the assignment of `%=` for any pairs of numbers

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
