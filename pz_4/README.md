# ASPZ

Завдання 4.1
Скільки пам’яті може виділити malloc(3) за один виклик?
Параметр malloc(3) є цілим числом типу даних size_t, тому логічно максимальне число, яке можна передати як параметр malloc(3), — це максимальне значення size_t на платформі (sizeof(size_t)). У 64-бітній Linux size_t становить 8 байтів, тобто 8 * 8 = 64 біти. Відповідно, максимальний обсяг пам’яті, який може бути виділений за один виклик malloc(3), дорівнює 2^64. Спробуйте запустити код на x86_64 та x86. Чому теоретично максимальний обсяг складає 8 ексабайт, а не 16?

![image](https://github.com/user-attachments/assets/95f6736d-e407-4874-8e12-d2aca43fddda)
Теоретично malloc може прийняти SIZE_MAX (16 EiB), але на практиці:

Обмеження ОС/апаратури роблять це неможливим.

Реальний максимум залежить від доступної фізичної + віртуальної пам’яті


Завдання 4.2
Що станеться, якщо передати malloc(3) від’ємний аргумент? Напишіть тестовий випадок, який обчислює кількість виділених байтів за формулою num = xa * xb. Що буде, якщо num оголошене як цілочисельна змінна зі знаком, а результат множення призведе до переповнення? Як себе поведе malloc(3)? Запустіть програму на x86_64 і x86.
![image](https://github.com/user-attachments/assets/a3038822-45be-4969-9bdb-84edb9371b31)
Якщо num (результат множення xa * xb) перевищує INT_MAX, виникає невизначена поведінка (UB) через переповнення знакового int. На практиці це призводить до отримання негативного значення.
Небезпечний аргумент для malloc:
При передачі негативного значення num у malloc, воно неявно перетворюється на велике додатнє число типу size_t (через приведення беззнакового типу), що може спричинити спробу виділення неможливо великого блоку пам’яті.
Поведінка malloc:
У більшості випадків malloc поверне NULL (помилка), оскільки ОС відхиляє надмірні запити. Однак якщо переповнення призведе до малого додатнього size_t, malloc може виділити пам’ять, що створить вразливість.




Завдання 4.3
Що станеться, якщо використати malloc(0)? Напишіть тестовий випадок, у якому malloc(3) повертає NULL або вказівник, що не є NULL, і який можна передати у free(). Відкомпілюйте та запустіть через ltrace. Поясніть поведінку програми.

![image](https://github.com/user-attachments/assets/ba25f6d8-1b74-45e3-97bc-8ea2627c6721)
Специфікація стандарту C:
Виклик malloc(0) є implementation-defined (залежить від реалізації). Він може повернути або NULL, або не-NULL вказівник, який, проте, не можна використовувати для доступу до пам’яті (оскільки виділено 0 байт). Обидва варіанти є коректними згідно зі стандартом.

Поведінка у практиці:
У більшості сучасних систем (Linux/Windows) malloc(0) повертає не-NULL вказівник на "мінімальний" блок пам’яті (наприклад, 16 байт для аліасингу або відлагодження).
Цей вказівник можна (і потрібно!) передавати у free() — ігнорування цього призведе до витоку пам’яті.
При спробі запиу/читання через такий вказівник виникає невизначена поведінка (UB).




Завдання 4.4
Чи є помилки у такому коді?
void *ptr = NULL;
while (<some-condition-is-true>) {
    if (!ptr)
        ptr = malloc(n);
    [... <використання 'ptr'> ...]
    free(ptr);
}

Напишіть тестовий випадок, який продемонструє проблему та правильний варіант коду.
![image](https://github.com/user-attachments/assets/ef5670f9-9ec6-4248-b820-d8bb93e2b3de)

Проблема у "buggy_version":
Код звільняє пам'ять (free(ptr)) на кожній ітерації циклу, але продовжує використовувати вже звільнений вказівник
Це призводить до використання після звільнення (use-after-free) - серйозної вразливості безпеки
Пам'ять може бути перевикористана іншими частинами програми
Коректний варіант ("correct_version"):
Пам'ять виділяється один раз перед циклом
Використовується перед звільненням
Звільнення відбувається після завершення роботи з вказівником
Додано перевірку на помилку виділення пам'яті



Завдання 4.5
Що станеться, якщо realloc(3) не зможе виділити пам’ять? Напишіть тестовий випадок, що демонструє цей сценарій.
![image](https://github.com/user-attachments/assets/06d9a532-c0ee-4ac3-a89d-af322be68673)
Поведінка realloc() при помилці:
Якщо realloc() не може виділити новий блок пам'яті, він повертає NULL
Оригінальний казівник залишається валідним і його можна продовжувати використовувати
Дані в оригінальному блоці не втрачаються
Демонстрація у тестових випадках:
test_realloc_fail(): Спроба виділити неправдоподібно великий блок (1TB)
test_fragmentation(): Симуляція фрагментації пам'яті через багато дрібних виділень
Ключові особливості:
Після невдалого realloc() оригінальні дані доступні для читання/запису
Потрібно явно звільняти оригінальний вказівник, якщо він більше не потрібен
При фрагментації пам'яті realloc() може не знайти суцільного блоку, навіть якщо загалом пам'яті достатньо





Завдання 4.6
Якщо realloc(3) викликати з NULL або розміром 0, що станеться? Напишіть тестовий випадок.

![image](https://github.com/user-attachments/assets/dbee0044-9f9d-4639-9057-d313daf86d32)
realloc(NULL, size)
Еквівалентний malloc(size) - створює новий блок пам'яті заданого розміру
realloc(ptr, 0)
Еквівалентний free(ptr) + повернення NULL
Оригінальний вказівник звільняється, але:
Стандарт C не гарантує, що ptr стане NULL (на відміну від явного free)
Повертається NULL (не ноий вказівник)
Небезпека: Якщо результат не присвоїти, виникає витік пам'яті!



Завдання 4.7
Перепишіть наступний код, використовуючи reallocarray(3):
struct sbar *ptr, *newptr;
ptr = calloc(1000, sizeof(struct sbar));
newptr = realloc(ptr, 500*sizeof(struct sbar));

Порівняйте результати виконання з використанням ltrace.
![image](https://github.com/user-attachments/assets/85c642b5-6c97-4b45-ae4d-ad6adfe56851)

Ключові відмінності між realloc та reallocarray
reallocarray спеціально розроблений для запобігання переповнення множення (integer overflow) при обчисленні розміру блоку пам'яті

Формальна перевірка: reallocarray(ptr, nmemb, size) еквівалентний realloc(ptr, nmemb * size), але з автоматичною перевіркою на переповнення

Безпека: reallocarray поверне NULL і встановить errno = ENOMEM, якщо nmemb * size перевищує SIZE_MAX


Напишіть кастомний memory allocator на базі freelist.

![image](https://github.com/user-attachments/assets/7ad141a4-450e-41e9-93b1-a93af7fce02f)


Виділння пам'яті (my_malloc):
Пошу вільного блоку достатнього розміру
Розділення блоку при необхідності
Позначення блоку як зайнятого
Звільнення пам'яті (my_free):
Позначення блоку як вільного
Об'єднання сусідніх вільних блоків
Розділення блоків: split_block() дозволяє ефективніше використовувати пам'ять
Об'єднання блоків: merge_blocks() запобігає фрагментації











Напишіть кастомний memory allocator на базі freelist.

![image](https://github.com/user-attachments/assets/79808a0d-835e-4551-95ce-67d812ac49f4)

