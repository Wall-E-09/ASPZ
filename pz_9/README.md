# ASPZ
Завдання 9.1
 Напишіть програму, яка читає файл /etc/passwd за допомогою команди getent passwd, щоб дізнатись, які облікові записи визначені на вашому комп’ютері.
 Програма повинна визначити, чи є серед них звичайні користувачі (ідентифікатори UID повинні бути більші за 500 або 1000, залежно від вашого дистрибутива), окрім вас.

![image](https://github.com/user-attachments/assets/60e9d925-7160-4409-9cac-57ea69beaef2)

Виводить інформацію про поточного користувача (UID та ім'я)
Аналізує файл /etc/passwd через системні виклики
Визначає звичайних користувачів (UID ≥ 1000)
Фільтрує поточного користувача зі списку
Надає структурований вивід інших облікових записів
getuid() - отримання UID поточного користувача
getpwuid() - пошук інформації за UID
setpwent()/getpwent()/endpwent() - ітерація по всіх записах passwd

Втановлено мінімальний UID 1000 (типово для звичйних користувачів у сучасних дистрибутивах)Коректна обробка помилок для системних викликівЗручне форматування виводу з підрахунком результатівЕфективне використання пам'яті (не завантажує весь файл)



Завдання 9.2
 Напишіть програму, яка виконує команду cat /etc/shadow від імені адміністратора, хоча запускається від звичайного користувача.
 (Ваша програма повинна робити необхідне, виходячи з того, що конфігурація системи дозволяє отримувати адміністративний доступ за допомогою відповідної команди.)

![image](https://github.com/user-attachments/assets/925fcfb9-40d4-4113-86be-dfd91905eb62)


Ця програма намагається виконати команду sudo cat /etc/shadow, яка виводить вміст системного файлу, що містить зашифровані паролі користувачів. Звичайні користувачі не мають доступу до цього файлу, тому команда виконується через sudo, тобто від імені адміністратора. Функція system() запускає цю команду в оболонці. Якщо команда не змогла запуститися (наприклад, через помилку у виклику системи), програма виведе повідомлення про помилку. Якщо команда була запущена, але завершилась з ненульовим кодом, тобто з помилкою, програма також про це повідомить. Щоб усе це працювало без запиту пароля, система повинна бути налаштована так, щоб користувач мав дозвіл виконувати саме цю команду через sudo без введення пароля. Це задається в системному файлі /etc/sudoers, інакше при запуску програма або запросить пароль, або завершиться з помилкою доступу.

Завдання 9.3
 Напишіть програму, яка від імені root копіює файл, який вона перед цим створила від імені звичайного користувача. Потім вона повинна помістити копію у домашній каталог звичайного користувача.
 Далі, використовуючи звичайний обліковий запис, програма намагається змінити файл і зберегти зміни. Що відбудеться?
 Після цього програма намагається видалити цей файл за допомогою команди rm. Що відбудеться?
![image](https://github.com/user-attachments/assets/2a4266da-ed97-474b-8dbb-693b3a6732ff)
Спочатку створюється тестовий файл у /tmp з правами звичайного користувачаПотім файл копіюється під правами root до домашнього каталогуВ результаті отримуємо файл, що належить root, але знаходиться у каталозі користувача
Спроба відкриття файлу для допису (режим "a"):Зазвичай завершується помилкою "Permission denied"Причина: звичайний користувач не має прав запису у root-файл
Операція remove() часто виконується успішноПричина: права на каталог (не на файл) дозволяють модифікувати його вміст
Важливо: це залежить від прав на батьківський каталог, а не сам файл
Власність файлу (root) блокує зміни звичайним користувачемПрава на каталог часто дозволяють видалення навіть "захищених" файліДемонструє різницю між правами на файл і правами на каталог
Безпека: root-файли у домашніх каталогах не захищені від видаленняРекомендація: для захисту файлів важливо контролювати права на каталогиОсобливість UNIX: видалення - це операція над каталогом, а не файлом


Завдання 9.4
 Напишіть програму, яка по черзі виконує команди whoami та id, щоб перевірити стан облікового запису користувача, від імені якого вона запущена.
 Є ймовірність, що команда id виведе список різних груп, до яких ви належите. Програма повинна це продемонструвати.
![image](https://github.com/user-attachments/assets/a840061a-b624-4615-bc7f-ed68ec35cdd5)
Виконує дві кючові системні команди для ідентифікації користувача:
whoami - виводить ім'я поточного користувача
id - відображає детальну інформацію про користувача та його групи
Команди виконуютья послідовно через системний виклик system()
Вивід відбувається у стандартний потік виведення
Програма демонструє поточні права та членство в групах
Логін поточного користувача (з whoami
UID (user ID) та GID (group ID)
Список усіх груп, до яких належить користувач
Додаткові атрибути облікового запису



Завдання 9.5
 Напишіть програму, яка створює тимчасовий файл від імені звичайного користувача. Потім від імені суперкористувача використовує команди chown і chmod, щоб змінити тип володіння та права доступу.
 Програма повинна визначити, в яких випадках вона може виконувати читання та запис файлу, використовуючи свій обліковий запис.

![image](https://github.com/user-attachments/assets/bb82aec5-20b6-4840-97c6-4894e98d89a0)

Висновки щодо програми зміни прав доступу
Створює тимчасовий файл tempile.txt з правами звичайного користувача
Змінює власника на root за допомогою sudo chown
Встановлює обмежені права (600) через sudo chmod
Тестує можливість читання та запису
Видаляє фай
Читання (cat):
Зазвичай завершується помилкою "Permission denied"
Причина: права 600 дозволяють доступ лише власнику (root)
Запис (echo >>):
Також завершується помилкою доступу
Причина: відсутні права запису для звичайного користувача
Використання sudo для операцій, що вимагають прав root
Перенаправлення помилок (2>&1) для відображення повідомлень
Автоматичне очищення (видалення тестового файлу)



Завдання 9.6
 Напишіть програму, яка виконує команду ls -l, щоб переглянути власника і права доступу до файлів у своєму домашньому каталозі, в /usr/bin та в /etc.
 Продемонструйте, як ваша програма намагається обійти різні власники та права доступу користувачів, а також здійснює спроби читання, запису та виконання цих файлів.


![image](https://github.com/user-attachments/assets/caf979b3-56cf-466f-9976-9ae1d4af9e6d)
Аналізує права доступу у трьох критичних каталогах:
Домашній каталог користувача
Системний каталог /usr/bin
Каталог конфігурацій /etc
Виконує три типи операцій для тестування прав:
Перегляд атрибутів файлів (ls -l)
Спробу створення файлу (touch)
Спробу читання файлів (cat)Використовує змінну середовища HOME для визначення домашнього каталогу
Обмежує вивід першими 5 рядками для ls і 3 рядками для cat
Перенаправляє помилки у стандартний вивід для аналізу (2>&1)
Демонструє різницю між правами у різних каталогах



Чи можна мати два різні облікові записи з однаковим UID? Які наслідки?





Так, можна створити кілька записів у /etc/passwd з однаковим UID
Це робиться через useradd -u з явним вказівкам однакового UID
Обидва користувачі отримують однакові права доступу
Файл, створений одним користувачем, може бути змінений іншим
Систеа ідентифікує користувачів за UID, а не за іменем
Процеси обох користувачів будуть мати однакові права
whoami показує різні імена, але id покаже однаковий UID
Порушення принципу унікальної ідентифікації
Складність аудиту дій користувачів
Потенційні проблеми з квотами та моніторингом



Файл, створений testuser1, успішно змінюється testuser2
Обидва користувачі показують однаковий UID (10000) у id
Системні утиліти (ls -l) відображають тільки UID (не ім'я)
